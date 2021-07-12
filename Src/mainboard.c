#include "mainboard.h"
#include "gpio.h"
#include "mainled.h"
#include "usart.h"

uint8_t runStep;
static uint8_t inputCmd[RXBUFFERSIZE];


//static uint8_t cmd;
static uint8_t state;
static uint8_t decodeFlag;

static uint8_t cmdSize;
static uint8_t paraIndex;
static uint8_t crcCheck;
//static uint8_t level;

static void RunCmd(void);
static void UART_ReceiveDataFunction(void);

/*************************************************************************
 	*
	*Function Name: void DecodeTestCase(void)
	*Function : decode from UART receive data
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
 void DecodeTestCase(void)
 {
       if(decodeFlag){
			decodeFlag=0;
		    RunCmd();
	   }
 
}
/*************************************************************************
 	*
	*Function Name: static void RunCmd(void)
	*Function :led turn on or off
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
static void RunCmd(void)
{
	uint8_t cmdType=inputCmd[0];
	//uint8_t ret;

	switch(cmdType)
	{
	case 'S':	//	select led  hex:53
		LedOnOff(((inputCmd[1]-0x30)*10+inputCmd[2]-0x30),1);//ledCtrl(((inputCmd[1]-0x30)*10+inputCmd[2]-0x30),1);
		break;
	case 'C': // 0x43
		//turnOffAll();
		 mainTurnOff_TheSecondLedB();
         mainTurnOff_TheFirstLedA();
		break;
	case 'A':
		changeBrightness(inputCmd[1]);
	    cmdType = 'S';
		break;
	default:
		break;
	}



}
/*************************************************************************
 	*
	*Function Name: uint8_t BCC(uint8_t *sbytes,uint8_t width)
	*Function : BCC checksum code
	*Input Ref: 
	*Output Ref:No
	*
******************************************************************************/
void UART_ReceiveDataFunction(void)
{
	switch(state)
	{
	case STATE_PREAMBLE1:
		if(aRxBuffer[0]=='M' || aRxBuffer[0]=='Z') //0x4D or 0X56
			state=STATE_PREAMBLE2;
		break;
	case STATE_PREAMBLE2:
		if(aRxBuffer[0]=='X') // hex:58
		{
			state=STATE_ADDR;
		}
		else
			state=STATE_PREAMBLE1;  
		break;
	case STATE_ADDR:
		if(aRxBuffer[0]==BOARD_ADDR) //"L" -0x4C
		{
			state=STATE_CMD; 
		}
		else
			state=STATE_PREAMBLE1; 
		break;
	case STATE_CMD:
		inputCmd[0]=aRxBuffer[0]; //hex:53-->'S' hex:41 -> 'A'
		crcCheck = 0x55 ^ inputCmd[0];
		//decodeFlag=1;
		state=STATE_SIZE; //Next receive UART 1 bit new value
		break;
	case STATE_SIZE:
		cmdSize=aRxBuffer[0]-0x30;
		if(cmdSize>MAX_CMD_PARA_SIZE)	// out of range
		{
			state=STATE_PREAMBLE1;
		}
		else if(cmdSize>0)
		{
			paraIndex=1;
			crcCheck ^= aRxBuffer[0];
			state=STATE_PARA;
		}
		else	// no parameter
		{
			crcCheck ^= aRxBuffer[0];
			decodeFlag=1;
			state=STATE_PREAMBLE1;
		}
		break;
	case STATE_PARA:
		inputCmd[paraIndex]=aRxBuffer[0];
		crcCheck ^= aRxBuffer[0];
		paraIndex++;
		cmdSize--;
	//	HAL_UART_Transmit(&huart1,inputCmd,1,0);
		if(cmdSize==0)
		{
			HAL_UART_Transmit(&huart1,&inputCmd[1],1,2);
			HAL_UART_Transmit(&huart1,&inputCmd[2],1,2);
			decodeFlag=1; //receive UART data
			state=STATE_PREAMBLE1;
		}
		break;
	case STATE_CRC:
		//if((crcCheck ^ aRxBuffer[0])==0)
		{
			//decodeFlag=1;
		}
		state=STATE_PREAMBLE1;
		break;
	default:
		state=STATE_PREAMBLE1;
		decodeFlag=0;
	}
	HAL_UART_Receive_IT(&huart1,aRxBuffer,1);


}

 /********************************************************************************
	*
	*Function Name: HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*
	*
	*
********************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
   
     UART_ReceiveDataFunction();

}

