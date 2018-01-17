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


//Ҫд�뵽STM32 FLASH���ַ�������
//const u8 TEXT_Buffer[]={"Huanjiehua"};
//#define SIZE sizeof(TEXT_Buffer)		//���鳤��

//char ReadBuf[SIZE];                   //����������


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	u8 key_value;
	FsmTable_t fsm;   //����һ��״̬��
	Event_t event_t;  //�����¼�����
	
	delay_init(48);
	KEY_Init();
	LCD_Init();
	BK_ON();
	display_pic(black);
	Mic_Main_interface();  //������
	
	InitFsm(&fsm);  //��ʼ��״̬��
	
	while (1)
	{
		key_value = KEY_Scan();
		switch(key_value)
		{
			case 0:
				event_t = EVENT0;    //���¼�
				break;
			
			case 1:
				event_t = EVENT1;    //����+
				break;
			
			case 2:
				event_t = EVENT2;    //����-
				break;
			
			case 3:
				event_t = EVENT3;    //�ϼ�
				break;
			
			case 4:
				event_t = EVENT4;    //�¼�
				break;
			
			case 5:
				event_t = EVENT5;    //ȷ��
				break;
			
			case 6:
				event_t = EVENT6;    //�˳�
				break;
			
			case 7:
				event_t = EVENT7;
				break;
			
			default:
				break;
		}
		FSM_EventHandle(&fsm,key_value);   //״̬���ַ��¼�
		
		delay_ms(80);
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
	  BK_OFF();  //��������д����ص�LCD����
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
