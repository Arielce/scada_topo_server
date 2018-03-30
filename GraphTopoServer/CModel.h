/*
 * CModel.h
 *
 *  Created on: 2018锟�0锟�2锚2锟�0锟�8锟�0锟�01锟�0锟�6锟�0锟�9
 *      Author: Ge.Wenlin
 */

#ifndef CMODEL_H_
#define CMODEL_H_
//#include "CUDataValue.h"
//#include "CGraph.h"
#include "graphcore_global.h"
namespace SCADA_ALG
{

/* 閰嶇疆淇℃伅鍩虹被
 * 鐢ㄦ潵鎻忚堪妯″瀷閰嶇疆鏂囦欢涓殑淇℃伅
 * 妯″瀷閰嶇疆鏂囦欢涓篨ML鏍煎紡锛屾敮鎸佸叧绯绘ā鍨嬪拰鍥炬ā鍨嬬殑鎻忚堪
 * 閫氳繃_mapKv鏉ヤ繚瀛樺睘鎬у拰鍊�
 * 绫诲瀷PropertyInfoMap琛ㄧず灞炴�у悕绉板拰灞炴�т俊鎭殑鏄犲皠锛屽睘鎬т俊鎭湪鍏崇郴妯″瀷閰嶇疆鏂囦欢涓负涓�涓煙鐨勪俊鎭紝姣斿id鍩熺殑淇℃伅锛屽寘鎷煙鍚嶇О銆侀暱搴︺�佹槸鍚﹀叧閿瓧
 * 绫诲瀷PropertyTypeInfoMap琛ㄧず涓�绫绘ā鍨嬪璞＄殑鍚嶇О鍜屾墍鏈夊睘鎬т俊鎭殑鏄犲皠锛屾瘮濡傚湪鍏崇郴妯″瀷閰嶇疆鏂囦欢涓彲浠ヨ〃绀哄紑鍏冲拰寮�鍏崇殑鍩熷睘鎬т箣闂寸殑鏄犲皠
 * 绫诲瀷PropertyMap琛ㄧず搴旂敤鍩熷拰璇ュ簲鐢ㄥ煙涓嬬殑鎵�鏈夌被鍨嬬殑妯″瀷瀵硅薄灞炴�т箣闂寸殑鏄犲皠锛屾瘮濡俥ms鍜宔ms涓嬫墍鏈夎澶囩被鍨嬬殑灞炴�ф槧灏�*/
class IPropertyInfo
{
public:
	IPropertyInfo()
	{
	}
	virtual ~IPropertyInfo()
	{
	}
	virtual string& operator[](const string& p) = 0;
	virtual const string& name() = 0;
	virtual const bool isKey() = 0;
	virtual IPropertyInfo& operator()(const string property_name, const string property_value) = 0;
/*
	void setPropertyType(const string type)
	{
		_ptype = type;
	}
	string getPropertyType()
	{
		return _ptype;
	}
*/
	typedef map<string, string>::const_iterator const_iterator;
	const_iterator find(const std::string& t) const
	{
		return _mapKv.find(t);
	}
	const_iterator begin() const
	{
		return _mapKv.begin();
	}
	const_iterator end() const
	{
		return _mapKv.end();
	}
	bool hasProperty(const std::string& t)const
	{
		return (find(t) != end());
	}

	typedef map<string, IPropertyInfo*> PropertyInfoMap; //eg. "id" - propertyinfo , "nd" - propertyinfo
	typedef map<string, PropertyInfoMap> ObjPropertyInfoMap;  //eg. "breaker"
	typedef map<string, ObjPropertyInfoMap> AppPropertyInfoMap;  //eg. "ems" - property

	typedef map<string, IPropertyInfo*>::iterator PropertyInfoMapIterator;
	typedef map<string, PropertyInfoMap>::iterator ObjPropertyInfoMapIterator;
	typedef map<string, ObjPropertyInfoMap>::iterator AppPropertyInfoMapIterator;
protected:
	map<string, string> _mapKv;//attribute key-value
	//string _ptype;//property type
};

/*鍏崇郴搴撳睘鎬ф弿杩�*/
class CPropertyInfo: public IPropertyInfo
{
public:
	CPropertyInfo();
	~CPropertyInfo();

	/*鍩熷悕绉�*/
	virtual const string& name()
	{
		return _name;
	}
	/*鍩熺被鍨�*/
	const CUDataValue::DATA_TYPE& type()
	{
		return _type;
	}
	/*鏄惁鏄妭鐐瑰彿鍩�*/
	const bool isLink()
	{
		return _isLink;
	}
	/*鏄惁鏄彲浠ヨ〃绀烘ā鍨嬪紑鏂殑鍩�*/
	const bool isCb()
	{
		return _isCb;
	}
	/*鏄惁鏄叧閿瓧鍩�*/
	const bool isKey()
	{
		return _isKey;
	}
	/*鏄惁澶栭敭*/
	const bool hasParent()
	{
		return _hasParent;
	}
	const short len()
	{
		return _len;
	}
	/*琛ㄥ彿*/
	const int tabNo()
	{
		return _tabNo;
	}
	/*鍩熷彿*/
	const int fieldNo()
	{
		return _fieldNo;
	}

