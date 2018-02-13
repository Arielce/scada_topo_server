/*
 * CModelRtLoader.h
 *
 *  Created on: 2018Äê2ÔÂ1ÈÕ
 *      Author: Ge.Wenlin
 */

#ifndef CMODELRTLOADER_H_
#define CMODELRTLOADER_H_

#include <IModelLoader.h>
#include "GetAllRecFromRealdb.h"
namespace SCADA_ALG
{

class CModelRtLoader: public IModelLoader
{
public:
	CModelRtLoader();
	virtual ~CModelRtLoader();

	virtual void loadModelTo(CModelContainer& container,const string& app_str);
	virtual void loadOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key);

private:
	void loadModelFromRtdb(CModelContainer& container,const string& app_str,const int& app_no);
	void loadModelFromRtdbByKey(CModelContainer& container,const string& app_str,const int& app_no,const KEY_TYPE& key);

	void loadModel(CModelContainer& container,const IPropertyInfo::PropertyInfoMap& pinfo);
	char* assembleObjs(const CBuffer& buf, int record_num,
			const std::string& app_str, const CModelObj::ObjType& obj_type,
			IPropertyInfo::PropertyInfoMap& pinfo, std::vector<FIELD_BASE_INFO>& vec_field_info,CModelContainer& container);
};

} /* namespace SCADA_ALG */

#endif /* CMODELRTLOADER_H_ */
