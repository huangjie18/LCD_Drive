#include "led.h"
#include "stdlib.h"
#include "delay.h"
u16 LCD_id = 0;
/*
文件说明：该LCD驱动适合正点原子F1和F4开发板使用
文件使用：适合8线并口传输，只需要修改LCD_Init初始驱动
          接线按照lcd.h里的定义接
 */
void LCD_Writ_Bus(char data_1, char data_2)  //并行数据写入函数
{
    //下面是由于芯片引脚和lcd的数据传输引脚相反，所以需要把传输数据颠倒顺序再传输
    u16 i, j, addr2 = 0, addr3 = 0, temp2, temp3;
    for (i = 0; i <= 7; i++)
    {
        addr2 = addr2 << 1;
        addr2 = addr2 | (data_1 & 1);
        data_1 = data_1 >> 1;
    }
    for (j = 0; j <= 7; j++)
    {
        addr3 = addr3 << 1;
        addr3 = addr3 | (data_2 & 1);
        data_2 = data_2 >> 1;
    }
    addr2 = addr2 << 8; //因为用的芯片引脚是高八位，所以左移8位
    addr3 = addr3 << 8;

    CS = 0;
    WR = 1;



#if defined STM32F40_41xxx
    WR = 0;  //写操作使能,MCU告诉LCD我要控制DB数据线了
    GPIOE->ODR = addr2;
    WR = 1;  //写操作失能，LCD开始把数据线的数据写进自己的内存
    CS = 1;

    CS = 0;  //对LCD使能
    WR = 1;


    WR = 0;
    GPIOE->ODR = addr3;
    WR = 1;
    CS = 1;   //关闭片选使能

#elif defined STM32F10X_HD
    GPIOE->BSRR = temp2 << 16;
    GPIOE->BSRR = addr2;
    WR = 0;  //写操作使能
    WR = 1;  //写操作失能
    CS = 1;

    CS = 0;
    WR = 1;
    temp3 = (GPIOE->IDR & 0xff00);
    GPIOE->BSRR = temp3 << 16;
    GPIOE->BSRR = addr3;
    WR = 0;
    WR = 1;
    CS = 1;   //关闭片选使能
#endif
}

void LCD_WR_DATA8(char VH, char VL) //发送数据-8位参数
{
    LCD_RS = 1;
    LCD_Writ_Bus(VH, VL);
}
/***************************写数据**********************************************/
void LCD_WR_DATA(int da)
{
    LCD_RS = 1;
    LCD_Writ_Bus(da >> 8, da);
}
/***************************写命令**************************************************/
void LCD_WR_REG(int reg)
{
    LCD_RS = 0;
    LCD_Writ_Bus(reg >> 8, reg);
}
/****************************写命令和数据**********************************************/
void LCD_WR_REG_DATA(int reg, int da)
{
    LCD_WR_REG(reg);
    LCD_WR_DATA(da);
}

void LCD_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;//重新定义一个结构体

    //开启时钟线，stm32有，单片机没有
#ifdef STM32F40_41xxx   //判断芯片类型
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD |
                           RCC_AHB1Periph_GPIOE, ENABLE);
    //对结构体的变量进行初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


#elif defined  STM32F10X_HD
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
                           RCC_APB2Periph_GPIOE, ENABLE);
    //对结构体的变量进行初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器
#endif
}

void LCD_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;//重新定义一个结构体

    //开启时钟线，stm32有，单片机没有
#ifdef STM32F40_41xxx   //判断芯片类型
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD |
                           RCC_AHB1Periph_GPIOE, ENABLE);
    //对结构体的变量进行初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                  GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


#elif defined  STM32F10X_HD
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
                           RCC_APB2Periph_GPIOE, ENABLE);
    //对结构体的变量进行初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器
#endif

}
/****************初始化命令*******************/
void LCD_Init(u16 LCD_ID)
{

    GPIO_InitTypeDef GPIO_InitStructure;//重新定义一个结构体

    //开启时钟线，stm32有，单片机没有
#ifdef STM32F40_41xxx   //判断芯片类型
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD |
                           RCC_AHB1Periph_GPIOE, ENABLE);
    //对结构体的变量进行初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器
