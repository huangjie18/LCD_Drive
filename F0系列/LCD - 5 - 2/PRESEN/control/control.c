/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "control.h"
#include "DISPLAY_TFT.h"
#include "key.h"
#include "flash.h"

/* �궨�� --------------------------------------------------------------------*/
#define   interface_background     black 	 //���汳��
#define   zimo_backgroud           interface_background		 //��ģ����
#define   xuan_backgroud           blue		 //ѡ�б���

#define chushihua  1    //���г�ʼ��
/* ���� ----------------------------------------------------------------------*/
u8 buf_value[15];
//static ����������ȫ��
static uint16 sta=0x0001;
static uint8 putong = 0;//0��ͨ���棬1��������
uint8 kai_flag = 0;
uint8 symbol = 1;//1Ϊ������־��0Ϊ������־

uint8 mode_volume=0;//���������������

static uint8 i=0,mode=1,b=0; //i������ѡ�б�־;mode�����־λ;b�ӽ����־λ
static uint8 kai_guang=0; //״̬���ر�־λ

static uint8 number_1=0,number_3=0,number_4=0,
number_5=0,number_6=0,number_7=31;

static uint8 volume=50;  //����

static uint16 number_8=20,number_9=10,number_2=0;	
/*************����м����*************************/
uint16 sta_1=0x0000; //��Ž���ڶ������sta����
uint16 sta_2=0x0000; //��Ž�����������sta����
//���԰�number_1~number_9�����һ���ṹ��
/******************************
volume:����
number_1:����������Χ
number_2:ʪ��������Χ
number_3:��������Χ
number_4:�ռ��С��Χ
number_5:˥���̶ȷ�Χ
number_6:�ӳ�ʱ�䷶Χ
number_7:����˥����Χ
number_8:��Ƶ��ֹ��Χ
number_9:�������Ʒ�Χ
******************************/
//i��ѡ��״̬λ��sta����־��ͬģʽ�Ľ���2�ͽ���3��mode��ȷ������
void jiemian(void)
{
	uint16 temp=0;
	static uint16 count1=0;	
	delay_ms(100);
	temp = 	KEY_Scan();
 /*****************************�ػ�*****************************************/
	if(!key6)
	{
	  	count1++;
		if(count1>5)
		{
			count1=0;
			delay_ms(5);
			kai_flag = 0;  //�ػ���־λ�������ػ�����
			BK_OFF;
			POWER_OFF; //�ػ�
		}

	}
/*****************************�����Ӽ�����*****************************************/
	else if(temp==1)
	{
		putong = 1;
		if(volume<100)
		{
			volume++;
		}
		if(mode_volume==0)
		{
		 	display_pic(interface_background);  //����
			volume_sub(zimo_backgroud);
			showchar(32,list4_start,20,zimo_backgroud);
			showshuzi(40,list4_start,volume,zimo_backgroud);
			mode_volume = 1;
		}
		else if(mode_volume==1)
		{
			showshuzi(40,list4_start,volume,zimo_backgroud);
		}
	}
/*****************************������������*****************************************/
	else if(temp==2)
	{
		putong = 1;
		if(volume>0)
		{
			volume--;
		}
		if(mode_volume==0)
		{
		 	display_pic(interface_background);  //����
			volume_sub(zimo_backgroud);
			showchar(32,list4_start,20,zimo_backgroud);
			showshuzi(40,list4_start,volume,zimo_backgroud);
			mode_volume = 1;
		}
		else if(mode_volume==1)
		{
			showshuzi(40,list4_start,volume,zimo_backgroud);
		}
	}
/*****************************���ϼ�����*******************************************/
	else if(temp==3)	    //��ɫ��������ƶ�
	{
		if(putong==0)
		{
			shang();
		}	
	}

/***********************************���¼�����*************************************/
	else if(temp==4)  //��ɫ��������ƶ� 
	{
		if(putong==0)
		{
			xia();
		}
	}
/***************************ȷ����************************************************/
	else if(temp==5)	 //ȷ�ϼ�
	{
		if(putong==1)
		{
			putong = 0;
			mode_volume=0;
			if(mode==1)
			{
				xuanze_shang_1(&sta,&i);   //����֮ǰѡ�еĽ���1
			}
			else if(mode==2)
			{
			//Ϊʲô����û��Ӧ����Ϊ�ӽ����Ǹ���ǰһ��sta���жϵ�
			//�����ӽ����sta�Ѿ����ģ������޷�ʵ��
				sta = sta_1;  //�Ѵ洢��staֵȡ����������д������ж�ֵ	
				queding_2(); 
			}
			else
			{
			//����һ����ű�����Ϊ�˷�ֹ�˳���Ӱ��Խ����ˢ��
			//���û�����������2->3->�˳�->����->ȷ��ʱ�����ڴ�ʱsta��ֵ
			//��Ϊ2���棬mode=2;������2�����ʱ���ǿ�1�����sta���жϵģ������޷���ʾ
				sta = sta_2;
				queding_2();
			}
		}
		else
		{
			queding();
		}
	}
/*****************************�˳���***********************************************/
    else if(temp==6)	 //�˳���
	{
		if(putong==1)
		{
			putong = 0;
			mode_volume=0;
			if(mode==1)
			{
				xuanze_shang_1(&sta,&i);
			}
			else if(mode==2)
			{
			//Ϊʲô����û��Ӧ����Ϊ�ӽ����Ǹ���ǰһ��sta���жϵ�
			//�����ӽ����sta�Ѿ����ģ������޷�ʵ��
				sta = sta_1;  //�Ѵ洢��staֵȡ����������д������ж�ֵ	
				queding_2(); 
			}
			else
			{
				sta = sta_2;
				queding_2();
			}
		}
		else
		{
			tuichu();
		}
	}
	else
	{
		count1=0;
	}
}
/*************************������************************************/
void jiemian1(void)	   //������
{
	display_pic(interface_background);	//��ʾ����
	SetBkColor(0,xuan_backgroud);
	hunxiang(xuan_backgroud);
	huisheng(zimo_backgroud);
	biandiao(zimo_backgroud);
	dipingtisheng(zimo_backgroud);
	gaopingtisheng(zimo_backgroud);
	ganshikaiguang(zimo_backgroud);	
}

