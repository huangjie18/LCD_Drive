/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� mic_page2.c
  * @����       �� JieHuaHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��10��23
  * @ժҪ       �� �ڶ�ҳ�������
                   
  ******************************************************************************/
  
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "mic_page2.h"
#include "mic_page2_1.h"
#include "DISPLAY_TFT.h"
#include "lcd.h"
#include "reverb.h"
/* ��������  -----------------------------------------------------------------*/
//�����¼�
typedef void (* action_t)(u16 x,u16 y,uint16 bk);  //��ʾ�ַ����ĺ���ָ��

static u8 Equili_top = 1;       //ָʾ����Ķ��ˣ��൱�ڵڼ�������
static u8 S1orS9_refre= 0;      //��ֹSeg9��Seg1���ˢ��
static u8 Echo_top   = 1;       //ָʾ�����Ķ���
static u8 Echo_refrt = 0;       //��ֹ���ˢ��

/* ��������  -----------------------------------------------------------------*/

//ɫ������
static void Color_Conver(u8 list1, u8 list2);
static void Color_especial(u8 list3, u8 list4,action_t Common,action_t Elect);

//��������Ӻ���
static void Switch_UP_Equili_3(void);
static void Switch_UP_Equili_2(void);
static void Switch_UP_Equili_1(void);
static void Switch_Down_Equili_1(void);
static void Switch_Down_Equili_2(void);
static void Switch_Down_Equili_3(void);

//���������Ӻ���
static void Switch_Down_Echo_1(void);
static void Switch_Down_Echo_2(void);
static void Switch_Down_Echo_3(void);
static void Switch_Down_Echo_4(void);
static void Switch_Up_Echo_1(void);
static void Switch_Up_Echo_2(void);
static void Switch_Up_Echo_3(void);
static void Switch_Up_Echo_4(void);


