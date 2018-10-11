#include "SpiFlash.h"


#define 	DSP_SPICLK_PIN				GPIO_Pin_7
#define 	DSP_SPICLK_PORT			GPIOD

#define 	DSP_SPICS_PIN					GPIO_Pin_6
#define 	DSP_SPICS_PORT				GPIOD

#define 	DSP_SPIMOSI_PIN				GPIO_Pin_9
#define 	DSP_SPIMOSI_PORT			GPIOG

#define 	DSP0_SPIMISO_PIN			GPIO_Pin_0
#define 	DSP0_SPIMISO_PORT		GPIOD
#define 	DSP1_SPIMISO_PIN			GPIO_Pin_3
#define 	DSP1_SPIMISO_PORT		GPIOD

#define 	DSP0_RESET_PIN				GPIO_Pin_2
#define 	DSP0_ENABLE_PIN			GPIO_Pin_1
#define 	DSP0_INIT_PORT				GPIOD
#define 	DSP1_RESET_PIN				GPIO_Pin_5
#define 	DSP1_ENABLE_PIN			GPIO_Pin_4
#define 	DSP1_INIT_PORT				GPIOD

uint8_t			Select_DSP=0;

void DelayUs(unsigned int us)
{
//	unsigned int i,j;
//	for (i=0; i<us; ++i) 
//		for (j=0; j<40; ++j)
//		{}
	delay_us(us);

}

