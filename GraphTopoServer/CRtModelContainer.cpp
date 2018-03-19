/*
 * CRtModelContainer.cpp
 *
 *  Created on: 2018年2月12日
 *      Author: Ge.Wenlin
 */

#include "CRtModelContainer.h"
#include "CConfigurationInfo.h"
//#include "system.h"
#include "db_api/odb_tablenet.h"
namespace SCADA_ALG
{

CRtModelContainer::CRtModelContainer(CGraph* graph) :
		CModelContainer(graph)
{
	_relGraph = new CGraph("model_relationship");
}
CRtModelContainer::~CRtModelContainer()
{

}
void CRtModelContainer::addModelObj(CModelObj& obj)
{
	CModelContainer::addModelObj(obj); //调用父类的函数加入模型

	//以下建立模型层次关系，比如变压器绕组-变压器；交流线段端点-交流线段
	IPropertyInfo::PropertyInfoMap property = obj.getProperty();
	IPropertyInfo::PropertyInfoMapIterator itp;
	CModelObj::const_iterator it;
	for (it = obj.begin(); it != obj.end(); it++) //遍历模型的域信息
	{
		itp = property.find(it->first); //根据域名称找到对应的域属性
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //转换成描述实时库的属性
		assert(p != NULL);
		TRACE("name %s, hasParent %d\n", p->name().c_str(), p->hasParent() == true ? 1 : 0)
;
		if (p->hasParent()) //如果有父设备
		{
			CVertex* v = _relGraph->createVertex(obj.keyValue().c_long());
			CUDataValue parent_id = obj[p->name()];
			TRACE("parent_id is %ld\n",parent_id.c_long())
;
			CVertex* pv = _relGraph->createVertex(parent_id.c_long());
			v->createEdgeTo(pv->getId(), v->getId());
		}
	}

	addToGraph(obj, _graph);

}
void CRtModelContainer::delModelObj(CModelObj& obj)
{
	CModelContainer::delModelObj(obj);

	IPropertyInfo::PropertyInfoMap property = obj.getProperty();
	IPropertyInfo::PropertyInfoMapIterator itp;
	CModelObj::const_iterator it;
	for (it = obj.begin(); it != obj.end(); it++) //遍历模型的域信息
	{
		itp = property.find(it->first); //根据域名称找到对应的属性
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //转换成描述实时库的属性
		if (p->hasParent()) //如果有父设备
		{
			CEdge* e = _relGraph->findEdgeById(obj.keyValue().c_long());
			assert(e != NULL);
			delete e;
			//return;
		}
	}
	delFromGraph(obj, _graph);
}
bool CRtModelContainer::addToGraph(CModelObj& obj, CGraph* graph)
{
	IPropertyInfo::PropertyInfoMap property = obj.getProperty();
	IPropertyInfo::PropertyInfoMapIterator itp;
	CModelObj::const_iterator it;

	bool ret = false;
	const CUDataValue obj_id = obj.keyValue();
	int vcount = 0;
	CVertex* fv = NULL; //first vertex模型的第一个连接点
	for (it = obj.begin(); it != obj.end(); it++) //遍历模型的域
	{
		itp = property.find(it->first); //根据域名称找到对应的属性
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //转换成描述实时库的属性
		TRACE("p name is %s\n",p->name().c_str())
;
		if (p->isLink()) //表示连接点，转成CVertex
		{
			long id = obj[p->name()].c_long(); //连接点ID
			TRACE("link id ===== %ld \n",id)
;
			if (!checkLinkValid(id))
			{
				continue;
			}
			if (vcount == 0)
			{
				fv = graph->createVertex(id);
				_modelGraphMap[&obj].insert(fv);
				ret = true;
			}
			else
			{
				CVertex* v = graph->createVertex(id); //为连接点创建图节点
				_modelGraphMap[&obj].insert(v);
				CEdge* e = fv->createEdgeTo(id, obj_id.c_long()); //创建指向连接点的边，实时库的id必须是long
				assert(e != NULL);
				_modelGraphMap[&obj].insert(e);
				e->addLabel(graph->createLabel(obj.getObjType())); //将模型对象类型作为边的标签
				ret = true;
			}
			vcount++;
		}

	}
	if (fv == NULL)
	{
		TRACE("create vertex failed!\n")
;
		return false;
	}
	for (it = obj.begin(); it != obj.end(); it++)
	{
		itp = property.find(it->first); //根据域名称找到对应的属性
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //转换成描述实时库的属性
		if (p->hasParent()) //如果有父设备(比如：主网变压器、交流线段)
		{
			CUDataValue parent_id = obj[p->name()];
			ModelIndexIterator it_parent = _modelIndex.find(parent_id);
			if (it_parent == _modelIndex.end())
			{
				printf("%ld 未找到父对象%ld, field_name is %s\n", obj_id.c_long(),parent_id.c_long(),p->name().c_str());
				continue;
			}
			CVertex* v = _relGraph->findVertexById(obj_id.c_long());
			CVertex* pv = _relGraph->findVertexById(parent_id.c_long());
			vector<CEdge*> vec_edges = pv->getEdges();
			printf("vec edges size is %d ,v id = %ld , pv id = %ld\n", vec_edges.size(), v->getId(), pv->getId());
			int no = 0;
			for (vector<CEdge*>::iterator it = vec_edges.begin(); it != vec_edges.end(); ++it, ++no)
			{
				CVertex* oppv = (*it)->getOppVertex(pv); //层次图中与pv对侧的点
				if (oppv != v)
				{
					long opp_id = oppv->getId();
					ModelIndexIterator it_opp = _modelIndex.find(CUDataValue().c_long(opp_id));
					if (it_opp == _modelIndex.end())
					{
						printf("未找到对侧对象%ld\n", opp_id);
						continue;
					}
					CModelObj* opp_obj = it_opp->second; //通过id找到对侧点的模型指针
					printf("opp_obj keyvalue is %ld\n", opp_obj->keyValue().c_long());
					IPropertyInfo::PropertyInfoMap opp_property = opp_obj->getProperty(); //找到该模型对应的属性信息
					string tmp = CConfigurationInfo::getInst()->getAttributeValue(opp_property, "link"); //属性信息中link属性对应的值
					if (tmp.empty())
					{
						printf("未找到 %ld 的连接点属性\n", opp_id);
						continue;
					}
					int is_link = atoi(tmp.c_str());
					if (is_link == 0)
					{
						continue;
					}
					vector<IPropertyInfo*> vec_tmp;
					vec_tmp = CConfigurationInfo::getInst()->getPropertyInfoByAttrName(opp_property, "link");
					if (vec_tmp.empty())
					{
						continue;
					}

					IPropertyInfo* property = vec_tmp[0]; //找到此模型属性名称有link的域属性
					string field_name = property->name(); //is_link域的域名称
					long link_id = (*opp_obj)[field_name].c_long(); //根据域名称得到对侧对象的节点号
					if (!checkLinkValid(link_id))
					{
						continue;
					}
					CVertex* opp_v = graph->createVertex(link_id); //创建节点号在图中的点
					_modelGraphMap[opp_obj].insert(opp_v);
					//_modelGraphMap[opp_obj].insert(v);
					//long e_id = parent_id.c_long();
					//assert(no < 10); //不超过10个子设备
					//SET_RECORD_ID(e_id, GET_RECORD_ID(e_id) * 10 + no);
					CEdge* e = fv->createEdgeTo(link_id, opp_id);						//创建pv和opp_v之间的边，边的id为对端设备id
					_modelGraphMap[it_parent->second].insert(e);						//边都作为父对象对应的图模型，比如线段模型对应两个线端创建的边，变压器模型对应三个绕组创建的三条边
					e->addLabel(graph->createLabel(it_parent->second->getObjType()));	//将父对象的类型作为边的标签
					ret = true;
				}
			}
		}
	}

	return ret;
}
bool CRtModelContainer::delFromGraph(CModelObj& obj, CGraph* graph)
{
	IPropertyInfo::PropertyInfoMap property = obj.getProperty();
	IPropertyInfo::PropertyInfoMapIterator itp;
	CModelObj::const_iterator it;

	bool ret = false;
	const CUDataValue obj_id = obj.keyValue();
	int vcount = 0;
	CVertex* fv = NULL; //first vertex模型的第一个连接点
	for (it = obj.begin(); it != obj.end(); it++) //遍历模型的域
	{
		itp = property.find(it->first); //根据域名称找到对应的属性
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //转换成描述实时库的属性
		if (p->isLink())
		{
			long id = obj[p->name()].c_long(); //连接点ID
			if (!checkLinkValid(id))
			{
				continue;
			}
			if (vcount == 0)
			{
				fv = graph->findVertexById(id);
				if (fv)
				{
					fv->freeVertex();
				}
				ret = true;
			}
			else
			{
				CVertex* v = graph->findVertexById(id);
				if (v)
				{
					v->freeVertex();
				}
				CEdge* e = graph->findEdgeById(obj_id.c_long());
				if (e)
				{
					delete e;
				}
				ret = true;
			}
			vcount++;
		}
		if (p->hasProperty("sub"))
		{
			set<CPropertyContainer*>::iterator it_set;
			for (it_set = _modelGraphMap[&obj].begin(); it_set != _modelGraphMap[&obj].end(); it_set++)
			{
				CEdge* e = dynamic_cast<CEdge*>(*it_set);
				if (e)
				{
					delete e;
				}
			}
			ret = true;
		}
	}

	return ret;
}
bool CRtModelContainer::checkLinkValid(SCA_ND_ID id)
{
	if (id == -1)
	{
		return false;
	}
	return true;
}
void CRtModelContainer::debugPrint()
{
	ModelIndexIterator it;
	for (it = _modelIndex.begin(); it != _modelIndex.end(); it++)
	{
		//printf("debugPrint : obj id = %ld , address is %x \n",it->first.c_long(),it->second);
		printf("app type is %s \n", it->second->getAppType().c_str());
		printf("obj type is %s \n", it->second->getObjType().c_str());
		it->second->debugPrint();
	}
}
}
