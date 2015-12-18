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



////////�궨��/////////////////////////////////


#define true 0x1
#define false 0x0
 
#define HIGH 0x1
#define LOW  0x0


#define LSB_FIRST 0
#define MSB_FIRST 1

#define PI 3.1415926535898


typedef enum
{ 
    AIN         = 0x0,      //ģ������
    INPUT       = 0x04,     //�������븡��
    INPUT_PD    = 0x28,     //������������
    INPUT_PU    = 0x48,     //������������
    OUTPUT_OD   = 0x14,     //����OD���/��©�����
    OUTPUT_PP   = 0x10,     //�����������
    AF_OD       = 0x1C,     //���ù���OD/������Ĵ����Ͽ�������Ӧ����������
    AF_PP       = 0x18      //���ù�������/������Ĵ����Ͽ�������Ӧ����������
}PIN_MODE;

//�Ժ�NVIC_PriorityGroupConfig()��������Ҫ�ٱ����á����������Է�NVIC_GROUP_CONFIGֵ������
#define NVIC_GROUP_CONFIG NVIC_PriorityGroup_2   /*!< 2 bits for pre-emption priority
												      2 bits for subpriority */

#define interrupts() 		__enable_irq()  //�����ж�
#define no_interrupts() 	__disable_irq() //�ر������ж�
	
///////ȫ�ֱ���������///////////////////////////////////////////////
extern __IO uint32_t millis_seconds;

typedef void (*callback_fun_type)(void);	 
	 
void        ebox_init(void);	
void        ADC1_init(void);
uint32_t    millis( void ) ;
void        delay_ms(uint32_t ms);  //��ȷ��ʱ�����뼶
void        delay_us(uint16_t us);  //��ȷ��ʱ��΢�
void        delayus(uint32_t us);   //���ģ����ʱ�������жϵ�����£��޷���֤���ȣ�

class GPIO
{
    public:
        GPIO(GPIO_TypeDef *port, uint16_t pin);
        void mode(PIN_MODE mode);               //����ģʽ���ã�����ΪPIN_MODE���͵�ֵ��
        void set();                             //��������Ϊ1
        void reset();                           //��������Ϊ0
        void write(uint8_t val);                //��������Ϊval(valΪ0�����0����Ϊ0���1)
        void toggle();	                        //���������ת
        void read(uint8_t *val);                //���������ֵ�ƽ���������ֵ��val��
        uint8_t read(void);                     //���������ֵ�ƽ����������ء�

        GPIO_TypeDef* port;
        uint16_t pin;	
};

uint16_t	analog_read(GPIO *pin);	        //��ȡpin��ģ����������0~4095
uint16_t	analog_read_voltage(GPIO *pin); //��ȡpin��ģ���ѹ��0~3300����λmv

void        shift_out(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order, uint8_t val);
uint8_t		shift_in(GPIO *data_pin, GPIO *clock_pin, uint8_t bit_order);


#ifdef __cplusplus
}
#endif

#endif