/************************************************
�������� �� Top_Init
��    �� �� ����ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Top_Init(void)
{
	Equili_top = 1;
	Echo_top   = 1;
}
/************************************************
�������� �� Switch_UP_Equili_3
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_UP_Equili_3(void)
{
	switch(Choose_place)
	{
		case 6:
			mic_state.mic_state_2 = Seg8_flag;
			Color_especial(list_y7_start,list_y6_start,Seg9_Show,Seg8_Show);  //��ɫ��ˢ��
			break;
		
		case 5:
			mic_state.mic_state_2 = Seg7_flag;
			Color_especial(list_y6_start,list_y5_start,Seg8_Show,Seg7_Show);
			break;
		
		case 4:
			mic_state.mic_state_2 = Seg6_flag;
			Color_especial(list_y5_start,list_y4_start,Seg7_Show,Seg6_Show);
			break;
		
		case 3:
			mic_state.mic_state_2 = Seg5_flag;
			Color_especial(list_y4_start,list_y3_start,Seg6_Show,Seg5_Show);
			break;
		
		case 2:
			mic_state.mic_state_2 = Seg4_flag;
			Color_especial(list_y3_start,list_y2_start,Seg5_Show,Seg4_Show);
			break;
		
		case 1:
			mic_state.mic_state_2 = Seg3_flag;
			Color_especial(list_y2_start,list_y1_start,Seg4_Show,Seg3_Show);
			break;
		
		default:
			break;
	}
}

/************************************************
�������� �� Switch_UP_Equili_2
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_UP_Equili_2(void)
{
	if(Choose_place == 0)  //���ѡ��λ����7��������Ҫ����д����
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = Seg2_flag;
		gui_draw_arcrectangle(0,list_y1_start,64,18,3,1,gui_elect);
		Seg2_Show(0,list_y1_start,Elect_color);     //ѡ��Seg2
		Seg3_Show(0,list_y2_start,Common_color);    //д��Seg3
		Seg4_Show(0,list_y3_start,Common_color);
		Seg5_Show(0,list_y4_start,Common_color);
		Seg6_Show(0,list_y5_start,Common_color);
		Seg7_Show(0,list_y6_start,Common_color);
		Seg8_Show(0,list_y7_start,Common_color);
	}
	else
	{
		switch(Choose_place)
		{
			case 6:
				mic_state.mic_state_2 = Seg7_flag;
				Color_especial(list_y7_start,list_y6_start,Seg8_Show,Seg7_Show);
				break;
			
			case 5:
				mic_state.mic_state_2 = Seg6_flag;
				Color_especial(list_y6_start,list_y5_start,Seg7_Show,Seg6_Show);
				break;
			
			case 4:
				mic_state.mic_state_2 = Seg5_flag;
				Color_especial(list_y5_start,list_y4_start,Seg6_Show,Seg5_Show);
				break;
			
			case 3:
				mic_state.mic_state_2 = Seg4_flag;
				Color_especial(list_y4_start,list_y3_start,Seg5_Show,Seg4_Show);
				break;
			
			case 2:
				mic_state.mic_state_2 = Seg3_flag;
				Color_especial(list_y3_start,list_y2_start,Seg4_Show,Seg3_Show);
				break;
			
			case 1:
				mic_state.mic_state_2 = Seg2_flag;
				Color_especial(list_y2_start,list_y1_start,Seg3_Show,Seg2_Show);
				break;
			
			default:
				break;
		}
	}
}

/************************************************
�������� �� Switch_UP_Equili_1
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_UP_Equili_1(void)
{
	if((Choose_place == 0)&&(S1orS9_refre==1))
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = Seg1_flag;
		gui_draw_arcrectangle(0,list_y1_start,64,18,3,1,gui_elect);
		Seg1_Show(0,list_y1_start,Elect_color);     //ѡ��Seg1
		Seg2_Show(0,list_y2_start,Common_color);    
		Seg3_Show(0,list_y3_start,Common_color);
		Seg4_Show(0,list_y4_start,Common_color);
		Seg5_Show(0,list_y5_start,Common_color);
		Seg6_Show(0,list_y6_start,Common_color);
		Seg7_Show(0,list_y7_start,Common_color);
		S1orS9_refre = 0;
	}
	else
	{
		switch(Choose_place)
		{
			case 6:
				mic_state.mic_state_2 = Seg6_flag;
				Color_especial(list_y7_start,list_y6_start,Seg7_Show,Seg6_Show);
				break;
			
			case 5:
				mic_state.mic_state_2 = Seg5_flag;
				Color_especial(list_y6_start,list_y5_start,Seg6_Show,Seg5_Show);
				break;
			
			case 4:
				mic_state.mic_state_2 = Seg4_flag;
				Color_especial(list_y5_start,list_y4_start,Seg5_Show,Seg4_Show);
				break;
			
			case 3:
				mic_state.mic_state_2 = Seg3_flag;
				Color_especial(list_y4_start,list_y3_start,Seg4_Show,Seg3_Show);
				break;
			
			case 2:
				mic_state.mic_state_2 = Seg2_flag;
				Color_especial(list_y3_start,list_y2_start,Seg3_Show,Seg2_Show);
				break;
			
			case 1:
				mic_state.mic_state_2 = Seg1_flag;
				Color_especial(list_y2_start,list_y1_start,Seg2_Show,Seg1_Show);
				break;
			
			default:
				break;
		}
	}//end of switch
}	


/************************************************
�������� �� Switch_Down_Equili_1
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Down_Equili_1(void)
{
	switch(Choose_place)
	{
		case 2:
			mic_state.mic_state_2 = Seg2_flag;
			Color_especial(list_y1_start,list_y2_start,Seg1_Show,Seg2_Show);
			break;
		
		case 3:
			mic_state.mic_state_2 = Seg3_flag;
			Color_especial(list_y2_start,list_y3_start,Seg2_Show,Seg3_Show);
			break;
		
		case 4:
			mic_state.mic_state_2 = Seg4_flag;
			Color_especial(list_y3_start,list_y4_start,Seg3_Show,Seg4_Show);
			break;
		
		case 5:
			mic_state.mic_state_2 = Seg5_flag;
			Color_especial(list_y4_start,list_y5_start,Seg4_Show,Seg5_Show);
			break;
		
		case 6:
			mic_state.mic_state_2 = Seg6_flag;
			Color_especial(list_y5_start,list_y6_start,Seg5_Show,Seg6_Show);
			break;
		
		case 7:
			mic_state.mic_state_2 = Seg7_flag;
			Color_especial(list_y6_start,list_y7_start,Seg6_Show,Seg7_Show);
			break;
		
		default:
			break;
	}
}

/************************************************
�������� �� Switch_Down_Equili_2
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Down_Equili_2(void)
{
	if(Choose_place==8)  //���ѡ��λ����7��������Ҫ����д����
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = Seg8_flag;
		gui_draw_arcrectangle(0,list_y7_start,64,18,3,1,gui_elect);
		Seg8_Show(0,list_y7_start,Elect_color);     //ѡ��Seg8
		Seg7_Show(0,list_y6_start,Common_color);    //д��Seg7
		Seg6_Show(0,list_y5_start,Common_color);
		Seg5_Show(0,list_y4_start,Common_color);
		Seg4_Show(0,list_y3_start,Common_color);
		Seg3_Show(0,list_y2_start,Common_color);
		Seg2_Show(0,list_y1_start,Common_color);
	}
	else
	{
		switch(Choose_place)
		{
			case 2:
				mic_state.mic_state_2 = Seg3_flag;
				Color_especial(list_y1_start,list_y2_start,Seg2_Show,Seg3_Show);
				break;
			
			case 3:
				mic_state.mic_state_2 = Seg4_flag;
				Color_especial(list_y2_start,list_y3_start,Seg3_Show,Seg4_Show);
				break;
			
			case 4:
				mic_state.mic_state_2 = Seg5_flag;
				Color_especial(list_y3_start,list_y4_start,Seg4_Show,Seg5_Show);
				break;
			
			case 5:
				mic_state.mic_state_2 = Seg6_flag;
				Color_especial(list_y4_start,list_y5_start,Seg5_Show,Seg6_Show);
				break;
			
			case 6: 
				mic_state.mic_state_2 = Seg7_flag;
				Color_especial(list_y5_start,list_y6_start,Seg6_Show,Seg7_Show);
				break;
			
			case 7:
				mic_state.mic_state_2 = Seg8_flag;
				Color_especial(list_y6_start,list_y7_start,Seg7_Show,Seg8_Show);
				break;
			
			default:
				break;
		}
	}
}

/************************************************
�������� �� Switch_Down_Equili_3
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Down_Equili_3(void)
{
	if((Choose_place==8)&&(S1orS9_refre==1))  //���ѡ��λ����7��������Ҫ����д����
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = Seg9_flag;
		gui_draw_arcrectangle(0,list_y7_start,64,18,3,1,gui_elect);
		Seg9_Show(0,list_y7_start,Elect_color);     //ѡ��Seg9
		Seg8_Show(0,list_y6_start,Common_color);    //д��Seg8
		Seg7_Show(0,list_y5_start,Common_color);
		Seg6_Show(0,list_y4_start,Common_color);
		Seg5_Show(0,list_y3_start,Common_color);
		Seg4_Show(0,list_y2_start,Common_color);
		Seg3_Show(0,list_y1_start,Common_color);
		S1orS9_refre = 0;
	}
	else
	{
		switch(Choose_place)
		{
			case 2:
				mic_state.mic_state_2 = Seg4_flag;
				Color_especial(list_y1_start,list_y2_start,Seg3_Show,Seg4_Show);
				break;
			
			case 3:
				mic_state.mic_state_2 = Seg5_flag;
				Color_especial(list_y2_start,list_y3_start,Seg4_Show,Seg5_Show);
				break;
			
			case 4:
				mic_state.mic_state_2 = Seg6_flag;
				Color_especial(list_y3_start,list_y4_start,Seg5_Show,Seg6_Show);
				break;
			
			case 5:
				mic_state.mic_state_2 = Seg7_flag;
				Color_especial(list_y4_start,list_y5_start,Seg6_Show,Seg7_Show);
				break;
			
			case 6:
				mic_state.mic_state_2 = Seg8_flag;
				Color_especial(list_y5_start,list_y6_start,Seg7_Show,Seg8_Show);
				break;
			
			case 7:
				mic_state.mic_state_2 = Seg9_flag;
				Color_especial(list_y6_start,list_y7_start,Seg8_Show,Seg9_Show);
				break;
			
			default:
				break;
		}//end of switch
	}//end of (Choose_place==8)&&(S1orS9_refre==1)
}

/************************************************
�������� �� Switch_Down_Echo_1
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Down_Echo_1(void)
{
	switch(Choose_place)
	{
		case 2:
			mic_state.mic_state_2 = MDelay_A_flag;
			Color_especial(list_y1_start,list_y2_start,Advance_Delay_A,Main_Delay_A);
			break;
		
		case 3:
			mic_state.mic_state_2 = FValue_A_flag;
			Color_especial(list_y2_start,list_y3_start,Main_Delay_A,Feedback_Value_A);
			break;
		
		case 4:
			mic_state.mic_state_2 = Vout_A_flag;
			Color_especial(list_y3_start,list_y4_start,Feedback_Value_A,Volume_Out_A);
			break;
		
		case 5:
			mic_state.mic_state_2 = Filter_A_flag;
			Color_especial(list_y4_start,list_y5_start,Volume_Out_A,Filter_A);
			break;
		
		case 6:
			mic_state.mic_state_2 = ADelay_B_flag;
			Color_especial(list_y5_start,list_y6_start,Filter_A,Advance_Delay_B);
			break;
		
		case 7:
			mic_state.mic_state_2 = MDelay_B_flag;
			Color_especial(list_y6_start,list_y7_start,Advance_Delay_B,Main_Delay_B);
			break;
		
		default:
			break;
	}//end of switch
}


/************************************************
�������� �� Switch_Down_Echo_2
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Down_Echo_2(void)
{
	if(Choose_place == 8)
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = FValue_B_flag;   //ѡ�з���ֵB
		gui_draw_arcrectangle(0,list_y7_start,64,18,3,1,gui_elect);
		Feedback_Value_B(0,list_y7_start,Elect_color);     //ѡ�з���ֵB
		Main_Delay_B(0,list_y6_start,Common_color);    
		Advance_Delay_B(0,list_y5_start,Common_color);
		Filter_A(0,list_y4_start,Common_color);
		Volume_Out_A(0,list_y3_start,Common_color);
		Feedback_Value_A(0,list_y2_start,Common_color);
		Main_Delay_A(0,list_y1_start,Common_color);
	}
	else
	{
		switch(Choose_place)
		{
			case 2:
				mic_state.mic_state_2 = FValue_A_flag;
				Color_especial(list_y1_start,list_y2_start,Main_Delay_A,Feedback_Value_A);
				break;
			
			case 3:
				mic_state.mic_state_2 = Vout_A_flag;
				Color_especial(list_y2_start,list_y3_start,Feedback_Value_A,Volume_Out_A);
				break;
			
			case 4:
				mic_state.mic_state_2 = Filter_A_flag;
				Color_especial(list_y3_start,list_y4_start,Volume_Out_A,Filter_A);
				break;
			
			case 5:
				mic_state.mic_state_2 = ADelay_B_flag;
				Color_especial(list_y4_start,list_y5_start,Filter_A,Advance_Delay_B);
				break;
			
			case 6:
				mic_state.mic_state_2 = MDelay_B_flag;
				Color_especial(list_y5_start,list_y6_start,Advance_Delay_B,Main_Delay_B);
				break;
			
			case 7:
				mic_state.mic_state_2 = FValue_B_flag;
				Color_especial(list_y6_start,list_y7_start,Main_Delay_B,Feedback_Value_B);
				break;
			
			default:
				break;
		}//end of switch
	}//end of if
}

/************************************************
�������� �� Switch_Down_Echo_3
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Down_Echo_3(void)
{
	if(Choose_place == 8)
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = Vout_B_flag;  //ѡ���������B
		gui_draw_arcrectangle(0,list_y7_start,64,18,3,1,gui_elect);
		Volume_Out_B(0,list_y7_start,Elect_color);     
		Feedback_Value_B(0,list_y6_start,Common_color);    
		Main_Delay_B(0,list_y5_start,Common_color);
		Advance_Delay_B(0,list_y4_start,Common_color);
		Filter_A(0,list_y3_start,Common_color);
		Volume_Out_A(0,list_y2_start,Common_color);
		Feedback_Value_A(0,list_y1_start,Common_color);
	}
	else
	{
		switch(Choose_place)
		{
			case 2:
				mic_state.mic_state_2 = Vout_A_flag;
				Color_especial(list_y1_start,list_y2_start,Feedback_Value_A,Volume_Out_A);
				break;
			
			case 3:
				mic_state.mic_state_2 = Filter_A_flag;
				Color_especial(list_y2_start,list_y3_start,Volume_Out_A,Filter_A);
				break;
			
			case 4:
				mic_state.mic_state_2 = ADelay_B_flag;
				Color_especial(list_y3_start,list_y4_start,Filter_A,Advance_Delay_B);
				break;
			
			case 5:
				mic_state.mic_state_2 = MDelay_B_flag;
				Color_especial(list_y4_start,list_y5_start,Advance_Delay_B,Main_Delay_B);
				break;
			
			case 6:
				mic_state.mic_state_2 = FValue_B_flag;
				Color_especial(list_y5_start,list_y6_start,Main_Delay_B,Feedback_Value_B);
				break;
			
			case 7:
				mic_state.mic_state_2 = Vout_B_flag;
				Color_especial(list_y6_start,list_y7_start,Feedback_Value_B,Volume_Out_B);
				break;
			
			default:
				break;
		}//end of switch
	}
}

/************************************************
�������� �� Switch_Down_Echo_4
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Down_Echo_4(void)
{
	if((Choose_place == 8)&&(Echo_refrt == 1))
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = Filter_B_flag;  //ѡ���˲���B
		gui_draw_arcrectangle(0,list_y7_start,64,18,3,1,gui_elect);
		Filter_B(0,list_y7_start,Elect_color);     
		Volume_Out_B(0,list_y6_start,Common_color);    
		Feedback_Value_B(0,list_y5_start,Common_color);
		Main_Delay_B(0,list_y4_start,Common_color);
		Advance_Delay_B(0,list_y3_start,Common_color);
		Filter_A(0,list_y2_start,Common_color);
		Volume_Out_A(0,list_y1_start,Common_color);
		Echo_refrt = 0;
	}
	else
	{
		switch(Choose_place)
		{
			case 2:
				mic_state.mic_state_2 = Filter_A_flag;   //ѡ���˲���A
				Color_especial(list_y1_start,list_y2_start,Volume_Out_A,Filter_A);
				break;
			
			case 3:
				mic_state.mic_state_2 = ADelay_B_flag;   //ѡ��Ԥ��ʱB
				Color_especial(list_y2_start,list_y3_start,Filter_A,Advance_Delay_B);
				break;
			
			case 4:
				mic_state.mic_state_2 = MDelay_B_flag;   //ѡ������ʱB
				Color_especial(list_y3_start,list_y4_start,Advance_Delay_B,Main_Delay_B);
				break;
			
			case 5:
				mic_state.mic_state_2 = FValue_B_flag;   //ѡ�з���ֵB
				Color_especial(list_y4_start,list_y5_start,Main_Delay_B,Feedback_Value_B);
				break;
			
			case 6:
				mic_state.mic_state_2 = Vout_B_flag;     //ѡ���������B
				Color_especial(list_y5_start,list_y6_start,Feedback_Value_B,Volume_Out_B);
				break;
			
			case 7:
				mic_state.mic_state_2 = Filter_B_flag;   //ѡ���˲���B
				Color_especial(list_y6_start,list_y7_start,Volume_Out_B,Filter_B);
				break;
			
			default:
				break;
		}//end of switch
	}
}


/************************************************
�������� �� Switch_Up_Echo_1
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Up_Echo_1(void)
{
	if((Choose_place == 0)&&(Echo_refrt == 1))
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = ADelay_A_flag;   //ѡ��Ԥ��ʱA
		gui_draw_arcrectangle(0,list_y1_start,64,18,3,1,gui_elect);
		Advance_Delay_A(0,list_y1_start,Elect_color);     
		Main_Delay_A(0,list_y2_start,Common_color);    
		Feedback_Value_A(0,list_y3_start,Common_color);
		Volume_Out_A(0,list_y4_start,Common_color);
		Filter_A(0,list_y5_start,Common_color);
		Advance_Delay_B(0,list_y6_start,Common_color);
		Main_Delay_B(0,list_y7_start,Common_color);
		Echo_refrt = 0;
	}
	else
	{
		switch(Choose_place)
		{
			case 6:
				mic_state.mic_state_2 = ADelay_B_flag;      //ѡ��Ԥ��ʱB
				Color_especial(list_y7_start,list_y6_start,Main_Delay_B,Advance_Delay_B);
				break;
			
			case 5:
				mic_state.mic_state_2 = Filter_A_flag;      //ѡ���˲���A
				Color_especial(list_y6_start,list_y5_start,Advance_Delay_B,Filter_A);
				break;
			
			case 4:
				mic_state.mic_state_2 = Vout_A_flag;      //ѡ���������A
				Color_especial(list_y5_start,list_y4_start,Filter_A,Volume_Out_A);
				break;
			
			case 3:
				mic_state.mic_state_2 = FValue_A_flag;      //ѡ�з���ֵA
				Color_especial(list_y4_start,list_y3_start,Volume_Out_A,Feedback_Value_A);
				break;
			
			case 2:
				mic_state.mic_state_2 = MDelay_A_flag;      //ѡ������ʱA
				Color_especial(list_y3_start,list_y2_start,Feedback_Value_A,Main_Delay_A);
				break;
			
			case 1:
				mic_state.mic_state_2 = ADelay_A_flag;      //ѡ��Ԥ��ʱA
				Color_especial(list_y2_start,list_y1_start,Main_Delay_A,Advance_Delay_A);
				break;
			
			default:
				break;
		}//end of switch
	}
}

/************************************************
�������� �� Switch_Up_Echo_2
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Up_Echo_2(void)
{
	if(Choose_place == 0)
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = MDelay_A_flag;  //ѡ������ʱA
		gui_draw_arcrectangle(0,list_y1_start,64,18,3,1,gui_elect);
		Main_Delay_A(0,list_y1_start,Elect_color);     
		Feedback_Value_A(0,list_y2_start,Common_color);    
		Volume_Out_A(0,list_y3_start,Common_color);
		Filter_A(0,list_y4_start,Common_color);
		Advance_Delay_B(0,list_y5_start,Common_color);
		Main_Delay_B(0,list_y6_start,Common_color);
		Feedback_Value_B(0,list_y7_start,Common_color);
	}
	else 
	{
		switch(Choose_place)
		{
			case 6:
				mic_state.mic_state_2 = MDelay_B_flag;      //ѡ������ʱB
				Color_especial(list_y7_start,list_y6_start,Feedback_Value_B,Main_Delay_B);
				break;
			
			case 5:
				mic_state.mic_state_2 = ADelay_B_flag;      //ѡ��Ԥ��ʱB
				Color_especial(list_y6_start,list_y5_start,Main_Delay_B,Advance_Delay_B);
				break;
			
			case 4:
				mic_state.mic_state_2 = Filter_A_flag;      //ѡ���˲���A
				Color_especial(list_y5_start,list_y4_start,Advance_Delay_B,Filter_A);
				break;
			
			case 3:
				mic_state.mic_state_2 = Vout_A_flag;      //ѡ���������A
				Color_especial(list_y4_start,list_y3_start,Filter_A,Volume_Out_A);
				break;
			
			case 2:
				mic_state.mic_state_2 = FValue_A_flag;      //ѡ�з���ֵA
				Color_especial(list_y3_start,list_y2_start,Volume_Out_A,Feedback_Value_A);
				break;
			
			case 1:
				mic_state.mic_state_2 = MDelay_A_flag;      //ѡ������ʱA
				Color_especial(list_y2_start,list_y1_start,Feedback_Value_A,Main_Delay_A);
				break;
			
			default:
				break;
		}//end of switch
	}
}

/************************************************
�������� �� Switch_Up_Echo_3
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Up_Echo_3(void)
{
	if(Choose_place == 0)
	{
		display_pic(black);  //�����ɺ�ɫ
		mic_state.mic_state_2 = FValue_A_flag;  //ѡ�з���ֵA
		gui_draw_arcrectangle(0,list_y1_start,64,18,3,1,gui_elect);
		Feedback_Value_A(0,list_y1_start,Elect_color);     
		Volume_Out_A(0,list_y2_start,Common_color);    
		Filter_A(0,list_y3_start,Common_color);
		Advance_Delay_B(0,list_y4_start,Common_color);
		Main_Delay_B(0,list_y5_start,Common_color);
		Feedback_Value_B(0,list_y6_start,Common_color);
		Volume_Out_B(0,list_y7_start,Common_color);
	}
	else 
	{
		switch(Choose_place)
		{
			case 6:
				mic_state.mic_state_2 = FValue_B_flag;      //ѡ�з���ֵB
				Color_especial(list_y7_start,list_y6_start,Volume_Out_B,Feedback_Value_B);
				break;
			
			case 5:
				mic_state.mic_state_2 = MDelay_B_flag;      //ѡ������ʱB
				Color_especial(list_y6_start,list_y5_start,Feedback_Value_B,Main_Delay_B);
				break;
			
			case 4:
				mic_state.mic_state_2 = ADelay_B_flag;      //ѡ��Ԥ��ʱB
				Color_especial(list_y5_start,list_y4_start,Main_Delay_B,Advance_Delay_B);
				break;
			
			case 3:
				mic_state.mic_state_2 = Filter_A_flag;      //ѡ���˲���A
				Color_especial(list_y4_start,list_y3_start,Advance_Delay_B,Filter_A);
				break;
			
			case 2:
				mic_state.mic_state_2 = Vout_A_flag;      //ѡ���������A
				Color_especial(list_y3_start,list_y2_start,Filter_A,Volume_Out_A);
				break;
			
			case 1:
				mic_state.mic_state_2 = FValue_A_flag;      //ѡ�з���ֵA
				Color_especial(list_y2_start,list_y1_start,Volume_Out_A,Feedback_Value_A);
				break;
			
			default:
				break;
		}
	}
}

/************************************************
�������� �� Switch_Up_Echo_4
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Switch_Up_Echo_4(void)
{
	switch(Choose_place)
	{
		case 6:
			mic_state.mic_state_2 = Vout_B_flag;     //ѡ���������B
			Color_especial(list_y7_start,list_y6_start,Filter_B,Volume_Out_B);
			break;
		
		case 5:
			mic_state.mic_state_2 = FValue_B_flag;     //ѡ�з���ֵB
			Color_especial(list_y6_start,list_y5_start,Volume_Out_B,Feedback_Value_B);
			break;
		
		case 4:
			mic_state.mic_state_2 = MDelay_B_flag;     //ѡ������ʱB
			Color_especial(list_y5_start,list_y4_start,Feedback_Value_B,Main_Delay_B);
			break;
		
		case 3:
			mic_state.mic_state_2 = ADelay_B_flag;     //ѡ��Ԥ��ʱB
			Color_especial(list_y4_start,list_y3_start,Main_Delay_B,Advance_Delay_B);
			break;
		
		case 2:
			mic_state.mic_state_2 = Filter_A_flag;     //ѡ���˲���A
			Color_especial(list_y3_start,list_y2_start,Advance_Delay_B,Filter_A);
			break;
		
		case 1:
			mic_state.mic_state_2 = Vout_A_flag;      //ѡ���������A
			Color_especial(list_y2_start,list_y1_start,Filter_A,Volume_Out_A);
			break;
		
		default:
			break;
	}//end of switch
}


/************************************************
�������� �� Color_Conver
��    �� �� ɫ���л�
��    �� �� list1:ԭ����ɫ��λ�ã�list2:ɫ��Ҫת����λ��
�� �� ֵ �� ��
*************************************************/
static void Color_Conver(u8 list1, u8 list2)
{
	gui_draw_arcrectangle(0,list1,64,18,3,1,gui_Noelect);
	gui_draw_arcrectangle(0,list2,64,18,3,1,gui_elect);
}

