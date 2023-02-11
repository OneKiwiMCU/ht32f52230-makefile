#include "drv_i2c.h"

#define DRV_I2C                  (HT_I2C0)

#define I2C_SCL_GPIO_ID      (GPIO_PB)
#define I2C_SCL_AFIO_PIN     (AFIO_PIN_7)
#define I2C_SCL_AFIO_MODE    (AFIO_FUN_I2C)

#define I2C_SDA_GPIO_ID      (GPIO_PB)
#define I2C_SDA_AFIO_PIN     (AFIO_PIN_8)
#define I2C_SDA_AFIO_MODE    (AFIO_FUN_I2C)

#define I2C_SPEED         (400000)


void i2c_ack_polling(u8 i2c_addr)
{
    u32 reg;

    /* wait if bus busy                                                                                       */
    while (I2C_GetFlagStatus(DRV_I2C, I2C_FLAG_BUSBUSY));

    while (1)
    {
        /* send slave address                                                                                   */
        I2C_TargetAddressConfig(DRV_I2C, i2c_addr, I2C_MASTER_WRITE);

        /* check status                                                                                         */
        while (1)
        {
            reg = DRV_I2C->SR;

            if (reg & I2C_FLAG_ADRS)
            {
                return;
            }

            if (reg & I2C_FLAG_RXNACK)
            {
                I2C_ClearFlag(DRV_I2C, I2C_FLAG_RXNACK);
                break;
            }
        }
    }
}

void i2c_init(void)
{
    /* !!! NOTICE !!!
        Notice that the local variable (structure) did not have an initial value.
        Please confirm that there are no missing members in the parameter settings below in this function.
    */
    I2C_InitTypeDef I2C_InitStructure;

    /* Enable AFIO & I2C clock                                                                                */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.I2C0 = 1; 
    CKCUClock.Bit.AFIO = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Configure I2C SCL pin, I2C SDA pin                                                                     */
    AFIO_GPxConfig(I2C_SCL_GPIO_ID, I2C_SCL_AFIO_PIN, I2C_SCL_AFIO_MODE);
    AFIO_GPxConfig(I2C_SDA_GPIO_ID, I2C_SDA_AFIO_PIN, I2C_SDA_AFIO_MODE);

    /* I2C configuration                                                                                      */
    I2C_InitStructure.I2C_GeneralCall = I2C_GENERALCALL_DISABLE;
    I2C_InitStructure.I2C_AddressingMode = I2C_ADDRESSING_7BIT;
    I2C_InitStructure.I2C_Acknowledge = I2C_ACK_DISABLE;
    I2C_InitStructure.I2C_OwnAddress = 0x00;
    I2C_InitStructure.I2C_Speed = I2C_SPEED;
    I2C_InitStructure.I2C_SpeedOffset = 0;
    I2C_Init(DRV_I2C, &I2C_InitStructure);

    I2C_Cmd(DRV_I2C, ENABLE);
}

void i2c_write_registers(u8 i2c_addr, u8 reg_addr, u8 *buffer, u8 size)
{

    /* acknowledge polling                                                                                    */
    i2c_ack_polling(i2c_addr);

    /* set EEPROM address                                                                                     */
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
    I2C_SendData(DRV_I2C, reg_addr);

    /* page write                                                                                             */
    while (size--)
    {
        while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
        I2C_SendData(DRV_I2C, *buffer);
        buffer++;
    }

    /* end of write                                                                                           */
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
    I2C_GenerateSTOP(DRV_I2C);
}

void i2c_read_registers(u8 i2c_addr, u8 reg_addr, u8 *buffer, u8 size)
{
    /* check parameters                                                                                       */
    Assert_Param(size > 0);

    /* acknowledge polling                                                                                    */
    i2c_ack_polling(i2c_addr);

    /* set EEPROM address                                                                                     */
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
    I2C_SendData(DRV_I2C, reg_addr);

    /* send read command                                                                                      */
    I2C_TargetAddressConfig(DRV_I2C, i2c_addr, I2C_MASTER_READ);
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_SEND_START));
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_RECEIVER_MODE));

    /* enable master receiver ACK                                                                             */
    if (size > 1)
    {
        I2C_AckCmd(DRV_I2C, ENABLE);
    }

    /* sequential read                                                                                        */
    while (size)
    {
        while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_RX_NOT_EMPTY));
        *buffer = I2C_ReceiveData(DRV_I2C);

        buffer++;
        size--;

        if (size == 1)
        {
            I2C_AckCmd(DRV_I2C, DISABLE);
        }
    }

    /* end of read                                                                                            */
    I2C_GenerateSTOP(DRV_I2C);
}

void i2c_write_register(u8 i2c_addr, u8 reg_addr, u8 buffer)
{

    /* acknowledge polling                                                                                    */
    i2c_ack_polling(i2c_addr);

    /* set EEPROM address                                                                                     */
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
    I2C_SendData(DRV_I2C, reg_addr);

    /* page write                                                                                             */
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
    I2C_SendData(DRV_I2C, buffer);

    /* end of write                                                                                           */
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
    I2C_GenerateSTOP(DRV_I2C);
}

void i2c_read_register(u8 i2c_addr, u8 reg_addr, u8 *buffer)
{
    /* check parameters                                                                                       */
    Assert_Param(size > 0);

    /* acknowledge polling                                                                                    */
    i2c_ack_polling(i2c_addr);

    /* set EEPROM address                                                                                     */
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_TX_EMPTY));
    I2C_SendData(DRV_I2C, reg_addr);

    /* send read command                                                                                      */
    I2C_TargetAddressConfig(DRV_I2C, i2c_addr, I2C_MASTER_READ);
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_SEND_START));
    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_RECEIVER_MODE));

    while (!I2C_CheckStatus(DRV_I2C, I2C_MASTER_RX_NOT_EMPTY));
    *buffer = I2C_ReceiveData(DRV_I2C);
    I2C_AckCmd(DRV_I2C, DISABLE);

    /* end of read                                                                                            */
    I2C_GenerateSTOP(DRV_I2C);
}