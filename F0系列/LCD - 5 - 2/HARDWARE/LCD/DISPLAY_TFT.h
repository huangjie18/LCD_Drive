#ifndef __DISPLAY_TFT_H
#define __DISPLAY_TFT_H 
#include "sys.h"

#include "delay.h"
#include "stdlib.h"
#include "math.h"//作为绝对值运算
#include "string.h"


#define WHITE   0xFFFF
#define BLACK   0x0000
#define GREEN   0x07E0
#define RED     0xF800
#define BLUE    0x001F
#define GRAY    0x528A
#define YELLOW  0XFFE0
#define ORINGE  0XF4C4
#define GRAY1   0XC615

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern u16 BACK_COLOR; 
extern u16 POINT_COLOR; 
extern u16 colortbl[100];




void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);//画任意线
void LCD_DrawPoint(u16 x,u16 y);//画点
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2); //画矩形
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color); //填充颜色
void Draw_Circle(u16 x0,u16 y0,u8 r);    //画圆
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color); //画实心圆

void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);   //快速画点


//在指定位置画一个指定大小的圆
void gui_draw_arc(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,u16 r,u16 color,u8 mode);

//画圆角矩形
void gui_draw_arcrectangle(u16 x,u16 y,u16 width,u16 height,u8 r,u8 mode,u16 downcolor);

//画垂直线
void gui_draw_vline(u16 x0,u16 y0,u16 len,u16 color);

//画水平线
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color);

//填充矩形
void gui_fill_rectangle(u16 x0,u16 y0,u16 width,u16 height,u16 color);

//画8点(Bresenham算法)
void gui_draw_circle8(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,int a,int b,u16 color);


//在区域内画点
void gui_draw_expoint(u16 sx,u16 sy,u16 ex,u16 ey,u16 x,u16 y,u16 color);

//画一个大点
void gui_draw_bigpoint(u16 x0,u16 y0,u16 color);

//将一种颜色平滑过渡到另外一种颜色
void gui_smooth_color(u32 srgb,u32 ergb,u16*cbuf,u16 len);

//画一条平滑过渡的彩色矩形(或线)
void gui_draw_smooth_rectangle(u16 x,u16 y,u16 width,u16 height,u32 srgb,u32 ergb);

//写单个字符
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);

//写字符串
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);


void Fill_Fast_Rec(uint16_t X_Start , uint16_t Y_Start, uint16_t x_width, uint16_t y_hight,uint16_t color);


void Colorful_Music_DisplayA(u16 x, u16 y, u16 height, u16 weight);

void LCD_ShowChar_CN(u16 x,u16 y,u8 num,u8 size,u8 mode); //写汉字

void gundong_1(u16 x,u16 y,u8 num,u8 size,u8 mode);  //动态滚动显示
#endif