void SPI_DSP_CODE_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG ,ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin = DSP_SPICLK_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(DSP_SPICLK_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = DSP_SPICS_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(DSP_SPICS_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = DSP_SPIMOSI_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(DSP_SPIMOSI_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = DSP0_SPIMISO_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50M
	GPIO_Init(DSP0_SPIMISO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = DSP1_SPIMISO_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50M
	GPIO_Init(DSP1_SPIMISO_PORT, &GPIO_InitStructure);	
	
		// pe4--->d0_dsp_reset
	// pe5--->d0_updateEnable
	GPIO_InitStructure.GPIO_Pin = DSP0_RESET_PIN | DSP0_ENABLE_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(DSP0_INIT_PORT, &GPIO_InitStructure);	

	// pf15--->d1_dsp_reset
	// pf14--->d1_updateEnable
	GPIO_InitStructure.GPIO_Pin = DSP1_RESET_PIN | DSP1_ENABLE_PIN; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(DSP1_INIT_PORT, &GPIO_InitStructure);	
	DSP_Reset_Init();
	Select_DSP = 0;
}

void DSP_Reset_Init(void)
{
	GPIO_ResetBits(DSP0_INIT_PORT,  DSP0_ENABLE_PIN);//选择dsp0连接flash0
	GPIO_ResetBits(DSP1_INIT_PORT,  DSP1_ENABLE_PIN);//选择dsp1连接flash1
	DelayUs(60000);
	GPIO_ResetBits(DSP0_INIT_PORT,  DSP0_RESET_PIN);
	GPIO_ResetBits(DSP1_INIT_PORT,  DSP1_RESET_PIN);
	DelayUs(60000);
	GPIO_SetBits(DSP1_INIT_PORT,  DSP1_RESET_PIN);
	DelayUs(60000);
	GPIO_SetBits(DSP0_INIT_PORT,  DSP0_RESET_PIN);
}

void SelectDeviceDSP(uint8_t Device)
{
	
	if(Device==1)  {
		Select_DSP = Device;
		GPIO_SetBits(DSP0_INIT_PORT,  DSP0_ENABLE_PIN);//选择muc连接flash0
		DelayUs(1000);
		GPIO_ResetBits(DSP0_INIT_PORT,  DSP0_RESET_PIN);
	}
	else if(Device==2)  {
		Select_DSP = Device;
		GPIO_SetBits(DSP1_INIT_PORT,  DSP1_ENABLE_PIN);//选择mcu连接flash1
		DelayUs(1000);
		GPIO_ResetBits(DSP1_INIT_PORT,  DSP1_RESET_PIN);
	}
}

void CancelSelectDSP(uint8_t Device)
{	
	Select_DSP = Device;
	if(Select_DSP==1)  {
		GPIO_ResetBits(DSP0_INIT_PORT,  DSP0_ENABLE_PIN);//选择dsp0连接flash0
		DelayUs(1000);
		GPIO_SetBits(DSP0_INIT_PORT,  DSP0_RESET_PIN);//拉高复位dsp0
	}
	else if(Select_DSP==2)  {
		GPIO_ResetBits(DSP1_INIT_PORT,  DSP1_ENABLE_PIN);//选择dsp1连接flash1
		DelayUs(1000);
		GPIO_SetBits(DSP1_INIT_PORT,  DSP1_RESET_PIN);//拉高复位dsp1
	}
}

void SPI_SendByte(uint8_t date)
{
	uint8_t temp,i;
  	temp=date;
	for(i=0;i<8;i++)
  	{         
    	if(temp & 0x80)
		{
      		GPIO_SetBits(DSP_SPIMOSI_PORT,  DSP_SPIMOSI_PIN);
			   //SetSPIMOSI_DSP;			//SPI_O = 1;       
    	} 
		else
		{
      		GPIO_ResetBits(DSP_SPIMOSI_PORT,  DSP_SPIMOSI_PIN);	
			//ClrSPIMOSI_DSP;			//SPI_O = 0;
    	}
		GPIO_SetBits(DSP_SPICLK_PORT,  DSP_SPICLK_PIN);		
		//SetSPICLK_DSP;			//SPI_C = 1; 
		temp = temp << 1;
		DelayUs(CLK_Delay_Time);																		
		//_nop_(); _nop_(); 
    	GPIO_ResetBits(DSP_SPICLK_PORT,  DSP_SPICLK_PIN);		
		//ClrSPICLK_DSP;			//SPI_C = 0;    
		DelayUs(CLK_Delay_Time);																		
		//_nop_(); _nop_(); 
  	}
}

uint8_t SPI_ReadByte( void )
{
	uint8_t temp,i;			
  	temp=0;
	DelayUs(5*CLK_Delay_Time);
	
	if(Select_DSP==1)
	{			
			for(i=0;i<8;i++)
			{ 
				GPIO_SetBits(DSP_SPICLK_PORT,  DSP_SPICLK_PIN);				
				//SetSPICLK_DSP;				//SPI_C = 1;
				DelayUs(CLK_Delay_Time);	//_nop_(); _nop_();       
				temp = temp << 1;				
				if (GPIO_ReadInputDataBit(DSP0_SPIMISO_PORT, DSP0_SPIMISO_PIN))
					temp |= 0x01;      
				else
					temp &= 0xfe;     
				GPIO_ResetBits(DSP_SPICLK_PORT,  DSP_SPICLK_PIN);			
				//ClrSPICLK_DSP;				//SPI_C = 0; 
				DelayUs(CLK_Delay_Time);																		
				//_nop_();_nop_();_nop_();_nop_();   
			}			
	}
	else  if(Select_DSP==2)
	{
		for(i=0;i<8;i++)
			{ 
				GPIO_SetBits(DSP_SPICLK_PORT,  DSP_SPICLK_PIN);		
				//SetSPICLK_DSP;				//SPI_C = 1;
				DelayUs(CLK_Delay_Time);	//_nop_(); _nop_();       
				temp = temp << 1;		
				if (GPIO_ReadInputDataBit(DSP1_SPIMISO_PORT, DSP1_SPIMISO_PIN))
					temp |= 0x01;      
				else
					temp &= 0xfe;     
				GPIO_ResetBits(DSP_SPICLK_PORT,  DSP_SPICLK_PIN);						
				//ClrSPICLK_DSP;				//SPI_C = 0; 
				DelayUs(CLK_Delay_Time);																		
				//_nop_();_nop_();_nop_();_nop_();   
			}			
	}
	return temp;
}



void WriteEnableSPI(void)
{
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
	//ClrSPICS_DSP;					//SPI_S = 0;
	DelayUs(CLK_Delay_Time);
	SPI_SendByte(WREN);				//Enable PROM
	DelayUs(CLK_Delay_Time);
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);				
	//SetSPICS_DSP;					//SPI_S = 1;
}

void DisWriteEnableSPI(void)
{
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);				
	//ClrSPICS_DSP;					//SPI_S = 0;
	DelayUs(CLK_Delay_Time);
	SPI_SendByte(WRDI);			
	DelayUs(CLK_Delay_Time);
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);					
	//SetSPICS_DSP;					//SPI_S = 1;
}




