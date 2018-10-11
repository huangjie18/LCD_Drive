#include "control.h"
#include "led.h"
#include "adc.h"
#include "delay.h"
#define AD_lvbo 10
#define LEFT  1         //左
#define RIGHT 2         //右
#define ENCORE_STOP  0  //静止

extern u8 KEY_STATE;  
u8 HC595[10];
u8 SendBuff[SEND_BUF_SIZE]; //要传输的字节
u8 KeyValue=0;               //键值
u16 Fader_ADC_Value_1=0;      //电机1ADC采集数据
u16 Fader_ADC_Value_2=0;      //电机2ADC采集数据
u16 Fader_ADC_Value_3=0;      //电机3ADC采集数据
u16 Fader_ADC_Value_4=0;      //电机4ADC采集数据
u16 Fader_ADC_Value_5=0;      //电机5ADC采集数据
u16 Fader_ADC_Value_6=0;      //电机6ADC采集数据
u16 Fader_ADC_Value_7=0;      //电机7ADC采集数据
u16 Fader_ADC_Value_8=0;      //电机8ADC采集数据
u16 Fader_ADC_Value_9=0;      //电机9ADC采集数据
u16 Fader_ADC_Value_10=0;     //电机10ADC采集数据
u16 Fader_ADC_Value_11=0;     //电机11ADC采集数据
u16 Fader_ADC_Value_12=0;     //电机12ADC采集数据
u16 Fader_ADC_Value_13=0;     //电机13ADC采集数据
u16 Fader_ADC_Value_14=0;     //电机14ADC采集数据
u16 Fader_ADC_Value_15=0;     //电机15ADC采集数据
u16 Fader_ADC_Value_16=0;     //电机16ADC采集数据
u16 Fader_ADC_Value_17=0;     //电机17ADC采集数据
u16 Fader_ADC_Value_18=0;     //电机18ADC采集数据
u16 Fader_ADC_Value_19=0;     //电机19ADC采集数据
u16 Fader_ADC_Value_20=0;     //电机20ADC采集数据
u16 Fader_ADC_Value_21=0;     //电机21ADC采集数据
u16 Fader_ADC_Value_22=0;     //电机22ADC采集数据
//上一次采集到的数据
u16 Fader_ADC_Value_last[23]={0};      //电机1ADC采集数据

/**********************************************************************/
//编码器
u8 ES1_A_Old=1,ES2_A_Old=1,ES3_A_Old=1,ES4_A_Old=1;
u8 ES1_B_Old=1,ES2_B_Old=1,ES3_B_Old=1,ES4_B_Old=1;
u8 ES1_Flag=0,ES2_Flag=0,ES3_Flag=0,ES4_Flag=0; //正反转状态
u8 ES1_Flag_zuo=0,ES1_Flag_you=0;//默认发送0;1:发送1;2:发送2
u8 ES2_Flag_zuo=0,ES2_Flag_you=0;//默认发送0;1:发送1;2:发送2
u8 ES3_Flag_zuo=0,ES3_Flag_you=0;//默认发送0;1:发送1;2:发送2
u8 ES4_Flag_zuo=0,ES4_Flag_you=0;//默认发送0;1:发送1;2:发送2
u8 ENCODER_Value_1=0;  //USART传输值
u8 ENCODER_Value_2=0;
u8 ENCODER_Value_3=0;
u8 ENCODER_Value_4=0;
/**********************************************************************/
/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp=0;
		if(a<0)  
		{
			temp=-a;
		}			
		else 
		{
			temp=a;
		}
	  return temp;
}

