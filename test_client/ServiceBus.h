/***************************************************************
*
*        Copyright  @NARITECH, All rights reserved.
*
* ����ģ�� : scada
* �ļ�·�� :
* �� �� �� : ServiceBus.h
* �ļ����� :
* �̳й�ϵ :
* ����ϵͳ : PC & UNIX
* ��    ע :
* ��ʷ��¼ :
*
*   ʱ��            �汾                ����            ԭ��
*===============================================================
*   2009-09-28                          wangyong        created
*   2018-01-25                          zhoufu          modified
***************************************************************/

#ifndef __ServiceBus_h__
#define __ServiceBus_h__

#include "system.h"
#include "services.h"



/**
 * �����������߷����
 * @param port �˿ں�
 * @param theFunc �ص�����
 */
void CreateSrvBusServer(int port, Func theFunc);




/**
 * �������߿ͻ���
 */
class ServiceBus
{

public:

    /**
     * ��������
     * @param appNo Ӧ�ú�
     * @param port �˿ں�
     * @param ctxNo ̬��
     */
    ServiceBus(int appNo, int port, short ctxNo = AC_REALTIME_NO);
    ServiceBus(char* hostName,int appNo, int port, short ctxNo = AC_REALTIME_NO);//zhoufu added
    ~ServiceBus();


    /**
     * ͬ����ʽ��������
     * @param msgType �������������
     * @param msgBuf ��Ҫ���ݸ�������������
     * @param msgLen ���ݳ���
     * @return int
     *         ����ɹ�����1��������������m_RecvMsgBuf��m_RecvMsgLen�й��ⲿ����
     *         ����ʧ�ܷ���-1
     */
    int RequestSync(unsigned char srvType, int msgType, const char* msgBuf = NULL, int msgLen = 0);

    void SetTimeout(int timeout) { m_Timeout = timeout; }


    void RequestFree();


    const char* GetMsgBuf() const { return m_RecvMsgBuf; }
    int GetMsgLen() const { return m_RecvMsgLen; }

    int GetAppNo() const { return m_AppNo; }
    short GetCtxNo() const { return m_CtxNo; }
    int GetPort() const { return m_Port; }


private:

    int m_AppNo;
    short m_CtxNo;
    int m_Port;

    char* m_RecvMsgBuf;
    int m_RecvMsgLen;

    Handle m_Handle;
	ServiceInfo m_SrvInfo;

	int m_Timeout;

};



#endif