//anout  0.6S
uint8_t EraseSector(uint8_t sector)
{
	uint8_t  reg,iCnt;
	WriteEnableSPI();		
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);				
	//ClrSPICS_DSP;					//SPI_S = 0;
	DelayUs(CLK_Delay_Time);
	SPI_SendByte(SECTOR_ERASE);
	SPI_SendByte(sector);
	SPI_SendByte(0X00);
	SPI_SendByte(0x00);	
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
	//SetSPICS_DSP;					//SPI_S = 1;
	DelayUs(100000);		
	do
	{
		DelayUs(100000);		
		ReadStatusReg(&reg);
		reg=reg&0x01;
		if(reg==0x00)  
		{
				break;
		}
	}while(1);
	WaitFlash();
	//??
	WriteEnableSPI();
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);			
	//ClrSPICS_DSP;//SPI_S = 0;
	DelayUs(CLK_Delay_Time);
	//PP Program 
	SPI_SendByte(READ);						
	//three byte address
	SPI_SendByte(sector);
	SPI_SendByte(1);
	SPI_SendByte(0);	
	//SPI_SendByte(0xFF); 				
	for(iCnt=0;iCnt<128;iCnt++)					
	{						
		reg=SPI_ReadByte();
		if(reg != 0xff)  return ERASEFAILURE;
	}
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);	
	//SetSPICS_DSP;//SPI_S = 1;
	return ERASESUCCESS;
}



//about  15S
uint8_t Erase_All(void)
{
	uint8_t  reg,iCnt,j;
	WriteEnableSPI();		
	DelayUs(CLK_Delay_Time);
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
	//ClrSPICS_DSP;					//SPI_S = 0;
	DelayUs(CLK_Delay_Time);
	SPI_SendByte(BULK_ERASE);
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
	//SetSPICS_DSP;					//SPI_S = 1;
//	Delay_ms(30000);	

	do
	{
		DelayUs(100000);		
		ReadStatusReg(&reg);
		reg=reg&0x01;
		if(reg==0x00)  
		{
				break;
		}
	}while(1);	
	WaitFlash();
	for(j=0;j<32;j++)
	{
		//??
		WriteEnableSPI();
		GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);			
		//ClrSPICS_DSP;					//SPI_S = 0;
		DelayUs(CLK_Delay_Time);
		//PP Program 
		SPI_SendByte(READ);						
		//three byte address
		SPI_SendByte(j);
		SPI_SendByte(1);
		SPI_SendByte(0);	
		//SPI_SendByte(0xFF); 				
		for(iCnt=0;iCnt<128;iCnt++)					
		{						
			reg=SPI_ReadByte();
			if(reg != 0xff)  return ERASEFAILURE;
		}
		GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
		//SetSPICS_DSP;					//SPI_S = 1;
	}	
	return ERASESUCCESS;
}

void ReadStatusReg(uint8_t *pReg)
{	 
	WriteEnableSPI();
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);			
	//ClrSPICS_DSP;					//SPI_S = 0;
	DelayUs(CLK_Delay_Time);	
	SPI_SendByte(RDSR);			//Read PROM	 status
	*pReg = SPI_ReadByte();
	*pReg = SPI_ReadByte();
	DelayUs(CLK_Delay_Time);
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
	//SetSPICS_DSP;					//SPI_S = 1;
} 

void SPI_Protect(void)
{
    WriteEnableSPI();      
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);			
	//ClrSPICS_DSP;					//SPI_S = 0;
	DelayUs(CLK_Delay_Time);
	SPI_SendByte(WRSR);
	SPI_SendByte(0x9C);
	DelayUs(CLK_Delay_Time);
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);			
	//SetSPICS_DSP;					//SPI_S = 1;
}

void SPI_unProtect(void)
{
    WriteEnableSPI();      
	GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
	//ClrSPICS_DSP;					//SPI_S = 0;
	DelayUs(CLK_Delay_Time);
	SPI_SendByte(WRSR);
	SPI_SendByte(0x00);
	DelayUs(CLK_Delay_Time);
	GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);			
	//SetSPICS_DSP;					//SPI_S = 1;
}

void WaitFlash(void)
{
	uint8_t temp;
#if	 0
	do{
		 ReadStatusReg(&temp);	
		 DelayUs(10000);		
	  }while(0);
#else
	do{
		 ReadStatusReg(&temp);	
		 DelayUs(50*CLK_Delay_Time);	 	
	  }while(temp&0x01);			//while(0);Delay_ms(10);// 
#endif
}


