/*
 * CConfigurationInfo.h
 *
 *  Created on: 2018年2月12日
 *      Author: Ge.Wenlin
 */

#ifndef CCONFIGURATIONINFO_H_
#define CCONFIGURATIONINFO_H_
#include "CModel.h"
namespace SCADA_ALG
{
/*
static IPropertyInfo::PropertyMap& _propertyInfoInst;  //属性字典
static IPropertyInfo::PropertyMap property_info;
IPropertyInfo::PropertyMap &CModelObj::_propertyInfoInst = property_info;
*/
class CConfigurationInfo
{
public:
	static CConfigurationInfo* getInst()
	{
		static CConfigurationInfo _inst;
		return &_inst;
	}
	virtual ~CConfigurationInfo();

public:
	IPropertyInfo::PropertyInfoMap& getProperty(const CModelObj::AppType&,const CModelObj::ObjType&);
	IPropertyInfo::PropertyTypeInfoMap& getAppProperty(const CModelObj::AppType&);
	IPropertyInfo::PropertyMap& getAllProperty();
	const string getAttributeValue(IPropertyInfo::PropertyInfoMap& property,const string& attr_name);
private:
	CConfigurationInfo();
	IPropertyInfo::PropertyMap  _propertyInfo;
};

} /* namespace SCADA_ALG */

#endif /* CCONFIGURATIONINFO_H_ */
