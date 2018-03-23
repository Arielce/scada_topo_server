/*
 * CModelLoaderFactory.h
 *
 *  Created on: 2018Äê1ÔÂ30ÈÕ
 *      Author: Ge.Wenlin
 */

#ifndef CMODELLOADERFACTORY_H_
#define CMODELLOADERFACTORY_H_

#include <stdexcept>
//#include "CGraph.h"
#include "graphcore_global.h"
#include "IModelLoader.h"

namespace SCADA_ALG
{
	class SCADA_ALG_API CModelLoaderFactory
	{
	public:
		typedef std::auto_ptr<IModelLoader> (*create_function_t)();

		static CModelLoaderFactory& getInstance();
		void registerCreator(const std::string& class_name, create_function_t create_function);
		std::auto_ptr<IModelLoader> create(const std::string& class_name);
		bool registered(const std::string& class_name) const;

	private:
		CModelLoaderFactory();


		typedef std::map<std::string, create_function_t> creators_t;
		typedef creators_t::const_iterator const_iterator;

		creators_t creators_;
	};

} /* namespace SCADA_ALG */

#endif /* CMODELLOADERFACTORY_H_ */
