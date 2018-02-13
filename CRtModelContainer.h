/*
 * CRtModelContainer.h
 *
 *  Created on: 2018年2月12日
 *      Author: Ge.Wenlin
 */

#ifndef CRTMODELCONTAINER_H_
#define CRTMODELCONTAINER_H_
#include <CModelContainer.h>

namespace SCADA_ALG
{
/*
 * 关系型数据库添加模型对象
 * 在基类维护模型对象的基础上通过外键等建立模型层次关系，模型层次关系用也图来表示
 * */
class CRtModelContainer: public CModelContainer
{
public:
	CRtModelContainer(CGraph* graph);
	~CRtModelContainer();
public:
	/*向图中添加模型对象*/
	virtual void addModelObj(CModelObj& obj);
	/*从图中删除模型对象*/
	virtual void delModelObj(CModelObj& obj);

	void debugPrint();

protected:
	virtual bool transToGraph(CModelObj& obj, CGraph* graph);


private:
	bool checkLinkValid( SCA_ND_ID id );
private:
	CGraph* _relGraph;		//表示模型层次关系的图
};

}



#endif /* CRTMODELCONTAINER_H_ */
