/*
 * CUDataValue.h
 *
 *  Created on: 2016Äê10ÔÂ14ÈÕ
 *      Author: Administrator
 */

#ifndef CUDATAVALUE_H_
#define CUDATAVALUE_H_

#include <string>

using namespace std;

namespace SCADA_ALG
{

    const short C_DATATYPE_DEFAULT = 0;
    const short C_DATATYPE_STRING = 1;
    const short C_DATATYPE_UCHAR = 2;
    const short C_DATATYPE_SHORT = 3;
    const short C_DATATYPE_INT = 4;
    const short C_DATATYPE_DATETIME = 5;
    const short C_DATATYPE_FLOAT = 6;
    const short C_DATATYPE_DOUBLE = 7;
    const short C_DATATYPE_KEYID = 8;
    const short C_DATATYPE_BINARY = 9;
    const short C_DATATYPE_TEXT = 10;
    const short C_DATATYPE_IMAGE = 11;
    const short C_DATATYPE_APPKEYID = 12;
    const short C_DATATYPE_APPID = 13;
    const short C_DATATYPE_UINT = 14;
    const short C_DATATYPE_LONG = 15;

    class CUDataValue
    {
    public:
        CUDataValue();
        ~CUDataValue();
        CUDataValue(const CUDataValue&);
        CUDataValue& operator=(const CUDataValue&);
        bool operator==(const CUDataValue&);
        short dataType();
        bool isInit();
        void clear();

        void c_string(const char*);
        void c_string(const string&);
        const char* c_string()const;

        const CUDataValue& c_uchar(const unsigned char);
        const unsigned char c_uchar()const;

        void c_short(const short);
        const short c_short()const;

        const CUDataValue& c_int(const int);
        const int c_int()const;

        void c_float(const float);
        const float c_float()const;

        void c_double(const double);
        const double c_double()const;

        void c_default(const char);
        const char c_default()const;

        void c_uint(const unsigned int);
        const unsigned int c_uint()const;

        const CUDataValue& c_long(const long);
        const long c_long()const;
    private:
        union
        {
            char*   c_string;
            unsigned char   c_uchar;
            short   c_short;
            int     c_int;
            float   c_float;
            double  c_double;
            char    c_default;
            unsigned int    c_uint;
            long     c_long;
        }m_value;
        bool m_init;
        unsigned short m_type;
    };

} /* namespace SCADA_ALG */
#endif /* CUDATAVALUE_H_ */
