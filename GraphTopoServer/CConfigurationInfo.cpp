/*
 * CConfigurationInfo.cpp
 *
 *  Created on: 2018年2月12日
 *      Author: Ge.Wenlin
 */

#include <CConfigurationInfo.h>
#include <QLibrary>
#include <QString>
#ifdef D5000
#include "paramanage.h"
#endif

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
IPropertyInfo::PropertyInfoMap& CConfigurationInfo::getProperty(const CModelObj::AppType& apptype, const CModelObj::ObjType& objtype)
{
	IPropertyInfo::AppPropertyInfoMapIterator it_type;
	IPropertyInfo::ObjPropertyInfoMapIterator it;
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
IPropertyInfo::ObjPropertyInfoMap& CConfigurationInfo::getObjPropertyByApp(const CModelObj::AppType& apptype)
{
	IPropertyInfo::AppPropertyInfoMapIterator it_type;

	it_type = _propertyInfo.find(apptype);
	if (it_type != _propertyInfo.end())
	{
		return it_type->second;
	}
	return _propertyInfo[""];
}
IPropertyInfo::AppPropertyInfoMap& CConfigurationInfo::getAllProperty()
{
	return _propertyInfo;
}
const string CConfigurationInfo::getAttributeValue(IPropertyInfo::PropertyInfoMap& property, const string& attr_name)
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
vector<IPropertyInfo*> CConfigurationInfo::getPropertyInfoByAttrName(IPropertyInfo::PropertyInfoMap& property, const string& attr_name)
{
	vector<IPropertyInfo*> vec_ret;
	IPropertyInfo::const_iterator it_attr;
	IPropertyInfo::PropertyInfoMapIterator it;
	for (it = property.begin(); it != property.end(); it++)
	{
		it_attr = it->second->find(attr_name);
		if (it_attr != it->second->end())
		{
			vec_ret.push_back(it->second);
		}
	}
	return vec_ret;
}
void CConfigurationInfo::loadDynamicLibPara(vector<TServicePara>& vec_lib_para)
{
	CParaManage* paraManage = CParaManage::CreateObject("topo_server_lib.ini");
	if (paraManage == NULL)
	{
		printf("打开配置文件 topo_server_lib.ini 错误！\n");
		return;
	}
	char tmp_buf[64];
	int ret_code = paraManage->GetKey("LIBINFO", "num", tmp_buf, 64);
	if (ret_code < 0)
	{
		printf("配置文件 topo_server_lib.ini 未配置动态库数量！\n");
		return;
	}
	int num = atoi(tmp_buf);
	char key_buf[64];
	for (int i = 0; i < num; i++)
	{
		TServicePara tmp_para;
		sprintf(key_buf, "name_%d", i + 1);
		ret_code = paraManage->GetKey("LIBINFO", key_buf, tmp_buf, 64);
		//todo check lib name valid
		if (ret_code < 0)
		{
			printf("获取动态库%d名称失败\n", i + 1);
			continue;
		}
		tmp_para.lib_name = tmp_buf;
		sprintf(key_buf, "srvid_%d", i + 1);
		ret_code = paraManage->GetKey("LIBINFO", key_buf, tmp_buf, 64);
		if (ret_code < 0)
		{
			printf("获取动态库%d功能码失败\n", i + 1);
			continue;
		}
		//parseFuncNo(tmp_buf, tmp_para.vec_func_no);
		tmp_para.srvid = atoi(tmp_buf);
		printf("parse srvid is %d\n",tmp_para.srvid);

		vec_lib_para.push_back(tmp_para);
	}
}
void CConfigurationInfo::parseFuncNo(char* buf, vector<int>& vec_out)
{

#if 0
	QString tmp_str = QString("%1").arg(buf);

	QStringList list = tmp_str.split(",", QString::SkipEmptyParts);

	QStringList::const_iterator constIterator;
	for (constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator)
	{
		bool ok = false;
		int no = (*constIterator).toInt(&ok);
		if (ok)
		{
			vec_out.push_back(no);
		}
		//cout << (*constIterator).toLocal8Bit().constData() << endl;
	}
#endif
}
} /* namespace SCADA_ALG */
