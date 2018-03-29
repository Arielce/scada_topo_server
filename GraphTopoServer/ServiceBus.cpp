#ifndef _WINDOWS32
#include <netdb.h>
#include <arpa/inet.h>
#endif
#include <iostream>
using namespace std;

#include "ServiceBus.h"
#include "sam_service.h"



/**
 * 创建服务总线服务端
 * @param port 端口号
 * @param theFunc 回调函数
 */
void CreateSrvBusServer(int port, Func theFunc)
{
    //初始化结构
    ServiceInfo srvInfo;
    srvInfo.port = port;

    //服务端初始化
    ServiceServerInit(srvInfo, DISPATCH);

    //分发
    printf("begin ServiceDispatch...\n");
    ServiceDispatch(srvInfo, 2, theFunc);
    printf("end of ServiceDispatch...\n");
}




/**
 * 服务总线
 * @param appNo 应用号
 * @param port 端口号
 * @param ctxNo 态号
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
        cout<<"主机=="<<hostName<<endl;
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
 * 服务总线
 * @param hostServer
 * @param port 端口号
 * @param ctxNo 态号
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
 * 同步方式请求数据
 * @param msgType 请求的数据类型
 * @param msgBuf 需要传递给服务器的数据
 * @param msgLen 数据长度
 * @return int
 *         请求成功返回1，请求结果保存在m_RecvMsgBuf和m_RecvMsgLen中供外部调用
 *         请求失败返回-1
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





