#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"
#include "bsp_esp8266.h"


/********************************** �û���Ҫ���õĲ���**********************************/
#define   macUser_ESP8266_BulitApSsid         "IoTProject"      //Ҫ�������ȵ������
#define   macUser_ESP8266_BulitApEcn           OPEN               //Ҫ�������ȵ�ļ��ܷ�ʽ
#define   macUser_ESP8266_BulitApPwd           "test"         //Ҫ�������ȵ����Կ

#define   macUser_ESP8266_TcpServer_IP         "192.168.1.1"      //������������IP��ַ
#define   macUser_ESP8266_TcpServer_Port       "8080"             //�����������Ķ˿�   

#define   macUser_ESP8266_TcpServer_OverTime   "1800"             //��������ʱʱ�䣨��λ���룩



/********************************** ���Ժ������� ***************************************/
void                     ESP8266_StaTcpClient_UnvarnishTest  ( void );



#endif