void SendBuff_Init(void)
{
	KOGNZHI_1();
	SendBuff[0] = 0xab;      //数据头
	SendBuff[1] = 0xba;
	SendBuff[2] = KEY_STATE;   //按键值
	SendBuff[3] = KeyValue;
	SendBuff[4] = Fader_ADC_Value_1>>8;    //电机1的adc值
	SendBuff[5] = Fader_ADC_Value_1&0xff;
	SendBuff[6] = Fader_ADC_Value_2>>8;    //电机2的adc值
	SendBuff[7] = Fader_ADC_Value_2&0xff;
	SendBuff[8] = Fader_ADC_Value_3>>8;    //电机3的adc值
	SendBuff[9] = Fader_ADC_Value_3&0xff;
	SendBuff[10] = Fader_ADC_Value_4>>8;   //电机4的adc值
	SendBuff[11] = Fader_ADC_Value_4&0xff;
	SendBuff[12] = Fader_ADC_Value_5>>8;   //电机5的adc值
	SendBuff[13] = Fader_ADC_Value_5&0xff;
	SendBuff[14] = Fader_ADC_Value_6>>8;   //电机6的adc值
	SendBuff[15] = Fader_ADC_Value_6&0xff;
	SendBuff[16] = Fader_ADC_Value_7>>8;   //电机7的adc值
	SendBuff[17] = Fader_ADC_Value_7&0xff;
	SendBuff[18] = Fader_ADC_Value_8>>8;   //电机8的adc值
	SendBuff[19] = Fader_ADC_Value_8&0xff;
	SendBuff[20] = Fader_ADC_Value_9>>8;   //电机9的adc值
	SendBuff[21] = Fader_ADC_Value_9&0xff;
	SendBuff[22] = Fader_ADC_Value_10>>8;   //电机10的adc值
	SendBuff[23] = Fader_ADC_Value_10&0xff;
	SendBuff[24] = Fader_ADC_Value_11>>8;   //电机11的adc值
	SendBuff[25] = Fader_ADC_Value_11&0xff;
	SendBuff[26] = Fader_ADC_Value_12>>8;   //电机12的adc值
	SendBuff[27] = Fader_ADC_Value_12&0xff;
	SendBuff[28] = Fader_ADC_Value_13>>8;   //电机13的adc值
	SendBuff[29] = Fader_ADC_Value_13&0xff;
	SendBuff[30] = Fader_ADC_Value_14>>8;   //电机14的adc值
	SendBuff[31] = Fader_ADC_Value_14&0xff;
	SendBuff[32] = Fader_ADC_Value_15>>8;   //电机15的adc值
	SendBuff[33] = Fader_ADC_Value_15&0xff;
	SendBuff[34] = Fader_ADC_Value_16>>8;   //电机16的adc值
	SendBuff[35] = Fader_ADC_Value_16&0xff;
	SendBuff[36] = Fader_ADC_Value_17>>8;   //电机17的adc值
	SendBuff[37] = Fader_ADC_Value_17&0xff;
	SendBuff[38] = Fader_ADC_Value_18>>8;   //电机18的adc值
	SendBuff[39] = Fader_ADC_Value_18&0xff;
	SendBuff[40] = Fader_ADC_Value_19>>8;   //电机19的adc值
	SendBuff[41] = Fader_ADC_Value_19&0xff;
	SendBuff[42] = Fader_ADC_Value_20>>8;   //电机20的adc值
	SendBuff[43] = Fader_ADC_Value_20&0xff;
	SendBuff[44] = Fader_ADC_Value_21>>8;   //电机21的adc值
	SendBuff[45] = Fader_ADC_Value_21&0xff;
	SendBuff[46] = Fader_ADC_Value_22>>8;   //电机22的adc值
	SendBuff[47] = Fader_ADC_Value_22&0xff;
	SendBuff[48] = ENCODER_Value_1;   //编码器1
	SendBuff[49] = ENCODER_Value_2;   //编码器2
	SendBuff[50] = ENCODER_Value_3;   //编码器3
	SendBuff[51] = ENCODER_Value_4;   //编码器4
	SendBuff[52] = USART_check();                 //累加和校验   
	
}

