/*
 * CPropertyReaderImpl.h
 *
 *  Created on: 2018年2月1日
 *      Author: Ge.Wenlin
 */

#ifndef CPROPERTYREADERIMPL_H_
#define CPROPERTYREADERIMPL_H_
#include "CModel.h"
class QDomDocument;
class QDomNode;
namespace SCADA_ALG
{
class CPropertyReaderImpl
{
public:
	CPropertyReaderImpl();
	virtual ~CPropertyReaderImpl();

	void loadConfigure(const string& fileName);
	int getServiceInfo(const string& cmdStr,IPropertyInfo& service_info);
	int getPropertyInfo(const string& modelCatagory,CPropertyInfo::PropertyTypeInfoMap& property_info);
	int getAllPropertyInfo(CPropertyInfo::PropertyMap& propertys);
	int getAllServiceInfo(CPropertyInfo::PropertyInfoMap& vecCmdStr);

private:
	void parseModelProperty(const char* tagName,const QDomNode* node);
	void parseServiceProperty(const char* tagName,const QDomNode* node);
	bool checkConfigureValid();//校验配置文件的正确性
private:
	//map<string,int> m_mapServicePort;//ems-10098 ; dms-10099 ;...
	CPropertyInfo::PropertyInfoMap m_mapServiceInfo;
	CPropertyInfo::PropertyMap m_mapModelProperty;
	vector<IPropertyInfo*> m_vecPropertyForCleaner;

	QDomDocument *m_qDom;
};

} /* namespace SCADA_ALG */

#endif /* CPROPERTYREADERIMPL_H_ */
