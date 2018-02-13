/*
 * CPropertyReader.cpp
 *
 *  Created on: 2018Äê2ÔÂ1ÈÕ
 *      Author: Ge.Wenlin
 */

#include <CPropertyReader.h>
#include "CPropertyReaderImpl.h"
namespace SCADA_ALG
{
static CPropertyReaderImpl inst;
CPropertyReaderImpl *CPropertyReader::_impl = &inst;
CPropertyReader::CPropertyReader()
{
	// TODO Auto-generated constructor stub

}

CPropertyReader::~CPropertyReader()
{
	// TODO Auto-generated destructor stub
}

void CPropertyReader::loadConfigure(const string& fileName)
{
	_impl->loadConfigure(fileName);
}

int CPropertyReader::getPropertyInfo(const string& modelCatagory,CPropertyInfo::PropertyTypeInfoMap& propertyInfo)
{
	return _impl->getPropertyInfo(modelCatagory,propertyInfo);
	//return property_info.size();
}

int CPropertyReader::getServiceInfo(const string& cmdStr,IPropertyInfo& service_info)
{
	return _impl->getServiceInfo(cmdStr,service_info);
	//return port;
}
int CPropertyReader::getAllPropertyInfo(CPropertyInfo::PropertyMap& propertys)
{
	return _impl->getAllPropertyInfo(propertys);
}
int CPropertyReader::getAllServiceInfo(CPropertyInfo::PropertyInfoMap& vecCmdStr)
{
	return _impl->getAllServiceInfo(vecCmdStr);
}
} /* namespace SCADA_ALG */