	virtual string& operator[](const string& p)
	{
		return _mapKv[p];
	}
	virtual CPropertyInfo& operator()(const string property_name, const string property_value);

private:
	string _name;
	CUDataValue::DATA_TYPE _type;
	short _len;
	bool _isLink;
	bool _isCb;
	bool _isKey;
	bool _hasParent;
	int _tabNo;
	short _fieldNo;
};
/*鍥惧簱灞炴�ф弿杩�
 * 鏆傛湭瀹炵幇*/
class CGdbProperty: public IPropertyInfo
{
public:
	CGdbProperty();
	~CGdbProperty();
};

/*妯″瀷瀵硅薄
 * 鐢ㄦ潵鎻忚堪涓�涓叿浣撶殑搴旂敤妯″瀷锛屾瘮濡備竴涓壒瀹氱殑寮�鍏�
 * 閫氳繃PropertyNameValueMap灞炴�у悕绉板拰灞炴�у�兼槧灏勬潵瀛樺偍妯″瀷鐨勪俊鎭�
 * 绫诲瀷ObjType鐢ㄦ潵琛ㄧず妯″瀷鐨勭被鍨嬶紝涓嶪PropertyInfo::PropertyTypeInfoMap鐨刱ey瀵瑰簲锛屽嵆涓庢ā鍨嬫弿杩伴厤缃枃浠朵腑鐨勬ā鍨嬬被鍨嬪搴�
 * 蹇呴』閫氳繃setObjType鍜宻etAppType璁剧疆搴旂敤绫诲瀷鍜屽璞＄被鍨嬶紝鍚﹀垯鏃犳硶鑾峰緱璇ュ璞＄殑灞炴��*/
class CModelObj
{
public:
	typedef map<string, CUDataValue> PropertyNameValueMap;  //property name -- property value
	typedef string ObjType;
	typedef string AppType;

	CModelObj();
	CModelObj(const CModelObj& obj);  //鎷疯礉鏋勯�犲嚱鏁�
	~CModelObj();

	/*寰楀埌妯″瀷鐨勫叧閿瓧鍚嶇О*/
	const string& keyName();
	/*寰楀埌妯″瀷鐨勫叧閿瓧鍊�*/
    CUDataValue keyValue() ;
	/*鑾峰彇璇ユā鍨嬬殑灞炴�э紝鍗冲睘鎬у悕绉�-灞炴�т俊鎭紝姣斿鍦ㄥ叧绯绘ā鍨嬩腑鍗充负鍩熷悕绉板拰鍩熷睘鎬�*/
	const IPropertyInfo::PropertyInfoMap& getProperty();
	void setProperty(IPropertyInfo::PropertyInfoMap& property);
	/*涓烘ā鍨嬫坊鍔犲睘鎬у拰鍊�*/
	CModelObj& operator()(const string pname, const CUDataValue& pvalue);
	/*閫氳繃灞炴�у悕绉拌幏鍙栧��*/
	CUDataValue operator[](const string pname);
	/*璧嬪�兼搷浣滅*/
	CModelObj& operator=(const CModelObj& obj);
	/*姣旇緝涓や釜妯″瀷鏄惁涓�鑷达紝鍏抽敭瀛楀�间竴鑷村嵆璁や负涓�鑷�*/
    bool operator==(CModelObj& obj);
	/*璁剧疆妯″瀷绫诲瀷锛屾瘮濡傗�渂reaker鈥濓紝浠庢ā鍨嬩俊鎭厤缃枃浠朵腑寰楀埌*/
	void setObjType(const ObjType type)
	{
		m_objType = type;
	}
	/*璁剧疆搴旂敤绫诲瀷锛屾瘮濡傗�渆ms鈥濃�渄ms鈥濓紝浠庢ā鍨嬩俊鎭厤缃枃浠朵腑寰楀埌*/
	void setAppType(const AppType type)
	{
		m_appType = type;
		printf("setAppType %s\n", m_appType.c_str());
	}
	const ObjType& getObjType()
	{
		return m_objType;
		printf("setObjType %s\n", m_objType.c_str());
	}
	const AppType& getAppType()
	{
		return m_appType;
	}

	typedef PropertyNameValueMap::const_iterator const_iterator;
	typedef PropertyNameValueMap::iterator iterator;
	const_iterator find(const std::string& t) const
	{
		return m_mapProperty.find(t);
	}
	const_iterator begin() const
	{
		return m_mapProperty.begin();
	}
	const_iterator end() const
	{
		return m_mapProperty.end();
	}
	void erase(const_iterator it)
	{
		m_mapProperty.erase(it->first);
	}

	void debugPrint();
private:
	PropertyNameValueMap m_mapProperty; //灞炴�у悕绉�-鍊� e.g "id"-888888888
	ObjType m_objType; //瀵硅薄绫诲瀷"breaker"
	AppType m_appType; //瀵硅薄鎵�灞炵殑搴旂敤锛屾瘮濡俥ms/dms/other
	IPropertyInfo::PropertyInfoMap *m_objProperty;
	string m_keyName; //鍏抽敭瀛楀悕绉�
};

} /* namespace SCADA_ALG */

#endif /* CMODEL_H_ */