#elif defined  STM32F10X_HD
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD |
                           RCC_APB2Periph_GPIOE, ENABLE);
    //对结构体的变量进行初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                  | GPIO_Pin_11 | GPIO_Pin_12 |
                                  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_Init(GPIOD, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //把结构体的成员变量赋给对应寄存器
#endif
    RST = 0;
    delay_ms(100);
    RST = 1;
    delay_ms(10);


    LCD_CS = 1;
    LCD_RD = 1;
    LCD_WR = 1;
    delay_ms(5);
    LCD_CS = 0; //打开片选使能

    //下面是初始代码，不需要知道全部细节，一般由厂家提供
    //需要修改时要参考数据手册,初始化程序不一样显示效果也不一样
    if(LCD_ID == 9326)
    {
        LCD_WR_REG_DATA(0x0702,
                        0x3008);// Set internal timing, don?ˉt change this value
        LCD_WR_REG_DATA(0x0705,
                        0x0036);// Set internal timing, don?ˉt change this value
        LCD_WR_REG_DATA(0x070B,
                        0x1213);// Set internal timing, don?ˉt change this value
        LCD_WR_REG_DATA(0x0001, 0x0100); // set SS and SM bit
        LCD_WR_REG_DATA(0x0002, 0x0100); // set 1 line inversion
        //  LCD_WR_REG_DATA(0x0003, 0x1008); // set GRAM write direction and BGR=1. //1030
        LCD_WR_REG_DATA(0x0003, 0x0030);
        LCD_WR_REG_DATA(0x0008, 0x0202); // set the back porch and front porch
        LCD_WR_REG_DATA(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
        LCD_WR_REG_DATA(0x000C, 0x0000); // RGB interface setting
        LCD_WR_REG_DATA(0x000F, 0x0000); // RGB interface polarity
        //*************Power On sequence ****************//
        LCD_WR_REG_DATA(0x0100, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
        LCD_WR_REG_DATA(0x0102, 0x0000); // VREG1OUT voltage
        LCD_WR_REG_DATA(0x0103, 0x0000); // VDV[4:0] for VCOM amplitude
        delay_ms(200); // Dis-charge capacitor power voltage
        LCD_WR_REG_DATA(0x0100, 0x1190); // SAP, BT[3:0], AP, DSTB, SLP, STB
        LCD_WR_REG_DATA(0x0101, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
        delay_ms(50); // Delay 50ms
        LCD_WR_REG_DATA(0x0102, 0x001D); // VREG1OUT voltage
        delay_ms(50); // Delay 50ms
        LCD_WR_REG_DATA(0x0103, 0x2000); // VDV[4:0] for VCOM amplitude
        LCD_WR_REG_DATA(0x0281, 0x0001); // VCM[5:0] for VCOMH
        LCD_WR_REG_DATA(0x020b, 0x0000);
        delay_ms(50);
        LCD_WR_REG_DATA(0x0200, 0x0000); // GRAM horizontal Address
        LCD_WR_REG_DATA(0x0201, 0x0000); // GRAM Vertical Address
        // ----------- Adjust the Gamma Curve ----------//
        LCD_WR_REG_DATA(0x0300, 0x0000);
        LCD_WR_REG_DATA(0x0301, 0x0202);
        LCD_WR_REG_DATA(0x0302, 0x0202);
        LCD_WR_REG_DATA(0x0305, 0x0202);
        LCD_WR_REG_DATA(0x0306, 0x0202);
        LCD_WR_REG_DATA(0x0307, 0x0202);
        LCD_WR_REG_DATA(0x0308, 0x0202);
        LCD_WR_REG_DATA(0x0309, 0x0202);
        LCD_WR_REG_DATA(0x030C, 0x0202);
        LCD_WR_REG_DATA(0x030D, 0x0202);
        //------------------ Set GRAM area ---------------//
        LCD_WR_REG_DATA(0x0210, 0x0000); // Horizontal  Start Address
        LCD_WR_REG_DATA(0x0211, 0x00EF); // Horizontal  End Address
        LCD_WR_REG_DATA(0x0212, 0x0000); // Vertical  Start Address
        LCD_WR_REG_DATA(0x0213, 0x018F); // Vertical  End Address
        LCD_WR_REG_DATA(0x0400, 0x3100); // Gate Scan Line
        LCD_WR_REG_DATA(0x0401, 0x0001); // NDL,VLE, REV
        LCD_WR_REG_DATA(0x0404, 0x0000); // set scrolling line
        //-------------- Partial Display Control ---------//
        LCD_WR_REG_DATA(0x0500, 0x0000);//Partial Image 1 Display Position
        LCD_WR_REG_DATA(0x0501, 0x0000); //Partial Image 1 RAM Start/End Address
        LCD_WR_REG_DATA(0x0502, 0x0000); //Partial Image 1 RAM Start/End Address
        LCD_WR_REG_DATA(0x0503, 0x0000); //Partial Image 2 Display Position
        LCD_WR_REG_DATA(0x0504, 0x0000);//Partial Image 2 RAM Start/End Address
        LCD_WR_REG_DATA(0x0505, 0x0000); //Partial Image 2 RAM Start/End Address
        //-------------- Panel Control -------------------//
        LCD_WR_REG_DATA(0x0010, 0x0010); //DIVI[1:0];RTNI[4:0]
        LCD_WR_REG_DATA(0x0011, 0x0600); //NOWI[2:0];SDTI[2:0]
        LCD_WR_REG_DATA(0x0020, 0x0002); //DIVE[1:0];RTNE[5:0]
        LCD_WR_REG_DATA(0x0007, 0x0173); // 262K color and display ON

        LCD_WR_REG(0x0202);
        delay_ms(20);
    }
    else if (LCD_ID == 4551)
    {
        LCD_WR_REG_DATA(0x15, 0x0030);
        LCD_WR_REG_DATA(0x11, 0x0010);     //0x0110
        LCD_WR_REG_DATA(0x10, 0x3628);
        LCD_WR_REG_DATA(0x12, 0x0005);
        LCD_WR_REG_DATA(0x13, 0x0E40);
        delay_ms(40);
        LCD_WR_REG_DATA(0x12, 0x0015); //0x0016
        delay_ms(40);
        LCD_WR_REG_DATA(0x10, 0x3620);  //0x3620  //0x3640
        LCD_WR_REG_DATA(0x13, 0x2E40);      //0x2D24  0x2C2f
        delay_ms(20);
        LCD_WR_REG_DATA(0x30, 0x0007);
        LCD_WR_REG_DATA(0x31, 0x0602);
        LCD_WR_REG_DATA(0x32, 0x0106);
        LCD_WR_REG_DATA(0x33, 0x0405);
        LCD_WR_REG_DATA(0x34, 0x0203);
        LCD_WR_REG_DATA(0x35, 0x0602);
        LCD_WR_REG_DATA(0x36, 0x0007);
        LCD_WR_REG_DATA(0x37, 0x0504);
        LCD_WR_REG_DATA(0x38, 0x0809);
        LCD_WR_REG_DATA(0x39, 0x0809);
        delay_ms(20);
        LCD_WR_REG_DATA(0x01, 0x0100);
        LCD_WR_REG_DATA(0x02, 0x0300);
        LCD_WR_REG_DATA(0x03, 0x1030);
        LCD_WR_REG_DATA(0x08, 0x0808);
        LCD_WR_REG_DATA(0x0A, 0x0008);
        LCD_WR_REG_DATA(0x60, 0x3100);
        LCD_WR_REG_DATA(0x61, 0x0001);
        LCD_WR_REG_DATA(0x90, 0x0054); //0x003c(60)//0x0044(68)  //0x0058(90)
        LCD_WR_REG_DATA(0x92, 0x010F);
        LCD_WR_REG_DATA(0x93, 0x0501);
        LCD_WR_REG_DATA(0x9A, 0x0009);
        LCD_WR_REG_DATA(0xA3, 0x0010);
        LCD_WR_REG_DATA(0x07, 0x0001);
        LCD_WR_REG_DATA(0x07, 0x0021);
        LCD_WR_REG_DATA(0x07, 0x0023);
        LCD_WR_REG_DATA(0x07, 0x0033);
        LCD_WR_REG_DATA(0x07, 0x0133);
        delay_ms(20);
    }

    else if(LCD_ID == 5420)
    {
//--------------- Normal set ---------------//
        LCD_WR_REG_DATA(0x0000, 0x0000);
        LCD_WR_REG_DATA(0x0001, 0x0100);
        LCD_WR_REG_DATA(0x0002, 0x0100);
        LCD_WR_REG_DATA(0x0003, 0x1030);
        LCD_WR_REG_DATA(0x0008, 0x0808);
        LCD_WR_REG_DATA(0x0009, 0x0001);
        LCD_WR_REG_DATA(0x000B, 0x0010);
        LCD_WR_REG_DATA(0x000C, 0x0000);
        LCD_WR_REG_DATA(0x000F, 0x0000);
        LCD_WR_REG_DATA(0x0007, 0x0001);
        //--------------- Panel interface control 1~6 ---------------//

        LCD_WR_REG_DATA(0x0010, 0x0011);    //0x0012 0010
        LCD_WR_REG_DATA(0x0011, 0x0200);    //0x0202
        LCD_WR_REG_DATA(0x0012, 0x0300);    //
        LCD_WR_REG_DATA(0x0020, 0x021E);    //
        LCD_WR_REG_DATA(0x0021, 0x0202);    //
        LCD_WR_REG_DATA(0x0022, 0x0100);    //
        LCD_WR_REG_DATA(0x0090, 0x8000);    //


        //--------------- Power control 1~6 ---------------//
        LCD_WR_REG_DATA(0x0100, 0x17B0);
        LCD_WR_REG_DATA(0x0101, 0x0147);
        LCD_WR_REG_DATA(0x0102, 0x0138);

        LCD_WR_REG_DATA(0x0103, 0x3000);

        LCD_WR_REG_DATA(0x0107, 0x0000);
        LCD_WR_REG_DATA(0x0110, 0x0001);
        LCD_WR_REG_DATA(0x0280, 0x0000); // NVM write / read
        LCD_WR_REG_DATA(0x0281, 0x0000); // Vcom high voltage 1//0000
        LCD_WR_REG_DATA(0x0282, 0x0000); // Vcom high voltage 2


        //--------------- Gamma 2.2 control ---------------//


        LCD_WR_REG_DATA(0x0300, 0x1011);    //0x0101
        LCD_WR_REG_DATA(0x0301, 0x2524);    //0x0024
        LCD_WR_REG_DATA(0x0302, 0x2F20);    //0x1326
        LCD_WR_REG_DATA(0x0303, 0x202F);    //0x2313
        LCD_WR_REG_DATA(0x0304, 0x2325);    //0x2400
        LCD_WR_REG_DATA(0x0305, 0x1110);    //0x0100
        LCD_WR_REG_DATA(0x0306, 0x0e04);    //0x1704
        LCD_WR_REG_DATA(0x0307, 0x040e);    //0x0417
        LCD_WR_REG_DATA(0x0308, 0x0005);    //0x0007
        LCD_WR_REG_DATA(0x0309, 0x0003);    //0x0105
        LCD_WR_REG_DATA(0x030A, 0x0F04);    //0x0F05
        LCD_WR_REG_DATA(0x030B, 0x0F00);    //0x0F01
        LCD_WR_REG_DATA(0x030C, 0x000F);    //0x010F
        LCD_WR_REG_DATA(0x030D, 0x040F);    //0x050F
        LCD_WR_REG_DATA(0x030E, 0x0300);    //0x0501
        LCD_WR_REG_DATA(0x030F, 0x0500);    //0x0700
        LCD_WR_REG_DATA(0x0400, 0x3500);    //0x3100
        LCD_WR_REG_DATA(0x0401, 0x0001);    //0x0001
        LCD_WR_REG_DATA(0x0404, 0x0000);    //0x0000



        //--------------- Partial display ---------------//
        LCD_WR_REG_DATA(0x0201, 0x0000);
        LCD_WR_REG_DATA(0x0200, 0x0000);
        LCD_WR_REG_DATA(0x0210, 0x0000);
        LCD_WR_REG_DATA(0x0211, 0x00EF);
        LCD_WR_REG_DATA(0x0212, 0x0000);
        LCD_WR_REG_DATA(0x0213, 0x018F);

        LCD_WR_REG_DATA(0x0500, 0x0000);
        LCD_WR_REG_DATA(0x0501, 0x0000);
        LCD_WR_REG_DATA(0x0502, 0x0000);
        LCD_WR_REG_DATA(0x0503, 0x0000);
        LCD_WR_REG_DATA(0x0504, 0x0000);
        LCD_WR_REG_DATA(0x0505, 0x0000);
        LCD_WR_REG_DATA(0x0600, 0x0000);
        LCD_WR_REG_DATA(0x0606, 0x0000);
        LCD_WR_REG_DATA(0x06F0, 0x0000);
        //--------------- Orise mode ---------------//
        LCD_WR_REG_DATA(0x07F0, 0x5420);
        LCD_WR_REG_DATA(0x07de, 0x0000);
        LCD_WR_REG_DATA(0x07F2, 0x00df);
        LCD_WR_REG_DATA(0x07F3, 0x088e);    //0x288A
        LCD_WR_REG_DATA(0x07F4, 0x0022);
        LCD_WR_REG_DATA(0x07F5, 0x0001);    //
        LCD_WR_REG_DATA(0x07F0, 0x0000);
        LCD_WR_REG_DATA(0x0007, 0x0173); // Display on

        delay_ms(150);
    }
    else if(LCD_ID == 61509)
    {
        LCD_WR_REG(0x0000);
        LCD_WR_REG(0x0000);
        delay_ms(10);
        LCD_WR_REG(0x0000);
        LCD_WR_REG(0x0000);
        LCD_WR_REG(0x0000);
        LCD_WR_REG(0x0000);
        delay_ms(10);

        LCD_WR_REG(0x0400);
        LCD_WR_DATA(0x6200);
        LCD_WR_REG(0x0008);
        LCD_WR_DATA(0x0808);

        LCD_WR_REG(0x0300);
        LCD_WR_DATA(0x0109);
        LCD_WR_REG(0x0301);
        LCD_WR_DATA(0x7E0A);
        LCD_WR_REG(0x0302);
        LCD_WR_DATA(0x0704);
        LCD_WR_REG(0x0303);
        LCD_WR_DATA(0x0911);

        LCD_WR_REG(0x0304);
        LCD_WR_DATA(0x2100);

        LCD_WR_REG(0x0305);
        LCD_WR_DATA(0x1109);
        LCD_WR_REG(0x0306);
        LCD_WR_DATA(0x7407);
        LCD_WR_REG(0x0307);
        LCD_WR_DATA(0x0A0E);
        LCD_WR_REG(0x0308);
        LCD_WR_DATA(0x0901);

        LCD_WR_REG(0x0309);
        LCD_WR_DATA(0x0021);

        LCD_WR_REG(0x0010);
        LCD_WR_DATA(0x0018);
        LCD_WR_REG(0x0011);
        LCD_WR_DATA(0x0202);
        LCD_WR_REG(0x0012);
        LCD_WR_DATA(0x0300);
        LCD_WR_REG(0x0013);
        LCD_WR_DATA(0x0007);
        delay_ms(10);

        LCD_WR_REG(0x0100);
        LCD_WR_DATA(0x0330);
        LCD_WR_REG(0x0101);
        LCD_WR_DATA(0x0247);
        LCD_WR_REG(0x0103);
        LCD_WR_DATA(0x1000);
        LCD_WR_REG(0x0280);
        LCD_WR_DATA(0xc800);//0xc800
        LCD_WR_REG(0x0102);
        LCD_WR_DATA(0xD1B0);
        delay_ms(100);

        LCD_WR_REG(0x0001);
        LCD_WR_DATA(0x0100); //When SS = “1” and BGR = “1”, RGB dots are assigned one to one from S720 to S1.
        LCD_WR_REG(0x0002);
        LCD_WR_DATA(0x0100);
        LCD_WR_REG(0x0003);
        LCD_WR_DATA(0x5038);//0x1028  扫描和BGR要结合0x100寄存器来看扫描顺序
        LCD_WR_REG(0x0009);
        LCD_WR_DATA(0x0001);
        LCD_WR_REG(0x000C);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0090);
        LCD_WR_DATA(0x8000);
        LCD_WR_REG(0x000F);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0210);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0211);
        LCD_WR_DATA(0x00EF);
        LCD_WR_REG(0x0212);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0213);
        LCD_WR_DATA(0x018F);
        LCD_WR_REG(0x0500);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0501);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0502);
        LCD_WR_DATA(0x005F);
        LCD_WR_REG(0x0401);
        LCD_WR_DATA(0x0001);
        LCD_WR_REG(0x0404);
        LCD_WR_DATA(0x0000);
        delay_ms(50);

        LCD_WR_REG(0x0007);
        LCD_WR_DATA(0x0100);
        delay_ms(100);

        LCD_WR_REG(0x0200);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0201);
        LCD_WR_DATA(0x0000);
        LCD_WR_REG(0x0202);

