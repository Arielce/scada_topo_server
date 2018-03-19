/*
 * CRtModelContainer.cpp
 *
 *  Created on: 2018��2��12��
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
	CModelContainer::addModelObj(obj); //���ø���ĺ�������ģ��

	//���½���ģ�Ͳ�ι�ϵ�������ѹ������-��ѹ���������߶ζ˵�-�����߶�
	IPropertyInfo::PropertyInfoMap property = obj.getProperty();
	IPropertyInfo::PropertyInfoMapIterator itp;
	CModelObj::const_iterator it;
	for (it = obj.begin(); it != obj.end(); it++) //����ģ�͵�����Ϣ
	{
		itp = property.find(it->first); //�����������ҵ���Ӧ��������
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //ת��������ʵʱ�������
		assert(p != NULL);
		TRACE("name %s, hasParent %d\n", p->name().c_str(), p->hasParent() == true ? 1 : 0)
;
		if (p->hasParent()) //����и��豸
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
	for (it = obj.begin(); it != obj.end(); it++) //����ģ�͵�����Ϣ
	{
		itp = property.find(it->first); //�����������ҵ���Ӧ������
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //ת��������ʵʱ�������
		if (p->hasParent()) //����и��豸
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
	CVertex* fv = NULL; //first vertexģ�͵ĵ�һ�����ӵ�
	for (it = obj.begin(); it != obj.end(); it++) //����ģ�͵���
	{
		itp = property.find(it->first); //�����������ҵ���Ӧ������
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //ת��������ʵʱ�������
		TRACE("p name is %s\n",p->name().c_str())
;
		if (p->isLink()) //��ʾ���ӵ㣬ת��CVertex
		{
			long id = obj[p->name()].c_long(); //���ӵ�ID
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
				CVertex* v = graph->createVertex(id); //Ϊ���ӵ㴴��ͼ�ڵ�
				_modelGraphMap[&obj].insert(v);
				CEdge* e = fv->createEdgeTo(id, obj_id.c_long()); //����ָ�����ӵ�ıߣ�ʵʱ���id������long
				assert(e != NULL);
				_modelGraphMap[&obj].insert(e);
				e->addLabel(graph->createLabel(obj.getObjType())); //��ģ�Ͷ���������Ϊ�ߵı�ǩ
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
		itp = property.find(it->first); //�����������ҵ���Ӧ������
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //ת��������ʵʱ�������
		if (p->hasParent()) //����и��豸(���磺������ѹ���������߶�)
		{
			CUDataValue parent_id = obj[p->name()];
			ModelIndexIterator it_parent = _modelIndex.find(parent_id);
			if (it_parent == _modelIndex.end())
			{
				printf("%ld δ�ҵ�������%ld, field_name is %s\n", obj_id.c_long(),parent_id.c_long(),p->name().c_str());
				continue;
			}
			CVertex* v = _relGraph->findVertexById(obj_id.c_long());
			CVertex* pv = _relGraph->findVertexById(parent_id.c_long());
			vector<CEdge*> vec_edges = pv->getEdges();
			printf("vec edges size is %d ,v id = %ld , pv id = %ld\n", vec_edges.size(), v->getId(), pv->getId());
			int no = 0;
			for (vector<CEdge*>::iterator it = vec_edges.begin(); it != vec_edges.end(); ++it, ++no)
			{
				CVertex* oppv = (*it)->getOppVertex(pv); //���ͼ����pv�Բ�ĵ�
				if (oppv != v)
				{
					long opp_id = oppv->getId();
					ModelIndexIterator it_opp = _modelIndex.find(CUDataValue().c_long(opp_id));
					if (it_opp == _modelIndex.end())
					{
						printf("δ�ҵ��Բ����%ld\n", opp_id);
						continue;
					}
					CModelObj* opp_obj = it_opp->second; //ͨ��id�ҵ��Բ���ģ��ָ��
					printf("opp_obj keyvalue is %ld\n", opp_obj->keyValue().c_long());
					IPropertyInfo::PropertyInfoMap opp_property = opp_obj->getProperty(); //�ҵ���ģ�Ͷ�Ӧ��������Ϣ
					string tmp = CConfigurationInfo::getInst()->getAttributeValue(opp_property, "link"); //������Ϣ��link���Զ�Ӧ��ֵ
					if (tmp.empty())
					{
						printf("δ�ҵ� %ld �����ӵ�����\n", opp_id);
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

					IPropertyInfo* property = vec_tmp[0]; //�ҵ���ģ������������link��������
					string field_name = property->name(); //is_link���������
					long link_id = (*opp_obj)[field_name].c_long(); //���������Ƶõ��Բ����Ľڵ��
					if (!checkLinkValid(link_id))
					{
						continue;
					}
					CVertex* opp_v = graph->createVertex(link_id); //�����ڵ����ͼ�еĵ�
					_modelGraphMap[opp_obj].insert(opp_v);
					//_modelGraphMap[opp_obj].insert(v);
					//long e_id = parent_id.c_long();
					//assert(no < 10); //������10�����豸
					//SET_RECORD_ID(e_id, GET_RECORD_ID(e_id) * 10 + no);
					CEdge* e = fv->createEdgeTo(link_id, opp_id);						//����pv��opp_v֮��ıߣ��ߵ�idΪ�Զ��豸id
					_modelGraphMap[it_parent->second].insert(e);						//�߶���Ϊ�������Ӧ��ͼģ�ͣ������߶�ģ�Ͷ�Ӧ�����߶˴����ıߣ���ѹ��ģ�Ͷ�Ӧ�������鴴����������
					e->addLabel(graph->createLabel(it_parent->second->getObjType()));	//���������������Ϊ�ߵı�ǩ
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
	CVertex* fv = NULL; //first vertexģ�͵ĵ�һ�����ӵ�
	for (it = obj.begin(); it != obj.end(); it++) //����ģ�͵���
	{
		itp = property.find(it->first); //�����������ҵ���Ӧ������
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //ת��������ʵʱ�������
		if (p->isLink())
		{
			long id = obj[p->name()].c_long(); //���ӵ�ID
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
