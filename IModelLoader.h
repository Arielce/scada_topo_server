/*
 * IModelLoader.h
 *
 *  Created on: 2018年2月1日
 *      Author: Ge.Wenlin
 */

#ifndef IMODELLOADER_H_
#define IMODELLOADER_H_
#include "CModel.h"
#include "CModelContainer.h"
namespace SCADA_ALG
{
/*模型加载器
 * 将模型加载到CmodelContainer中*/
typedef long KEY_TYPE;//关键字必须是long型
class IModelLoader
{
public:
	virtual ~IModelLoader(){}
	/*向CModelContainer中加载所有app_str应用下的模型*/
	virtual void loadModelTo(CModelContainer& container,const string& app_str) = 0;
	/*向CModelContainer中加载app_str应用下关键字为key的模型*/
	virtual void loadOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key) = 0;
	/*从CModelContainer中删除所有app_str应用下的模型*/
	virtual void delModelFrom(CModelContainer& container,const string& app_str) = 0;
	/*从CModelContainer中删除app_str应用下关键字是key的模型*/
	virtual void delOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key) = 0;
	/**/
	virtual void refreshCbStatus(CModelContainer& container,const string& app_str) = 0;
	virtual void refreshCbStatusByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key) = 0;
};

} /* namespace SCADA_ALG */

#endif /* IMODELLOADER_H_ */
