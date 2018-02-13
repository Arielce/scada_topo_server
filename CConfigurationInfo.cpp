/*
 * CConfigurationInfo.cpp
 *
 *  Created on: 2018Äê2ÔÂ12ÈÕ
 *      Author: Ge.Wenlin
 */

#include <CConfigurationInfo.h>

namespace SCADA_ALG
{

CConfigurationInfo::CConfigurationInfo()
{
	// TODO Auto-generated constructor stub

}

CConfigurationInfo::~CConfigurationInfo()
{
	// TODO Auto-generated destructor stub
}
IPropertyInfo::PropertyInfoMap& CConfigurationInfo::getProperty(const CModelObj::AppType& apptype,
		const CModelObj::ObjType& objtype)
{
	IPropertyInfo::PropertyMapIterator it_type;
	IPropertyInfo::PropertyTypeInfoMapIterator it;
	it_type = _propertyInfo.find(apptype);
	if (it_type != _propertyInfo.end())
	{
		it = it_type->second.find(objtype);
		if (it != it_type->second.end())
		{
			return it->second;
		}
	}
	return _propertyInfo[""][""];
}
IPropertyInfo::PropertyTypeInfoMap& CConfigurationInfo::getAppProperty(const CModelObj::AppType& apptype)
{
	IPropertyInfo::PropertyMapIterator it_type;

	it_type = _propertyInfo.find(apptype);
	if (it_type != _propertyInfo.end())
	{
		return it_type->second;
	}
	return _propertyInfo[""];
}
IPropertyInfo::PropertyMap& CConfigurationInfo::getAllProperty()
{
	return _propertyInfo;
}
const string CConfigurationInfo::getAttributeValue(IPropertyInfo::PropertyInfoMap& property,const string& attr_name)
{
	IPropertyInfo::const_iterator it_attr;
	IPropertyInfo::PropertyInfoMapIterator it;
	for (it = property.begin(); it != property.end(); it++)
	{
		it_attr = it->second->find(attr_name);
		if (it_attr != it->second->end())
		{
			return it_attr->second;
		}
	}
	return string("");
}
} /* namespace SCADA_ALG */