///////////////////////////////////////////////////////////////////////
//		LCD_WR_REG_DATA(0x00,0x00);delay_ms(5); //四次写0x00
//		LCD_WR_REG_DATA(0x00,0x00);delay_ms(5);
//		LCD_WR_REG_DATA(0x00,0x00);delay_ms(5);
//		LCD_WR_REG_DATA(0x00,0x00);delay_ms(5);
//		LCD_WR_REG_DATA(0X400,0X6200); //base image 设置 400线
//		LCD_WR_REG_DATA(0X010,0X0019); //面板频率
//		LCD_WR_REG_DATA(0X100,0X330);//设置电源控制，平衡显示与电消耗
//		LCD_WR_REG_DATA(0x102,0xd1b0);delay_ms(5);//PSON,PON 都设为1，电源供应打开
//		LCD_WR_REG_DATA(0x280,0xbf00);delay_ms(5);//VCM
//		delay_ms(100);
//		LCD_WR_REG_DATA(0X0003,0X5038);delay_ms(5);//RGB设为5-6-5模式
//		delay_ms(3);
//		LCD_WR_REG_DATA(0X0001,0X0100);//When SS = “1” and BGR = “1”, RGB dots are assigned one to one from S720 to S1.
//		LCD_WR_REG_DATA(0X007,0X0100);//测试显示控制base image的关与开
//		delay_ms(3);
//		delay_ms(3);
//		LCD_WR_REG_DATA(0X200,0X00); //设置RAM ADDRESS
//		delay_ms(3);
//		LCD_WR_REG_DATA(0X201,0X00); 
//		delay_ms(3);


