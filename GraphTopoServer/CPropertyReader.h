/*
 * CPropertyReader.h
 *
 *  Created on: 2018Äê2ÔÂ1ÈÕ
 *      Author: Ge.Wenlin
 */

#ifndef CPROPERTYREADER_H_
#define CPROPERTYREADER_H_
#include "CModel.h"
namespace SCADA_ALG
{
class CPropertyReaderImpl;
class CPropertyReader
{
public:
	CPropertyReader();
	virtual ~CPropertyReader();

	static void loadConfigure(const string& fileName);
	static int getServiceInfo(const string& cmdStr,IPropertyInfo& service_info);
	static int getPropertyInfo(const string& modelCatagory,CPropertyInfo::PropertyTypeInfoMap& property_info);
	static int getAllPropertyInfo(CPropertyInfo::PropertyMap& propertys);
	static int getAllServiceInfo(CPropertyInfo::PropertyInfoMap& vecCmdStr);
private:
	static CPropertyReaderImpl *_impl;
};

} /* namespace SCADA_ALG */

#endif /* CPROPERTYREADER_H_ */