void KOGNZHI_1(void)
{
	u8 i=0;
	u16 Fader_ADC_Value_data[23];
	u16 Value_absolute;
	
	Fader_ADC_Value_data[1] = Get_Adc_Average(ADC1,0,AD_lvbo);
	Fader_ADC_Value_data[2] = Get_Adc_Average(ADC1,1,AD_lvbo);
	Fader_ADC_Value_data[3] = Get_Adc_Average(ADC1,2,AD_lvbo);
	Fader_ADC_Value_data[4] = Get_Adc_Average(ADC1,3,AD_lvbo);
	Fader_ADC_Value_data[5] = Get_Adc_Average(ADC1,4,AD_lvbo);
	Fader_ADC_Value_data[6] = Get_Adc_Average(ADC1,5,AD_lvbo);
	Fader_ADC_Value_data[7] = Get_Adc_Average(ADC1,6,AD_lvbo);
	Fader_ADC_Value_data[8] = Get_Adc_Average(ADC1,7,AD_lvbo);
	Fader_ADC_Value_data[9] = Get_Adc_Average(ADC1,14,AD_lvbo);
	Fader_ADC_Value_data[10] = Get_Adc_Average(ADC1,15,AD_lvbo);
	Fader_ADC_Value_data[11] = Get_Adc_Average(ADC1,8,AD_lvbo);
	Fader_ADC_Value_data[12] = Get_Adc_Average(ADC1,9,AD_lvbo);
	Fader_ADC_Value_data[13] = Get_Adc_Average(ADC3,5,AD_lvbo);
	Fader_ADC_Value_data[14] = Get_Adc_Average(ADC3,4,AD_lvbo);
	Fader_ADC_Value_data[15] = Get_Adc_Average(ADC3,6,AD_lvbo);
	Fader_ADC_Value_data[16] = Get_Adc_Average(ADC3,7,AD_lvbo);
	Fader_ADC_Value_data[17] = Get_Adc_Average(ADC3,8,AD_lvbo);
	Fader_ADC_Value_data[18] = Get_Adc_Average(ADC1,10,AD_lvbo);
	Fader_ADC_Value_data[19] = Get_Adc_Average(ADC1,11,AD_lvbo);
	Fader_ADC_Value_data[20] = Get_Adc_Average(ADC1,12,AD_lvbo);
///////////////////////////////////////////////////////////	
	C0 = 0;
	Fader_ADC_Value_data[21] = Get_Adc_Average(ADC1,13,AD_lvbo);
	C0 = 1;
	Fader_ADC_Value_data[22] = Get_Adc_Average(ADC1,13,AD_lvbo);
	
	ENCODER_SW_1();       //编码器1
	ENCODER_SW_2();       //编码器2
	ENCODER_SW_3();       //编码器3
	ENCODER_SW_4();       //编码器4
	
	//推子数据处理
	for(i=1;i<23;i++)
	{
		Value_absolute=myabs(Fader_ADC_Value_data[i]-Fader_ADC_Value_last[i]);
		
		if(Value_absolute>10)
		{
			Fader_ADC_Value_last[i] = Fader_ADC_Value_data[i]; //存放为上一次数据
		}
		else
		{
			Fader_ADC_Value_data[i] = Fader_ADC_Value_last[i]; //舍弃这一次采集数据
		}
	}
	
	//发送采集值
	Fader_ADC_Value_1 = Fader_ADC_Value_data[1];
	Fader_ADC_Value_2 = Fader_ADC_Value_data[2];
	Fader_ADC_Value_3 = Fader_ADC_Value_data[3];
	Fader_ADC_Value_4 = Fader_ADC_Value_data[4];
	Fader_ADC_Value_5 = Fader_ADC_Value_data[5];
	Fader_ADC_Value_6 = Fader_ADC_Value_data[6];
	Fader_ADC_Value_7 = Fader_ADC_Value_data[7];
	Fader_ADC_Value_8 = Fader_ADC_Value_data[8];
	Fader_ADC_Value_9 = Fader_ADC_Value_data[9];
	Fader_ADC_Value_10 = Fader_ADC_Value_data[10];
	Fader_ADC_Value_11 = Fader_ADC_Value_data[11];
	Fader_ADC_Value_12 = Fader_ADC_Value_data[12];
	Fader_ADC_Value_13 = Fader_ADC_Value_data[13];
	Fader_ADC_Value_14 = Fader_ADC_Value_data[14];
	Fader_ADC_Value_15 = Fader_ADC_Value_data[15];
	Fader_ADC_Value_16 = Fader_ADC_Value_data[16];
	Fader_ADC_Value_17 = Fader_ADC_Value_data[17];
	Fader_ADC_Value_18 = Fader_ADC_Value_data[18];
	Fader_ADC_Value_19 = Fader_ADC_Value_data[19];
	Fader_ADC_Value_20 = Fader_ADC_Value_data[20];
	Fader_ADC_Value_21 = Fader_ADC_Value_data[21];
	Fader_ADC_Value_22 = Fader_ADC_Value_data[22];
}


