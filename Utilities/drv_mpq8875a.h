#ifndef __DRV_MPQ8875A_H
#define __DRV_MPQ8875A_H

#include "ht32f5xxxx_01.h"

#define MPQ8875A_ADDR 0x01

#define REGISTER_0x00 0x00
#define REGISTER_0x01 0x01
#define REGISTER_0x02 0x02
#define REGISTER_0x03 0x03
#define REGISTER_0x04 0x04
#define REGISTER_0x05 0x05
#define REGISTER_0x06 0x06
#define REGISTER_0x07 0x07
#define REGISTER_0x08 0x08
#define REGISTER_0x09 0x09
#define REGISTER_0x0A 0x0a
#define REGISTER_0x0B 0x0b
#define REGISTER_0x0C 0x0c
#define REGISTER_0x0D 0x0d
#define REGISTER_0x0E 0x0e
#define REGISTER_0x0F 0x0f
#define REGISTER_0x10 0x10


typedef enum{
	Recoverable_Mode,
	LatchOff_Mode
} Over_Voltage_Protection_t;

void mpq8875a_read_all_register(void);
uint8_t mpq8875a_read_reference_voltage(void);
void mpq8875a_write_reference_voltage(uint8_t data);
uint8_t mpq8875a_read_vout_divider_ratio(void);
void mpq8875a_write_vout_divider_ratio(uint8_t data);

#endif /* __DRV_MPQ8875A_H */
