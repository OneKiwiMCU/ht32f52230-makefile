#include "drv_mpq8875a.h"
#include "drv_i2c.h"

uint8_t get_bits(uint8_t reg, uint8_t shift, uint8_t mask)
{
	uint8_t temp = 0;
	switch(mask){
		case 1:
			temp = 0x01;
			break;
		case 2:
			temp = 0x03;
			break;
		case 3:
			temp = 0x07;
			break;
		case 4:
			temp = 0x0f;
			break;
		case 5:
			temp = 0x1f;
			break;
		case 6:
			temp = 0x3f;
			break;
		case 7:
			temp = 0x7f;
			break;
		default:
			temp = 0xff;
			break;
	}
	temp = temp << shift;
	reg = reg & temp;
	reg = reg >> shift;
	return reg;
}

uint8_t modify_reg(uint8_t reg, uint8_t data, uint8_t shift, uint8_t mask)
{
	uint8_t temp = 0;
	switch(mask){
		case 1:
			temp = 0x01;
			break;
		case 2:
			temp = 0x03;
			break;
		case 3:
			temp = 0x07;
			break;
		case 4:
			temp = 0x0f;
			break;
		case 5:
			temp = 0x1f;
			break;
		case 6:
			temp = 0x3f;
			break;
		case 7:
			temp = 0x7f;
			break;
		default:
			temp = 0xff;
			break;
	}

	temp = temp << shift;
	temp = ~temp;
	reg = reg & temp;
	data = data << shift;
	reg = reg | data;
	return reg;
}

void mpq8875a_read_all_register(void)
{
    uint8_t reg = 0;
    uint8_t buffer[17];
    printf("mpq8875a_read_all_register:\n");
    i2c_read_registers(MPQ8875A_ADDR, 0x00, buffer, sizeof(buffer));
    for(reg = 0; reg < 17; reg++)
    {
        printf("    Registers 0x%02x: 0x%02x\n", reg, buffer[reg]);
    }
}

uint8_t mpq8875a_read_reference_voltage(void)
{
    uint8_t data;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x00, &data);
    return data;
}

void mpq8875a_write_reference_voltage(uint8_t data)
{
    i2c_write_register(MPQ8875A_ADDR, REGISTER_0x00, data);
}

uint8_t mpq8875a_read_vout_divider_ratio(void)
{
    uint8_t data;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x01, &data);
    data = data & 0x07;
    return data;
}

void mpq8875a_write_vout_divider_ratio(uint8_t data)
{
    uint8_t temp;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x01, &temp);
    temp = temp & 0xf8;
    temp = temp | data;
    i2c_write_register(MPQ8875A_ADDR, REGISTER_0x01, temp);
}

/* Register 0x0D */

/**
 * return:
 * 0: Recoverable mode
 * 1: Latch-off mode
 */
uint8_t mpq8875a_read_over_voltage_protection(void)
{
    uint8_t data;
    uint8_t result;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x0D, &data);
    result = get_bits(data, 0, 1);
    return result;
}

void mpq8875a_write_over_voltage_protection(Over_Voltage_Protection_t value)
{
	uint8_t data;
	uint8_t result;
	i2c_read_register(MPQ8875A_ADDR, REGISTER_0x0D, &data);
	result = modify_reg(data, value, 0, 1);
	i2c_write_register(MPQ8875A_ADDR, REGISTER_0x0D, result);
}


/* Register 0x0E */

/* Register 0x0F */

/**
 * return:
 * 0: No THS has occurred
 * 1: THS has occurred
 */
uint8_t mpq8875a_read_thermal_shutdown_status(void)
{
    uint8_t data;
    uint8_t result;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x0F, &data);
    result = get_bits(data, 0, 1);
    return result;
}

/**
 * return:
 * 0: No VIN OV condition has occurred
 * 1: A VIN OV condition has occurred
 */
uint8_t mpq8875a_read_over_voltage_status(void)
{
    uint8_t data;
    uint8_t result;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x0F, &data);
    result = get_bits(data, 4, 1);
    return result;
}

/**
 * return:
 * 0: Power not good
 * 1: Power good
 */
uint8_t mpq8875a_read_power_good_status(void)
{
    uint8_t data;
    uint8_t result;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x0F, &data);
    result = get_bits(data, 5, 1);
    return result;
}

uint8_t mpq8875a_read_one_time_programmable(void)
{
    uint8_t data;
    uint8_t result;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x0F, &data);
    result = get_bits(data, 6, 2);
    return result;
}

/* Register 0x10 */
uint8_t mpq8875a_read_revision(void)
{
    uint8_t data;
    uint8_t result;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x10, &data);
    result = get_bits(data, 0, 3);
    return result;
}

uint8_t mpq8875a_read_manufacturer(void)
{
    uint8_t data;
    uint8_t result;
    i2c_read_register(MPQ8875A_ADDR, REGISTER_0x10, &data);
    result = get_bits(data, 3, 5);
    return result;
}
