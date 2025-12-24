#ifndef ATU10_BB_UART_H
#define ATU10_BB_UART_H

#include <stdint.h>
#include <stdbool.h>

#ifdef EXT_BITBANG_UART_TEST
void bb_uart_tx_isr_tick(void);
void bb_uart_tx_init(void);
bool bb_uart_tx_has_space(void);
bool bb_uart_tx_enqueue(uint8_t c);
void bb_uart_tx_puts_blocking(const char *s);
#endif

#endif // ATU10_BB_UART_H