//判断编码器，判断A脚有变化，然后根据A脚的状态变化来和B脚对比，从而判断正反转
void ENCODER_SW_1(void)
{

///////////////////////////////////////////////////////////////////////////////////////////
	static u8 curr_encoder_b;
	static u8 Last_encoder_b;
	static u8 updata=0;
	
	if(!ES1_A)
	{
		curr_encoder_b = ES1_B;
		updata = 1;
		ENCODER_Value_1 = 0;
	}
	else
	{
		ENCODER_Value_1 = 0;
		if(updata)
		{
			updata = 0;
			if((ES1_B_Old==0)&&(curr_encoder_b==1))
			{
				ES1_Flag_zuo++;
				ES1_Flag_you = 0;
				if(ES1_Flag_zuo>=3)
				{
					ES1_Flag_zuo = 1;
				}
				if(ES1_Flag_zuo==1)
				{
					ENCODER_Value_1 = 1;
				}
				else if(ES1_Flag_zuo==2)
				{
					ENCODER_Value_1 = 2;
				}
			}
			else if((ES1_B_Old==1)&&(curr_encoder_b==0))
			{
				ES1_Flag_you++;
				ES1_Flag_zuo = 0;
				if(ES1_Flag_you>=3)
				{
					ES1_Flag_you = 1;
				}
				if(ES1_Flag_you==1)
				{
					ENCODER_Value_1 = 3;
				}
				else if(ES1_Flag_you==2)
				{
					ENCODER_Value_1 = 4;
				}
			}
		}
		ES1_B_Old = ES1_B;
	}
}




//编码器2
void ENCODER_SW_2(void)
{
	static u8 curr_encoder_2b;
	static u8 Last_encoder_2b;
	static u8 updata2=0;
	
	if(!ES2_A)
	{
		curr_encoder_2b = ES2_B;
		updata2 = 1;
		ENCODER_Value_2 = 0;
	}
	else
	{
		ENCODER_Value_2 = 0;
		if(updata2)
		{
			updata2 = 0;
			if((ES2_B_Old==0)&&(curr_encoder_2b==1))
			{
				ES2_Flag_zuo++;
				ES2_Flag_you = 0;
				if(ES2_Flag_zuo>=3)
				{
					ES2_Flag_zuo = 1;
				}
				if(ES2_Flag_zuo==1)
				{
					ENCODER_Value_2 = 1;
				}
				else if(ES2_Flag_zuo==2)
				{
					ENCODER_Value_2 = 2;
				}
			}
			else if((ES2_B_Old==1)&&(curr_encoder_2b==0))
			{
				ES2_Flag_you++;
				ES2_Flag_zuo = 0;
				if(ES2_Flag_you>=3)
				{
					ES2_Flag_you = 1;
				}
				if(ES2_Flag_you==1)
				{
					ENCODER_Value_2 = 3;
				}
				else if(ES2_Flag_you==2)
				{
					ENCODER_Value_2 = 4;
				}
			}
		}
		ES2_B_Old = ES2_B;
	}
}

