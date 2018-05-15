/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/****************************************************************
注意：本次用到PF0和PF1引脚，所以修改了SetSysClock里面的代码
*****************************************************************/
void Open(void);
void Close(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int main(void)
{
	u16 count = 0;
	u8 state = 0;
	u8 state_last=0;
	delay_init(8);
	LCD_GPIO_Init(); //LCD引脚初始化
	GPIO_SetBits(GPIOB,GPIO_Pin_1);  //背光开
//	POWER_CTR = 1;
//	WR = 1;
//	RS = 1;
//	LCD_Init();
//	display_test_8();
//	KEY_Init();      //按键引脚初始化


//	Open();  //开机

	//SPI
	LCD_Init();
	LCD_Init();
	display_test();

	
	ST7789_Init_24(); //24引脚的LCD初始化
	ST7789_Init_24(); //24引脚的LCD初始化
	display_test_8();
	display_test_8();
//	Close();  //关机
	while(1)
	{
//		if(!key6)
//		{
//			count++;
//			state = state_last;
//			state++;
//			if(state==1)
//			{
//				mode = 3;
//			}
//			else if(state==2)
//			{
//				mode = 4;
//			}
//			else if(state==3)
//			{
//				state = 1;
//			}
//			state_last = state;
//		
//		}
//		else
//		{
//			count=0;
//			state=0;
//		}
//		if(count==100)
//		{
////			Close(); //关机
//		}
//		switch(state)
//		{
//			case 1 :
////					LCD_Init();
////					display_test();
//			BK=0;
//					break;
//			case 2 :
////					LCD_Init();
////					display_test();
//			BK = 1;
//					break;
//			default:
//					break;
//		}

//		delay_ms(1000);
	}

}

//开机函数
void Open(void)
{
	u8 count=0;
	u8 kai_flag = 1;
	while(kai_flag)
	{
		if(!key6)
		{
			count++;
		}
		else
		{
			count = 0;
		}
		if(count==2)
		{
			POWER_CTR = 1; //电源开
			BK = 1;        //背光开
			kai_flag = 0;
		}
		delay_ms(1000);
	}
}

//关机函数
void Close(void)
{
	u8 count=0;
	while(1)
	{
		if(!key6)
		{
			count++;
		}
		else
		{
			count = 0;
		}
		if(count==2)
		{
			POWER_CTR = 0; //电源开
			BK = 0;        //背光开
		}
		delay_ms(1000);
	}
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
