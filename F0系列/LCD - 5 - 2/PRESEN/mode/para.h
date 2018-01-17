#ifndef __PARA_H
#define __PARA_H
#include "sys.h"
#include "lcd.h"
#include "mode.h"
#define parazimo  16



/**************混响子选项函数*********************/
void ganshengbili(uint16 bk);
void shishengbili(uint16 bk);
void litishengkuangdu(uint16 bk);
void kongjiandaxiao(uint16 bk);
void shuaijianchengdu(uint16 bk);

/**************回声子选项函数********************/
void yanchishijian(uint16 bk);
void huishengshuaijian(uint16 bk);
void zhidasheng(uint16 bk);
void dipingjiezhi(uint16 bk);

/**************音调子选项函数********************/
void yindiaokongzhi(uint16 bk);

/*****************剩余选项函数*****************************/
void zhuangtaixianshi(uint16 bk);
void kai_guan(uint16 bk,uint8 c);

#endif

