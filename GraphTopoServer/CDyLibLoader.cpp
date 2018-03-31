/*
 * CDyLibLoader.cpp
 *
 *  Created on: 2018Äê3ÔÂ28ÈÕ
 *      Author: Ge.Wenlin
 */

#include <CDyLibLoader.h>
#include <QLibrary>
namespace SCADA_ALG
{

CDyLibLoader::CDyLibLoader()
{
	// TODO Auto-generated constructor stub

}

CDyLibLoader::~CDyLibLoader()
{
	int num = m_libToClean.size();
	for (int i=0;i<num;i++)
	{
		if (m_libToClean[i])
		{
			delete m_libToClean[i];
		}
	}
}

int CDyLibLoader::loadDynamicLoad(vector<TServicePara>& vec_lib_para)
{
	vector<TServicePara>::iterator it;
	for (it = vec_lib_para.begin();it != vec_lib_para.end(); it++)
	{
		printf("The lib name is %s\n",it->lib_name.c_str());
		QLibrary* lib = new QLibrary(it->lib_name.c_str());

		if (lib)
		{
			bool ret = lib->load();
			if (!ret)
			{
				printf("err:%s\n",lib->errorString().toStdString().c_str());
				assert(0);
			}
			it->lib_ptr = lib;
			m_libToClean.push_back(lib);
		}

	}
	return m_libToClean.size();
}

} /* namespace SCADA_ALG */