void jiemian_hun(uint16 *sta,uint8 *b)	//�����ӽ���
{
	display_pic(interface_background);  //����
	ganshengbili(zimo_backgroud);	//д�б�1Ϊ��������
	shishengbili(zimo_backgroud);	//д�б�2Ϊʪ�������ͱ���
	litishengkuangdu(zimo_backgroud);	  //д�б�3Ϊ������
	kongjiandaxiao(zimo_backgroud);	  //д�б�4Ϊ�ռ��С
	shuaijianchengdu(zimo_backgroud);	  //д�б�5λ˥���̶�
	switch_b_hun(sta,b);
}

void jiemian_hui(uint16 *sta,uint8 *b)	  //�����ӽ���
{
	display_pic(interface_background); //����
	yanchishijian(zimo_backgroud);	 //ѡ���ӳ�ʱ��
	huishengshuaijian(zimo_backgroud); //��ʾ����˥��
	zhidasheng(zimo_backgroud);		//��ʾֱ����ʹ��
	dipingjiezhi(zimo_backgroud);	//��ʾ��Ƶ
	switch_b_hui(sta,b);
}
/*****************************���ϼ�����*******************************************/
void shang(void)
{
	if(mode==1&&sta)
	{
		if(i==0)
		{
			i=5;
		}
		else
		{
			i--;
		}
		switch_i(&sta,&i);
	}
	else if(mode==2)
	{
		//����2 ������ѡ��
		if(sta&0x0001)
		{
			if(b==0)
			{
				b=4;
			}
			else
			{
				b--;
			}
			switch_b_hun(&sta,&b);
		}
		//����2 ������ѡ��
		else if(sta&0x0002)
		{
			if(b==0)
			{
				b=3;
			}
			else
			{
				b--;
			}
			switch_b_hui(&sta,&b);
		}
		//�޸���ʾ��״̬��kai_guang������־����״̬:1Ϊ��,0Ϊ��
		//0x01Ϊ��Ƶ������־λ;0x02Ϊ��Ƶ������־λ;0x04Ϊ��ʪ���ر�־λ
		else if((sta&0x0008)|(sta&0x0010)|(sta&0x0020))
		{
			if(sta==0x0008)	//�޸ĵ�Ƶ������״̬
			{
				if(kai_guang&0x01) //�жϵ�Ƶ������־λ�Ƿ�Ϊ��״̬
				{
					kai_guan(zimo_backgroud,2);//�޸�״̬Ϊ��
					kai_guang &= 0xfe;	//�����Ƶ������־λ
				}
				else
				{
					kai_guan(zimo_backgroud,0);	//�޸�״̬Ϊ��
					kai_guang |= 0x01;	 //��1��Ƶ������־λ
				}
			}
			else if(sta==0x0010) //�޸ĸ�Ƶ������״̬
			{
				if(kai_guang&0x02)	//�жϸ�Ƶ������־λ�Ƿ�Ϊ��״̬
				{
					kai_guan(zimo_backgroud,2);	 //�޸�״̬Ϊ��
					kai_guang &= 0xfd;	   //�����Ƶ������־λ
				}
				else
				{
					kai_guan(zimo_backgroud,0);
					kai_guang |= 0x02;	 //��1��Ƶ������־λ
				}
			}
			else if(sta==0x0020)  //�޸ĸ�ʪ���ص�״̬
			{
				if(kai_guang&0x04)
				{
					kai_guan(zimo_backgroud,2);	//�޸�״̬Ϊ��
					kai_guang &= 0xfb;	 //�����ʪ���ر�־λ
				}
				else
				{
					kai_guan(zimo_backgroud,0);	//�޸�״̬Ϊ��
					kai_guang |= 0x04;	 //��1��ʪ���ر�־λ
				}
			}
		}

	}
	else if(mode==3)
	{
//		//���ϼ����ܣ���������
			if(sta&0x0001) //�ж��Ƿ����ڻ�����ӽ���
			{
				if(sta==0x0041)	//�ж��Ƿ����ڸ�����������
				{
					if(number_1<200) //���������ķ�ΧΪ0~200%
					{
						number_1++;
						showshuzi(0,list4_start,number_1,zimo_backgroud);
					}
				}
				else if(sta==0x0081)//�ж��Ƿ�����ʪ����������
				{
					if(number_2<300)//��Χ��0~300%
					{
						number_2++;
						showshuzi(0,list4_start,number_2,zimo_backgroud);
					}
				}
				else if(sta==0x0101)//�ж��Ƿ���������������
				{
					if(number_3<100) //��Χ��0~100%
					{
						number_3++;
						showshuzi(0,list4_start,number_3,zimo_backgroud);
					}
				}
				else if(sta==0x0201) //�ж��Ƿ����ڿռ��С����
				{
					if(number_4<100) //��Χ��0~100%
					{
						number_4++;
						showshuzi(0,list4_start,number_4,zimo_backgroud);
					}
				}
				else if(sta==0x0401)//�ж��Ƿ�����˥���̶�
				{
					if(number_5<100) //��Χ��0~100%
					{
						number_5++;
						showshuzi(0,list4_start,number_5,zimo_backgroud);
					}
				}
			}
			else if(sta&0x0002)//�ж��Ƿ����ڻ����ӽ���
			{
				if(sta==0x0802)	//�ж��Ƿ������ӳ�ʱ�����
				{
					if(number_6<250) //��Χ��0~250ms
					{
						number_6++;
						showshuzi(0,list4_start,number_6,zimo_backgroud);
					}
				}
				else if(sta==0x1002) //�ж��Ƿ����ڻ���˥������
				{
					if(number_7>1)	//��Χ��-31~-1dB
					{
						number_7--;
						showshuzi(8,list4_start,number_7,zimo_backgroud);
						showchar(32,list4_start,13,zimo_backgroud);
					}
				}
				else if(sta==0x2002) //�ж��Ƿ�����ֱ����
				{
					if(kai_guang&0x08) //�жϴ�ʱʹ��״̬��־λ�Ƿ�Ϊ1
					{
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xf7;	//�����־λ
					}
					else
					{
						kai_guan(zimo_backgroud,0);	//�ڶ�������0ʱ,״̬Ϊ��;2ʱ��״̬Ϊ��
						kai_guang |= 0x08;	//��1��־λ
					}
				}
				else if(sta==0x4002) //�ж��Ƿ����ڵ�Ƶ��ֹ
				{
					if(number_8<20000) //��Χ��20~20000Hz
					{
						number_8++;
						showshuzi(0,list4_start,number_8,zimo_backgroud);
					}
				}
			}
			else if(sta&0x0004)
			{
				if(symbol==1)  //������ʾ
				{
					if(number_9>0)
					{
						number_9--;
						if(number_9==0)
						{
							symbol=1;
							showchar(0,list4_start,19,zimo_backgroud);
							showshuzi(8,list4_start,number_9,zimo_backgroud);
							showchar(40,list4_start,18,zimo_backgroud);
						}
						else
						{
							showchar(0,list4_start,17,zimo_backgroud);
							showshuzi(8,list4_start,number_9,zimo_backgroud);
							showchar(40,list4_start,18,zimo_backgroud);
						}
					}
				}
				else		   //������ʾ
				{
					if(number_9<1200)
					{
						number_9++;
					}
					showchar(0,list4_start,19,zimo_backgroud);
					showshuzi(8,list4_start,number_9,zimo_backgroud);
					showchar(40,list4_start,18,zimo_backgroud);
				}
			}
	}
}

