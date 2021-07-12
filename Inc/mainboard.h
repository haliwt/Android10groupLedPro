#ifndef __MAINBOARD_H
#define __MAINBOARD_H
#include "main.h"
#include "gpio.h"


#define MAX_CMD_PARA_SIZE   8

#define BOARD_ADDR			76	// 'L'

#define STATE_PREAMBLE1	  	0	// 'M'	fixed
#define STATE_PREAMBLE2		1	// 'X'	fixed
#define STATE_ADDR			2	// 'L' this board
#define STATE_CMD			3	// 'S' led select command
#define STATE_SIZE			4	// length of command parameter
#define STATE_PARA			5	// parameter
#define STATE_CRC			6	// checksum

extern uint8_t runStep;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//void UART_ReceiveDataFunction(void);


#endif 


