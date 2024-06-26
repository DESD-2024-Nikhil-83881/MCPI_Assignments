/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"
#include "eeprom.h"
#include "uart.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	int choice;
	char str[32] = "";
	SystemInit();
	EEPROM_Init();
	I2CInit();
	UartInit(BAUD_9600);
	//EEPROM_Write(0x0020, (uint8_t*)"GOD BLESS YOU!\r\n", 16);


	do {

				UartPuts("Enter your choice : \r\n");
				UartPuts("1. To Write the string\r\n");
				UartPuts("2. To Read the string\r\n");


				UartGets(str);
				sscanf(str, "%d", &choice);



			switch(choice)
		      {

		     case 1:
		    	 UartGets(str);
		    	 EEPROM_Write(0x0020, (uint8_t*)str, 16);
		        break;

		     case 2:
		    	 EEPROM_Read(0x0020, (uint8_t*)str, 16);
		    	 UartPuts(str);
		        break;

		      }

			}while(choice!=0);
	return 0;
}


