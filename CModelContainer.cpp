/*
 * CModelContainer.cpp
 *
 *  Created on: 2018年2月12日
 *      Author: Ge.Wenlin
 */

#include "CModelContainer.h"
namespace SCADA_ALG
{
CModelContainer::CModelContainer(CGraph* graph) :
		_graph(graph), _modelNum(0)
{
	// TODO Auto-generated constructor stub

}

CModelContainer::~CModelContainer()
{
	// TODO Auto-generated destructor stub
	//todo 析构_modelVec
}
void CModelContainer::addModelObj(CModelObj& obj)
{
	//printf("========== add model obj ,key name is %s , keyvalue is %ld\n",obj.keyName().c_str(),obj.keyValue().c_long());
	CModelObj* model_obj = new CModelObj(obj);
	_modelVec.push_back(model_obj);
	_modelIndex.insert(make_pair(obj.keyValue(), model_obj));
}
void CModelContainer::delModelObj(CModelObj& obj)
{
	ModelIndex::iterator it;
	it = _modelIndex.find(obj.keyValue());
	if (it != _modelIndex.end())
	{
		int index = it->second;
		ModelVec::iterator it_vec = _modelVec.begin() + index;
		_modelVec.erase(it_vec);
		_modelNum--;
		_modelIndex.erase(it);
	}
}
void CModelContainer::delModelObjProperty(CModelObj& obj, const string property_name)
{
	CModelObj::const_iterator it;
	it = obj.find(property_name);
	if (it != obj.end())
	{
		obj.erase(it);
	}
}
void CModelContainer::addModelObjProperty(CModelObj& obj, const string property_name,
		CUDataValue& value)
{
	obj[property_name] = value;
}
void CModelContainer::updateModelObj(CModelObj& obj)
{
	ModelIndex::iterator it;
	it = _modelIndex.find(obj.keyValue());
	if (it != _modelIndex.end())
	{
		int index = it->second;
		ModelVec::iterator it_vec = _modelVec.begin() + index;
		*(*it_vec) = obj;
	}
}
bool CModelContainer::transToGraph(CModelObj& obj, CGraph* graph)
{
	//留给子类实现
	return false;
}
void CModelContainer::transAllModelToGraph()
{
	ModelVec::iterator it;
	for (it = _modelVec.begin(); it != _modelVec.end(); it++)
	{
		transToGraph(*(*it), _graph);
	}
	return;
}

}
