/*
 * CModel.h
 *
 *  Created on: 2018�0�2ê2�0�8�0�01�0�6�0�9
 *      Author: Ge.Wenlin
 */

#ifndef CMODEL_H_
#define CMODEL_H_
#include "CUDataValue.h"
#include "CGraph.h"
namespace SCADA_ALG
{

/* 配置信息基类
 * 用来描述模型配置文件中的信息
 * 模型配置文件为XML格式，支持关系模型和图模型的描述
 * 通过_mapKv来保存属性和值
 * 类型PropertyInfoMap表示属性名称和属性信息的映射，属性信息在关系模型配置文件中为一个域的信息，比如id域的信息，包括域名称、长度、是否关键字
 * 类型PropertyTypeInfoMap表示一类模型对象的名称和所有属性信息的映射，比如在关系模型配置文件中可以表示开关和开关的域属性之间的映射
 * 类型PropertyMap表示应用域和该应用域下的所有类型的模型对象属性之间的映射，比如ems和ems下所有设备类型的属性映射*/
class IPropertyInfo
{
public:
	IPropertyInfo()
	{
	}
	virtual ~IPropertyInfo()
	{
	}
	virtual string& operator[](const string& p) = 0;
	virtual const string& name() = 0;
	virtual const bool isKey() = 0;
	virtual IPropertyInfo& operator()(const string property_name, const string property_value) = 0;

	typedef map<string, string>::const_iterator const_iterator;
	const_iterator find(const std::string& t) const
	{
		return _mapKv.find(t);
	}
	const_iterator begin() const
	{
		return _mapKv.begin();
	}
	const_iterator end() const
	{
		return _mapKv.end();
	}
	bool hasProperty(const std::string& t)const
	{
		return (find(t) != end());
	}

	typedef map<string, IPropertyInfo*> PropertyInfoMap; //eg. "id" - propertyinfo , "nd" - propertyinfo
	typedef map<string, PropertyInfoMap> PropertyTypeInfoMap;  //eg. "breaker"
	typedef map<string, PropertyTypeInfoMap> PropertyMap;  //eg. "ems" - property

	typedef map<string, IPropertyInfo*>::iterator PropertyInfoMapIterator;
	typedef map<string, PropertyInfoMap>::iterator PropertyTypeInfoMapIterator;
	typedef map<string, PropertyTypeInfoMap>::iterator PropertyMapIterator;
protected:
	map<string, string> _mapKv;//attribute key-value
};

/*关系库属性描述*/
class CPropertyInfo: public IPropertyInfo
{
public:
	CPropertyInfo();
	~CPropertyInfo();

	/*域名称*/
	virtual const string& name()
	{
		return _name;
	}
	/*域类型*/
	const CUDataValue::DATA_TYPE& type()
	{
		return _type;
	}
	/*是否是节点号域*/
	const bool isLink()
	{
		return _isLink;
	}
	/*是否是可以表示模型开断的域*/
	const bool isCb()
	{
		return _isCb;
	}
	/*是否是关键字域*/
	const bool isKey()
	{
		return _isKey;
	}
	/*是否外键*/
	const bool hasParent()
	{
		return _hasParent;
	}
	const short len()
	{
		return _len;
	}
	/*表号*/
	const int tabNo()
	{
		return _tabNo;
	}
	/*域号*/
	const int fieldNo()
	{
		return _fieldNo;
	}

	virtual string& operator[](const string& p)
	{
		return _mapKv[p];
	}
	virtual CPropertyInfo& operator()(const string property_name, const string property_value);

private:
	string _name;
	CUDataValue::DATA_TYPE _type;
	short _len;
	bool _isLink;
	bool _isCb;
	bool _isKey;
	bool _hasParent;
	int _tabNo;
	short _fieldNo;
};
/*图库属性描述
 * 暂未实现*/
class CGdbProperty: public IPropertyInfo
{
public:
	CGdbProperty();
	~CGdbProperty();
};

/*模型对象
 * 用来描述一个具体的应用模型，比如一个特定的开关
 * 通过PropertyNameValueMap属性名称和属性值映射来存储模型的信息
 * 类型ObjType用来表示模型的类型，与IPropertyInfo::PropertyTypeInfoMap的key对应，即与模型描述配置文件中的模型类型对应
 * 必须通过setObjType和setAppType设置应用类型和对象类型，否则无法获得该对象的属性*/
class CModelObj
{
public:
	typedef map<string, CUDataValue> PropertyNameValueMap;  //property name -- property
	typedef string ObjType;
	typedef string AppType;

	CModelObj();
	CModelObj(const CModelObj& obj);  //拷贝构造函数
	~CModelObj();

	/*得到模型的关键字名称*/
	const string& keyName();
	/*得到模型的关键字值*/
	const CUDataValue& keyValue();
	/*获取该模型的属性，即属性名称-属性信息，比如在关系模型中即为域名称和域属性*/
	const IPropertyInfo::PropertyInfoMap& getProperty();
	void setProperty(IPropertyInfo::PropertyInfoMap& property);
	/*为模型添加属性和值*/
	CModelObj& operator()(const string pname, const CUDataValue& pvalue);
	/*通过属性名称获取值*/
	CUDataValue operator[](const string pname);
	/*赋值操作符*/
	CModelObj& operator=(const CModelObj& obj);
	/*比较两个模型是否一致，关键字值一致即认为一致*/
	bool operator==(CModelObj& obj);
	/*设置模型类型，比如“breaker”，从模型信息配置文件中得到*/
	void setObjType(const ObjType type)
	{
		m_objType = type;
	}
	/*设置应用类型，比如“ems”“dms”，从模型信息配置文件中得到*/
	void setAppType(const AppType type)
	{
		m_appType = type;
		printf("setAppType %s\n", m_appType.c_str());
	}
	const ObjType& getObjType()
	{
		return m_objType;
		printf("setObjType %s\n", m_objType.c_str());
	}
	const AppType& getAppType()
	{
		return m_appType;
	}

	typedef PropertyNameValueMap::const_iterator const_iterator;
	typedef PropertyNameValueMap::iterator iterator;
	const_iterator find(const std::string& t) const
	{
		return m_mapProperty.find(t);
	}
	const_iterator begin() const
	{
		return m_mapProperty.begin();
	}
	const_iterator end() const
	{
		return m_mapProperty.end();
	}
	void erase(const_iterator it)
	{
		m_mapProperty.erase(it->first);
	}

	void debugPrint();
private:
	PropertyNameValueMap m_mapProperty; //属性名称-值 e.g "id"-888888888
	ObjType m_objType; //对象类型"breaker"
	AppType m_appType; //对象所属的应用，比如ems/dms/other
	IPropertyInfo::PropertyInfoMap *m_objProperty;
	string m_keyName; //关键字名称
};

} /* namespace SCADA_ALG */

#endif /* CMODEL_H_ */
