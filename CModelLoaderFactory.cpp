/*
 * CModelLoaderFactory.cpp
 *
 *  Created on: 2018年1月30日
 *      Author: Ge.Wenlin
 */

#include <CModelLoaderFactory.h>

namespace SCADA_ALG
{
static CModelLoaderFactory* loader_factory_ = 0;

std::auto_ptr<IModelLoader> create_rt_loader(); //关系模型加载
std::auto_ptr<IModelLoader> create_file_loader();//文件模型加载
//std::auto_ptr<IModelLoader> create_gdb_loader(); //图模型加载
CModelLoaderFactory::CModelLoaderFactory()
{
	// TODO Auto-generated constructor stub

}

CModelLoaderFactory& CModelLoaderFactory::getInstance()
{
	if (!loader_factory_)
	{
		std::auto_ptr<CModelLoaderFactory> af(new CModelLoaderFactory);

		af->registerCreator("rt", &create_rt_loader);
		af->registerCreator("file",&create_file_loader);
		//af->registerCreator("gdb", &create_gdb_loader);

		loader_factory_ = af.release();
	}

	return *loader_factory_;
}

void CModelLoaderFactory::registerCreator(const std::string& class_name,
		create_function_t create_function)
{
	const_iterator i = creators_.find(class_name);
	if (i != creators_.end())
		throw std::invalid_argument(
				"ModelLoader creator for type name '" + class_name + "' already registered");

	creators_[class_name] = create_function;
}

std::auto_ptr<IModelLoader> CModelLoaderFactory::create(const std::string& class_name)
{
	const_iterator i = creators_.find(class_name);
	if (i == creators_.end())
		throw std::invalid_argument("There is no ModelLoader with type name '" + class_name + "'");

	return (*i->second)();
}

bool CModelLoaderFactory::registered(const std::string& class_name) const
{
	return creators_.end() != creators_.find(class_name);
}
} /* namespace SCADA_ALG */
