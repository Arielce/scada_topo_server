//******************************************************************
//
// Author :     ZhaoTiger 
//
// function:    ͨ��IDL���壬������IDL����  
//
// time :       2003.05.12
//              2003.09.01   Modified by ZhaoTiger   ������������ APPKEYID �� APPID
//							2009.05.13   Modified by leibl for mcode								
//
//******************************************************************
//#include </usr/local/corba/idl/OB/Types.idl>
#include"mcode/mtypes.h"
//#include"public.h"
typedef vector<varchar>       StrSeq;
typedef vector<long>          LongSeq;
typedef vector<short>         ShortSeq;
//typedef vector<char>         CharSeq;
typedef binary          			CharSeq;

//typedef CORBA::LongSeq          LongSeq;
//typedef CORBA::ShortSeq         ShortSeq;
//typedef CORBA::CharSeq          CharSeq;

// C++�������Ͷ���
const short     C_DATATYPE_DEFAULT      = 0;
const short     C_DATATYPE_STRING       = 1;
const short     C_DATATYPE_UCHAR        = 2;
const short     C_DATATYPE_SHORT        = 3;
const short     C_DATATYPE_INT          = 4;
const short     C_DATATYPE_DATETIME     = 5;
const short     C_DATATYPE_FLOAT        = 6;
const short     C_DATATYPE_DOUBLE       = 7;
const short     C_DATATYPE_KEYID        = 8;
const short     C_DATATYPE_BINARY       = 9;
const short     C_DATATYPE_TEXT         = 10;
const short     C_DATATYPE_IMAGE        = 11;
const short     C_DATATYPE_APPKEYID     = 12;
const short     C_DATATYPE_APPID        = 13;
const short   	C_DATATYPE_UINT       	= 14;
const short   	C_DATATYPE_LONG       	= 15;

// KEY_ID �ṹ
//struct TKeyID
//{
//        long    record_id;
//        short   column_id;
//};
//
// APP_KEY_ID�ṹ
//struct TAppKeyID
//{
//        long    app_id;
//        long    record_id;
//        short   column_id;
//};
//
// APP_ID�ṹ
//struct TAppID
//{
//        long    app_id;
//        long    record_id;
//};

typedef long TKeyID;

struct TAppKeyID
{
	int app_id;
	TKeyID key_id;
};

typedef TAppKeyID TAppID;

// ������ݶ���
struct UDataValue
{
				int type;
				union{
        varchar						c_string;//C_DATATYPE_STRING
        unsigned char			c_uchar;//C_DATATYPE_UCHAR
        short							c_short;//C_DATATYPE_SHORT
        int								c_int;//C_DATATYPE_INT
        long 							c_time;//C_DATATYPE_DATETIME
        float							c_float;//C_DATATYPE_FLOAT
        double						c_double;//C_DATATYPE_DOUBLE
        TKeyID						c_keyid;//C_DATATYPE_KEYID
        CharSeq						c_binary;//C_DATATYPE_BINARY
        CharSeq						c_text;//C_DATATYPE_TEXT
        CharSeq						c_image;//C_DATATYPE_IMAGE
        TAppKeyID					c_appkeyid;//C_DATATYPE_APPKEYID
        TAppID						c_appid;//C_DATATYPE_APPID
        char							c_default;//C_DATATYPE_DEFAULT
        unsigned int			c_uint;//C_DATATYPE_UINT
        long 							c_long;//C_DATATYPE_LONG
        }_val;
};
typedef vector<UDataValue>    SEQDataValue;

// ������Ϣ�ṹ
struct TDBErrorStru
{
        unsigned int           error_no;
        varchar                  error_msg;
};

// ������Ϣ�ṹ����
typedef vector<TDBErrorStru> SEQDBErrorStru;
