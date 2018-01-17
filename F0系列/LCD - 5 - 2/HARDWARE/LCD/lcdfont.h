#ifndef __LCDFONT_H
#define __LCDFONT_H

//因为这里是定义变量，并不是声明变量，所以只能包含一次，否则会出现重复定义
extern const unsigned char PIC3[95][16];          //横向扫描的8*16数组
extern const unsigned char asc2_1206[95][12];     //纵向扫描的6*12数组
extern const unsigned char asc2_1608[95][16];     //纵向扫描的8*16数组
extern const unsigned char asc2_2412[95][36];     //纵向扫描的12*24数组
extern const unsigned char asc2_1608_chu[95][36]; //纵向扫描的8*16粗体数组
extern const unsigned char asc2_M[24];            //纵向扫描的24*16 M数组
extern const unsigned char asc2_juhao[14];         //纵向扫描7*16 句号数组
extern const unsigned char shuzizimo[21][16];
extern const unsigned char asc2_1616_CN[96][16];      //混响字模
#endif

