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
	virtual void loadModelTo(CModelContainer& container,const string& app_str) = 0;
	virtual void loadOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key) = 0;
};

} /* namespace SCADA_ALG */

#endif /* IMODELLOADER_H_ */
