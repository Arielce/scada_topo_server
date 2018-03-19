/*
 * ITopoService.h
 *
 *  Created on: 2018年3月19日
 *      Author: Ge.Wenlin
 */

#ifndef ITOPOSERVICE_H_
#define ITOPOSERVICE_H_

#include "CConfigurationInfo.h"

class ITopoServiceFactory;
class CGraph;
class ITopoService//如何把图模型传递给该类？？？
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
