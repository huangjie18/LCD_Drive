#include "mode.h"
#include "modefont.h"
#define  x   0		   //������ʾ��x���
#define  y   0		   //������ʾ��y���
  
//uint8 xend,yend;
/**********************���ú���*********************************************/
//num:��ʾ���ٸ���
void diaoyong(uint8 list_start,uint8 list_end,uint8 num,uint16 bk,const uint8 (*p)[16])
{
	uint8 i,c=0;
	for(i=0;i<num;i++)
	{
		LCD_qu(x+(16*i),y+list_start,(16*i)+15,list_end);
		xianshi(&c,p,32,bk);
		c++;
	}
}
/*******************��ģ��ʾ����***************************/
void xianshi(uint8 *c,const uint8 (*p)[16],uint8 num,uint16 bk)
{
	uint8 temp;
	uint8 b,i=0,a;	 //iҪ��ֵΪ�㣬����i��ֵ�ڶ�����8�������ʼΪ��
	for(b=0;b<num;b++)
	{
		if(i>15)
		{
			i=0;			  //i���������е�����
			(*c)++;			 //c���������е�����
			temp = (*(*(p+*c)+i));	//��ȡ��ģ�����Ӧ����
		}
		else
		{
			temp = *(*(p+*c)+i);
		}
		for(a=0;a<8;a++)
		{
			if(temp&(0x01<<a))
			{
				LCD_WR_data(fontcolor>>8,fontcolor&0x00ff);	//д������ɫ
			}
			else
			{
				LCD_WR_data(bk>>8,bk);//д����ɫ
			}
		}
		i++;
	}
}

#ifdef   hengping     //�����Ƿ������������������������������
#if(zimo==16)		  //������ģ��СΪ16����ʾ����,ֻ���ṩһ��ģ��
//���º�������ȥ��i��������ʡ�ڴ�ռ�
//�б�1��ʾ����
void  hunxiang(uint16 bk)
{
	diaoyong(list1_start,list1_end,2,bk,hunxian);
}
//�б�2��ʾ����
void huisheng(uint16 bk)
{
	diaoyong(list2_start,list2_end,2,bk,huishen);
}
//�б�3��ʾ���
void biandiao(uint16 bk)
{
	diaoyong(list3_start,list3_end,2,bk,biandia);
}
//�б�4��ʾ��Ƶ����
void dipingtisheng(uint16 bk)
{
	diaoyong(list4_start,list4_end,4,bk,diping);
}
//�б�5��ʾ��Ƶ����
void gaopingtisheng(uint16 bk)
{
	diaoyong(list5_start,list5_end,4,bk,gaoping);
}
//�б�6��ʾ��ʪ����
void ganshikaiguang(uint16 bk)
{
	diaoyong(list6_start,list6_end,4,bk,ganshi);
}


#else
void  hunxiang(void)      //������ģΪ40����ʾ����
{
	uint8 a,i=0,c=0;
	uint8 temp,b;
	LCD_qu(x,y,xend+40-1,yend+40-1);
	xianshi(&c,hunxian,200);

} //д�������֣���Ϊ40+40=80����64
#endif
#endif

#ifdef  shuping		  //������������
#if(zimo==16)		  //������ģ��СΪ16����ʾ����
void  hunxiang(void)
{
	uint8 c=0;
	LCD_qu(x,y,xend+16-1,yend+16-1);
	xianshi(&c,hunxian,32);
	LCD_qu(x,y+16,xend+15,yend+31);
	c++;
	xianshi(&c,hunxian,32);
}
#else
void  hunxiang(void)	 //������ģ��СΪ40����ʾ����
{
	uint8 c=0;		 
	LCD_qu(x,y,xend+39,yend+39);//����ʾ������һ���ֲ���ʾ����
	xianshi(&c,hunxian,200);	//��ʾ��һ����ģ����
	LCD_qu(x,y+40,xend+39,yend+79);	//������һ����ģ��ʾ����
	c++;				 //��ȡ��һ����ģ����
	xianshi(&c,hunxian,200); //��ʾ��һ����ģ
}
//ֻ���޸Ĵ���xianshi��������ģ�����num�������Լ�����
void huisheng(void)
{
	uint8 c=0;
	LCD_qu(x+0,y+0,xend+39,yend+39);
	xianshi(&c,huishen,200);
	LCD_qu(x+0,y+40,xend+39,yend+79);
	c++;
	xianshi(&c,huishen,200);
}

void  biandiao(void)
{
	uint8 c=0;
	LCD_qu(x+0,y+0,xend+39,yend+39);
	xianshi(&c,biandia,200);
	LCD_qu(x+0,y+40,xend+39,yend+79);
	c++;
	xianshi(&c,biandia,200);
}

void  dipingtisheng(void)
{
	uint8 c=0;
	LCD_qu(x+0,0,xend+31,31);
	xianshi(&c,diping,128);
	LCD_qu(x+0,32,xend+31,63);
	c++;
	xianshi(&c,diping,128);
	LCD_qu(x+0,64,xend+31,95);
	c++;
	xianshi(&c,diping,128);
	LCD_qu(x+0,96,xend+31,127);
	c++;
	xianshi(&c,diping,128);
}

void  gaopingtisheng(void)
{
	uint8 c=0;
	LCD_qu(x+0,0,xend+31,31);
	xianshi(&c,gaoping,128);
	LCD_qu(x+0,32,xend+31,63);
	c++;
	xianshi(&c,gaoping,128);
	LCD_qu(x+0,64,xend+31,95);
	c++;
	xianshi(&c,gaoping,128);
	LCD_qu(x+0,96,xend+31,127);
	c++;
	xianshi(&c,gaoping,128);
}


#endif
#endif

