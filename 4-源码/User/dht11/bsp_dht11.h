#ifndef __DHT11_H
#define	__DHT11_H



#include "stm32f10x.h"



/************************** DHT11 �������Ͷ���********************************/
typedef struct
{
	uint8_t  humi_int;		//ʪ�ȵ���������
	uint8_t  humi_deci;	 	//ʪ�ȵ�С������
	uint8_t  temp_int;	 	//�¶ȵ���������
	uint8_t  temp_deci;	 	//�¶ȵ�С������
	uint8_t  check_sum;	 	//У���
		                 
} DHT11_Data_TypeDef;



/************************** DHT11 �������Ŷ���********************************/
#define      macDHT11_Dout_SCK_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define      macDHT11_Dout_GPIO_CLK                       RCC_APB2Periph_GPIOE

#define      macDHT11_Dout_GPIO_PORT                      GPIOE
#define      macDHT11_Dout_GPIO_PIN                       GPIO_Pin_6



/************************** DHT11 �����궨��********************************/
#define      macDHT11_Dout_0	                            GPIO_ResetBits ( macDHT11_Dout_GPIO_PORT, macDHT11_Dout_GPIO_PIN ) 
#define      macDHT11_Dout_1	                            GPIO_SetBits ( macDHT11_Dout_GPIO_PORT, macDHT11_Dout_GPIO_PIN ) 

#define      macDHT11_Dout_IN()	                          GPIO_ReadInputDataBit ( macDHT11_Dout_GPIO_PORT, macDHT11_Dout_GPIO_PIN ) 



/************************** DHT11 �������� ********************************/
void                     DHT11_Init                      ( void );
uint8_t                  DHT11_Read_TempAndHumidity      ( DHT11_Data_TypeDef * DHT11_Data );

;

#endif /* __DHT11_H */







