#include "para.h"
#include "parafont.h"


#if(parazimo==16)
//���º�������ȥ��i������LCD_qu��ֱ�Ӷ������ֲ��ñ�����ʡ�ڴ�ռ�
//�����Ǹ�ѡ�����ʾ����
/************************����ѡ��*******************************************/
void ganshengbili(uint16 bk)
{
	diaoyong(list1_start,list1_end,4,bk,gansheng);
}
//�б�2��ʾʪ������
void shishengbili(uint16 bk)
{
	diaoyong(list2_start,list2_end,4,bk,shisheng);
}
//�б�3��ʾ���������
void litishengkuangdu(uint16 bk)
{
	diaoyong(list3_start,list3_end,3,bk,litisheng);
}
//�б�4��ʾ�ռ��С
void kongjiandaxiao(uint16 bk)
{
	diaoyong(list4_start,list4_end,4,bk,kongjian);
}
//�б�5��ʾ˥���̶�
void shuaijianchengdu(uint16 bk)
{
	diaoyong(list5_start,list5_end,4,bk,shuaijian);
}	

/***********************����ѡ��*****************************/
void yanchishijian(uint16 bk)   //�ӳ�ʱ��
{
	diaoyong(list1_start,list1_end,4,bk,yanchi);
}

void huishengshuaijian(uint16 bk) //����˥������
{
	diaoyong(list2_start,list2_end,4,bk,huishengshuai);
}

void zhidasheng(uint16 bk)		  //ֱ����ʹ��
{
	diaoyong(list3_start,list3_end,3,bk,zhida);
}

void dipingjiezhi(uint16 bk)	  //��Ƶ��ֹ
{
	diaoyong(list4_start,list4_end,4,bk,dipingjie);
}


/*********************���ѡ��***********************************/
void yindiaokongzhi(uint16 bk)
{
	diaoyong(list1_start,list1_end,4,bk,yindiaokong);
}

/********************��Ƶ����ѡ��******************************/
void zhuangtaixianshi(uint16 bk)
{
	diaoyong(list4_start,list4_end,3,bk,zhuangtai);
}

void kai_guan(uint16 bk,uint8 c)   //c�����в����ڲ�����ֱ�Ӹ�Ĭ��ֵ��
{
	//c=0����;c=2�����
    LCD_qu((16*3),list4_start,(16*3)+15,list4_end);
	xianshi(&c,kaiguang,32,bk);
}
#endif
