/*
 * CModelFileLoader.h
 *
 *  Created on: 2018Äê3ÔÂ6ÈÕ
 *      Author: Ge.Wenlin
 */

#ifndef CMODELFILELOADER_H_
#define CMODELFILELOADER_H_
#include <IModelLoader.h>
namespace SCADA_ALG
{

class CModelFileLoader : public IModelLoader
{
public:
	CModelFileLoader();
	virtual ~CModelFileLoader();
	virtual void loadModelTo(CModelContainer& container,const string& app_str);
	virtual void loadOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key);
    virtual void delModelFrom(CModelContainer& container,const string& app_str);
    virtual void delOneModelByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key);
    virtual void refreshCbStatus(CModelContainer& container,const string& app_str);
    virtual void refreshCbStatusByKey(CModelContainer& container,const string& app_str,const KEY_TYPE& key);

private:
	void readModelFile(const string& file_name);
};

} /* namespace SCADA_ALG */

#endif /* CMODELFILELOADER_H_ */