//		delay_ms(3);
//		LCD_WR_REG_DATA(0X401,0X01); //设置base image 滚动模式，开启滚动
//		delay_ms(3);
//		LCD_WR_REG_DATA(0x0C,0x0000);delay_ms(5); //外部显示接口控制，默认值
//		LCD_WR_REG_DATA(0x090,0x8000);delay_ms(5); //窗特征控制，FMARK interface
//		LCD_WR_REG_DATA(0X404,0X00);delay_ms(3);  //从0线开始滚
//		LCD_WR_REG_DATA(0X502,0X5f);delay_ms(3);
//		LCD_WR_REG_DATA(0x200,0x0000);delay_ms(5);//RAM address 设置
//		LCD_WR_REG_DATA(0x201,0x0000);delay_ms(5);
//		delay_ms(500);
//		LCD_WR_REG(0X202);delay_ms(200);

    }
}

/*************************三色函数**********************************************/
//9225是特殊的，需要用这个
void LCD_Clear(u16 LCD_ID)
{
    u16 i, j;
    if(LCD_ID == 5420)
    {
        LCD_WR_REG_DATA(0x0210, 0x0000);    //X_Start); //x start
        LCD_WR_REG_DATA(0x0211, 0x00EF);    //X_End);       //x end
        LCD_WR_REG_DATA(0x0212, 0x0000);    //Y_Start); //y start
        LCD_WR_REG_DATA(0x0213, 0x018f);    //Y_End);       //y end
        LCD_WR_REG_DATA(0x0201, 0x0000);    //Y_Start); //y addres
        LCD_WR_REG_DATA(0x0200, 0x0000);    //X_Start); //x addres

        LCD_WR_REG(0x0202);

    }
    else if (LCD_ID == 9225)
    {
        LCD_WR_REG_DATA(0x36, 0x00af);    //horizontal address  水平地址高八位
        LCD_WR_REG_DATA(0x37, 0x0000);    //horizontal address  水平地址低八位
        LCD_WR_REG_DATA(0x38, 0x00db);    //vertical address    垂直地址高八位
        LCD_WR_REG_DATA(0x39, 0x0000);    //vertical address    垂直地址高八位

        LCD_WR_REG_DATA(0x20, 0x0000);   //GRAM address set   设置地址计数器的初始值
        LCD_WR_REG_DATA(0x21, 0x0000);

        LCD_WR_REG(0x22);
    }
    RS = 1;  //写数据
    CS = 0;
	//清屏
	for (i = 0; i < 240; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(BLACK);
        }
    }
	

	for (i = 0; i < 80; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(BLUE);
        }
    }

	for (i = 0; i < 80; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(GREEN);
        }
    }
	
	for (i = 0; i < 80; i++)
    {
        for (j = 0; j < 400; j++)
        {
            LCD_WR_DATA(0XF000);
        }
    }

}