//编码器3
void ENCODER_SW_3(void)
{
	static u8 curr_encoder_3b;
	static u8 Last_encoder_3b;
	static u8 updata3=0;
	
	if(!ES3_A)
	{
		curr_encoder_3b = ES3_B;
		updata3 = 1;
		ENCODER_Value_3 = 0;
	}
	else
	{
		ENCODER_Value_3 = 0;
		if(updata3)
		{
			updata3 = 0;
			if((ES3_B_Old==0)&&(curr_encoder_3b==1))
			{
				ES3_Flag_zuo++;
				ES3_Flag_you = 0;
				if(ES3_Flag_zuo>=3)
				{
					ES3_Flag_zuo = 1;
				}
				if(ES3_Flag_zuo==1)
				{
					ENCODER_Value_3 = 1;
				}
				else if(ES3_Flag_zuo==2)
				{
					ENCODER_Value_3 = 2;
				}
			}
			else if((ES3_B_Old==1)&&(curr_encoder_3b==0))
			{
				ES3_Flag_you++;
				ES3_Flag_zuo = 0;
				if(ES3_Flag_you>=3)
				{
					ES3_Flag_you = 1;
				}
				if(ES3_Flag_you==1)
				{
					ENCODER_Value_3 = 3;
				}
				else if(ES3_Flag_you==2)
				{
					ENCODER_Value_3 = 4;
				}
			}
		}
		ES3_B_Old = ES3_B;
	}
}

//编码器4
void ENCODER_SW_4(void)
{
	static u8 curr_encoder_4b;
	static u8 Last_encoder_4b;
	static u8 updata4=0;
	
	if(!ES4_A)
	{
		curr_encoder_4b = ES4_B;
		updata4 = 1;
		ENCODER_Value_4 = 0;
	}
	else
	{
		ENCODER_Value_3 = 0;
		if(updata4)
		{
			updata4 = 0;
			if((ES4_B_Old==0)&&(curr_encoder_4b==1))
			{
				ES4_Flag_zuo++;
				ES4_Flag_you = 0;
				if(ES4_Flag_zuo>=3)
				{
					ES4_Flag_zuo = 1;
				}
				if(ES4_Flag_zuo==1)
				{
					ENCODER_Value_4 = 1;
				}
				else if(ES4_Flag_zuo==2)
				{
					ENCODER_Value_4 = 2;
				}
			}
			else if((ES4_B_Old==1)&&(curr_encoder_4b==0))
			{
				ES4_Flag_you++;
				ES4_Flag_zuo = 0;
				if(ES4_Flag_you>=3)
				{
					ES4_Flag_you = 1;
				}
				if(ES4_Flag_you==1)
				{
					ENCODER_Value_4 = 3;
				}
				else if(ES4_Flag_you==2)
				{
					ENCODER_Value_4 = 4;
				}
			}
		}
		ES4_B_Old = ES4_B;
	}
}