/************************************************
�������� �� Color_especial
��    �� �� �����ɫ���л�
��    �� �� list3��list4:��ɫ��ת��λ�ã�Common��Elect:��ʾ�ַ�������
�� �� ֵ �� ��
*************************************************/
static void Color_especial(u8 list3, u8 list4,action_t Common,action_t Elect)
{
	Color_Conver(list3,list4);
	Common(0,list3,Common_color);   //Ϩ��
	Elect(0,list4,Elect_color);     //ѡ��
}

/************************************************
�������� �� Mic_Main_Switch_UP
��    �� �� UP����ʾѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Mic_Main_Switch_UP(void)
{
	switch(mic_state.mic_state_1)
	{
		case Reverb_flag:
			mic_state.mic_state_1 = Input_flag;
			Color_especial(list_y1_start,list_y7_start,Reverb_Show,Input_qualcomm);
			break;
		
		case Equili_flag:
			mic_state.mic_state_1 = Reverb_flag;
			Color_especial(list_y2_start,list_y1_start,Equili_Show,Reverb_Show);
			break;
		
		case Echo_flag:
			mic_state.mic_state_1 = Equili_flag;
			Color_especial(list_y3_start,list_y2_start,Echo_Show,Equili_Show);
			break;
		
		case Frequenc_flag:
			mic_state.mic_state_1 = Echo_flag;
			Color_especial(list_y4_start,list_y3_start,Frequenc_shift_Show,Echo_Show);
			break;
		
		case Noise_flag:
			mic_state.mic_state_1 = Frequenc_flag;
			Color_especial(list_y5_start,list_y4_start,Noise_shold,Frequenc_shift_Show);
			break;
		
		case DR_flag:
			mic_state.mic_state_1 = Noise_flag;
			Color_especial(list_y6_start,list_y5_start,DR_compress,Noise_shold);
			break;
		
		case Input_flag:
			mic_state.mic_state_1 = DR_flag;
			Color_especial(list_y7_start,list_y6_start,Input_qualcomm,DR_compress);
			break;
		
		default:
			break;
	}//end of switch

}

/************************************************
�������� �� Mic_Main_Switch_Down
��    �� �� DOWN����ʾѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Mic_Main_Switch_Down(void)
{
	switch(mic_state.mic_state_1)
	{
		case Reverb_flag:
			mic_state.mic_state_1 = Equili_flag;
			Color_especial(list_y1_start,list_y2_start,Reverb_Show,Equili_Show);
			break;
		
		case Equili_flag:
			mic_state.mic_state_1 = Echo_flag;
			Color_especial(list_y2_start,list_y3_start,Equili_Show,Echo_Show);
			break;
		
		case Echo_flag:
			mic_state.mic_state_1 = Frequenc_flag;
			Color_especial(list_y3_start,list_y4_start,Echo_Show,Frequenc_shift_Show);
			break;
		
		case Frequenc_flag:
			mic_state.mic_state_1 = Noise_flag;
			Color_especial(list_y4_start,list_y5_start,Frequenc_shift_Show,Noise_shold);
			break;
		
		case Noise_flag:
			mic_state.mic_state_1 = DR_flag;
			Color_especial(list_y5_start,list_y6_start,Noise_shold,DR_compress);
			break;
		
		case DR_flag:
			mic_state.mic_state_1 = Input_flag;
			Color_especial(list_y6_start,list_y7_start,DR_compress,Input_qualcomm);
			break;
		
		case Input_flag:
			mic_state.mic_state_1 = Reverb_flag;
			Color_especial(list_y7_start,list_y1_start,Input_qualcomm,Reverb_Show);
			break;
		
		default:
			break;
	}
}

/************************************************
�������� �� Reverb_Page2_Switch_UP
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Reverb_Page2_Switch_UP(void)
{
	switch(mic_state.mic_state_2)
	{
		case Dry_flag:
			mic_state.mic_state_2 = HightorLow_flag;
			Color_especial(list_y1_start,list_y6_start,Dry_voice,HightorLow_Cut);
			break;
		
		case Wet_flag:
			mic_state.mic_state_2 = Dry_flag;
			Color_especial(list_y2_start,list_y1_start,Wet_voice,Dry_voice);
			break;
		
		case Echo_time_flag:
			mic_state.mic_state_2 = Wet_flag;
			Color_especial(list_y3_start,list_y2_start,Echo_time_delay,Wet_voice);
			break;
		
		case Echo_Gain_flag:
			mic_state.mic_state_2 = Echo_time_flag;
			Color_especial(list_y4_start,list_y3_start,Echo_Gain,Echo_time_delay);
			break;
		
		case Reverb_Time_flag:
			mic_state.mic_state_2 = Echo_Gain_flag;
			Color_especial(list_y5_start,list_y4_start,Reverb_Time,Echo_Gain);
			break;
		
		case HightorLow_flag:
			mic_state.mic_state_2 = Reverb_Time_flag;
			Color_especial(list_y6_start,list_y5_start,HightorLow_Cut,Reverb_Time);
			break;
		
		default:
			break;
	}//end of switch
}

/************************************************
�������� �� Reverb_Page2_Switch_DOWN
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Reverb_Page2_Switch_DOWN(void)
{
	switch(mic_state.mic_state_2)
	{
		case Dry_flag:
			mic_state.mic_state_2 = Wet_flag;
			Color_especial(list_y1_start,list_y2_start,Dry_voice,Wet_voice);
			break;
		
		case Wet_flag:
			mic_state.mic_state_2 = Echo_time_flag;
			Color_especial(list_y2_start,list_y3_start,Wet_voice,Echo_time_delay);
			break;
		
		case Echo_time_flag:
			mic_state.mic_state_2 = Echo_Gain_flag;
			Color_especial(list_y3_start,list_y4_start,Echo_time_delay,Echo_Gain);
			break;
		
		case Echo_Gain_flag:
			mic_state.mic_state_2 = Reverb_Time_flag;
			Color_especial(list_y4_start,list_y5_start,Echo_Gain,Reverb_Time);
			break;
		
		case Reverb_Time_flag:
			mic_state.mic_state_2 = HightorLow_flag;
			Color_especial(list_y5_start,list_y6_start,Reverb_Time,HightorLow_Cut);
			break;
		
		case HightorLow_flag:
			mic_state.mic_state_2 = Dry_flag;
			Color_especial(list_y6_start,list_y1_start,HightorLow_Cut,Dry_voice);
			break;
		
		default:
			break;
	}//end of switch
}

/************************************************
�������� �� DR_Page2_Switch_UP
��    �� �� ��̬��Χ�ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void DR_Page2_Switch_UP(void)
{
	switch(mic_state.mic_state_2)
	{
		case PerGain_flag:
			mic_state.mic_state_2 = Release_flag;
			Color_especial(list_y1_start,list_y5_start,PreGain_Show,Release_Show);
			break;
		
		case Thershold_flag:
			mic_state.mic_state_2 = PerGain_flag;
			Color_especial(list_y2_start,list_y1_start,Shold_Show,PreGain_Show);
			break;
		
		case Ratio_flag:
			mic_state.mic_state_2 = Thershold_flag;
			Color_especial(list_y3_start,list_y2_start,Ratio_Show,Shold_Show);
			break;
		
		case Attack_flag:
			mic_state.mic_state_2 = Ratio_flag;
			Color_especial(list_y4_start,list_y3_start,Attack_Show,Ratio_Show);
			break;
		
		case Release_flag:
			mic_state.mic_state_2 = Attack_flag;
			Color_especial(list_y5_start,list_y4_start,Release_Show,Attack_Show);
			break;
		
		default:
			break;
	}//end of switch
}

/************************************************
�������� �� DR_Page2_Switch_DOWN
��    �� �� ��̬��Χ�ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void DR_Page2_Switch_DOWN(void)
{
	switch(mic_state.mic_state_2)
	{
		case PerGain_flag:
			mic_state.mic_state_2 = Thershold_flag;     //����д��ɫ��
			Color_especial(list_y1_start,list_y2_start,PreGain_Show,Shold_Show);
			break;
		
		case Thershold_flag:
			mic_state.mic_state_2 = Ratio_flag;
			Color_especial(list_y2_start,list_y3_start,Shold_Show,Ratio_Show);
			break;
		
		case Ratio_flag:
			mic_state.mic_state_2 = Attack_flag;
			Color_especial(list_y3_start,list_y4_start,Ratio_Show,Attack_Show);
			break;
		
		case Attack_flag:
			mic_state.mic_state_2 = Release_flag;
			Color_especial(list_y4_start,list_y5_start,Attack_Show,Release_Show);
			break;
		
		case Release_flag:
			mic_state.mic_state_2 = PerGain_flag;
			Color_especial(list_y5_start,list_y1_start,Release_Show,PreGain_Show);
			break;
		
		default:
			break;
	}//end of switch
}

/************************************************
�������� �� FS_Page2_Switch_UP
��    �� �� ��Ƶ�ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void FS_Page2_Switch_UP(void)
{
	switch(mic_state.mic_state_2)
	{
		case FS_value_flag:
			mic_state.mic_state_2 = FS_switch_flag;
			Color_especial(list_y1_start,list_y2_start,Frequency_shift_value,Frequency_shift_switch);
			break;
		
		case FS_switch_flag:
			mic_state.mic_state_2 = FS_value_flag;
			Color_especial(list_y2_start,list_y1_start,Frequency_shift_switch,Frequency_shift_value);
			break;
		
		default:
			break;
	}
}

/************************************************
�������� �� FS_Page2_Switch_DOWN
��    �� �� ��Ƶ�ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void FS_Page2_Switch_DOWN(void)
{
	switch(mic_state.mic_state_2)
	{
		case FS_value_flag:
			mic_state.mic_state_2 = FS_switch_flag;
			Color_especial(list_y1_start,list_y2_start,Frequency_shift_value,Frequency_shift_switch);
			break;
		
		case FS_switch_flag:
			mic_state.mic_state_2 = FS_value_flag;
			Color_especial(list_y2_start,list_y1_start,Frequency_shift_switch,Frequency_shift_value);
			break;
		
		default:
			break;
	}
}

/************************************************
�������� �� Equili_Page2_Switch_UP
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Equili_Page2_Switch_UP(void)
{
	Choose_place--;
	if(((Choose_place == 0)&&(mic_state.mic_state_2 != Seg1_flag)))
	{
		Equili_top = Equili_top - 1;
		S1orS9_refre = 1;
	}
	if(Equili_top==3)
	{
		Switch_UP_Equili_3(); //ʵ��ɫ��ת������3
	}
	else if(Equili_top==2)
	{
		Switch_UP_Equili_2(); //ʵ��ɫ��ת������2
	}
	else if(Equili_top==1)
	{
		Switch_UP_Equili_1(); //ʵ��ɫ��ת������1
	}//end of if
	if(Choose_place < 1) //���ѡ����λ�õ͹�1
	{
		Choose_place = 1; //ѡ��λ�ò���
	}
}

/************************************************
�������� �� Equili_Page2_Switch_DOWN
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Equili_Page2_Switch_DOWN(void)
{
	Choose_place++;  //ѡ��λ�ü�1
	if(((Choose_place > 7)&&(mic_state.mic_state_2 != Seg9_flag)))
	{
		Equili_top = Equili_top + 1;
		S1orS9_refre = 1;
	}
	
	if(Equili_top==1) //Seg1~Seg7
	{
		Switch_Down_Equili_1(); //����1ɫ��ת��
	}
	else if(Equili_top==2)  //������2��  Seg2~Seg8
	{
		Switch_Down_Equili_2(); //����2ɫ��ת��
	}
	else if(Equili_top==3)  //������3��  Seg3~Seg9
	{
		Switch_Down_Equili_3(); //����3ɫ��ת��
	}//end of if
	if(Choose_place > 7) //���ѡ����λ�ó���7
	{
		Choose_place = 7; //ѡ��λ�ò���
	}
}

/************************************************
�������� �� Echo_Page2_Switch_DOWN
��    �� �� �����ӽ����¼�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Echo_Page2_Switch_DOWN(void)
{
	Choose_place++;    //ѡ��λ�ü�1
	if((Choose_place > 7)&&(mic_state.mic_state_2 != Filter_B_flag))
	{
		Echo_top++;
		Echo_refrt = 1;
	}
	if(Echo_top == 1)
	{
		Switch_Down_Echo_1();   //����1��ɫ��ת��
	}
	else if(2 == Echo_top)
	{
		Switch_Down_Echo_2();   //����2��ɫ��ת��
	}
	else if(3 == Echo_top)
	{
		Switch_Down_Echo_3();   //����3��ɫ��ת��
	}
	else if(4 == Echo_top)
	{
		Switch_Down_Echo_4();   //����4��ɫ��ת��
	}
	if(Choose_place > 7) //���ѡ����λ�ó���7
	{
		Choose_place = 7; //ѡ��λ�ò���
	}
}

/************************************************
�������� �� Echo_Page2_Switch_UP
��    �� �� �����ӽ����ϼ�ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Echo_Page2_Switch_UP(void)
{
	Choose_place--;    //ѡ��λ�ü�1
	if((Choose_place == 0)&&(mic_state.mic_state_2 != ADelay_A_flag))
	{
		Echo_top--;
		Echo_refrt = 1;
	}
	if(Echo_top == 4)
	{
		Switch_Up_Echo_4();  //����4�ϼ�ת��
	}
	else if(Echo_top == 3)
	{
		Switch_Up_Echo_3();  //����3
	}
	else if(Echo_top == 2)
	{
		Switch_Up_Echo_2();  //����2
	}//end of Echo_top == 2
	else if(Echo_top == 1)
	{
		Switch_Up_Echo_1();  //����1
	}//end of Echo_top == 1
	if(Choose_place < 1) //���ѡ����λ�õ͹�1
	{
		Choose_place = 1; //ѡ��λ�ò���
	}
}

/************************************************
�������� �� Mic_Main_Enter
��    �� �� ������ȷ��ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Mic_Main_Enter(void)
{
	display_pic(black);
	switch(mic_state.mic_state_1)
	{
		case Reverb_flag:
			MIC_Reverb_page2();  //�����ӽ���
		    break;
		
		case Equili_flag:
			MIC_Equili_page2();  //�����ӽ���
			break;
		
		case Echo_flag:
			MIC_Echo_page2();    //�����ӽ���
			break;
		
		case Frequenc_flag:
			MIC_Frequenc_page2(); //��Ƶ�ӽ���
			break;
		
		case DR_flag:
			MIC_DR_page2();       //��̬�ӽ���
			break;
		
		case Noise_flag:
			break;
		
		case Input_flag:
			break;
		
		default:
			break;
	}
}

/************************************************
�������� �� Mic_Main_Esc
��    �� �� �˳���������ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Mic_Main_Esc(void)
{
	display_pic(black);
	Reverb_Show(0,0,Common_color); 		      //��ʾ����
	Equili_Show(0,18,Common_color);           //��ʾ����
	Echo_Show(0,36,Common_color);       	  //��ʾ����
	Frequenc_shift_Show(0,54,Common_color);   //��ʾ��Ƶ
	Noise_shold(0,72,Common_color);           //��ʾ��������
	DR_compress(0,90,Common_color);           //��ʾ��̬��Χ
	Input_qualcomm(0,108,Common_color);       //��ʾ�����ͨ
	switch(mic_state.mic_state_1)
	{
		case Reverb_flag:         //ѡ�л���
			gui_draw_arcrectangle(0,list_y1_start,64,18,3,1,gui_elect);
			Reverb_Show(0,list_y1_start,Elect_color); 		      
		    break;
		
		case Equili_flag:         //ѡ�о���
			gui_draw_arcrectangle(0,list_y2_start,64,18,3,1,gui_elect);
			Equili_Show(0,18,Elect_color);
			break;
		
		case Echo_flag:           //ѡ�л���
			gui_draw_arcrectangle(0,list_y3_start,64,18,3,1,gui_elect);
			Echo_Show(0,list_y3_start,Elect_color);
			break;
		
		case Frequenc_flag:       //ѡ����Ƶ
			gui_draw_arcrectangle(0,list_y4_start,64,18,3,1,gui_elect);
			Frequenc_shift_Show(0,list_y4_start,Elect_color);
			break;
		
		case Noise_flag:          //ѡ������
			gui_draw_arcrectangle(0,list_y5_start,64,18,3,1,gui_elect);
			Noise_shold(0,list_y5_start,Elect_color);
			break;
		
		case DR_flag:             //ѡ�ж�̬
			gui_draw_arcrectangle(0,list_y6_start,64,18,3,1,gui_elect);
			DR_compress(0,list_y6_start,Elect_color);
			break;
		
		case Input_flag:          //ѡ�������ͨ
			gui_draw_arcrectangle(0,list_y7_start,64,18,3,1,gui_elect);
			Input_qualcomm(0,list_y7_start,Elect_color);
			break;
		
		default:
			break;
	}

}

/************************************************
�������� �� Reverb_Page2_Enter
��    �� �� �����ӽ���ȷ��ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Reverb_Page2_Enter(void)
{
	switch(mic_state.mic_state_2)
	{
		case Dry_flag:
			break;
		
		case Wet_flag:
			break;
		
		case Echo_time_flag:
			break;
		
		case Echo_Gain_flag:
			break;
		
		case Reverb_Time_flag:
			break;
		
		case HightorLow_flag:
			break;
		
		default:
			break;
	}//end of switch
}

/************************************************
�������� �� DR_Page2_Enter
��    �� �� ��̬��Χ�ӽ���ȷ��ѡ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void DR_Page2_Enter(void)
{
	
}



