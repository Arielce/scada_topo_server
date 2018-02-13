/*
 * CGraphManager.h
 *
 *  Created on: 2018��2��7��
 *      Author: Ge.Wenlin
 */

#ifndef CGRAPHMANAGER_H_
#define CGRAPHMANAGER_H_

namespace SCADA_ALG
{
class CModelMapper;
class CModelContainer;
/*ͼ�����࣬Ϊ����
 * ������ö�̬���еĹ��߽���ģ�ͼ��ء�������з֡��������˷������������ںϵ���Ҫ����
 * �Ƿ������ĺ����࣬Ϊ�������ṩ���õ�����ģ��*/
class CGraphManager
{
private:
	CGraphManager();
public:
	CGraphManager* inst();
	virtual ~CGraphManager();

private:
	CModelMapper *m_modelMapper;//ģ�ͷ�����
	CModelContainer *m_modelContainer;//ģ������
};

} /* namespace SCADA_ALG */

#endif /* CGRAPHMANAGER_H_ */