/***********************************���¼�����*************************************/
void xia(void)
{
	//������
		if(mode==1&&sta)
		{
			i++;
			switch(i)
			{
				case 1:		   //ѡ�л���
					sta = 0x0002;	  
					SetBkColor(list2_start,xuan_backgroud);
					huisheng(xuan_backgroud);
					SetBkColor(list1_start,zimo_backgroud);
					hunxiang(zimo_backgroud);
					break;
				case 2:		  //ѡ�б��
					sta = 0x0004;
					SetBkColor(list3_start,xuan_backgroud);
					biandiao(xuan_backgroud);
					SetBkColor(list2_start,zimo_backgroud);
					huisheng(zimo_backgroud);
					break;
				case 3:		  //ѡ�е�Ƶ����
					sta = 0x0008;
					SetBkColor(list4_start,xuan_backgroud);
					dipingtisheng(xuan_backgroud);
					SetBkColor(list3_start,zimo_backgroud);
					biandiao(zimo_backgroud);
					break;
				case 4:		 //ѡ�и�Ƶ����
					sta = 0x0010;
					SetBkColor(list5_start,xuan_backgroud);
					gaopingtisheng(xuan_backgroud);
					SetBkColor(list4_start,zimo_backgroud);
					dipingtisheng(zimo_backgroud);
					break;
				case 5:		 //ѡ�и�ʪ����
					sta = 0x0020;
					SetBkColor(list6_start,xuan_backgroud);
					ganshikaiguang(xuan_backgroud);
					SetBkColor(list5_start,zimo_backgroud);
					gaopingtisheng(zimo_backgroud);
					break;
				case 6:		 //ѡ�л���
					sta = 0x0001;
					SetBkColor(list1_start,xuan_backgroud);
					hunxiang(xuan_backgroud);
					SetBkColor(list6_start,zimo_backgroud);
					ganshikaiguang(zimo_backgroud);
					i=0;
					break;
			}
		}
		//����2 ������ѡ��
		if(mode==2)
		{
			b++;
			//������ѡ��
			if(sta&0x0001)
			{
				switch(b)
				{
					case 1:
						 //ѡ��ʪ������ 
						sta = 0x0081;
						SetBkColor(list2_start,xuan_backgroud);
						shishengbili(xuan_backgroud);
						SetBkColor(list1_start,zimo_backgroud);
						ganshengbili(zimo_backgroud);
						
						break;
					case 2:
						 //ѡ��������
						sta = 0x0101;
						SetBkColor(list3_start,xuan_backgroud);
						litishengkuangdu(xuan_backgroud);
						SetBkColor(list2_start,zimo_backgroud);
						shishengbili(zimo_backgroud);
						break;
					case 3:
						//ѡ�пռ��С
						sta = 0x0201;
						SetBkColor(list4_start,xuan_backgroud);
						kongjiandaxiao(xuan_backgroud);
						SetBkColor(list3_start,zimo_backgroud);
						litishengkuangdu(zimo_backgroud);
						break;
					case 4:
						//ѡ��˥���̶�
						sta = 0x0401;
						SetBkColor(list5_start,xuan_backgroud);
						shuaijianchengdu(xuan_backgroud);
						SetBkColor(list4_start,zimo_backgroud);
						kongjiandaxiao(zimo_backgroud);
						break;
					case 5:
						 //ѡ�и�������
						sta = 0x0041;
						SetBkColor(list1_start,xuan_backgroud);
						ganshengbili(xuan_backgroud);
						SetBkColor(list5_start,zimo_backgroud);
						shuaijianchengdu(zimo_backgroud);
						b=0;
						break;
						
				}
			}
			//����2 ������ѡ��
			else if(sta&0x0002)
			{
				switch(b)
				{
					case 1:
						 //ѡ�л���˥��
						sta = 0x1002; 
						SetBkColor(list2_start,xuan_backgroud);
						huishengshuaijian(xuan_backgroud);
						SetBkColor(list1_start,zimo_backgroud);
						yanchishijian(zimo_backgroud);
						
						break;
					case 2:
						 //ѡ��ֱ����
						sta = 0x2002;
						SetBkColor(list3_start,xuan_backgroud);
						zhidasheng(xuan_backgroud);
						SetBkColor(list2_start,zimo_backgroud);
						huishengshuaijian(zimo_backgroud);
						break;
					case 3:
						//ѡ�е�Ƶ��ֹ
						sta = 0x4002;
						SetBkColor(list4_start,xuan_backgroud);
						dipingjiezhi(xuan_backgroud);
						SetBkColor(list3_start,zimo_backgroud);
						zhidasheng(zimo_backgroud);
						break;
					case 4:
						//ѡ���ӳ�ʱ��
						sta = 0x0802;
						SetBkColor(list1_start,xuan_backgroud);
						yanchishijian(xuan_backgroud);
						SetBkColor(list4_start,zimo_backgroud);
						dipingjiezhi(zimo_backgroud);
						b=0;
						break;
						
				}
			}
		//�ж��Ƿ����ڵ�Ƶ��������Ƶ��������ʪ�����ӽ���
			else if((sta&0x0008)|(sta&0x0010)|(sta&0x0020))
			{
				if(sta==0x0008)//�ж��Ƿ����ڵ�Ƶ�����Ŀ���״̬
				{
					if(kai_guang&0x01) //�жϵ�Ƶ�������ر�־λ
					{	
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xfe; //�����־λ
					}
					else
					{
						kai_guan(zimo_backgroud,0);
						kai_guang |= 0x01; //��1��־λ
					}
				}
				else if(sta==0x0010) //�ж��Ƿ����ڸ�Ƶ�����Ŀ���״̬
				{
					if(kai_guang&0x02) //�жϸ�Ƶ�������ر�־λ
					{	
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xfd; //�����־λ
					}
					else
					{
						kai_guan(zimo_backgroud,0);
						kai_guang |= 0x02;	//��1��־λ
					}
				}
				else if(sta==0x0020) //�ж��Ƿ����ڸ�ʪ���صĿ���״̬
				{
					if(kai_guang&0x04)	//�жϱ�־λ
					{	
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xfb; //�����־λ
					}
					else
					{
						kai_guan(zimo_backgroud,0);
						kai_guang |= 0x04; //��1��־λ
					}
				}
			}
		}
		else if(mode==3)
		{
		//���¼����ܣ���������ʵ��
			if(sta&0x0001) //�ж��Ƿ����ڻ���ĵ�������
			{
				if(sta==0x0041)	 //�ж��Ƿ����ڸ��������ĵ�������
				{
					if(number_1>0)
					{
						number_1--;
						showshuzi(0,list4_start,number_1,zimo_backgroud);
					}	
				}
				else if(sta==0x0081) //�ж��Ƿ�����ʪ�������ĵ�������
				{
					if(number_2>0)
					{
						number_2--;
						showshuzi(0,list4_start,number_2,zimo_backgroud);
					}
				}
				else if(sta==0x0101)//�ж��Ƿ������������ĵ�������
				{
					if(number_3>0)
					{
						number_3--;
						showshuzi(0,list4_start,number_3,zimo_backgroud);
					}
				}
				else if(sta==0x0201) //�ռ��С
				{
					if(number_4>0)
					{
						number_4--;
						showshuzi(0,list4_start,number_4,zimo_backgroud);
					}
				}
				else if(sta==0x0401) //˥���̶�
				{
					if(number_5>0)
					{
						number_5--;
						showshuzi(0,list4_start,number_5,zimo_backgroud);
					}
				}
			}
			//������������ʵ��
			else if(sta&0x0002)
			{
				if(sta==0x0802)//�ж��Ƿ������ӳ�ʱ��ĵ�������
				{
					if(number_6>0)
					{
						number_6--;
						showshuzi(0,list4_start,number_6,zimo_backgroud);
					}	
				}
				else if(sta==0x1002)  //����˥��
				{
					if(number_7<31)
					{
						number_7++;
						showshuzi(8,list4_start,number_7,zimo_backgroud);
						showchar(32,list4_start,13,zimo_backgroud);
					}
				}
				else if(sta==0x2002)  //ֱ����
				{
					if(kai_guang&0x08)
					{
						kai_guan(zimo_backgroud,2);
						kai_guang &= 0xf7;	
					}
					else 
					{
						kai_guan(zimo_backgroud,0);	//�ڶ�������0ʱ,״̬Ϊ��;2ʱ��״̬Ϊ��
						kai_guang |= 0x08;
					}
				}
				else if(sta==0x4002) //��Ƶ��ֹ
				{
					if(number_8>20)
					{
						number_8--;
						qingqu(8,list4_start,zimo_backgroud);
						showshuzi(0,list4_start,number_8,zimo_backgroud);

					}
				}	
			}
		//�����������ʵ��
			else if(sta&0x0004)
			{
				if(symbol==1)  //����
				{
				tack:
					if(number_9<1200)
					{
						number_9++;
						showchar(0,list4_start,17,zimo_backgroud);
						showshuzi(8,list4_start,number_9,zimo_backgroud);
						showchar(40,list4_start,18,zimo_backgroud);
					}
				}
				else		   //����
				{
					if(number_9>=0)
					{
						if(number_9==0)	 //��֤0���������������ϼ���ȷ����
						{
							symbol = 0;
							goto tack;
						}
						else
						{
							number_9--;
							showchar(0,list4_start,19,zimo_backgroud);
							showshuzi(8,list4_start,number_9,zimo_backgroud);
							showchar(40,list4_start,18,zimo_backgroud);
						}
					}
						
				}
			}
		}
}
/***************************ȷ����************************************************/
void queding(void)
{
	//���ж���ʲô������������Ƶ�����У�����ȡ����������sta��mode
	//�������ͨ�������ֱ��ִ�г���
		if(mode<4)
		{
			if(mode<2)
			{
				mode++;
			}
			//��Ϊ��Ƶ��������Ƶ��������ʪ����û�е������棬������ӿ�������
			else if((sta&0x07c1)|(sta&0x7802)|(sta&0x8004))
			{
				if(mode<3)	  //��mode=2ʱ�ɵڶ���������������
				{
					mode++;
				}
				else	   //��mode=3ʱ���ص�һ����
				{
					mode=1;
					sta = sta_1;
					b=0;
					xuanze_shang_1(&sta,&i);
					mode_volume=0;
	
				}
			}
			else
			{
				mode=1;
				sta = sta_1;
				b=0;
				xuanze_shang_1(&sta,&i);
				mode_volume=0;
			}
			
		}
		queding_2();
}

