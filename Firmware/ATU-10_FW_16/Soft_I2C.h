#ifndef ATU10_SOFT_I2C_H
#define ATU10_SOFT_I2C_H


void Soft_I2C_Init(void);
void Soft_I2C_Start(void);
char Soft_I2C_Write(char);
char Soft_I2C_Read(void);
void Soft_I2C_ACK(void);
void Soft_I2C_NACK(void);
void Soft_I2C_Stop(void);
//

#endif // ATU10_SOFT_I2C_H
