#ifndef __KEY_H
#define __KEY_H
#include "sys.h"


#define  key1  PEin(9)
#define  key2  PEin(8)
#define  key3  PEin(7)
#define  key4  PEin(10)
#define  key5  PEin(11)
#define  key6  PEin(12)
#define  key7  PEin(13)
#define  key8  PEin(14)
#define  key9  PEin(15)

#define  key10  PCout(13)
#define  key11  PCout(14)
#define  key12  PCout(15)
#define  key13  PFout(0)
#define  key14  PFout(1)
#define  key15  PFout(2)
#define  key16  PFout(3)
#define  key17  PFout(4)
#define  key18  PFout(5)



void KEY_Init(void);  //按键初始化
u8 KEY_Scan(void);    //按键扫描

#endif



