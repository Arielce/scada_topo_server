/*
 * CModelContainer.h
 *
 *  Created on: 2018��2��12��
 *      Author: Ge.Wenlin
 */

#ifndef CMODELCONTAINER_H_
#define CMODELCONTAINER_H_
#include <CModel.h>
//#include <CGraph.h>

namespace SCADA_ALG
{

/*ģ������
 * Ӧ��ģ�͵Ĵ洢����
 * �ṩģ����ӡ�ɾ�������µķ���
 * �ṩӦ��ģ��ת����ͼģ�͵ķ���(����ʵ�ֽ�������ʵ�֣���Ϊ��ͬ���͵�ģ��������Ӧ��ת��������ͬ�������ϵ��ģ�͵�ģ��������ͼģ������ת��������һ��)
 * һ��ģ���������������һ��ͼģ�ͣ�����ͨ��CModelMapper��ͼģ���зֳ���ͼ*/
class CModelContainer
{
public:
	CModelContainer(CGraph* graph);
	virtual ~CModelContainer();

	typedef vector<CModelObj*> ModelVec;
	//typedef map<string, ModelVec> ModelMap;
	typedef map<CUDataValue, CModelObj*> ModelIndex;
	typedef map<CUDataValue, CModelObj*>::iterator ModelIndexIterator;

	/*��ͼ�����ģ�Ͷ���*/
	virtual void addModelObj(CModelObj& obj);
	/*��ͼ��ɾ��ģ�Ͷ���*/
	virtual void delModelObj(CModelObj& obj);
	/*ɾ��ͼ��ĳ��������ԣ�ע������Ҫȷ���Ѿ�����addModelObj�����ģ��*/
	void delModelObjProperty(CModelObj& obj, const string property_name);
	/*��ͼ�еĶ���������ԣ�ע������Ҫȷ���Ѿ�����addModelObj�����ģ��*/
	void addModelObjProperty(CModelObj& obj, const string property_name, CUDataValue& value);
	/*����ͼ�еĶ���*/
	void updateModelObj(CModelObj& obj);
	/*������ģ��ת��ͼ*/
	void transAllModelToGraph();

	CGraph* getGraph()
	{
		return _graph;
	}

protected:
	virtual bool transToGraph(CModelObj& obj, CGraph* graph);

protected:
	ModelVec _modelVec; //ԭʼģ��
	ModelIndex _modelIndex; //ģ������
	CGraph* _graph;		//ͼģ��
	unsigned int _modelNum;		//ģ������
};
}

#endif /* CMODELCONTAINER_H_ */
