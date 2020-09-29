#include "test.h"
#include "bsp_esp8266.h"
#include "bsp_SysTick.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>
#include "bsp_dht11.h"
#include "bsp_led.h"
#include "bsp_beep.h"

volatile uint8_t ucLed1Status = 0, ucLed2Status = 0, ucLed3Status = 0, ucBuzzerStatus = 0;

/**
  * @brief  ESP8266 ��Sta Tcp Client��͸��
  * @param  ��
  * @retval ��
  */
void ESP8266_StaTcpClient_UnvarnishTest ( void )
{
	uint8_t ucId, ucLen;

	char cStr [ 100 ] = { 0 }, cCh;

  char * pCh, * pCh1;

	DHT11_Data_TypeDef DHT11_Data;
	

  printf ( "\r\n�������� ESP8266 ......\r\n" );

	macESP8266_CH_ENABLE();
	
	/* ATָ����� */
	ESP8266_AT_Test ();
	
	/* ѡ��ESP8266��Ϊ����� */
	ESP8266_Net_Mode_Choose ( AP );

	/* ����ESP8266��IP */
  while ( ! ESP8266_CIPAP ( macUser_ESP8266_TcpServer_IP ) );

	/* ����Wifi����,����,���ܷ�ʽ */
  while ( ! ESP8266_BuildAP ( macUser_ESP8266_BulitApSsid, macUser_ESP8266_BulitApPwd, macUser_ESP8266_BulitApEcn ) );	
	
	/* ʹ�ܶ����� */
	ESP8266_Enable_MultipleId ( ENABLE );
	
	/* ����������,���ö˿ں�,��ʱʱ�� */
	while ( !	ESP8266_StartOrShutServer ( ENABLE, macUser_ESP8266_TcpServer_Port, macUser_ESP8266_TcpServer_OverTime ) );

	/* ��ȡIP��ַ��ŵ�cStr */
	ESP8266_Inquire_ApIp ( cStr, 20 );
	printf ( "\r\n��ģ��WIFIΪ%s�����뿪��\r\nAP IP Ϊ��%s�������Ķ˿�Ϊ��%s\r\n�ֻ������������Ӹ� IP �Ͷ˿ڣ���������5���ͻ���\r\n",
           macUser_ESP8266_BulitApSsid, cStr, macUser_ESP8266_TcpServer_Port );
	
	
	strEsp8266_Fram_Record .InfBit .FramLength = 0;
	strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
	
	while ( 1 )
	{		
		/* ���ESP8266���յ�����,������� */
		if ( strEsp8266_Fram_Record .InfBit .FramFinishFlag )
		{
			USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, DISABLE ); //���ô��ڽ����ж�
			strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ]  = '\0';
			
//			printf ( "\r\n%s\r\n", strEsp8266_Fram_Record .Data_RX_BUF );//
			/* ��������������CMD_LED_���� */
			if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_LED_" ) ) != 0 ) 
			{
				cCh = * ( pCh + 8 );
				
				switch ( cCh )
				{
					case '1':
						cCh = * ( pCh + 10 );
					  switch ( cCh )
					  {
							case '0':
								macLED1_OFF ();
							  ucLed1Status = 0;
						    break;
							case '1':
								macLED1_ON ();
							  ucLed1Status = 1;
						    break;
							default :
								break;
						}
						break;
						
					case '2':
						cCh = * ( pCh + 10 );
					  switch ( cCh )
					  {
							case '0':
								macLED2_OFF ();
							  ucLed2Status = 0;
						    break;
							case '1':
								macLED2_ON ();
							  ucLed2Status = 1;
						    break;
							default :
								break;
						}
						break;

//					case '3':
//						cCh = * ( pCh + 10 );
//					  switch ( cCh )
//					  {
//							case '0':
//								macLED3_OFF ();
//							  ucLed3Status = 0;
//						    break;
//							case '1':
//								macLED3_ON ();
//							  ucLed3Status = 1;
//						    break;
//							default :
//								break;
//						}
//						break;
						
				  default :
            break;					
						
				}
				
				sprintf ( cStr, "CMD_LED_%d_%d_%d_ENDLED_END", ucLed1Status, ucLed2Status, ucLed3Status );
				printf("\r\nLED������յ�����%s\r\n",cStr);
				
			}
			
			/* ��������������CMD_BUZZER_���� */
			else if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_BUZZER_" ) ) != 0 ) 
			{
				cCh = * ( pCh + 11 );
				
				switch ( cCh )
				{
					case '0':
						macBEEP_OFF ();
					  ucBuzzerStatus = 0;
						break;
					case '1':
						macBEEP_ON ();
					  ucBuzzerStatus = 1;
						break;
					default:
						break;
				}
				
				sprintf ( cStr, "CMD_BUZZER_%d_ENDBUZZER_END", ucBuzzerStatus );
				printf("\r\nBUZZER������յ�����%s\r\n",cStr);
			}
				
			/* �������������н��� */
			else if ( ( ( pCh  = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_UART_" ) ) != 0 ) && 
				        ( ( pCh1 = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "_ENDUART_END" ) )  != 0 ) ) 
			{
				if ( pCh < pCh1)
				{
					ucLen = pCh1 - pCh + 12;
					memcpy ( cStr, pCh, ucLen );
					cStr [ ucLen ] = '\0';
				}
				printf("\r\n���ڽ��յ�����%s\r\n",cStr);
			}

			else if ( strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CMD_READ_ALL_END" ) != 0 ) 
			{
				DHT11_Read_TempAndHumidity ( & DHT11_Data );
				sprintf ( cStr, "CMD_LED_%d_%d_%d_ENDLED_DHT11_%d.%d_%d.%d_ENDDHT11_BUZZER_%d_ENDBUZZER_END", 
									ucLed1Status, ucLed2Status, ucLed3Status, DHT11_Data .temp_int, 
			            DHT11_Data .temp_deci, DHT11_Data .humi_int, DHT11_Data .humi_deci,
                  ucBuzzerStatus );
				printf("\r\n��ȫ��������յ�����%s\r\n",cStr);
			}
			
			/* �������ݵ��ֻ�APP */
			if ( ( pCh = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "+IPD," ) ) != 0 ) 
			{
				ucId = * ( pCh + strlen ( "+IPD," ) ) - '0';
				ESP8266_SendString ( DISABLE, cStr, strlen ( cStr ), ( ENUM_ID_NO_TypeDef ) ucId );
			}
			
		  strEsp8266_Fram_Record .InfBit .FramLength = 0;
	    strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;	
			
			USART_ITConfig ( macESP8266_USARTx, USART_IT_RXNE, ENABLE ); //ʹ�ܴ��ڽ����ж�
			
		}
		
	}
	
		
}


