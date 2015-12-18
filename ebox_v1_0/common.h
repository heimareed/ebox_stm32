/*
file   : common.h
author : shentq
version: V1.0
date   : 2015/7/5

Copyright 2015 shentq. All Rights Reserved.

Copyright Notice
No part of this software may be used for any commercial activities by any form or means, without the prior written consent of shentq.

Disclaimer
This specification is preliminary and is subject to change at any time without notice. shentq assumes no responsibility for any errors contained herein.
*/
#ifndef __COMMON_H
#define __COMMON_H
#ifdef __cplusplus
extern "C"{
#endif
	
#include "stm32f10x.h"                  // Device header



////////宏定义/////////////////////////////////


#define true 0x1
#define false 0x0
 
#define HIGH 0x1
#define LOW  0x0


#define LSB_FIRST 0
#define MSB_FIRST 1

#define PI 3.1415926535898


typedef enum
{ 
    AIN         = 0x0,      //模拟输入
    INPUT       = 0x04,     //数字输入浮空
    INPUT_PD    = 0x28,     //数字输入下拉
    INPUT_PU    = 0x48,     //数字输入上拉
    OUTPUT_OD   = 0x14,     //数字OD输出/开漏极输出
    OUTPUT_PP   = 0x10,     //数字推挽输出
    AF_OD       = 0x1C,     //复用功能OD/与输出寄存器断开，与相应的外设连接
    AF_PP       = 0x18      //复用功能推挽/与输出寄存器断开，与相应的外设连接
}PIN_MODE;

//以后NVIC_PriorityGroupConfig()函数不需要再被调用。更不能再以非NVIC_GROUP_CONFIG值填充调用
#define NVIC_GROUP_CONFIG NVIC_PriorityGroup_2   /*!< 2 bits for pre-emption priority
												      2 bits for subpriority */

#define interrupts() 		__enable_irq()  //允许中断
#define no_interrupts() 	__disable_irq() //关闭所有中断
	
///////全局变量、函数///////////////////////////////////////////////
extern __IO uint32_t millis_seconds;

typedef void (*callback_fun_type)(void);	 
	 
void        ebox_init(void);	
void        ADC1_init(void);
uint32_t    millis( void ) ;
void        delay_ms(uint32_t ms);  //精确延时，毫秒级
void        delay_us(uint16_t us);  //精确延时，微妙级
void        delayus(uint32_t us);   //软件模拟延时，在有中断的情况下，无法保证精度！

class GPIO
{
    public:
        GPIO(GPIO_TypeDef *port, uint16_t pin);
        void mode(PIN_MODE mode);               //引脚模式设置，参数为PIN_MODE类型的值。
        void set();                             //引脚设置为1
        void reset();                           //引脚设置为0
        void write(uint8_t val);                //引脚设置为val(val为0，输出0，不为0输出1)
        void toggle();	                        //引脚输出翻转
        void read(uint8_t *val);                //读引脚数字电平，将结果赋值给val。
        uint8_t read(void);                     //读引脚数字电平，将结果返回。

        GPIO_TypeDef* port;
        uint16_t pin;	
};

uint16_t	analog_read(GPIO *pin);	        //读取pin的模拟量，返回0~4095
uint16_t	analog_read_voltage(GPIO *pin); //读取pin的模拟电压，0~3300，单位mv

void        shift_out(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order, uint8_t val);
uint8_t		shift_in(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order);


#ifdef __cplusplus
}
#endif

#endif
