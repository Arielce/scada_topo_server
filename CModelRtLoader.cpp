/*
 * CModelRtLoader.cpp
 *
 *  Created on: 2018年2月1日
 *      Author: Ge.Wenlin
 */

#include <CModelRtLoader.h>
#include <CPropertyReader.h>
#include <CConfigurationInfo.h>
namespace SCADA_ALG
{

CModelRtLoader::CModelRtLoader()
{
	// TODO Auto-generated constructor stub

}

CModelRtLoader::~CModelRtLoader()
{
	// TODO Auto-generated destructor stub
}
/*container 是存放模型的容器
 * app_str是服务程序的命令行参数*/
void CModelRtLoader::loadModelTo(CModelContainer& container, const string& app_str)
{
	//vector<string> vec_sys_types;
	//vector<string>::iterator it;
	CPropertyInfo::PropertyInfoMap service_info;
	CPropertyInfo::PropertyInfoMapIterator it_service;
	CPropertyReader::getAllServiceInfo(service_info);

	for (it_service = service_info.begin(); it_service != service_info.end(); it_service++)
	{
		CPropertyInfo* p = dynamic_cast<CPropertyInfo*>(it_service->second);
		assert(p != NULL);
		string app = (*p)["app"];
		int app_no = atoi(app.c_str());
		//string port = *(it_service->second)["port"];
		//int port_no = atoi(port.c_str());
		string name = (*p)["name"];
		if (name == app_str || app_str == "-all")		//如果命令行参数为-all表示加载所有模型
		{
			loadModelFromRtdb(container, app_str, app_no);
		}
	}

}
void CModelRtLoader::loadOneModelByKey(CModelContainer& container, const string& app_str,
		const KEY_TYPE& key)
{

}
char* CModelRtLoader::assembleObjs(const CBuffer& buf, int record_num, const string& app_str,
		const CModelObj::ObjType& obj_type, IPropertyInfo::PropertyInfoMap& pinfo,
		std::vector<FIELD_BASE_INFO>& vec_field_info, CModelContainer& container)
{
	//assert(record_size == buf.GetLength() / record_num); //todo check
	int record_size = buf.GetLength() / record_num;
	char* buf_ptr = buf.GetBufPtr();
	for (int i = 0; i < record_num; i++)
	{
		CModelObj model_obj;
		model_obj.setProperty(CConfigurationInfo::getInst()->getProperty(app_str, obj_type));
		model_obj.setAppType(app_str);
		model_obj.setObjType(obj_type);
		TRACE("app_str is %s,obj_type is %s \n ",app_str.c_str(),obj_type.c_str());
#if 1
		int j = 0;
		//buf_ptr += i * record_size;
		buf_ptr += record_size;
		IPropertyInfo::PropertyInfoMapIterator itp;
		CPropertyInfo* p = NULL;
		for (itp = pinfo.begin(); itp != pinfo.end(); itp++, j++)
		{
			char* fptr = buf_ptr + vec_field_info[j].offset;
			printf("buf_ptr = %d , offset is %d , j=%d\n",buf_ptr,vec_field_info[j].offset,j);
			p = dynamic_cast<CPropertyInfo*>(itp->second);
			printf("property field no is %d , vecfieldinfo field no is %d\n",p->fieldNo(),vec_field_info[j].field_no);
			if (p->fieldNo() < 0)
			{
				continue;
			}
			CUDataValue::DATA_TYPE type = p->type();
			switch (type)
			{
			case CUDataValue::C_DATATYPE_DOUBLE:
			{
				double dv = 0.0;
				memcpy((char*) (&dv), fptr, sizeof(double));
				model_obj(p->name(), CUDataValue().c_double(dv));
				//buf_ptr += j * sizeof(double);
				TRACE("field name is %s , value is %f \n ",p->name().c_str(),dv)
;			}
			break;
			case CUDataValue::C_DATATYPE_DATETIME:
			case CUDataValue::C_DATATYPE_LONG:
			case CUDataValue::C_DATATYPE_KEYID:
			{
				long lv = 0;
				memcpy((char*) (&lv), fptr, sizeof(long));
				model_obj(p->name(), CUDataValue().c_long(lv));
				TRACE("name is %s,long value is %ld\n",p->name().c_str(),lv);
				//buf_ptr += j * sizeof(long);
			}
			break;
			case CUDataValue::C_DATATYPE_FLOAT:
			{
				float fv = 0.0;
				memcpy((char*) (&fv), fptr, sizeof(float));
				model_obj(p->name(), CUDataValue().c_float(fv));
				//buf_ptr += j * sizeof(float);
				TRACE("field name is %s , value is %f \n ",p->name().c_str(),fv);
			}
			break;
			case CUDataValue::C_DATATYPE_INT:
			{
				int iv = 0;
				memcpy((char*) (&iv), fptr, sizeof(int));
				model_obj(p->name(), CUDataValue().c_int(iv));
				//buf_ptr += j * sizeof(int);
				TRACE("field name is %s , value is %d \n ",p->name().c_str(),iv);
			}
			break;
			case CUDataValue::C_DATATYPE_SHORT:
			{
				short sv = 0;
				memcpy((char*) (&sv), fptr, sizeof(short));
				model_obj(p->name(), CUDataValue().c_short(sv));
				//buf_ptr += j * sizeof(short);
				TRACE("field name is %s , value is %d \n ",p->name().c_str(),sv);
			}
			break;
			case CUDataValue::C_DATATYPE_STRING:
			case CUDataValue::C_DATATYPE_TEXT:
			{
				char str[1024];
				strncpy(str,fptr,strlen(fptr)+1);
				printf("str = %s\n",str);
				model_obj(p->name(), CUDataValue().c_string(str));
				assert(strlen(fptr) < p->len());
				//buf_ptr += j * p->len();
				TRACE("field name is %s , value is %s \n ",p->name().c_str(),str);
			}
			break;
			case CUDataValue::C_DATATYPE_UCHAR:
			{
				unsigned char ucv = 0;
				memcpy((char*) (&ucv), fptr, sizeof(unsigned char));
				model_obj(p->name(), CUDataValue().c_uchar(ucv));
				//buf_ptr += j * sizeof(unsigned char);
				//printf("uchar value is %d\n",ucv);
				TRACE("field name is %s , value is %d \n ",p->name().c_str(),ucv);
			}
			break;
			case CUDataValue::C_DATATYPE_UINT:
			{
				unsigned int uiv = 0;
				memcpy((char*) (&uiv), fptr, sizeof(unsigned int));
				model_obj(p->name(), CUDataValue().c_uint(uiv));
				//buf_ptr += j * sizeof(unsigned int);
				TRACE("field name is %s , value is %d \n ",p->name().c_str(),uiv);
			}
			break;
			default:
			{
				int v = 0;
				memcpy((char*) (&v), fptr, sizeof(int));
				model_obj(p->name(), CUDataValue().c_int(v));
				//buf_ptr += j * sizeof(int);
				TRACE("field name is %s , value is %d \n ",p->name().c_str(),v);
			}
			break;
		}
	}
#endif
		//model_obj.debugPrint();
		container.addModelObj(model_obj);
	}
	return buf_ptr;
}

void CModelRtLoader::loadModelFromRtdb(CModelContainer& container, const string& app_str,
		const int& app_no)
{
	IPropertyInfo::PropertyTypeInfoMap& appProperty = CConfigurationInfo::getInst()->getAppProperty(app_str);
	IPropertyInfo::PropertyTypeInfoMapIterator it;
	for (it = appProperty.begin(); it != appProperty.end(); it++)
	{
		CModelObj::ObjType obj_type = it->first;
		vector<int> vec_fields;
		CPropertyInfo* p = dynamic_cast<CPropertyInfo*>(it->second["tab"]);
		int tab = p->tabNo();
		printf("tab_no is %d \n", tab);
		IPropertyInfo::PropertyInfoMap pinfo = it->second;
		IPropertyInfo::PropertyInfoMapIterator itp;
		int record_size = 0;
		for (itp = pinfo.begin(); itp != pinfo.end(); itp++)
		{
			p = dynamic_cast<CPropertyInfo*>(itp->second);
			if (p->name() == "tab")
			{
				continue;
			}
			//field_name += p->name();
			vec_fields.push_back(p->fieldNo());
			printf("field_name is  %s , field_no  is %d ,len = %d\n", p->name().c_str(),
					p->fieldNo(), p->len());
			//record_size += p->len();
		}
		static NET_ODB::CTableNet tab_net;
		tab_net.Open(app_no, tab);

		std::vector<FIELD_BASE_INFO> vec_field_info;
		tab_net.GetFieldInfo(vec_fields, vec_field_info);
		//debug
		for (int i = 0; i < vec_fields.size(); i++)
		{
			printf("field %d\n", vec_fields[i]);
		}
		CBuffer buf;
		int record_num = RTDB_INTERFACE::GetAllRec<NET_ODB::CTableNet>(vec_fields, app_no, tab,
				buf);
		if (record_num > 0)
		{
			assembleObjs(buf, record_num, app_str, obj_type, pinfo, vec_field_info, container);
		}
	}

}
void CModelRtLoader::loadModelFromRtdbByKey(CModelContainer& container, const string& app_str,
		const int& app_no, const KEY_TYPE& key)
{
	int tab_no = GET_TABLE_NO(key);
	IPropertyInfo::PropertyTypeInfoMap& appProperty = CConfigurationInfo::getInst()->getAppProperty(app_str);
	IPropertyInfo::PropertyTypeInfoMapIterator it;
	for (it = appProperty.begin();
			it != appProperty.end(); it++)
	{
		CModelObj::ObjType obj_type = it->first;
		vector<int> vec_fields;
		CPropertyInfo* p = dynamic_cast<CPropertyInfo*>(it->second["tab"]);
		int tab = p->tabNo();
		if (tab == tab_no)
		{
			IPropertyInfo::PropertyInfoMap pinfo = it->second;
			IPropertyInfo::PropertyInfoMapIterator itp;
			int record_size = 0;
			for (itp = pinfo.begin(); itp != pinfo.end(); itp++)
			{
				p = dynamic_cast<CPropertyInfo*>(itp->second);
				vec_fields.push_back(p->fieldNo());
				record_size += p->len();
			}
			CBuffer buf;
			static NET_ODB::CTableNet tab_net;
			int ret = tab_net.Open(app_no, tab);
			if (ret != DB_OK)
			{
				return;
			}
			std::vector<FIELD_BASE_INFO> vec_field_info;
			tab_net.GetFieldInfo(vec_fields, vec_field_info);
			char* buf_ptr = NULL;
			int buf_size = 0;
			int record_num = tab_net.TableGetByKey((char*) &key, vec_fields, (char*) &buf_ptr,
					buf_size);
			buf.SetBuffer(buf_ptr, buf_size);

			if (record_num > 0)
			{
				assembleObjs(buf, record_num, app_str, obj_type, pinfo, vec_field_info, container);
			}
			return;
		}

	}

}

std::auto_ptr<IModelLoader> create_rt_loader()
{
	return std::auto_ptr<IModelLoader>(new CModelRtLoader());
}

} /* namespace SCADA_ALG */