void USART_Light(void)  //点灯程序
{
	//配置好第一个595数据:
	HC595[9] = (USART_RX_BUF[56]<<7)+(USART_RX_BUF[30]<<6)+(USART_RX_BUF[4]<<5)
			+(USART_RX_BUF[5]<<4)+(USART_RX_BUF[31]<<3)+(USART_RX_BUF[57]<<2)+
			(USART_RX_BUF[6]<<1)+USART_RX_BUF[32];
	//配置好第二个595数据:
	HC595[8] = (USART_RX_BUF[58]<<7)+(USART_RX_BUF[59]<<6)+(USART_RX_BUF[33]<<5)
			+(USART_RX_BUF[7]<<4)+(USART_RX_BUF[8]<<3)+(USART_RX_BUF[34]<<2)+
			(USART_RX_BUF[60]<<1)+USART_RX_BUF[61];
	
	//配置好第三个595数据:
	HC595[7] = (USART_RX_BUF[35]<<7)+(USART_RX_BUF[9]<<6)+(USART_RX_BUF[62]<<5)
			+(USART_RX_BUF[36]<<4)+(USART_RX_BUF[10]<<3)+(USART_RX_BUF[11]<<2)+
			(USART_RX_BUF[37]<<1)+USART_RX_BUF[63];
	
	//配置好第四个595数据:
	HC595[6] = (USART_RX_BUF[64]<<7)+(USART_RX_BUF[38]<<6)+(USART_RX_BUF[12]<<5)
			+(USART_RX_BUF[65]<<4)+(USART_RX_BUF[39]<<3)+(USART_RX_BUF[13]<<2)+
			(USART_RX_BUF[40]<<1)+USART_RX_BUF[66];
	
	//配置好第五个595数据:
	HC595[5] = (USART_RX_BUF[67]<<7)+(USART_RX_BUF[41]<<6)+(USART_RX_BUF[14]<<5)
			+(USART_RX_BUF[15]<<4)+(USART_RX_BUF[68]<<3)+(USART_RX_BUF[42]<<2)+
			(USART_RX_BUF[16]<<1)+USART_RX_BUF[69];
			
	//配置好第六个595数据:
	HC595[4] = (USART_RX_BUF[43]<<7)+(USART_RX_BUF[17]<<6)+(USART_RX_BUF[70]<<5)
			+(USART_RX_BUF[44]<<4)+(USART_RX_BUF[18]<<3)+(USART_RX_BUF[19]<<2)+
			(USART_RX_BUF[45]<<1)+USART_RX_BUF[71];
			
	//配置好第七个595数据:
	HC595[3] = (USART_RX_BUF[72]<<7)+(USART_RX_BUF[46]<<6)+(USART_RX_BUF[20]<<5)
			+(USART_RX_BUF[21]<<4)+(USART_RX_BUF[47]<<3)+(USART_RX_BUF[73]<<2)+
			(USART_RX_BUF[22]<<1)+USART_RX_BUF[48];
			
	//配置好第八个595数据:
	HC595[2] = (USART_RX_BUF[74]<<7)+(USART_RX_BUF[75]<<6)+(USART_RX_BUF[49]<<5)
			+(USART_RX_BUF[23]<<4)+(USART_RX_BUF[24]<<3)+(USART_RX_BUF[50]<<2)+
			(USART_RX_BUF[76]<<1)+USART_RX_BUF[77];
			
	//配置好第九个595数据:
	HC595[1] = (USART_RX_BUF[78]<<7)+(USART_RX_BUF[52]<<6)+(USART_RX_BUF[26]<<5)
			+(USART_RX_BUF[27]<<4)+(USART_RX_BUF[53]<<3)+(USART_RX_BUF[28]<<2)+
			(USART_RX_BUF[54]<<1)+USART_RX_BUF[79];
			
	//配置好第十个595数据:
	HC595[0] = (USART_RX_BUF[80]<<7)+(USART_RX_BUF[3]<<6)+(USART_RX_BUF[2]<<5)
			+(USART_RX_BUF[29]<<4)+(USART_RX_BUF[55]<<3)+(USART_RX_BUF[81]<<2)+
			(USART_RX_BUF[25]<<1)+USART_RX_BUF[51];
			
			
	LED_bright_one(HC595);  //点灯程序
}

//累加和校验
u8 USART_check(void)
{
	u8 i;
	u8 sum=0;  //累加和
	for(i=0;i<(SEND_BUF_SIZE-1);i++)
	{
		sum += SendBuff[i];
	}
	return sum;
	
}