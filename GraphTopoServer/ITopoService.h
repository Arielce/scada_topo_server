/*
 * ITopoService.h
 *
 *  Created on: 2018��3��19��
 *      Author: Ge.Wenlin
 */

#ifndef ITOPOSERVICE_H_
#define ITOPOSERVICE_H_

#include "CConfigurationInfo.h"

class ITopoServiceFactory;
class CGraph;
class ITopoService//��ΰ�ͼģ�ʹ��ݸ����ࣿ����
{
public:
	virtual ~ITopoService()
	{
	}

	void setGraph(CGraph* g){m_graph = g;}
	virtual void doService(char* requestBuffer, int requestlen, char** responseBuffer, int* responselen) = 0;
protected:
	CGraph* m_graph;
};

class ITopoServiceFactory
{
public:
	virtual ~ITopoServiceFactory()
	{
	}
	virtual void CreateTopoService(ITopoService** p_obj) = 0;
};

extern "C" void DllGetTopoServiceFactory(ITopoServiceFactory** p);


#endif /* ITOPOSERVICE_H_ */
