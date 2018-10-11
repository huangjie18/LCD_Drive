#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
//***************ADC配置************************
//AD0：推子1→PA0        ADC1-通道0
//AD1：推子2→PA1        ADC1-通道1
//AD2：推子3→PA2        ADC1-通道2
//AD3：推子4→PA3        ADC1-通道3
//AD4：推子5→PA4        ADC1-通道4
//AD5：推子6→PA5        ADC1-通道5
//AD6：推子7→PA6        ADC1-通道6
//AD7：推子8→PA7        ADC1-通道7
//AD8：推子9→PC4        ADC1-通道14
//AD9：推子10→PC5       ADC1-通道15
//AD10：推子11→PB0      ADC1-通道8
//AD11：推子12→PB1      ADC1-通道9
//AD12：推子13→PF7      ADC3-通道5
//AD13：推子14→PF6      ADC3-通道4
//AD14：推子15→PF8      ADC3-通道6
//AD15：推子16→PF9      ADC3-通道7
//AD16：推子17→PF10     ADC3-通道8
//AD17：推子18→PC0      ADC1-通道10
//AD18：推子19→PC1      ADC1-通道11
//AD19：推子20→PC2      ADC1-通道12

////////////////还没测试///////////////////////////
//AD20：推子21-22→PC3   ADC1-通道13   C0:0→推子21;   1→推子22;
//CO:PB12
//**********************************************
#define C0 PBout(12)


void  Adc_Init(void);  //ADC初始化
u16 Get_Adc(ADC_TypeDef *adc,u8 ch); //获得ADC值
u16 Get_Adc_Average(ADC_TypeDef *adc,u8 ch,u8 times); //获得ADC平均值



 
#endif



