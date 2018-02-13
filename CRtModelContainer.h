/*
 * CRtModelContainer.h
 *
 *  Created on: 2018��2��12��
 *      Author: Ge.Wenlin
 */

#ifndef CRTMODELCONTAINER_H_
#define CRTMODELCONTAINER_H_
#include <CModelContainer.h>

namespace SCADA_ALG
{
/*
 * ��ϵ�����ݿ����ģ�Ͷ���
 * �ڻ���ά��ģ�Ͷ���Ļ�����ͨ������Ƚ���ģ�Ͳ�ι�ϵ��ģ�Ͳ�ι�ϵ��Ҳͼ����ʾ
 * */
class CRtModelContainer: public CModelContainer
{
public:
	CRtModelContainer(CGraph* graph);
	~CRtModelContainer();
public:
	/*��ͼ�����ģ�Ͷ���*/
	virtual void addModelObj(CModelObj& obj);
	/*��ͼ��ɾ��ģ�Ͷ���*/
	virtual void delModelObj(CModelObj& obj);

	void debugPrint();

protected:
	virtual bool transToGraph(CModelObj& obj, CGraph* graph);


private:
	bool checkLinkValid( SCA_ND_ID id );
private:
	CGraph* _relGraph;		//��ʾģ�Ͳ�ι�ϵ��ͼ
};

}



#endif /* CRTMODELCONTAINER_H_ */
