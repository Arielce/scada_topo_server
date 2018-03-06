/*
 * CConfigurationInfo.h
 *
 *  Created on: 2018��2��12��
 *      Author: Ge.Wenlin
 */

#ifndef CCONFIGURATIONINFO_H_
#define CCONFIGURATIONINFO_H_
#include "CModel.h"
namespace SCADA_ALG
{
/*
 static IPropertyInfo::PropertyMap& _propertyInfoInst;  //�����ֵ�
 static IPropertyInfo::PropertyMap property_info;
 IPropertyInfo::PropertyMap &CModelObj::_propertyInfoInst = property_info;
 */
/*ʾ����
 * <ems> //��ʾӦ������ AppType
 	 <breaker> //��ʾ�������� ObjType
 	 	 <tab>407</tab>   								//����IPropertyInfo , ��ϵ�������ļ���Ӧ������CPropertyInfo
 	 	 <field_num>5</field_num> 						//����IPropertyInfo , ��ϵ�������ļ���Ӧ������CPropertyInfo
 	 	 <field name="id" type="15" key="1">1</field>		//����IPropertyInfo , ��ϵ�������ļ���Ӧ������CPropertyInfo
 	 	 <field name="name" type="1" len="64">3</field>	//����IPropertyInfo , ��ϵ�������ļ���Ӧ������CPropertyInfo
 	 	 <field name="ind" type="15" link="1">9</field>	//����IPropertyInfo , ��ϵ�������ļ���Ӧ������CPropertyInfo
 	 	 <field name="jnd" type="15" link="1">10</field>	//����IPropertyInfo , ��ϵ�������ļ���Ӧ������CPropertyInfo
 	 	 <field name="point" type="2" cb="1">40</field>	//����IPropertyInfo , ��ϵ�������ļ���Ӧ������CPropertyInfo
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
	/*����Ӧ�����ͺͶ������͵õ��ö���������Ӧ������*/
	IPropertyInfo::PropertyInfoMap& getProperty(const CModelObj::AppType&, const CModelObj::ObjType&);
	/*����Ӧ�����͵õ���Ӧ�������ж��������*/
	IPropertyInfo::PropertyTypeInfoMap& getAppProperty(const CModelObj::AppType&);
	/*�õ����е�������Ϣ*/
	IPropertyInfo::PropertyMap& getAllProperty();
	/*��������Ķ���������Ϣproperty�Լ�������Ϣ�е��������Ƶõ�����ֵ*/
	const string getAttributeValue(IPropertyInfo::PropertyInfoMap& property, const string& attr_name);
	/*��������Ķ���������Ϣproperty�Լ�������Ϣ�е��������Ƶõ�����ָ��*/
	vector<IPropertyInfo*> getPropertyInfoByAttrName(IPropertyInfo::PropertyInfoMap& property, const string& attr_name);
private:
	CConfigurationInfo();
	IPropertyInfo::PropertyMap _propertyInfo;
};

} /* namespace SCADA_ALG */

#endif /* CCONFIGURATIONINFO_H_ */
