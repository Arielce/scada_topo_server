/*
 * CModel.cpp
 *
 *  Created on: 2018年2月1日
 *      Author: Ge.Wenlin
 */

#include <CModel.h>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <CConfigurationInfo.h>

namespace SCADA_ALG
{

CPropertyInfo::CPropertyInfo() :
		_name(""), _type(CUDataValue::C_DATATYPE_DEFAULT), _len(0), _isLink(false), _isCb(false), _isKey(
				false), _hasParent(false), _tabNo(-1), _fieldNo(-1)
{
}
CPropertyInfo::~CPropertyInfo()
{
}

CPropertyInfo& CPropertyInfo::operator()(const string property_name, const string property_value)
{
	if (property_name.empty() || property_value.empty()) //传入的参数异常
	{
		return *this;
	}
	printf("GGGGGG p = %s , v = %s \n", property_name.c_str(), property_value.c_str());
	_mapKv[property_name] = property_value;
	short value = 0;
	std::stringstream s;
	s << property_value;
	s >> value;
	if (property_name == "name")
	{
		_name = property_value;
	}
	else if (property_name == "key")
	{
		_isKey = value == 1 ? true : false;
	}
	else if (property_name == "link")
	{
		_isLink = value == 1 ? true : false;
	}
	else if (property_name == "type")
	{
		_type = (CUDataValue::DATA_TYPE) value;
		_len = CUDataValue::length(_type);
		printf("WWWWWW len is %d\n", _len);
	}
	else if (property_name == "len")
	{
		_len = value;
	}
	else if (property_name == "cb")
	{
		_isCb = value == 1 ? true : false;
	}
	else if (property_name == "parent")
	{
		_hasParent = true;
	}
	else if (property_name == "field_no")
	{
		short t = 0;
		std::stringstream ss;
		ss << property_value;
		ss >> t;
		_fieldNo = t;
	}
	else if (property_name == "tab")
	{
		int t = 0;
		std::stringstream ss;
		ss << property_value;
		ss >> t;
		_tabNo = t;
		_name = "tab";
		return *this;
	}

	return *this;
}
/*
 static IPropertyInfo::PropertyMap& _propertyInfoInst;  //属性字典
 static IPropertyInfo::PropertyMap property_info;
 IPropertyInfo::PropertyMap &CModelObj::_propertyInfoInst = property_info;
 */
CModelObj::CModelObj() :
		m_objType(""), m_appType(""), m_objProperty(NULL), m_keyName("")
{

}
CModelObj::CModelObj(const CModelObj& obj)
{
	this->m_appType = obj.m_appType;
	this->m_objType = obj.m_objType;
	//printf("%x",&(CModelObj::_propertyInfoInst));
	printf("CModelObj::constructor app %s , objtype %s \n", m_appType.c_str(), m_objType.c_str());
	m_objProperty = obj.m_objProperty;
	//this->m_keyName = keyName();
	this->m_mapProperty = obj.m_mapProperty;
	//m_objProperty = obj.m_objProperty;
}
CModelObj::~CModelObj()
{

}
const IPropertyInfo::PropertyInfoMap& CModelObj::getProperty()
{
	return *m_objProperty;
}
void CModelObj::setProperty(IPropertyInfo::PropertyInfoMap& property)
{
	m_objProperty = &property;
}
const string& CModelObj::keyName()
{
	if (!m_keyName.empty())
	{
		return m_keyName;
	}
	IPropertyInfo::PropertyInfoMap property = getProperty();
	IPropertyInfo::PropertyInfoMapIterator it;
	for (it = property.begin(); it != property.end(); it++)
	{
		printf("fname is %s ,%d\n", it->second->name().c_str(),
				it->second->isKey() == true ? 1 : 0);
		if (it->second->isKey())
		{
			m_keyName = it->first;
			return m_keyName;
		}
	}
	//todo 如果配置文件中没有指定哪个是关键字属性，需要记录日志并退出程序
	assert(1);
	return m_keyName;

}
const CUDataValue& CModelObj::keyValue()
{
	printf("key_name is %s \n", keyName().c_str());
	const_iterator it = find(keyName());
	if (it != end())
	{
		printf("find key_name %s\n", keyName().c_str());
		return it->second;
	}
	printf("can not find key_name %s\n", keyName().c_str());
	return CUDataValue();
	//return m_mapProperty[keyName()];
}
CModelObj& CModelObj::operator()(const string pname, const CUDataValue& pvalue)
{
	printf("obj insert name %s \n", pname.c_str());
	m_mapProperty.insert(make_pair(pname, pvalue));
	return *this;
}
CUDataValue CModelObj::operator[](const string pname)
{
	const_iterator it = find(pname);
	if (it != end())
	{
		return it->second;
	}
	return CUDataValue();
}
bool CModelObj::operator==(CModelObj& obj)
{
	return this->keyValue() == obj.keyValue();
}
CModelObj& CModelObj::operator=(const CModelObj& obj)
{
	if (this != &obj)
	{
		this->m_appType = obj.m_appType;
		this->m_objType = obj.m_objType;
		this->m_keyName = keyName();
		//this->m_keyName = obj.m_keyName;
		this->m_mapProperty = obj.m_mapProperty;
		//this->m_objProperty = obj.m_objProperty;
	}
	return *this;
}
void CModelObj::debugPrint()
{
	printf("========obj property======%s,%s\n", m_appType.c_str(), m_objType.c_str());
#if 1
	IPropertyInfo::PropertyTypeInfoMap &pp = CConfigurationInfo::getInst()->getAppProperty(
			m_appType);
	//IPropertyInfo::PropertyInfoMap &p = CConfigurationInfo::getInst()->getProperty(m_appType,m_objType);
	IPropertyInfo::PropertyInfoMap p = getProperty();
	IPropertyInfo::PropertyInfoMapIterator itp;
	for (itp = p.begin(); itp != p.end(); itp++)
	{
		printf("CModelObj::debugPrint : pro %s \n", itp->second->name().c_str());
	}

	printf("=======obj value======\n");
	map<string, CUDataValue>::iterator it;
	for (it = m_mapProperty.begin(); it != m_mapProperty.end(); it++)
	{
		printf("CModelObj::debugPrint : pro %s ,value is %x\n", it->first.c_str(), &(it->second));
	}
#endif
}
} /* namespace SCADA_ALG */
