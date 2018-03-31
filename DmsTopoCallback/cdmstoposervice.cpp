#include "cdmstoposervice.h"
#include "CommTools_global.h"

#include "cdmstopoimpl.h"

#ifdef _BIGENDIAN
const unsigned char g_endian = 1;
#else
const unsigned char g_endian = 0;
#endif



CDmsTopoService::CDmsTopoService():m_Impl(NULL)
{

}

CDmsTopoService::~CDmsTopoService()
{
	if (m_Impl)
	{
		delete m_Impl;
	}
}

void CDmsTopoService::setGraph(SCADA_ALG::CGraph* g)
{
	m_graph = g;
	printf("call CDmsTopoService::setGraph...\n");
	m_Impl = new CDmsTopoImpl(m_graph);
}

void CDmsTopoService::doService(char* requestBuffer, int requestlen, char** responseBuffer, int* responselen)
{
	int buffer_switch_offset;
	int func_no = 0;
	int ret = 0;
	unsigned char client_endian;

	buffer_switch_offset = 0;
	memcpy(&client_endian, requestBuffer, sizeof(unsigned char)); //高低字节
	buffer_switch_offset += sizeof(unsigned char);
	memcpy(&func_no, requestBuffer + buffer_switch_offset, sizeof(int)); //函数号
	buffer_switch_offset += sizeof(int);
	if (client_endian != g_endian)
	{
		CCommTools::getInst()->ExchangeInt(func_no);
	}
	printf("doService funno is %d \n",func_no);
	switch (func_no)
	{
	case 0:
	{
		TRequestDmsTopo in_para;
		TRespondDmsTopo out_para;
		M_DECODE(in_para, requestBuffer + buffer_switch_offset, requestlen - buffer_switch_offset);
		ret = m_Impl->getConnectedDev(in_para, out_para);
		char* p;
		int psize;
		M_CODE(out_para, p, psize);
		int resp_size = sizeof(unsigned char) + sizeof(int) * 2 + psize;
		*responseBuffer = (char*) malloc(resp_size);
		buffer_switch_offset = 0;
		memcpy(*responseBuffer, &g_endian, sizeof(unsigned char));	//高低字节
		buffer_switch_offset += sizeof(unsigned char);
		memcpy(*responseBuffer + buffer_switch_offset, &ret, sizeof(int));	//返回值
		buffer_switch_offset += sizeof(int);
		memcpy(*responseBuffer + buffer_switch_offset, &psize, sizeof(int));	//大小
		buffer_switch_offset += sizeof(int);
		memcpy(*responseBuffer + buffer_switch_offset, p, psize);
		*responselen = resp_size;
		free(p);
		break;
	}
	}

	return;
}

void CDmsTopoServiceFactory::CreateTopoService(ITopoService** p_obj)
{
	*p_obj = new CDmsTopoService();
	return;
}
void CDmsTopoServiceFactory::Release()
{
	delete this;
}
void DllGetTopoServiceFactory(ITopoServiceFactory** p)
{
	*p = new CDmsTopoServiceFactory();
	return;
}
