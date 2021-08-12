#include "mainled.h"
#include "usart.h"
#include "pwm.h"
#include "gpio.h"

mainled_t mainled;
static uint8_t lastOnLed = 0xff;
static uint8_t hasLedOn;
//static uint8_t level_a;
//static uint8_t level_b;


static void setLevel_PWMA(uint8_t level);
static void setLevel_PWMB(uint8_t level);


/*************************************************************************
 	*
	*Function Name: void LedOnOff(void)
	*Function : Turn On LEDAxx LED
	*Input Ref: receive UART of data
	*Output Ref:No
	*
******************************************************************************/
void LedOnOff(uint8_t ledNum,uint8_t onOff)
{
  // uint8_t temp;
   if((lastOnLed !=ledNum)||(onOff ==0)){

                //turn off all led 
              mainTurnOff_TheSecondLedB();
              mainTurnOff_TheFirstLedA();
			  mainled.led_by_a = 0;
			  mainled.led_by_b = 0;

   }
    
   if(onOff){

	   lastOnLed = ledNum;
	   hasLedOn =1;
	  
	  
	   switch(ledNum){

		   case 0://PA11---[5]---oled "white" oled {0}  //group
				mainled.led_by_a = 0;
				mainled.led_by_b = 1;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
		        HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);
                //turn on LEDA6
                //HAL_GPIO_WritePin(LEDA6_GPIO_Port, LEDA6_Pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin, GPIO_PIN_SET);
				//setLevel_PWMA(mainled.pwmDutyCycle_ch22);
				setLevel_PWMB(mainled.pwmDutyCycle_ch12);
			    
           break;

		   case 1://PB1 [0] ---oled "UV365"-{7}
			    mainled.led_by_a = 1;
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
		       
		        HAL_Delay(20);
                //turn on LEDA7
                HAL_GPIO_WritePin(LEDA8_GPIO_Port, LEDA8_Pin, GPIO_PIN_SET);
		         HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_SET);//WT.EDIT 2021.08.12
				setLevel_PWMA(mainled.pwmDutyCycle_ch22);
                
           break;

		   case 2://PB0-[3]-----oled menu "Violet" {1}
				mainled.led_by_a = 1;
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);
               
                HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin, GPIO_PIN_SET);
		        //2 .EN
				setLevel_PWMA(mainled.pwmDutyCycle_ch22);
			    //  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
           break;

		   

		   case 3://PA2-[3]-----oled menu "BLUE" {1}
				mainled.led_by_a = 1;
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
				HAL_Delay(20);
                //turn on LEDA4
                HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin, GPIO_PIN_SET);
		        HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_SET);//WT.EDIT 2021.08.12
			    //2 .EN
				setLevel_PWMA(mainled.pwmDutyCycle_ch22);
			    //  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;
                break;
				
           case 4: //PA12 -> "Cyan"
				mainled.led_by_b = 1;
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				mainTurnOff_TheSecondLedB();
		        HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);

				//turn on LEDB1
                HAL_GPIO_WritePin(LEDB2_GPIO_Port, LEDB2_Pin, GPIO_PIN_SET);
				setLevel_PWMB(mainled.pwmDutyCycle_ch12);
				// HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2); //TIM1_CH2
				break;

			case 5: //PA5 ->'Green'
			 	mainled.led_by_a = 1;
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
			    HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);
                //turn on LEDA7
                HAL_GPIO_WritePin(LEDA4_GPIO_Port, LEDA4_Pin, GPIO_PIN_SET);
				setLevel_PWMA(mainled.pwmDutyCycle_ch22);
				//HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;//2.the second turn on Enable
			    

			 break;

			 case 6://PB4--[1]----oled menu "Orange" -{4}
				mainled.led_by_b = 1;
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				mainTurnOff_TheSecondLedB();
			    HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);

				//turn on LEDB1
                HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin, GPIO_PIN_SET);
				setLevel_PWMB(mainled.pwmDutyCycle_ch12);
             break;

			 case 7: //PB8-[6]----oled menu "Red"--{6}
				mainled.led_by_b = 1;
				mainled.led_by_a = 0;
				mainTurnOff_TheFirstLedA();
				mainTurnOff_TheSecondLedB();
			    HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);

				//turn on LEDB1
                HAL_GPIO_WritePin(LEDB7_GPIO_Port, LEDB7_Pin, GPIO_PIN_SET);
				setLevel_PWMB(mainled.pwmDutyCycle_ch12);
			    
             break;

			 case 8://PC14-[7]----oled "IR730"--{5}
				mainled.led_by_b = 1;
				mainled.led_by_a = 0;
				// temp =0x0E;
				// HAL_UART_Transmit(&huart1,&temp,1,2);
				mainTurnOff_TheFirstLedA();
			    mainTurnOff_TheSecondLedB();
			    HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);
				//turn on LEDB7 =1
                HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_SET);
				setLevel_PWMB(mainled.pwmDutyCycle_ch12);
			    
            break;
			
		   //LEDB -The second group 
		    case 9://PA3[8]-----olde "IR850"-{9}
		    	mainled.led_by_a = 1;
				mainled.led_by_b = 0;
				mainTurnOff_TheSecondLedB();
				mainTurnOff_TheFirstLedA();
			    HAL_GPIO_WritePin(LEDACUT_GPIO_Port,LEDACUT_Pin,GPIO_PIN_RESET);//WT.EDIT 2021.08.12
				HAL_Delay(20);
                //turn on LEDA7
                HAL_GPIO_WritePin(LEDA2_GPIO_Port, LEDA2_Pin, GPIO_PIN_SET);
				setLevel_PWMA(mainled.pwmDutyCycle_ch22);
				
                break;
	   }
	  
   }
}
/*************************************************************************
 	*
	*Function Name:static void FanControl(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void mainFanControl(uint8_t fanval)
{
    switch(fanval){
		   
			case 0:  
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
			
			case 1:
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_RESET);
			break;
			
			case 2:
				HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
			
			default :
					HAL_GPIO_WritePin( FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
			break;
		
	  }

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheFirstLedA(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void mainTurnOff_TheFirstLedA(void)
{
     //turn off LEDA LED
	   HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_2) ; //HAL_GPIO_WritePin(LEDAPWM_GPIO_Port, LEDAPWM_Pin, GPIO_PIN_RESET);//TIM2_CH2
	   HAL_Delay(20);
	   HAL_GPIO_WritePin(LEDA1_GPIO_Port, LEDA1_Pin | LEDA2_Pin | LEDA4_Pin  , GPIO_PIN_RESET);
       HAL_GPIO_WritePin(LEDA7_GPIO_Port, LEDA7_Pin | LEDA8_Pin, GPIO_PIN_RESET);
	   mainled.pwmDutyCycle_ch22=LEVEL_DEFAULT; //WT.EDIT 2021.07.10
	   MX_TIM2_Init();//WT.EDIT 2021.07.10

}
/*************************************************************************
 	*
	*Function Name:void TurnOff_TheSecondLedB(void)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void mainTurnOff_TheSecondLedB(void)
{
		 //turn off LEDB LED
		 HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);//TIM1_CH2 --PB3//HAL_GPIO_WritePin(LEDBPWM_GPIO_Port, LEDBPWM_Pin, GPIO_PIN_RESET);
		 HAL_Delay(20);
		 HAL_GPIO_WritePin(LEDB1_GPIO_Port, LEDB1_Pin | LEDB2_Pin , GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB4_GPIO_Port, LEDB4_Pin | LEDB7_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LEDB8_GPIO_Port, LEDB8_Pin, GPIO_PIN_RESET);
	     mainled.pwmDutyCycle_ch12=LEVEL_DEFAULT; //WT.EDIT 2021.07.10

	     MX_TIM1_Init();
	 
	     
}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
//static uint8_t BCC_CHECK(void)
//{
//   uint8_t i;
//	 
//	 uint8_t tembyte =0xAA ^ aRxBuffer[2];
//	
//    for (i = 3; i <6; i++) {
//        tembyte = tembyte ^ aRxBuffer[i];
//    }
//    return tembyte;

//}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/

static void setLevel_PWMB(uint8_t levelval)
{
   // mainled.pwmDutyCycle_ch12 =levelval;
	if(mainled.pwmDutyCycle_ch12 <LEVEL_MIN) mainled.pwmDutyCycle_ch12 =LEVEL_ZERO;;
    if(mainled.pwmDutyCycle_ch12 > LEVEL_PWM_MAX)mainled.pwmDutyCycle_ch12=LEVEL_PWM_MAX;
     
	 MX_TIM1_Init();
	 HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
}
/*************************************************************************
 	*
	*Function Name:
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/

static void setLevel_PWMA(uint8_t levelval)
{
   // mainled.pwmDutyCycle_ch22 = levelval;
    if(mainled.pwmDutyCycle_ch22 <LEVEL_MIN) mainled.pwmDutyCycle_ch22=LEVEL_ZERO;;
	if(mainled.pwmDutyCycle_ch22 > LEVEL_PWM_MAX)mainled.pwmDutyCycle_ch22 = LEVEL_PWM_MAX;
	
	MX_TIM2_Init();
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2) ;  //2.the second turn on Enable

}
/*************************************************************************
 	*
	*Function Name:void changeBrightness(uint8_t dir)
	*Function : 
	*Input Ref: NO
	*Output Ref:No
	*
******************************************************************************/
void changeBrightness(uint8_t dir)
{
	if(hasLedOn)
	{
		if(mainled.led_by_a == 1){
			if(dir=='1')	// adj +
			{
				//level_a+=LEVEL_STEP;
				mainled.pwmDutyCycle_ch22 +=LEVEL_STEP;
				//if(level_a>LEVEL_PWM_MAX ) level_a=LEVEL_PWM_MAX ;
				if(mainled.pwmDutyCycle_ch22 >LEVEL_PWM_MAX)mainled.pwmDutyCycle_ch22 =LEVEL_PWM_MAX;
			}
			else	// adj -
			{
				if(mainled.pwmDutyCycle_ch22 < LEVEL_MIN)mainled.pwmDutyCycle_ch22=LEVEL_ZERO;//if(level_a<LEVEL_MIN)	level_a=LEVEL_MIN;
				else if(mainled.pwmDutyCycle_ch22< LEVEL_STEP){
					mainled.pwmDutyCycle_ch22=LEVEL_ZERO;
				}
				else 	mainled.pwmDutyCycle_ch22-=LEVEL_STEP;
			}
			setLevel_PWMA(mainled.pwmDutyCycle_ch22);
		}
		if(mainled.led_by_b == 1){
			if(dir=='1')	// adj +
			{
				mainled.pwmDutyCycle_ch12 += LEVEL_STEP;//level_b+=LEVEL_STEP;
				//if(level_b>LEVEL_PWM_MAX ) level_b=LEVEL_PWM_MAX ;
				if(mainled.pwmDutyCycle_ch12 > LEVEL_PWM_MAX)mainled.pwmDutyCycle_ch12 =LEVEL_PWM_MAX;
			}
			else	// adj -
			{
				if(mainled.pwmDutyCycle_ch12 <LEVEL_MIN)	mainled.pwmDutyCycle_ch12 =LEVEL_ZERO;
				else if(mainled.pwmDutyCycle_ch12  < LEVEL_STEP) mainled.pwmDutyCycle_ch12 =LEVEL_ZERO;
				else 	
					mainled.pwmDutyCycle_ch12 -=LEVEL_STEP;
			}
		    setLevel_PWMB(mainled.pwmDutyCycle_ch12 );
		}
	}
}


