/*
 * CModelFileLoader.cpp
 *
 *  Created on: 2018Äê3ÔÂ6ÈÕ
 *      Author: Ge.Wenlin
 */

#include <CModelFileLoader.h>

namespace SCADA_ALG
{

CModelFileLoader::CModelFileLoader()
{
	// TODO Auto-generated constructor stub
    //add sth
}

CModelFileLoader::~CModelFileLoader()
{
	// TODO Auto-generated destructor stub
}
void CModelFileLoader::loadModelTo(CModelContainer& container,const string& app_str)
{
	return;
}
void CModelFileLoader::loadOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key)
{
	return;
}
void CModelFileLoader::delModelFrom(CModelContainer& container,const string& app_str)
{
   return;
}
void CModelFileLoader::delOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key)
{
    return ;
}
void CModelFileLoader::refreshCbStatus(CModelContainer& container,const string& app_str)
{
    return;
}
void CModelFileLoader::refreshCbStatusByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key)
{
    return;
}
void CModelFileLoader::readModelFile(const string& file_name)
{
	//todo load models from file
	return;
}
std::auto_ptr<IModelLoader> create_file_loader()
{
	return std::auto_ptr<IModelLoader>(new CModelFileLoader());
}
} /* namespace SCADA_ALG */
