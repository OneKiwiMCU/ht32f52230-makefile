#ifndef __DRV_BOARD_H
#define __DRV_BOARD_H

#include "ht32f5xxxx_01.h"

typedef enum
{
    BUTTON_IDLE = 0,
    BUTTON_EDGE_POS,
    BUTTON_EDGE_NEG,
    BUTTON_RUN,
    BUTTON_SETTING,
    BUTTON_INTERRUPT,
    BUTTON_STOP
}  Button_Enum;

typedef struct
{
	u8 btn1_status;
    u32 btn1_current;
    u32 relay1_time;
    u32 relay1_start;

	u8 btn2_status;
    u32 btn2_current;
    u32 relay2_time;
    u32 relay2_start;
	
    u8 btn3_status;
    u32 btn3_current;
    u32 relay3_time;
    u32 relay3_start;
	
    u32 start_time;
    u32 end_time;
} Board_Status;


#define TIME_BLINK      500 //ms
#define TIME_DEFAULT    5000 //ms
extern Board_Status cafe;

void Board_Init(void);
void Button1_Check(void);
void Button2_Check(void);
void Button3_Check(void);
void Button1_2_EXTI(void);
void Button3_EXTI(void);

#endif /* __DRV_BOARD_H */
