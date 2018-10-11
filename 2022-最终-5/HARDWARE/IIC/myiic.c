#include "myiic.h"
#include "delay.h"



////////////////////////
/////////DAC//////////////
/////////////////////////
//初始化IIC
void dac_iic_init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//使能GPIOG时钟

  //GPIOG4,G5初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11| GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	dac_iic_scl=1;
	dac_iic_sda=1;	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
}




//产生IIC起始信号
void dac_iic_start(void)
{
	dac_sda_out();     //sda线输出
	dac_iic_sda=1;	  	  
	dac_iic_scl=1;
	delay_us(4);
 	dac_iic_sda=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	dac_iic_scl=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void dac_iic_stop(void)
{
	dac_sda_out();//sda线输出
	dac_iic_scl=0;
	dac_iic_sda=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	dac_iic_scl=1; 
	dac_iic_sda=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 dac_iic_wait_ack(void)	
{
	u8 ucErrTime=0;
	dac_sda_in();      //SDA设置为输入  
	dac_iic_sda=1;delay_us(1);	   
	dac_iic_scl=1;delay_us(1);	 
	while(dac_read_sda)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			dac_iic_stop();
			return 1;
		}
	}
	dac_iic_scl=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void dac_iic_ack(void)
{
	dac_iic_scl=0;
	dac_sda_out();
	dac_iic_sda=0;
	delay_us(2);
	dac_iic_scl=1;
	delay_us(2);
	dac_iic_scl=0;
}
//不产生ACK应答		    
void dac_iic_nack(void)
{
	dac_iic_scl=0;
	dac_sda_out();
	dac_iic_sda=1;
	delay_us(2);
	dac_iic_scl=1;
	delay_us(2);
	dac_iic_scl=0;
}	













//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
u8 dac_iic_send_byte(u8 txd)
{                        
    u8 t;   
	u8 ucErrTime=0;	
	dac_sda_out(); 	    
    dac_iic_scl=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        dac_iic_sda=(txd&0x80)>>7;
        txd<<=1; 	  
		    delay_us(2);   //对TEA5767这三个延时都是必须的
		    dac_iic_scl=1;
	    	delay_us(2); 
		    dac_iic_scl=0;	
		    delay_us(2);
    }	 
		
		

	dac_sda_in();      //SDA设置为输入  
	dac_iic_sda=1;delay_us(1);	   
	dac_iic_scl=1;delay_us(1);	 
	while(dac_read_sda)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			dac_iic_stop();
			return 1;
		}
	}
	dac_iic_scl=0;//时钟输出0 	   
	return 0;  		
		
		
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
	u8 dac_iic_read_byte(u8 ack)
{
	unsigned char i,receive=0;
	dac_sda_in();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        dac_iic_scl=0; 
        delay_us(2);
		    dac_iic_scl=1;
        receive<<=1;
        if(dac_read_sda)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        dac_iic_nack();//发送nACK
    else
        dac_iic_ack(); //发送ACK   
    return receive;
}




u8 read_dac_data0(u8 device_addr, u8 register_addr)
{
	u8 data;
	delay_us(2);
	dac_iic_start();
	dac_iic_send_byte(device_addr);			  	
	dac_iic_send_byte(register_addr);	
	dac_iic_stop();
	dac_iic_start();
	dac_iic_send_byte(device_addr | 0x01);		
	data = dac_iic_read_byte(0);
	dac_iic_stop();
	delay_us(2);
	return data;
}


void write_dac_data0(u8 device_addr,u8 register_addr,u8 dat)
{
	while(1) {
		dac_iic_start();
		if (dac_iic_send_byte(device_addr)) {
				dac_iic_stop();
				continue;
		}
		if (dac_iic_send_byte(register_addr)) {
				dac_iic_stop();
				continue;
		}
		if (dac_iic_send_byte(dat)) {
				dac_iic_stop();
				continue;
		}
		dac_iic_stop();
		break;
	}	 
}