/*****************************�˳���***********************************************/
void tuichu(void)
{
	//�����жϽ����־mode��������ʾͼ��
	if(mode==1)
	{
	}
	else
	{
		if(mode>1)
		{
			mode--;
		}
		if(mode==1)
		{
			sta = sta_1;
			b=0;
			xuanze_shang_1(&sta,&i);
			mode_volume=0;	
		}
		else if(mode==2)
		{
			sta = sta_2;
			if(sta&0x0001) //�����ӽ���
			{
				display_pic(interface_background);  //����
				ganshengbili(zimo_backgroud);	//д�б�1Ϊ��������
				shishengbili(zimo_backgroud);	//д�б�2Ϊʪ�������ͱ���
				litishengkuangdu(zimo_backgroud);	  //д�б�3Ϊ������
				kongjiandaxiao(zimo_backgroud);	  //д�б�4Ϊ�ռ��С
				shuaijianchengdu(zimo_backgroud);  //д�б�5λ˥���̶�
				switch_b_hun(&sta,&b);
			}
			else if(sta&0x0002)	//�����ӽ���
			{	
				display_pic(interface_background); //����
				yanchishijian(zimo_backgroud);	 //ѡ���ӳ�ʱ��
				huishengshuaijian(zimo_backgroud); //��ʾ����˥��
				zhidasheng(zimo_backgroud);		//��ʾֱ����ʹ��
				dipingjiezhi(zimo_backgroud);	//��ʾ��Ƶ
				switch_b_hui(&sta,&b);
			}
			else if(sta&0x0004)	//����ӽ���
			{
				display_pic(interface_background);				
				SetBkColor(0,xuan_backgroud);
				yindiaokongzhi(xuan_backgroud);	
			}	
		}	
	}
	
}

