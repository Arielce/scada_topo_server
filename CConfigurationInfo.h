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
/*示例：
 * <ems> //表示应用类型 AppType
 	 <breaker> //表示对象类型 ObjType
 	 	 <tab>407</tab>   								//属性IPropertyInfo , 关系库配置文件对应的类是CPropertyInfo
 	 	 <field_num>5</field_num> 						//属性IPropertyInfo , 关系库配置文件对应的类是CPropertyInfo
 	 	 <field name="id" type="15" key="1">1</field>		//属性IPropertyInfo , 关系库配置文件对应的类是CPropertyInfo
 	 	 <field name="name" type="1" len="64">3</field>	//属性IPropertyInfo , 关系库配置文件对应的类是CPropertyInfo
 	 	 <field name="ind" type="15" link="1">9</field>	//属性IPropertyInfo , 关系库配置文件对应的类是CPropertyInfo
 	 	 <field name="jnd" type="15" link="1">10</field>	//属性IPropertyInfo , 关系库配置文件对应的类是CPropertyInfo
 	 	 <field name="point" type="2" cb="1">40</field>	//属性IPropertyInfo , 关系库配置文件对应的类是CPropertyInfo
 	 </breaker>
 </ems>
 * */
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
	/*根据应用类型和对象类型得到该对象类型相应的属性*/
	IPropertyInfo::PropertyInfoMap& getProperty(const CModelObj::AppType&, const CModelObj::ObjType&);
	/*根据应用类型得到该应用下所有对象的属性*/
	IPropertyInfo::PropertyTypeInfoMap& getAppProperty(const CModelObj::AppType&);
	/*得到所有的属性信息*/
	IPropertyInfo::PropertyMap& getAllProperty();
	/*根据输入的对象属性信息property以及属性信息中的属性名称得到属性值*/
	const string getAttributeValue(IPropertyInfo::PropertyInfoMap& property, const string& attr_name);
	/*根据输入的对象属性信息property以及属性信息中的属性名称得到属性指针*/
	vector<IPropertyInfo*> getPropertyInfoByAttrName(IPropertyInfo::PropertyInfoMap& property, const string& attr_name);
private:
	CConfigurationInfo();
	IPropertyInfo::PropertyMap _propertyInfo;
};

} /* namespace SCADA_ALG */

#endif /* CCONFIGURATIONINFO_H_ */
