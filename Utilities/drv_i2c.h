#ifndef __DRV_I2C_H
#define __DRV_I2C_H

#include "ht32f5xxxx_01.h"

void i2c_init(void);
void i2c_write_registers(u8 i2c_addr, u8 reg_addr, u8 *buffer, u8 size);
void i2c_read_registers(u8 i2c_addr, u8 reg_addr, u8 *buffer, u8 size);
void i2c_write_register(u8 i2c_addr, u8 reg_addr, u8 buffer);
void i2c_read_register(u8 i2c_addr, u8 reg_addr, u8 *buffer);


#endif /* __DRV_I2C_H */