void queding_2(void)	 //����2�ͽ���3����ʾ
{
	if(mode==2)	 //����2  ��ѡ����ʾʵ��
	{
		sta_1 = sta;  //��sta��������������������ķ�����ͨ������ж�ֵ
		switch(sta)
		{
		case 0x0001:
			jiemian_hun(&sta,&b); //�����ӽ�����ʾ
			break;
		case 0x0002:
			jiemian_hui(&sta,&b); //�����ӽ�����ʾ
			break;
		case 0x0004:   //����ӽ�����ʾ
			display_pic(interface_background);
			SetBkColor(0,xuan_backgroud);
			yindiaokongzhi(xuan_backgroud);
			break;
		case 0x0008:  //��Ƶ����
			display_pic(interface_background);
			zhuangtaixianshi(zimo_backgroud);
			if(kai_guang&0x01)
			{
				kai_guan(zimo_backgroud,0);
			}
			else
			{
				kai_guan(zimo_backgroud,2);	//�ڶ�������0ʱ,״̬Ϊ��;2ʱ��״̬Ϊ��
			}
			break;
		case 0x0010: //��Ƶ����
			display_pic(interface_background);
			zhuangtaixianshi(zimo_backgroud);
			if(kai_guang&0x02)
			{
				kai_guan(zimo_backgroud,0);
			}
			else
			{
				kai_guan(zimo_backgroud,2);
			}
			break;
		case 0x0020:  //��ʪ����
			display_pic(interface_background);
			zhuangtaixianshi(zimo_backgroud);
			if(kai_guang&0x04)
			{
				kai_guan(zimo_backgroud,0);
			}
			else
			{
				kai_guan(zimo_backgroud,2);
			}
			break;
		}
	}
	//����������ʾʵ��
	else if(mode==3)
	{
		sta_2 = sta; //��sta��������������������ķ�����ͨ������ж�ֵ
		display_pic(interface_background);//����
		if(sta&0x0001)	//�����������
		{
			if(sta==0x0041)	  //���������ӽ���ĵ���������ʾ
			{
				showshuzi(0,list4_start,number_1,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0081) //ʪ������
			{
				showshuzi(0,list4_start,number_2,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0101) //������
			{
				showshuzi(0,list4_start,number_3,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0201) //�ռ��С
			{
				showshuzi(0,list4_start,number_4,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
			else if(sta==0x0401)  //˥���̶�
			{
				showshuzi(0,list4_start,number_5,zimo_backgroud);
				showchar(32,list4_start,10,zimo_backgroud);
			}
		}
		//���������������ʾʵ��
		else if(sta&0x0002)
		{
			if(sta==0x0802)	//�ӳ�ʱ��
			{
				showshuzi(0,list4_start,number_6,zimo_backgroud);
				showchar(32,list4_start,11,zimo_backgroud);
				showchar(40,list4_start,12,zimo_backgroud);
			}
			else if(sta==0x1002) //����˥��
			{
				if(number_7==0)
				{
					number_7=1;
				}
				showchar(0,list4_start,17,zimo_backgroud);
				showshuzi(8,list4_start,number_7,zimo_backgroud);
				showchar(32,list4_start,13,zimo_backgroud);
				showchar(40,list4_start,14,zimo_backgroud);
			}
			else if(sta==0x2002) //ֱ����
			{
				zhuangtaixianshi(zimo_backgroud);
				if(kai_guang&0x08)
				{
					kai_guan(zimo_backgroud,0);
				}
				else
				{
					kai_guan(zimo_backgroud,2);	//�ڶ�������0ʱ,״̬Ϊ��;2ʱ��״̬Ϊ��
				}
			}
			else if(sta==0x4002) //��Ƶ��ֹ
			{
				showshuzi(0,list4_start,number_8,zimo_backgroud);
				showchar(40,list4_start,15,zimo_backgroud);
				showchar(48,list4_start,16,zimo_backgroud);
			}
		}
		//�������������ʾʵ��
		else if(sta&0x0004)
		{
			if(symbol==1)
			{
				showchar(0,list4_start,17,zimo_backgroud);
				showshuzi(8,list4_start,number_9,zimo_backgroud);
				showchar(40,list4_start,18,zimo_backgroud);
			}
			else
			{
				showchar(0,list4_start,19,zimo_backgroud);
				showshuzi(8,list4_start,number_9,zimo_backgroud);
				showchar(40,list4_start,18,zimo_backgroud);
			}
		}
	}
}
//*********************************
//*********��������****************
//*********************************
void kaiji(void)
{
	unsigned char count=0;
	unsigned char xuan=2;
	u8 buf_value_1[35]; 
	while(!kai_flag)	           //����ѭ���ж�
	{
	 	if(!key6)                      //���̰�����
		{
			count++;
			if(count>5)
			{
				kai_flag=1;
				POWER_ON;
			}
		}
		else
		{
			count = 0;
		}
		delay_ms(500);
	} //��������ѭ��
	
	
	//������ɺ���Ҫ���õ��Ĳ�����ʼ��
	sta=0x0001;
	putong = 0;
	
	mode_volume = 0;
	i = 0;
	mode = 1;
	b = 0;
	sta_1 = 0x0000;
	FLASH_ReadNWord((uint16_t *)buf_value_1,FLASH_SAVE_ADDR,15);
	//��ȡ�����eprom�е�����
	if(chushihua)
	{
//		while(xuan--)						   //��ȡ���Σ���Ϊ��ȡһ��ʱ���������д���
//		{									   //�����Ż������⣬���ԼӶ�һ��ѭ��
			symbol = buf_value_1[14];	 //���ű�־��ȡ
			kai_guang = buf_value_1[13];	 //���ر�־��ȡ
			volume = buf_value_1[0];	 //�������ݶ�ȡ
			number_1=buf_value_1[1];	 //�����������ݶ�ȡ
			number_3=buf_value_1[2];	 //���������ݶ�ȡ
			number_4=buf_value_1[3];	 //�ռ��С
			number_5=buf_value_1[4];	 //˥���̶�
			number_6=buf_value_1[5];	 //�ӳ�ʱ��
			number_7=buf_value_1[6];	 //����˥��

			number_8=buf_value_1[7];	 //��Ƶ��ֹ
			number_8 = (number_8<<8) | buf_value_1[8];

			number_9=buf_value_1[9];	 //��������
			number_9 = (number_9<<8) | buf_value_1[10];

			number_2=buf_value_1[11];	 //ʪ������
			number_2 = (number_2<<8) | buf_value_1[12];
//		}
		
	}
			
}
/****************************����������ʾ���ܺ���********************************/
void xuanze_shang_1(uint16 *sta,uint8 *i)
{
	display_pic(interface_background);	//��ʾ��ɫ
	hunxiang(zimo_backgroud);
	huisheng(zimo_backgroud);
	biandiao(zimo_backgroud);
	dipingtisheng(zimo_backgroud);
	gaopingtisheng(zimo_backgroud);
	ganshikaiguang(zimo_backgroud);
	switch_i(sta,i);

}

//���������л�����
void switch_i(uint16 *sta,uint8 *i)
{
	switch(*i)
	{
		case 0:
			*sta = 0x0001;	 //ѡ�л���
			SetBkColor(list2_start,zimo_backgroud);
			huisheng(zimo_backgroud);
			SetBkColor(list1_start,xuan_backgroud);
			hunxiang(xuan_backgroud);
			*i=0;
			break;
		case 1:
			*sta = 0x0002;	 //ѡ�л���
			SetBkColor(list3_start,zimo_backgroud);
			biandiao(zimo_backgroud);
			SetBkColor(list2_start,xuan_backgroud);
			huisheng(xuan_backgroud);
			break;
		case 2:
			*sta = 0x0004;	//ѡ�б��
			SetBkColor(list4_start,zimo_backgroud);
			dipingtisheng(zimo_backgroud);
			SetBkColor(list3_start,xuan_backgroud);
			biandiao(xuan_backgroud);
			break;
		case 3:
			*sta = 0x0008;	//ѡ�е�Ƶ����
			SetBkColor(list5_start,zimo_backgroud);
			gaopingtisheng(zimo_backgroud);
			SetBkColor(list4_start,xuan_backgroud);
			dipingtisheng(xuan_backgroud);
			break;
		case 4:
			*sta = 0x0010;  //ѡ�и�Ƶ����
			SetBkColor(list6_start,zimo_backgroud);
			ganshikaiguang(zimo_backgroud);
			SetBkColor(list5_start,xuan_backgroud);
			gaopingtisheng(xuan_backgroud);
			break;
		case 5:
			*sta = 0x0020;   //ѡ�и�ʪ����
			SetBkColor(list1_start,zimo_backgroud);
			hunxiang(zimo_backgroud);
			SetBkColor(list6_start,xuan_backgroud);
			ganshikaiguang(xuan_backgroud);
			break;
	}
}
	
//�Ի����ӽ����л�����
void switch_b_hun(uint16 *sta,uint8 *b)
{
	switch(*b)
	{
		case 0:
			//ѡ�и�������
			*sta = 0x0041;
			SetBkColor(list2_start,zimo_backgroud);
			shishengbili(zimo_backgroud);
			SetBkColor(list1_start,xuan_backgroud);
			ganshengbili(xuan_backgroud);
			*b=0;
			break;
		case 1:
			//ѡ��ʪ������
			*sta = 0x0081;
			SetBkColor(list3_start,zimo_backgroud);
			litishengkuangdu(zimo_backgroud);
			SetBkColor(list2_start,xuan_backgroud);
			shishengbili(xuan_backgroud);
			break;
		case 2:
			//ѡ��������
			*sta = 0x0101;
			SetBkColor(list4_start,zimo_backgroud);
			kongjiandaxiao(zimo_backgroud);
			SetBkColor(list3_start,xuan_backgroud);
			litishengkuangdu(xuan_backgroud);
			break;
		case 3:
			//ѡ�пռ��С
			*sta = 0x0201;
			SetBkColor(list5_start,zimo_backgroud);
			shuaijianchengdu(zimo_backgroud);
			SetBkColor(list4_start,xuan_backgroud);
			kongjiandaxiao(xuan_backgroud);
			break;
		case 4:
			//ѡ��˥���̶�
			*sta = 0x0401;
			SetBkColor(list1_start,zimo_backgroud);
			ganshengbili(zimo_backgroud);
			SetBkColor(list5_start,xuan_backgroud);
			shuaijianchengdu(xuan_backgroud);
			break;
	}
}

void switch_b_hui(uint16 *sta,uint8 *b)
{
	switch(*b)
	{
		case 0:
			//ѡ���ӳ�ʱ��
			*sta = 0x0802;
			SetBkColor(list2_start,zimo_backgroud);
			huishengshuaijian(zimo_backgroud);
			SetBkColor(list1_start,xuan_backgroud);
			yanchishijian(xuan_backgroud);
			*b=0;
			break;
		case 1:
			//ѡ�л���˥������
			*sta = 0x1002;
			SetBkColor(list3_start,zimo_backgroud);
			zhidasheng(zimo_backgroud);
			SetBkColor(list2_start,xuan_backgroud);
			huishengshuaijian(xuan_backgroud);
			break;
		case 2:
			//ѡ��ֱ����ʹ��
			*sta = 0x2002;
			SetBkColor(list4_start,zimo_backgroud);	
			dipingjiezhi(zimo_backgroud);
			SetBkColor(list3_start,xuan_backgroud);
			zhidasheng(xuan_backgroud);
			break;
		case 3:
			//ѡ�е�Ƶ��ֹƵ��
			*sta = 0x4002;
			SetBkColor(list1_start,zimo_backgroud);
			yanchishijian(zimo_backgroud);
			SetBkColor(list4_start,xuan_backgroud);
			dipingjiezhi(xuan_backgroud);
			break;
	}
}


/************************************************
�������� �� Write_Flash
��    �� �� ���ݱ���
��    �� �� ��
�� �� ֵ �� ��
��    �� �� huangjiehua
*************************************************/
void Write_Flash(void)
{
	u8 data_buf[15];
	data_buf[0] = volume;
	data_buf[1] = number_1;
	data_buf[2] = number_3;
	data_buf[3] = number_4;
	data_buf[4] = number_5;
	data_buf[5] = number_6;
	data_buf[6] = number_7;
	data_buf[7] = number_8>>8;
	data_buf[8] = number_8&0xff;
	data_buf[9] = number_9>>8;
	data_buf[10] = number_9&0xff;
	data_buf[11] = number_2>>8;
	data_buf[12] = number_2&0xff;
	data_buf[13] = kai_guang;
	data_buf[14] = symbol;
//	data_buf[0] = 48;
//	data_buf[1] = 49;
//	data_buf[2] = 50;
//	data_buf[3] = 55;
//	data_buf[4] = 59;
//	data_buf[5] = number_6;
//	data_buf[6] = number_7;
//	data_buf[7] = number_8>>8;
//	data_buf[8] = number_8&0xff;
//	data_buf[9] = number_9>>8;
//	data_buf[10] = number_9&0xff;
//	data_buf[11] = number_2>>8;
//	data_buf[12] = number_2&0xff;
//	data_buf[13] = kai_guang;
//	data_buf[14] = symbol;
	FLASH_WriteNWord((uint16_t *)data_buf,FLASH_SAVE_ADDR,15);
}

