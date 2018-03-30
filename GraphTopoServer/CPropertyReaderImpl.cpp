/*
 * CPropertyReaderImpl.cpp
 *
 *  Created on: 2018年2月1日
 *      Author: Ge.Wenlin
 */

#include <CPropertyReaderImpl.h>
#include <iostream>
#include <QDomDocument>
#include <QFile>
namespace SCADA_ALG
{

CPropertyReaderImpl::CPropertyReaderImpl()
{
	// TODO Auto-generated constructor stub
	m_qDom = new QDomDocument("conf");
}

CPropertyReaderImpl::~CPropertyReaderImpl()
{
	// TODO Auto-generated destructor stub
	vector<IPropertyInfo*>::iterator it_vec;
	for (it_vec = m_vecPropertyForCleaner.begin(); it_vec != m_vecPropertyForCleaner.end(); it_vec++)
	{
		delete *it_vec;
	}
}
void CPropertyReaderImpl::loadConfigure(const string& fileName)
{
	//QDomDocument doc("conf");
	QFile file(fileName.c_str());
	if (!file.open(QIODevice::ReadOnly))
		return;
	if (!m_qDom->setContent(&file))
	{
		file.close();
		return;
	}
	file.close();

	// print out the element names of all elements that are direct children
	// of the outermost element.
	QDomElement docElem = m_qDom->documentElement();

	QDomNode n = docElem.firstChild();
	while (!n.isNull())
	{
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if (!e.isNull())
		{
			std::cout << qPrintable(e.tagName()) << std::endl; // the node really is an element.
			if (e.tagName() == "service")
			{
				parseServiceProperty("service", &n);
			}
			else
			{
				parseModelProperty(e.tagName().toStdString().c_str(), &n);
			}
		}
		n = n.nextSibling();
	}

}
void CPropertyReaderImpl::parseModelProperty(const char* tagName, const QDomNode* node)
{
	//typedef map<string,CPropertyInfo> PropertyInfoMap; //eg. "id" - propertyinfo , "nd" - propertyinfo
	//typedef map<string,PropertyInfoMap> PropertyTypeInfoMap;  //eg. "breaker"
	assert(node != NULL);
	QDomNode n = *node;
	if (!n.isNull())
	{
		QDomNodeList nodes = n.childNodes();
		int num = nodes.count();
		int i = 0;
		CPropertyInfo::ObjPropertyInfoMap property_map;
		for (; i < num; i++)
		{
			QDomNode node = nodes.item(i);
			string model_type = node.toElement().tagName().toStdString();
			int tab_no = 0;
			int field_num = 0, field_count = 0;
			int j = 0;
			QDomNodeList sub_nodes = node.childNodes();
			int sub_num = sub_nodes.count();
			CPropertyInfo::PropertyInfoMap p_map;
			for (; j < sub_num; j++)
			{
				QDomNode sub_node = sub_nodes.item(j);
				QDomElement e = sub_node.toElement();
				if (e.isNull())
				{
					continue;
				}
				std::cout << qPrintable(e.tagName()) << std::endl; //tab/field_num/field

				if (e.tagName() == "prop")
				{
					field_count++;
					IPropertyInfo *property = new CPropertyInfo();

					QDomNamedNodeMap attrs = e.attributes();
					int num = attrs.length();
					for (int i = 0; i < num; i++)
					{
						QDomAttr attr = attrs.item(i).toAttr();
						(*property)(attr.name().toStdString(), attr.value().toStdString());
					}

					m_vecPropertyForCleaner.push_back(property);

					p_map.insert(make_pair(property->name(), property));
					std::cout << qPrintable(e.attribute("name")) << std::endl;
				}

			}
			property_map.insert(make_pair(model_type, p_map));
			//CPropertyInfo::mapTabObjType.insert( make_pair(tab_no,model_type) ); //建立表号和名称关系
			std::cout << qPrintable(node.toElement().tagName()) << std::endl; //model type
		}
		m_mapModelProperty.insert(make_pair(tagName, property_map));
	}
	if (!checkConfigureValid())
	{
		printf("configuration file check failed!!! error!");
		exit(0);
	}
}
void CPropertyReaderImpl::parseServiceProperty(const char* tagName, const QDomNode* node)
{
	QString tag = QString("%1").arg(tagName);
	if (tag != "service")
	{
		return;
	}
	m_mapServiceInfo.clear();
	assert(node != NULL);
	QDomNode n = *node;
	QDomNodeList nodes = n.childNodes();

	int num = nodes.count();
	printf("num is %d \n", num);
	int i = 0;
	for (; i < num; i++)
	{
		QDomElement e = nodes.item(i).toElement();
		string cmd = e.attribute("name").toStdString();
		string port = e.attribute("port").toStdString();
		string app = e.attribute("app").toStdString();

		CPropertyInfo* p = new CPropertyInfo();
		(*p)("name", cmd)("port", port)("app", app);
		//m_mapServicePort[cmd] = port;
		m_mapServiceInfo.insert(make_pair(cmd, p));
		m_vecPropertyForCleaner.push_back(p);

		printf("cmd = %s , port = %s\n", cmd.c_str(), port.c_str());
	}
}

int CPropertyReaderImpl::getPropertyInfo(const string& modelCatagory, CPropertyInfo::ObjPropertyInfoMap& propertyInfo)
{
	propertyInfo = m_mapModelProperty[modelCatagory];
	printf("size is %d \n", propertyInfo.size());
	return propertyInfo.size();
}

int CPropertyReaderImpl::getServiceInfo(const string& cmdStr, IPropertyInfo& service_info)
{
	service_info = *(m_mapServiceInfo[cmdStr]);
	return 1;
}
int CPropertyReaderImpl::getAllPropertyInfo(CPropertyInfo::AppPropertyInfoMap& propertys)
{
	propertys = m_mapModelProperty;
	return propertys.size();
}
int CPropertyReaderImpl::getAllServiceInfo(CPropertyInfo::PropertyInfoMap& service_infos)
{
	service_infos = m_mapServiceInfo;
	return m_mapServiceInfo.size();
}
bool CPropertyReaderImpl::checkConfigureValid()
{
	return true;
}
} /* namespace SCADA_ALG */
