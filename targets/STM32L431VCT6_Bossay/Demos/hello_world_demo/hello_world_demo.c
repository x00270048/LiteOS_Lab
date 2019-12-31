/*----------------------------------------------------------------------------
 * Copyright (c) <2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/
/**
 *  DATE                AUTHOR      INSTRUCTION
 *  2019-07-23 10:00    yuhengP    The first version  
 *
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <osal.h>


#include <boudica150_oc.h>
#include "Actuators.h"
#include "lcd.h"

#include <gpio.h>
#include <stm32l4xx_it.h>
#include "stm32l4xx_hal.h"


static int app_hello_world_entry()
{
    while (1)
    {
        printf("Hello World! This is LiteOS!\r\n");
        //IotBox_Light_StatusSet(OFF);
        //IotBox_Motor_StatusSet(ON);
        //Led_blink();
        //IotBox_Beep_StatusSet(OFF);
        
        HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
        HAL_Delay(100);
        HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);	
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)// Press KEY1
		{
				HAL_Delay(10);// delay 10ms
				if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)//��ѯ����KEY1�͵�ƽ
				{
					HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_SET);//��
				 }
		}
		if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)//��ѯ����KEY2�͵�ƽ
		{
				 HAL_Delay(10);//����
				 if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)==GPIO_PIN_RESET)//��ѯ����KEY2�͵�ƽ
				{
					HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,GPIO_PIN_RESET);//��
				}
		}
        HAL_Delay(20000);
	}
    return (1);
}

int standard_app_demo_main()
{
    
    //IotBox_Light_StatusSet(ON);
    //IotBox_Beep_StatusSet(ON);
    osal_task_create("helloworld",app_hello_world_entry,NULL,0x400,NULL,2);
    return 0;
}




