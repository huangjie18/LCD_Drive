#ifndef __PARA_H
#define __PARA_H
#include "sys.h"
#include "lcd.h"
#include "mode.h"
#define parazimo  16



/**************������ѡ���*********************/
void ganshengbili(uint16 bk);
void shishengbili(uint16 bk);
void litishengkuangdu(uint16 bk);
void kongjiandaxiao(uint16 bk);
void shuaijianchengdu(uint16 bk);

/**************������ѡ���********************/
void yanchishijian(uint16 bk);
void huishengshuaijian(uint16 bk);
void zhidasheng(uint16 bk);
void dipingjiezhi(uint16 bk);

/**************������ѡ���********************/
void yindiaokongzhi(uint16 bk);

/*****************ʣ��ѡ���*****************************/
void zhuangtaixianshi(uint16 bk);
void kai_guan(uint16 bk,uint8 c);

#endif

