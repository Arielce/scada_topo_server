/***************************************************************
*
*        Copyright  @NARITECH, All rights reserved.
*
* 所属模块 : scada
* 文件路径 :
* 文 件 名 : ServiceBus.h
* 文件功能 :
* 继承关系 :
* 操作系统 : PC & UNIX
* 备    注 :
* 历史记录 :
*
*   时间            版本                作者            原因
*===============================================================
*   2009-09-28                          wangyong        created
*   2018-01-25                          zhoufu          modified
***************************************************************/

#ifndef __ServiceBus_h__
#define __ServiceBus_h__

#include "system.h"
#include "services.h"



/**
 * 创建服务总线服务端
 * @param port 端口号
 * @param theFunc 回调函数
 */
void CreateSrvBusServer(int port, Func theFunc);




/**
 * 服务总线客户端
 */
class ServiceBus
{

public:

    /**
     * 服务总线
     * @param appNo 应用号
     * @param port 端口号
     * @param ctxNo 态号
     */
    ServiceBus(int appNo, int port, short ctxNo = AC_REALTIME_NO);
    ServiceBus(char* hostName,int appNo, int port, short ctxNo = AC_REALTIME_NO);//zhoufu added
    ~ServiceBus();


    /**
     * 同步方式请求数据
     * @param msgType 请求的数据类型
     * @param msgBuf 需要传递给服务器的数据
     * @param msgLen 数据长度
     * @return int
     *         请求成功返回1，请求结果保存在m_RecvMsgBuf和m_RecvMsgLen中供外部调用
     *         请求失败返回-1
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

