/*
 * IModelLoader.h
 *
 *  Created on: 2018��2��1��
 *      Author: Ge.Wenlin
 */

#ifndef IMODELLOADER_H_
#define IMODELLOADER_H_
#include "CModel.h"
#include "CModelContainer.h"
namespace SCADA_ALG
{
/*ģ�ͼ�����
 * ��ģ�ͼ��ص�CmodelContainer��*/
typedef long KEY_TYPE;//�ؼ��ֱ�����long��
class IModelLoader
{
public:
	virtual ~IModelLoader(){}
	/*��CModelContainer�м�������app_strӦ���µ�ģ��*/
	virtual void loadModelTo(CModelContainer& container,const string& app_str) = 0;
	/*��CModelContainer�м���app_strӦ���¹ؼ���Ϊkey��ģ��*/
	virtual void loadOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key) = 0;
	/*��CModelContainer��ɾ������app_strӦ���µ�ģ��*/
	virtual void delModelFrom(CModelContainer& container,const string& app_str) = 0;
	/*��CModelContainer��ɾ��app_strӦ���¹ؼ�����key��ģ��*/
	virtual void delOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key) = 0;
	/**/
	virtual void refreshCbStatus(CModelContainer& container,const string& app_str) = 0;
	virtual void refreshCbStatusByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key) = 0;
};

} /* namespace SCADA_ALG */

#endif /* IMODELLOADER_H_ */
