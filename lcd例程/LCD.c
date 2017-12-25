#include "lcd.h"
#include "fonts.h"
static vu16 TextColor = 0x0000, BackColor = 0xFFFF;
void Delay(int n)
{
	unsigned int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < 3000; ++j);
}
//LCD 寄存器初始化
#define lcm_mdelay(X) Delay(X)
void lcd_reg_init( void)
{
	LCD_WriteReg(0x0000, 0x0001);
	lcm_mdelay(1000); //at least 100ms
	LCD_WriteReg(0x0001, 0x0000); // set SS and SM bit
//LCD_CtrlWrite(0x0003,0x1030); // set GRAM write
	direction and BGR = 1.
	                    LCD_WriteReg(0x0010, 0x1790);
	LCD_WriteReg(0x0060, 0x2700);
	LCD_WriteReg(0x0061, 0x0001);
	LCD_WriteReg(0x0046, 0x0002);
	LCD_WriteReg(0x0013, 0x8010);
	LCD_WriteReg(0x0012, 0x80fe);
	LCD_WriteReg(0x0002, 0x0500);
	LCD_WriteReg(0x0003, 0x1030);
	LCD_WriteReg(0x0030, 0x0303);
	LCD_WriteReg(0x0031, 0x0303);
	LCD_WriteReg(0x0032, 0x0303);
	LCD_WriteReg(0x0033, 0x0300);
	LCD_WriteReg(0x0034, 0x0003);
	LCD_WriteReg(0x0035, 0x0303);
	LCD_WriteReg(0x0036, 0x0014);
	LCD_WriteReg(0x0037, 0x0303);
	LCD_WriteReg(0x0038, 0x0303);
	LCD_WriteReg(0x0039, 0x0303);
	LCD_WriteReg(0x003a, 0x0300);
	LCD_WriteReg(0x003b, 0x0003);
	LCD_WriteReg(0x003c, 0x0303);
	LCD_WriteReg(0x003d, 0x1400);
	LCD_WriteReg(0x0092, 0x0200);
	LCD_WriteReg(0x0093, 0x0303); LCD_WriteReg(0x0090, 0x080d);
	LCD_WriteReg(0x0003, 0x1018); // set GRAMwrite direction
	and BGR = 1.
	          LCD_WriteReg(0x0007, 0x0173);
}
//LCD 初始化
void STM3210B_LCD_Init(void)
{
	vu16 dummy = 0;
	LCD_CtrlLinesConfig();
	lcd_reg_init();
	dummy = LCD_ReadReg(0);
}
// 设置文字颜色
void LCD_SetTextColor(vu16 Color)
{
	TextColor = Color;
}
// 设置背景色
void LCD_SetBackColor(vu16 Color)
{
	BackColor = Color;
}
// 清除行， Line:0-9
void LCD_ClearLine(u8 Line)
{
	LCD_DisplayStringLine(Line, " ");
}
//LCD 清屏
void LCD_Clear(u16 Color)
{
	u32 index = 0;
	LCD_SetCursor(0x00, 0x0000);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for (index = 0; index < 76800; index++)
	{
		LCD_WriteRAM(Color);
	}
}
//LCD 光标设置
void LCD_SetCursor(u8 Xpos, u16 Ypos)
{
	LCD_WriteReg(R32, Xpos); LCD_WriteReg(R33, Ypos);
}
// 在 LCD指定位置上显示
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c)
{
	u32 index = 0, i = 0;
	u8 Xaddress = 0;
	Xaddress = Xpos;
	LCD_SetCursor(Xaddress, Ypos);
	for (index = 0; index < 24; index++)
	{
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		for (i = 0; i < 16; i++)
		{
			if ((c[index] & (1 << i)) == 0x00)
			{
				LCD_WriteRAM(BackColor);
			}
			else
			{
				LCD_WriteRAM(TextColor);
			}
		}
		Xaddress++;
		LCD_SetCursor(Xaddress, Ypos);
	}
}
// 显示一个字符
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii)
{
	Ascii -= 32;
	LCD_DrawChar(Line, Column, &ASCII_Table[Ascii * 24]);
}
//LCD 显示字符串
void LCD_DisplayStringLine(u8 Line, u8 *ptr)
{
	u32 i = 0;
	u16 refcolumn = 319;//319;
	while ((*ptr != 0) && (i < 20)) // 20
	{
		/* Display one character on LCD */
		LCD_DisplayChar(Line, refcolumn, *ptr);
		/* Decrement the column position by 16 */
		refcolumn -= 16;/* Point on the next character */
		ptr++;
		/* Increment the character counter */
		i++;
	}
}
// 设置 LCD显示模式
void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Height, u16
                          Width)
{
	if (Xpos >= Height)
	{
		LCD_WriteReg(R80, (Xpos - Height + 1));
	}
	else
	{
		LCD_WriteReg(R80, 0);
	}
	LCD_WriteReg(R81, Xpos);
	if (Ypos >= Width)
	{
		LCD_WriteReg(R82, (Ypos - Width + 1));
	}
	else
	{
		LCD_WriteReg(R82, 0);
	}
	/* Vertical GRAM End Address */
	LCD_WriteReg(R83, Ypos);
	LCD_SetCursor(Xpos, Ypos);
}
//LCD 窗口模式配置
void LCD_WindowModeDisable(void)
{
	LCD_SetDisplayWindow(239, 0x13F, 240, 320);
	LCD_WriteReg(R3, 0x1018);
}
//LCD 画线
void LCD_DrawLine(u8 Xpos, u16 Ypos, u16 Length, u8
                  Direction)
{
	u32 i = 0;
	LCD_SetCursor(Xpos, Ypos);
	if (Direction == Horizontal) {
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		for (i = 0; i < Length; i++)
		{
			LCD_WriteRAM(TextColor);
		}
	}
	else
	{
		for (i = 0; i < Length; i++)
		{
			LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
			LCD_WriteRAM(TextColor);
			Xpos++;
			LCD_SetCursor(Xpos, Ypos);
		}
	}
}
//LCD 画矩形
void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Height, u16 Width)
{
	LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
	LCD_DrawLine((Xpos + Height), Ypos, Width, Horizontal);
	LCD_DrawLine(Xpos, Ypos, Height, Vertical);
	LCD_DrawLine(Xpos, (Ypos - Width + 1), Height, Vertical);
}
//LCD 画圆
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius)
{
	s32 D;
	u32 CurX;
	u32 CurY;
	D = 3 - (Radius << 1);
	CurX = 0;
	CurY = Radius;
	while (CurX <= CurY)
	{
		LCD_SetCursor(Xpos + CurX, Ypos + CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_WriteRAM(TextColor);
		LCD_SetCursor(Xpos + CurX, Ypos - CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */LCD_WriteRAM(TextColor);
		LCD_SetCursor(Xpos - CurX, Ypos + CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_WriteRAM(TextColor);
		LCD_SetCursor(Xpos - CurX, Ypos - CurY);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_WriteRAM(TextColor);
		LCD_SetCursor(Xpos + CurY, Ypos + CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_WriteRAM(TextColor);
		LCD_SetCursor(Xpos + CurY, Ypos - CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_WriteRAM(TextColor);
		LCD_SetCursor(Xpos - CurY, Ypos + CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_WriteRAM(TextColor);
		LCD_SetCursor(Xpos - CurY, Ypos - CurX);
		LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
		LCD_WriteRAM(TextColor);
		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}
// 显示灰阶图片（Monocolor Picture ）
void LCD_DrawMonoPict(uc32 *Pict)
{
	u32 index = 0, i = 0;
	LCD_SetCursor(0, 319);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	for (index = 0; index < 2400; index++)
	{
		for (i = 0; i < 32; i++)
		{
			if ((Pict[index] & (1 << i)) == 0x00)
			{
				LCD_WriteRAM(BackColor);
			}
			else
			{
				LCD_WriteRAM(TextColor);
			}
		}
	}
}
// 显示位图（BMP Picture ）
void LCD_WriteBMP(u32 BmpAddress)
{
	u32 index = 0, size = 0;
	size = *(vu16 *) (BmpAddress + 2);
	size |= (*(vu16 *) (BmpAddress + 4)) << 16;
	index = *(vu16 *) (BmpAddress + 10);
	index |= (*(vu16 *) (BmpAddress + 12)) << 16;
	size = (size - index) / 2;
	BmpAddress += index;
	LCD_WriteReg(R3, 0x1008);
	LCD_WriteRAM_Prepare();
	for (index = 0; index < size; index++)
	{
		LCD_WriteRAM(*(vu16 *)BmpAddress);
		BmpAddress += 2;
	}
	LCD_WriteReg(R3, 0x1018);
}
// 写 LCD寄存器
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{
	GPIOB->BRR = 0x0200; //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100; //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOC->ODR = LCD_Reg;
//GPIO_Write(LCD_DataPort,LCD_Reg);
	GPIOB->BRR = 0x0020; //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100; //LCD_RS_HIGH();
	GPIOC->ODR = LCD_RegValue;
//GPIO_Write(LCD_DataPort,LCD_RegValue);
	GPIOB->BRR = 0x0020; //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100; //LCD_RS_HIGH();
}// 读 LCD寄存器
u16 LCD_ReadReg(u8 LCD_Reg)
{
	u16 temp;
	GPIOB->BRR = 0x0200; //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100; //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOC->ODR = LCD_Reg;
//GPIO_Write(LCD_DataPort,LCD_Reg);
	GPIOB->BRR = 0x0020; //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100; //LCD_RS_HIGH();
	LCD_BusIn();
	GPIOB->BRR = 0x0400; //LCD_NRD_LOW();
	temp = GPIOC->IDR;
//temp=GPIO_ReadInputData(LCD_DataPort);
	GPIOB->BSRR = 0x0400; //LCD_NRD_HIGH();
	LCD_BusOut();
	GPIOB->BSRR = 0x0200; //LCD_NCS_HIGH();
	return temp;
}
// 写 LCD-RAM预处理
void LCD_WriteRAM_Prepare(void)
{
	GPIOB->BRR = 0x0200; //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100; //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOC->ODR = R34; //GPIO_Write(LCD_DataPort,R34);
	GPIOB->BRR = 0x0020; //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100; //LCD_RS_HIGH();
	GPIOB->BSRR = 0x0200; //LCD_NCS_HIGH();
}
// 写 LCD-RAM
void LCD_WriteRAM(u16 RGB_Code)
{
	GPIOB->BRR = 0x0200; //LCD_NCS_LOW();
	GPIOB->BSRR = 0x0100; //LCD_RS_HIGH();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOC->ODR = RGB_Code;
//GPIO_Write(LCD_DataPort,RGB_Code);
	GPIOB->BRR = 0x0020; //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100; //LCD_RS_HIGH();GPIOB->BSRR = 0x0200; //LCD_NCS_HIGH();
}
// 读取 LCD-RAM
u16 LCD_ReadRAM(void)
{
	u16 temp;
	GPIOB->BRR = 0x0200; //LCD_NCS_LOW();
	GPIOB->BRR = 0x0100; //LCD_RS_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOC->ODR = R34; //GPIO_Write(LCD_DataPort,R34);
	GPIOB->BRR = 0x0020; //LCD_NWR_LOW();
	GPIOB->BSRR = 0x0020; //LCD_NWR_HIGH();
	GPIOB->BSRR = 0x0100; //LCD_RS_HIGH();
	LCD_BusIn();
	GPIOB->BRR = 0x0400; //LCD_NRD_LOW();
	temp = GPIOC->IDR;
//temp=GPIO_ReadInputData(LCD_DataPort);
	GPIOB->BSRR = 0x0400; //LCD_NRD_HIGH();
	LCD_BusOut();
	GPIOB->BSRR = 0x0200; //LCD_NCS_HIGH();
	return temp;
}
//LCD 上电
void LCD_PowerOn(void)
{
	LCD_WriteReg(R16, 0x0000);
	LCD_WriteReg(R17, 0x0000);
	LCD_WriteReg(R18, 0x0000);
	LCD_WriteReg(R19, 0x0000);
	Delay(20);
	LCD_WriteReg(R16, 0x17B0);
	LCD_WriteReg(R17, 0x0137);
	Delay(5);
	LCD_WriteReg(R18, 0x0139);
	Delay(5);
	LCD_WriteReg(R19, 0x1d00);
	LCD_WriteReg(R41, 0x0013);
	Delay(5);
	LCD_WriteReg(R7, 0x0173);
}
// 开启 LCD显示
void LCD_DisplayOn(void)
{
	LCD_WriteReg(R7, 0x0173);
}
// 关闭 LCD显示
void LCD_DisplayOff(void)
{
	LCD_WriteReg(R7, 0x0);
}
//LCD 控制引脚配置
void LCD_CtrlLinesConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
	                       RCC_APB2Periph_GPIOC , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_5 |
	                              GPIO_Pin_8 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	LCD_BusOut();
	GPIOB->BSRR |= 0x0620;
}
// 数据总线输入配置
void LCD_BusIn(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
// 数据总线输出配置
void LCD_BusOut(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
//
void LCD_DrawPicture(const u8* picture)
{
	int index;
	LCD_SetCursor(0x00, 0x0000);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */for (index = 0; index < 76800; index++)
	{
		LCD_WriteRAM(picture[2 * index + 1] << 8 | picture[2 * index]);
	}
}
== == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
#ifndef __LCD_H
#define __LCD_H
#include "stm32f10x.h"
/* LCD Registers */
#define R0 0x00
#define R1 0x01
#define R2 0x02
#define R3 0x03
#define R4 0x04
#define R5 0x05
#define R6 0x06
#define R7 0x07
#define R8 0x08
#define R9 0x09
#define R10 0x0A
#define R12 0x0C
#define R13 0x0D
#define R14 0x0E
#define R15 0x0F
#define R16 0x10
#define R17 0x11
#define R18 0x12
#define R19 0x13
#define R20 0x14
#define R21 0x15
#define R22 0x16
#define R23 0x17
#define R24 0x18
#define R25 0x19
#define R26 0x1A
#define R27 0x1B
#define R28 0x1C
#define R29 0x1D
#define R30 0x1E
#define R31 0x1F
#define R32 0x20
#define R33 0x21#define R34 0x22
#define R36 0x24
#define R37 0x25
#define R40 0x28
#define R41 0x29
#define R43 0x2B
#define R45 0x2D
#define R48 0x30
#define R49 0x31
#define R50 0x32
#define R51 0x33
#define R52 0x34
#define R53 0x35
#define R54 0x36
#define R55 0x37
#define R56 0x38
#define R57 0x39
#define R59 0x3B
#define R60 0x3C
#define R61 0x3D
#define R62 0x3E
#define R63 0x3F
#define R64 0x40
#define R65 0x41
#define R66 0x42
#define R67 0x43
#define R68 0x44
#define R69 0x45
#define R70 0x46
#define R71 0x47
#define R72 0x48
#define R73 0x49
#define R74 0x4A
#define R75 0x4B
#define R76 0x4C
#define R77 0x4D
#define R78 0x4E
#define R79 0x4F
#define R80 0x50
#define R81 0x51
#define R82 0x52
#define R83 0x53
#define R96 0x60
#define R97 0x61#define R106 0x6A
#define R118 0x76
#define R128 0x80
#define R129 0x81
#define R130 0x82
#define R131 0x83
#define R132 0x84
#define R133 0x85
#define R134 0x86
#define R135 0x87
#define R136 0x88
#define R137 0x89
#define R139 0x8B
#define R140 0x8C
#define R141 0x8D
#define R143 0x8F
#define R144 0x90
#define R145 0x91
#define R146 0x92
#define R147 0x93
#define R148 0x94
#define R149 0x95
#define R150 0x96
#define R151 0x97
#define R152 0x98
#define R153 0x99
#define R154 0x9A
#define R157 0x9D
#define R192 0xC0
#define R193 0xC1
#define R227 0xE3
#define R229 0xE5
#define R231 0xE7
#define R239 0xEF
/* LCD Control pins */
//#define CtrlPin_NCS GPIO_Pin_9 /* PB.9 */
//#define CtrlPin_RS GPIO_Pin_8 /* PB.8 */
//#define CtrlPin_NWR GPIO_Pin_5 /* Pb.5 */
//#define CtrlPin_NRD GPIO_Pin_10 /* Pb.10 */
/* LCD color */
#define White 0xFFFF
#define Black 0x0000#define Grey 0xF7DE
#define Blue 0x001F
#define Blue2 0x051F
#define Red 0xF800
#define Magenta 0xF81F
#define Green 0x07E0
#define Cyan 0x7FFF
#define Yellow 0xFFE0
#define Line0 0
#define Line1 24
#define Line2 48
#define Line3 72
#define Line4 96
#define Line5 120
#define Line6 144
#define Line7 168
#define Line8 192
#define Line9 216
#define Horizontal 0x00
#define Vertical 0x01
/*----- High layer function -----*/
void STM3210B_LCD_Init(void);
void LCD_SetTextColor(vu16 Color);
void LCD_SetBackColor(vu16 Color);
void LCD_ClearLine(u8 Line);
void LCD_Clear(u16 Color);
void LCD_SetCursor(u8 Xpos, u16 Ypos);
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c);
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii);
void LCD_DisplayStringLine(u8 Line, u8 *ptr);
void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Height, u16
                          Width);
void LCD_WindowModeDisable(void);
void LCD_DrawLine(u8 Xpos, u16 Ypos, u16 Length, u8
                  Direction);
void LCD_DrawRect(u8Xpos, u16 Ypos, u8 Height, u16 Width);
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius);
void LCD_DrawMonoPict(uc32 *Pict);
void LCD_WriteBMP(u32 BmpAddress);
void LCD_DrawBMP(u32 BmpAddress);/*----- Medium layer function -----*/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
u16 LCD_ReadRAM(void);
void LCD_PowerOn(void);
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
/*----- Low layer function -----*/
void LCD_CtrlLinesConfig(void);
void LCD_FSMCConfig(void);
void LCD_BusIn(void);
void LCD_BusOut(void);
#endif /* __LCD_H */