void ReadSectorDate(uint16_t PageNum,uint8_t *pbuffer)
{
	uint16_t jCnt,iCnt;
	

	GPIO_SetBits(DSP0_INIT_PORT,  DSP0_ENABLE_PIN);
	GPIO_SetBits(DSP1_INIT_PORT,  DSP1_ENABLE_PIN);
	DelayUs(500*CLK_Delay_Time);
	SPI_unProtect();						
	DelayUs(5*CLK_Delay_Time);
	WriteEnableSPI();			
	for(jCnt=0;jCnt<PageNum;jCnt++)				
	{		  
		iCnt=0;
		WaitFlash();							  
		WriteEnableSPI();					
		GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
		//ClrSPICS_DSP;					//SPI_S = 0;
		DelayUs(CLK_Delay_Time);
		//PP Program 
		SPI_SendByte(READ);						
		//three byte address
		SPI_SendByte(jCnt/256);
		SPI_SendByte(jCnt%256);
		SPI_SendByte(0);	
		//SPI_SendByte(0xFF); 				
		for(iCnt=0;iCnt<256;iCnt++)					
		{						
			pbuffer[iCnt]=SPI_ReadByte();
		}
		GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
		//SetSPICS_DSP;					//SPI_S = 1;
		
		for(iCnt=0;iCnt<256;iCnt++)		
		{
//			U0_SendByte(pbuffer[iCnt]);	//8-263   code
		}
//		U0_SendByte(UARTEndByte0);	//264
	}

}

void WriteSectorDate	(uint8_t Sector_Address, uint16_t cLength, uint8_t *buf)
{
	uint16_t j,k;
	uint8_t *ptr = NULL;

	DelayUs(CLK_Delay_Time);
	WriteEnableSPI();
	DelayUs(CLK_Delay_Time);
	SPI_unProtect();
	DelayUs(CLK_Delay_Time);
	WriteEnableSPI();
	while(EraseSector(Sector_Address)==ERASEFAILURE);
	WriteEnableSPI();

	for(j=0;j<cLength;j++)
	{
		
		ptr = &buf[j*256];
		WaitFlash();			

		WriteEnableSPI();					

		GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		//ClrSPICS_DSP;					//SPI_S = 0;
		DelayUs(CLK_Delay_Time);
		//PP Program 
		SPI_SendByte(PRAM);
		//three byte address
		SPI_SendByte(Sector_Address);
		SPI_SendByte(j);
		SPI_SendByte(0x00);		
		//256 serial date
		for(k=0;k<256;k++)
		{
			SPI_SendByte(ptr[k]);		
		}
		GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		//SetSPICS_DSP;					//SPI_S = 1;
		DelayUs(CLK_Delay_Time);
	}	
	
	DelayUs(CLK_Delay_Time);
    
}

void M25P20_Tx_Str	(uint8_t Sector_Address,uint16_t cLength)
{
	uint16_t j,k,CNT;

	DelayUs(CLK_Delay_Time);
	WriteEnableSPI();
	DelayUs(CLK_Delay_Time);
	SPI_unProtect();
	DelayUs(CLK_Delay_Time);
	WriteEnableSPI();
	while(EraseSector(Sector_Address)==ERASEFAILURE);
	WriteEnableSPI();

	CNT=0;

	for(j=0;j<cLength;j++)
	{
		WaitFlash();			

		WriteEnableSPI();					

		GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		//ClrSPICS_DSP;					//SPI_S = 0;
		DelayUs(CLK_Delay_Time);
		//PP Program 
		SPI_SendByte(PRAM);
		//three byte address
		SPI_SendByte(Sector_Address);
		SPI_SendByte(j);
		SPI_SendByte(0x00);		
		//256 serial date
		for(k=0;k<256;k++)
		{
			SPI_SendByte(CNT++);		
		}
		GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		//SetSPICS_DSP;					//SPI_S = 1;
		DelayUs(CLK_Delay_Time);
	}	
	
	DelayUs(CLK_Delay_Time);
    
}


void M25P20_Rx_Str(uint16_t PageNum,  uint8_t *pbuffer)
{
	uint16_t iCnt;
	
	GPIO_SetBits(DSP0_INIT_PORT,  DSP0_ENABLE_PIN);
	GPIO_SetBits(DSP1_INIT_PORT,  DSP1_ENABLE_PIN);
	DelayUs(500*CLK_Delay_Time);
	SPI_unProtect();						
	DelayUs(5*CLK_Delay_Time);
	WriteEnableSPI();			

		WaitFlash();							  
		WriteEnableSPI();					
		GPIO_ResetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		
		//ClrSPICS_DSP;					//SPI_S = 0;
		DelayUs(CLK_Delay_Time);
		//PP Program 
		SPI_SendByte(READ);						
		//three byte address
		SPI_SendByte(PageNum/256);
		SPI_SendByte(PageNum%256);
		SPI_SendByte(0);	
		//SPI_SendByte(0xFF); 				
		for(iCnt=0;iCnt<256;iCnt++)					
		{						
			pbuffer[iCnt]=SPI_ReadByte();
		}
		GPIO_SetBits(DSP_SPICS_PORT,  DSP_SPICS_PIN);		

}
