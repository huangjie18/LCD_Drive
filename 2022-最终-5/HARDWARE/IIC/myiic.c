#include "myiic.h"
#include "delay.h"



////////////////////////
/////////DAC//////////////
/////////////////////////
//��ʼ��IIC
void dac_iic_init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//ʹ��GPIOGʱ��

  //GPIOG4,G5��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11| GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	dac_iic_scl=1;
	dac_iic_sda=1;	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
}




//����IIC��ʼ�ź�
void dac_iic_start(void)
{
	dac_sda_out();     //sda�����
	dac_iic_sda=1;	  	  
	dac_iic_scl=1;
	delay_us(4);
 	dac_iic_sda=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	dac_iic_scl=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void dac_iic_stop(void)
{
	dac_sda_out();//sda�����
	dac_iic_scl=0;
	dac_iic_sda=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	dac_iic_scl=1; 
	dac_iic_sda=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 dac_iic_wait_ack(void)	
{
	u8 ucErrTime=0;
	dac_sda_in();      //SDA����Ϊ����  
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
	dac_iic_scl=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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













//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
u8 dac_iic_send_byte(u8 txd)
{                        
    u8 t;   
	u8 ucErrTime=0;	
	dac_sda_out(); 	    
    dac_iic_scl=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        dac_iic_sda=(txd&0x80)>>7;
        txd<<=1; 	  
		    delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		    dac_iic_scl=1;
	    	delay_us(2); 
		    dac_iic_scl=0;	
		    delay_us(2);
    }	 
		
		

	dac_sda_in();      //SDA����Ϊ����  
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
	dac_iic_scl=0;//ʱ�����0 	   
	return 0;  		
		
		
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
	u8 dac_iic_read_byte(u8 ack)
{
	unsigned char i,receive=0;
	dac_sda_in();//SDA����Ϊ����
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
        dac_iic_nack();//����nACK
    else
        dac_iic_ack(); //����ACK   
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





