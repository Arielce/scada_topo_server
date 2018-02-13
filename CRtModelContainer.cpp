/*
 * CRtModelContainer.cpp
 *
 *  Created on: 2018��2��12��
 *      Author: Ge.Wenlin
 */

#include "CRtModelContainer.h"
#include "CConfigurationInfo.h"
#include "system.h"
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
#if 1
	//���½���ģ�Ͳ�ι�ϵ�������ѹ������-��ѹ���������߶ζ˵�-�����߶�
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
		assert(p != NULL);
		printf("name %s, hasParent %d\n",p->name().c_str(),p->hasParent()==true?1:0);
		if (p->hasParent()) //����и��豸
		{
			CVertex* v = _relGraph->createVertex(obj.keyValue().c_long());
			CUDataValue parent_id = obj[p->name()];
			CVertex* pv = _relGraph->createVertex(parent_id.c_long());
			v->createEdgeTo(pv->getId(), v->getId());
			return;
		}
	}
#endif
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
			return;
		}
	}
}
bool CRtModelContainer::transToGraph(CModelObj& obj, CGraph* graph)
{
	IPropertyInfo::PropertyInfoMap property = obj.getProperty();
	IPropertyInfo::PropertyInfoMapIterator itp;
	CModelObj::const_iterator it;

	bool ret = false;
	const CUDataValue obj_id = obj.keyValue();
	int vcount = 0;
	CVertex* fv = NULL;
	for (it = obj.begin(); it != obj.end(); it++) //����ģ�͵���
	{
		itp = property.find(it->first); //�����������ҵ���Ӧ������
		if (itp == property.end())
		{
			continue;
		}
		CPropertyInfo *p = dynamic_cast<CPropertyInfo*>(itp->second); //ת��������ʵʱ�������
		if (p->isLink()) //��ʾ���ӵ㣬ת��CVertex
		{
			long id = obj[p->name()].c_long();//���ӵ�ID
			if (!checkLinkValid(id))
			{
				continue;
			}
			if (vcount == 0)
			{
				fv = graph->createVertex(id);
				ret = true;
			}
			else
			{
				graph->createVertex(id);//Ϊ���ӵ㴴��ͼ�ڵ�
				CEdge* e = fv->createEdgeTo(id, obj_id.c_long()); //����ָ�����ӵ�ıߣ�ʵʱ���id������long
				assert(e!=NULL);
				e->addLabel(graph->createLabel(obj.getObjType())); //��ģ�Ͷ���������Ϊ�ߵı�ǩ
				ret = true;
			}
			vcount++;
		}
		if (p->hasParent()) //����и��豸
		{
			CUDataValue parent_id = obj[p->name()];
			CVertex* v = _relGraph->findVertexById(obj_id.c_long());
			CVertex* pv = _relGraph->findVertexById(parent_id.c_long());
			vector<CEdge*> vec_edges = pv->getEdges();
			printf("vec edges size is %d ,v id = %ld , pv id = %ld\n",vec_edges.size(),v->getId(),pv->getId());
			int no = 0;
			for (vector<CEdge*>::iterator it = vec_edges.begin(); it != vec_edges.end(); ++it, ++no)
			{
				CVertex* oppv = (*it)->getOppVertex(pv); //���ͼ����pv�Բ�ĵ�
				if (oppv != v)
				{
					long opp_id = oppv->getId();
					ModelIndexIterator it_opp = _modelIndex.find(  CUDataValue().c_long(opp_id) );
					if (it_opp == _modelIndex.end())
					{
						printf("δ�ҵ��Բ����%ld\n",opp_id);
						continue;
					}
					CModelObj* opp_obj = it_opp->second; //ͨ��id�ҵ��Բ���ģ��ָ��
					printf("opp_obj keyvalue is %ld\n",opp_obj->keyValue().c_long());
					IPropertyInfo::PropertyInfoMap opp_property = opp_obj->getProperty();
					string tmp = CConfigurationInfo::getInst()->getAttributeValue(opp_property,"link");
					//IPropertyInfo::PropertyInfoMapIterator it = opp_property.find("link");
					if (it == opp_property.end())//�����ӵ�
					{
						printf("δ�ҵ� %ld �����ӵ�����\n",opp_id);
						continue;
					}
					IPropertyInfo* property = it->second; //�ҵ���ģ������������is_link��������
					string field_name = property->name(); //is_link���������
					long link_id = (*opp_obj)[field_name].c_long(); //���������Ƶõ��Բ����Ľڵ��
					CVertex* opp_v = graph->createVertex(link_id); //�����ڵ����ͼ�еĵ�
					long e_id = parent_id.c_long();
					assert(no < 10); //������10�����豸
					SET_RECORD_ID(e_id, GET_RECORD_ID(e_id) * 10 + no);
					CEdge* e = fv->createEdgeTo(link_id, e_id); //����pv��opp_v֮��ıߣ��ߵ�idΪ�����豸��¼id*10+���豸˳���
					e->addLabel(graph->createLabel(opp_obj->getObjType())); //���������������Ϊ�ߵı�ǩ
					ret = true;
				}
			}
		}
	}
	return ret;
}
bool CRtModelContainer::checkLinkValid(SCA_ND_ID id)
{
	return true;
}
void CRtModelContainer::debugPrint()
{
	ModelIndexIterator it ;
	for (it = _modelIndex.begin();it != _modelIndex.end(); it++)
	{
		//printf("debugPrint : obj id = %ld , address is %x \n",it->first.c_long(),it->second);
		printf("app type is %s \n",it->second->getAppType().c_str());
		printf("obj type is %s \n",it->second->getObjType().c_str());
		it->second->debugPrint();
	}
}
}
