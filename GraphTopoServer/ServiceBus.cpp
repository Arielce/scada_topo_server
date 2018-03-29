#ifndef _WINDOWS32
#include <netdb.h>
#include <arpa/inet.h>
#endif
#include <iostream>
using namespace std;

#include "ServiceBus.h"
#include "sam_service.h"



/**
 * �����������߷����
 * @param port �˿ں�
 * @param theFunc �ص�����
 */
void CreateSrvBusServer(int port, Func theFunc)
{
    //��ʼ���ṹ
    ServiceInfo srvInfo;
    srvInfo.port = port;

    //����˳�ʼ��
    ServiceServerInit(srvInfo, DISPATCH);

    //�ַ�
    printf("begin ServiceDispatch...\n");
    ServiceDispatch(srvInfo, 2, theFunc);
    printf("end of ServiceDispatch...\n");
}




/**
 * ��������
 * @param appNo Ӧ�ú�
 * @param port �˿ں�
 * @param ctxNo ̬��
 */
ServiceBus::ServiceBus(int appNo, int port, short ctxNo)
                : m_AppNo(appNo), m_Port(port), m_CtxNo(ctxNo), m_Timeout(10)
{
    m_Handle = HANDLE_INIT;

    char hostName[64];
    CServicesManage srvMan;
    int rtn =srvMan.RequestService(appNo, 1, hostName, ctxNo); 
    if (rtn >= 1)
    {
        cout<<"����=="<<hostName<<endl;
        struct hostent* hst = NULL;
        hst = gethostbyname(hostName);
        if (hst)
        {
            char ipAddress[64];
            inet_ntop(AF_INET, hst->h_addr, ipAddress, 16);
            printf("ip == %s\n", ipAddress);

            m_SrvInfo.port = port;
            char* ip = ipAddress;
            inet_pton(AF_INET, ip, &(m_SrvInfo.addr));
        }
    }
    else
	    printf("ERROR:else rtn ===%d\n",rtn);
}

/**
 * ��������
 * @param hostServer
 * @param port �˿ں�
 * @param ctxNo ̬��
 */
ServiceBus::ServiceBus(char* hostServer,int appNo, int port, short ctxNo)
	:m_AppNo(appNo), m_Port(port), m_CtxNo(ctxNo), m_Timeout(10)
{
	m_Handle = HANDLE_INIT;

	char hostName[64];
	sprintf(hostName,"%s",hostServer);
	struct hostent* hst = NULL;
	hst = gethostbyname(hostName);
	if (hst)
	{
		char ipAddress[64];
		inet_ntop(AF_INET, hst->h_addr, ipAddress, 16);
		printf("ip == %s\n", ipAddress);

		m_SrvInfo.port = port;
		char* ip = ipAddress;
		inet_pton(AF_INET, ip, &(m_SrvInfo.addr));
	}
}



ServiceBus::~ServiceBus()
{
	RequestFree();
	serviceHandleFree(m_Handle);
}



void ServiceBus::RequestFree()
{
	serviceRequestFree(m_Handle);
}



/**
 * ͬ����ʽ��������
 * @param msgType �������������
 * @param msgBuf ��Ҫ���ݸ�������������
 * @param msgLen ���ݳ���
 * @return int
 *         ����ɹ�����1��������������m_RecvMsgBuf��m_RecvMsgLen�й��ⲿ����
 *         ����ʧ�ܷ���-1
 */

int ServiceBus::RequestSync(int msgType, const char* msgBuf, int msgLen)
{
	if (msgLen < 0)
	{
		return -1;
	}
	RequestFree();

	int sendMsgLen = sizeof(int) + msgLen;
	char* sendMsgBuf = new char[sendMsgLen];

	int offset = 0;
	memcpy(sendMsgBuf, (char*)&msgType, sizeof(int));
	offset += sizeof(int);

	if (msgLen > 0)
	{
		memcpy(sendMsgBuf + offset, msgBuf, msgLen);
		offset += msgLen;
	}

	int ret = serviceRequestSync(m_SrvInfo, sendMsgBuf, sendMsgLen, m_Timeout, &m_RecvMsgBuf, &m_RecvMsgLen, &m_Handle);
	delete [] sendMsgBuf;

	return ret;
}





