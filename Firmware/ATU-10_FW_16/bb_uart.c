#include "bb_uart.h"

#ifdef EXT_BITBANG_UART_TEST
#include "pic_init.h"

#define BB_UART_TX_BUF_SIZE 16u
#define BB_UART_TX_BUF_MASK (BB_UART_TX_BUF_SIZE - 1u)
#define BB_UART_TX_IDLE 0u
#define BB_UART_TX_START 1u
#define BB_UART_TX_DATA 2u
#define BB_UART_TX_STOP 3u

static volatile char data_to_send[BB_UART_TX_BUF_SIZE];
static volatile uint8_t data_to_send_head = 0;
static volatile uint8_t data_to_send_tail = 0;
static volatile uint8_t data_to_send_count = 0;
static volatile uint8_t bb_uart_tx_state = BB_UART_TX_IDLE;
static volatile uint8_t bb_uart_tx_bit = 0;
static volatile uint8_t bb_uart_tx_shift = 0;
static volatile uint8_t bb_uart_subtick = 0;
static volatile uint8_t bb_uart_tx_ready = 0;

static void bb_uart_set_levels(uint8_t rd1_level){
   LATDbits.LATD1 = rd1_level ? 1 : 0;
}

static uint8_t bb_uart_irq_save(void){
   uint8_t gie = INTCONbits.GIE;
   INTCONbits.GIE = 0;
   return gie;
}

static void bb_uart_irq_restore(uint8_t gie){
   INTCONbits.GIE = gie;
}

bool bb_uart_tx_has_space(void){
   uint8_t gie = bb_uart_irq_save();
   bool has_space = (data_to_send_count < BB_UART_TX_BUF_SIZE);
   bb_uart_irq_restore(gie);
   return has_space;
}

bool bb_uart_tx_enqueue(uint8_t c){
   uint8_t gie = bb_uart_irq_save();
   if(data_to_send_count >= BB_UART_TX_BUF_SIZE){
      bb_uart_irq_restore(gie);
      return false;
   }
   data_to_send[data_to_send_head] = c;
   data_to_send_head = (uint8_t)((data_to_send_head + 1u) & BB_UART_TX_BUF_MASK);
   data_to_send_count++;
   bb_uart_irq_restore(gie);
   return true;
}

static void bb_uart_tx_fsm_step(void){
   switch(bb_uart_tx_state){
      case BB_UART_TX_IDLE:
         if(data_to_send_count == 0u){
            bb_uart_set_levels(1u);
            break;
         }
         bb_uart_tx_shift = data_to_send[data_to_send_tail];
         bb_uart_tx_bit = 0u;
         bb_uart_tx_state = BB_UART_TX_START;
         bb_uart_set_levels(0u);
         break;
      case BB_UART_TX_START:
         bb_uart_set_levels((uint8_t)(bb_uart_tx_shift & 0x01u));
         bb_uart_tx_shift >>= 1;
         bb_uart_tx_bit = 1u;
         bb_uart_tx_state = BB_UART_TX_DATA;
         break;
      case BB_UART_TX_DATA:
         bb_uart_set_levels((uint8_t)(bb_uart_tx_shift & 0x01u));
         bb_uart_tx_shift >>= 1;
         bb_uart_tx_bit++;
         if(bb_uart_tx_bit >= 8u){
            bb_uart_tx_state = BB_UART_TX_STOP;
         }
         break;
      case BB_UART_TX_STOP:
      default:
         bb_uart_set_levels(1u);
         data_to_send_tail = (uint8_t)((data_to_send_tail + 1u) & BB_UART_TX_BUF_MASK);
         if(data_to_send_count > 0u){
            data_to_send_count--;
         }
         bb_uart_tx_state = BB_UART_TX_IDLE;
         break;
   }
}

void bb_uart_tx_isr_tick(void){
   if(!bb_uart_tx_ready){
      return;
   }
   bb_uart_subtick++;
   if(bb_uart_subtick >= BB_UART_OVERSAMPLE){
      bb_uart_subtick = 0u;
      bb_uart_tx_fsm_step();
   }
}

void bb_uart_tx_init(void){
   uint8_t gie = bb_uart_irq_save();
   bb_uart_tx_ready = 0u;
   data_to_send_head = 0u;
   data_to_send_tail = 0u;
   data_to_send_count = 0u;
   bb_uart_tx_state = BB_UART_TX_IDLE;
   bb_uart_tx_bit = 0u;
   bb_uart_tx_shift = 0u;
   bb_uart_subtick = 0u;
   bb_uart_irq_restore(gie);
   ODCONDbits.ODCD1 = 0;
   TRISDbits.TRISD1 = 0;
   bb_uart_set_levels(1u);
   bb_uart_tx_ready = 1u;
   INTCONbits.PEIE = 1;
   PIR4bits.TMR2IF = 0;
   PIE4bits.TMR2IE = 1;
   T2CONbits.TMR2ON = 1;
}

void bb_uart_tx_puts_blocking(const char *s){
   while(*s){
      if(*s=='\n'){
         while(!bb_uart_tx_has_space()) { }
         (void)bb_uart_tx_enqueue('\r');
      }
      while(!bb_uart_tx_has_space()) { }
      (void)bb_uart_tx_enqueue((uint8_t)*s++);
   }
}
#endif
