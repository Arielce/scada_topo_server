/*
 * ITopoService.h
 *
 *  Created on: 2018年3月19日
 *      Author: Ge.Wenlin
 */

#ifndef ITOPOSERVICE_H_
#define ITOPOSERVICE_H_

#ifdef _WINDOWS64
#ifdef TOPO_SERVICE_EXPORTS
#define TOPO_SERVICE_API __declspec(dllexport)
#else
#define TOPO_SERVICE_API __declspec(dllimport)
#endif
#else
#define TOPO_SERVICE_API
#endif

//#include "CConfigurationInfo.h"
#include "graphcore_global.h"
class ITopoServiceFactory;
class ITopoService//如何把图模型传递给该类？？？
{
public:
	virtual ~ITopoService()
	{
	}

	void setGraph(SCADA_ALG::CGraph* g){m_graph = g;}
	virtual void doService(char* requestBuffer, int requestlen, char** responseBuffer, int* responselen) = 0;
protected:
	SCADA_ALG::CGraph* m_graph;
};

class ITopoServiceFactory
{
public:
	virtual ~ITopoServiceFactory()
	{
	}
    virtual void CreateTopoService(ITopoService** p_obj) = 0;
    virtual void Release() = 0;
};

extern "C" void DllGetTopoServiceFactory(ITopoServiceFactory** p);


#endif /* ITOPOSERVICE_H_ */
