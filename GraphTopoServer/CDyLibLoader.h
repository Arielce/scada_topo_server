/*
 * CDyLibLoader.h
 *
 *  Created on: 2018Äê3ÔÂ28ÈÕ
 *      Author: Ge.Wenlin
 */

#ifndef GRAPHTOPOSERVER_CDYLIBLOADER_H_
#define GRAPHTOPOSERVER_CDYLIBLOADER_H_

#include "CConfigurationInfo.h"
class QLibrary;
namespace SCADA_ALG
{

class CDyLibLoader
{
public:
	CDyLibLoader();
	virtual ~CDyLibLoader();

	int loadDynamicLoad( vector<TServicePara>& vec_lib_para );

private:
	vector<QLibrary*> m_libToClean;
};

} /* namespace SCADA_ALG */

#endif /* GRAPHTOPOSERVER_CDYLIBLOADER_H_ */
