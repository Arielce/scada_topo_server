/*
 * CModelContainer.h
 *
 *  Created on: 2018年2月12日
 *      Author: Ge.Wenlin
 */

#ifndef CMODELCONTAINER_H_
#define CMODELCONTAINER_H_
#include <CModel.h>
//#include <CGraph.h>

namespace SCADA_ALG
{

/*模型容器
 * 应用模型的存储容器
 * 提供模型添加、删除及更新的方法
 * 提供应用模型转换成图模型的方法(具体实现交给子类实现，因为不同类型的模型容器对应的转换方法不同，比如关系型模型的模型容器和图模型容器转换方法不一致)
 * 一个模型容器对象仅关联一个图模型，可以通过CModelMapper将图模型切分成子图*/
class CModelContainer
{
public:
	CModelContainer(CGraph* graph);
	virtual ~CModelContainer();

	typedef vector<CModelObj*> ModelVec;
	typedef map<CUDataValue, CModelObj*> ModelIndex;
	typedef map<CUDataValue, CModelObj*>::iterator ModelIndexIterator;
	typedef map<CModelObj*,set<CPropertyContainer*> > ModelGraphIndex;
	typedef map<CModelObj::ObjType,vector<CModelObj*> > ModelTypeMap;

	/*向图中添加模型对象*/
	virtual void addModelObj(CModelObj& obj);
	/*从图中删除模型对象*/
	virtual void delModelObj(CModelObj& obj);
	/*删除图中某对象的属性，注意首先要确保已经调用addModelObj添加了模型*/
	void delModelObjProperty(CModelObj& obj, const string property_name);
	/*向图中的对象添加属性，注意首先要确保已经调用addModelObj添加了模型*/
	void addModelObjProperty(CModelObj& obj, const string property_name, CUDataValue& value);
	/*更新图中的对象*/
	void updateModelObj(CModelObj& obj);
	/*将所有模型转成图*/
	void transAllModelToGraph();

	CGraph* getGraph()
	{
		return _graph;
	}

protected:
	virtual bool addToGraph(CModelObj& obj, CGraph* graph);
	virtual bool delFromGraph(CModelObj& obj, CGraph* graph);

protected:
	ModelVec _modelVec; //原始模型
	ModelIndex _modelIndex; //模型索引
	ModelTypeMap _modelType;//模型类型-模型
	ModelGraphIndex _modelGraphMap;//模型与图模型对应
	CGraph* _graph;		//图模型
	unsigned int _modelNum;		//模型数量
};
}

#endif /* CMODELCONTAINER_H_ */
