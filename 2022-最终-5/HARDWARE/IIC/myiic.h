#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h" 

   	   		   


#define	adc_reset			PCout(10)  //输入ADC 复位引脚
#define	dac_reset			PAout(15)  //输入DAC 复位引脚


//IO方向设置
#define dac_sda_in()  {GPIOC->CRH&=0X0FF0FFFF;GPIOC->CRH|=(u32)8<<16;}
#define dac_sda_out() {GPIOC->CRH&=0X0FF0FFFF;GPIOC->CRH|=(u32)3<<16;}
//IO操作函数	 
#define dac_iic_scl     PCout(11) //SCL PG5
#define dac_iic_sda    PCout(12) //SDA	 
#define dac_read_sda   PCin(12)  //输入SDA 


//IIC所有操作函数

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 
void write_ad_data0(u8 device_addr,u8 register_addr,u8 dat);
u8 read_ad_data0(u8 device_addr, u8 register_addr);


void dac_iic_init(void);
u8 read_dac_data0(u8 device_addr, u8 register_addr);
void write_dac_data0(u8 device_addr,u8 register_addr,u8 dat);
#endif
