void SLEEPEXIT(void)
{
    LCD_WR_REG_DATA(0x10, 0x0008);
    LCD_WR_REG_DATA(0x15, 0x7040);
    LCD_WR_REG_DATA(0x11, 0x0510);     //0x0110
    LCD_WR_REG_DATA(0x10, 0x3628);
    LCD_WR_REG_DATA(0x12, 0x0006);
    LCD_WR_REG_DATA(0x13, 0x0c2f);
    delay_ms(40);
    LCD_WR_REG_DATA(0x12, 0x0015); //0x0016
    delay_ms(40);
    LCD_WR_REG_DATA(0x10, 0x3640);  //0x3620  //0x3640
    LCD_WR_REG_DATA(0x13, 0x2b28);      //0x2D24  0x2C2f
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0001);
    LCD_WR_REG_DATA(0x07, 0x0021);
    LCD_WR_REG_DATA(0x07, 0x0023);
    LCD_WR_REG_DATA(0x07, 0x0033);
    LCD_WR_REG_DATA(0x07, 0x0133);

}

void SLEEPON(void)
{

    LCD_WR_REG_DATA(0x07, 0x0032);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0022);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0002);
    delay_ms(20);
    LCD_WR_REG_DATA(0x07, 0x0000);
    delay_ms(10);
    LCD_WR_REG_DATA(0x17, 0x0001);
    LCD_WR_REG_DATA(0x13, 0x0000);
    LCD_WR_REG_DATA(0x12, 0x0000);
    LCD_WR_REG_DATA(0x10, 0x0008);
    delay_ms(10);
    LCD_WR_REG_DATA(0x10, 0x000A);

}

void LCD_Read(void)
{
    u16 temp;
    CS = 0;
    RS = 0;
    WR = 1;
    GPIOE->ODR = 0;
    WR = 0;
    WR = 1;
    RS = 1;
    LCD_IN();  //设置引脚为输入
    RD = 0;
    delay_us(5);
    RD = 1;
    LCD_id = GPIOE->IDR;
    temp = LCD_id & 0xff00;
    RD = 0;
    LCD_id = GPIOE->IDR;
    RD = 1;
    temp |= (LCD_id >> 8);
    LCD_id = temp;
    LCD_OUT(); //设置引脚为输出
    CS = 1;
}