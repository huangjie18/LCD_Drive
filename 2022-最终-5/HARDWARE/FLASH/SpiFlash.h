#ifndef __SpiFlash_H_
#define __SpiFlash_H_

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"

/**********************************************************************************************************
M25P16
**********************************************************************************************************/											
#define     	__DEBUG_M25P16_     0   			
#define 		CLK_Delay_Time			8


#define 		WRSR 					0x01 	
#define 		PRAM  					0x02		
#define 		READ 					0x03		
#define 		WRDI					0x04		
#define 		RDSR 					0x05		
#define 		WREN 					0x06		
#define 		SECTOR_ERASE 		0xd8		 
#define 		BULK_ERASE			0xC7		
#define  		RDID						0x9f			
#define         FAST_READ			0x0b		
#define   		DEEP_POWER		0xb9		
#define    		RES						0xab			

#define 		ERASESUCCESS		0
#define      	ERASEFAILURE		1

void DelayUs(unsigned int us);

void SPI_DSP_CODE_Init 	(void);
void WriteEnableSPI		(void);
void DisWriteEnableSPI	(void);
void SPI_unProtect 		(void);
void SPI_Protect 		(void);
void WaitFlash		 	(void);

void SPI_SendByte  		( uint8_t date);
void ReadStatusReg(uint8_t *pReg);
void ReadyLoadCmd 		( uint8_t *pbuffer );

void SelectDeviceDSP(uint8_t Device);
void CancelSelectDSP(uint8_t Device);
void SPI_VariableInit(void);

uint8_t Erase_All	   		(void);
uint8_t  EraseSector		( uint8_t sector);
uint8_t SPI_ReadByte(void);


void  ProgramDSPCode(uint8_t *pbuf);
uint16_t LoadPageCode( uint8_t *pbuffer );

void DSP_Reset_Init(void);

#if 1//__DEBUG_M25P16_

void M25P20_Rx_Str(uint16_t PageNum,  uint8_t *pbuffer);
void ReadSectorDate	(uint16_t PageNum,uint8_t *pbuffer);
void WriteSectorDate	(uint8_t Sector_Address, uint16_t cLength, uint8_t *buf);
void M25P20_Tx_Str	(uint8_t Sector_Address,uint16_t cLength);

#endif

//#define 	DSP_SPICLK_PIN				GPIO_Pin_3
//#define 	DSP_SPICLK_PORT			GPIOE

//#define 	DSP_SPICS_PIN					GPIO_Pin_2
//#define 	DSP_SPICS_PORT				GPIOE

//#define 	DSP_SPIMOSI_PIN				GPIO_Pin_6
//#define 	DSP_SPIMOSI_PORT			GPIOE

//#define 	DSP0_SPIMISO_PIN			GPIO_Pin_2
//#define 	DSP0_SPIMISO_PORT		GPIOF
//#define 	DSP1_SPIMISO_PIN			GPIO_Pin_13
//#define 	DSP1_SPIMISO_PORT		GPIOF

//#define 	DSP0_RESET_PIN				GPIO_Pin_4
//#define 	DSP0_ENABLE_PIN			GPIO_Pin_5
//#define 	DSP0_INIT_PORT				GPIOE
//#define 	DSP1_RESET_PIN				GPIO_Pin_15
//#define 	DSP1_ENABLE_PIN			GPIO_Pin_14
//#define 	DSP1_INIT_PORT				GPIOF
#endif

