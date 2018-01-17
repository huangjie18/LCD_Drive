#ifndef __DISPLAY_TFT_H
#define __DISPLAY_TFT_H 
#include "sys.h"

#include "delay.h"
#include "stdlib.h"
#include "math.h"//��Ϊ����ֵ����
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




void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);//��������
void LCD_DrawPoint(u16 x,u16 y);//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2); //������
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color); //�����ɫ
void Draw_Circle(u16 x0,u16 y0,u8 r);    //��Բ
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color); //��ʵ��Բ

void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);   //���ٻ���


//��ָ��λ�û�һ��ָ����С��Բ
void gui_draw_arc(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,u16 r,u16 color,u8 mode);

//��Բ�Ǿ���
void gui_draw_arcrectangle(u16 x,u16 y,u16 width,u16 height,u8 r,u8 mode,u16 downcolor);

//����ֱ��
void gui_draw_vline(u16 x0,u16 y0,u16 len,u16 color);

//��ˮƽ��
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color);

//������
void gui_fill_rectangle(u16 x0,u16 y0,u16 width,u16 height,u16 color);

//��8��(Bresenham�㷨)
void gui_draw_circle8(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,int a,int b,u16 color);


//�������ڻ���
void gui_draw_expoint(u16 sx,u16 sy,u16 ex,u16 ey,u16 x,u16 y,u16 color);

//��һ�����
void gui_draw_bigpoint(u16 x0,u16 y0,u16 color);

//��һ����ɫƽ�����ɵ�����һ����ɫ
void gui_smooth_color(u32 srgb,u32 ergb,u16*cbuf,u16 len);

//��һ��ƽ�����ɵĲ�ɫ����(����)
void gui_draw_smooth_rectangle(u16 x,u16 y,u16 width,u16 height,u32 srgb,u32 ergb);

//д�����ַ�
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);

//д�ַ���
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p);


void Fill_Fast_Rec(uint16_t X_Start , uint16_t Y_Start, uint16_t x_width, uint16_t y_hight,uint16_t color);


void Colorful_Music_DisplayA(u16 x, u16 y, u16 height, u16 weight);

void LCD_ShowChar_CN(u16 x,u16 y,u8 num,u8 size,u8 mode); //д����

void gundong_1(u16 x,u16 y,u8 num,u8 size,u8 mode);  //��̬������ʾ
#endif





