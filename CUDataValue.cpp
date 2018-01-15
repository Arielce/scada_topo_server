/*
 * CUDataValue.cpp
 *
 *  Created on: 2016Äê10ÔÂ14ÈÕ
 *      Author: Administrator
 */

#include "CUDataValue.h"
#include <cstring>
#include <cassert>
using namespace std;

namespace SCADA_ALG
{

    CUDataValue::CUDataValue()
        :m_init(false),m_type(0)
    {
        // TODO Auto-generated constructor stub

    }

    CUDataValue::~CUDataValue()
    {
        // TODO Auto-generated destructor stub
    }

    CUDataValue::CUDataValue(const CUDataValue& udata)
        :m_init(false),m_type(0)
    {
        *this = udata;
    }

    CUDataValue& CUDataValue::operator=(const CUDataValue& udata)
    {
        if (this == &udata)
        {
            return *this;
        }
        clear();
        if (!udata.m_init)
        {
            return *this;
        }
        m_init = true;
        m_type = udata.m_type;
        switch(m_type)
        {
        case C_DATATYPE_STRING:
        {
            m_value.c_string = new char[ strlen(udata.m_value.c_string)+1 ];
            strcpy(m_value.c_string,udata.m_value.c_string);
            break;
        }
        case C_DATATYPE_UCHAR:
        {
            m_value.c_uchar = udata.m_value.c_uchar;
            break;
        }
        case C_DATATYPE_SHORT:
        {
            m_value.c_short = udata.m_value.c_short;
            break;
        }
        case C_DATATYPE_INT:
        {
            m_value.c_int = udata.m_value.c_int;
            break;
        }
        case C_DATATYPE_FLOAT:
        {
            m_value.c_float = udata.m_value.c_float;
            break;
        }
        case C_DATATYPE_DOUBLE:
        {
            m_value.c_double = udata.m_value.c_double;
            break;
        }
        case C_DATATYPE_DEFAULT:
        {
            m_value.c_default = udata.m_value.c_default;
            break;
        }
        case C_DATATYPE_UINT:
        {
            m_value.c_uint = udata.m_value.c_uint;
            break;
        }
        case C_DATATYPE_LONG:
        {
            m_value.c_long = udata.m_value.c_long;
            break;
        }
        default:
        {
            assert(0);
            break;
        }
        return *this;
        }
    }
    bool CUDataValue::operator==(const CUDataValue& value)
    {
        if (this->m_init == value.m_init && this->m_type == value.m_type)
        {
            switch(m_type)
            {
            case C_DATATYPE_STRING:
            {
                int ret = strcmp(m_value.c_string,value.m_value.c_string);
                if (ret == 0) return true;
                return false;
            }
            case C_DATATYPE_UCHAR:
            {
                return m_value.c_uchar==value.m_value.c_uchar;
            }
            case C_DATATYPE_SHORT:
            {
                return m_value.c_short==value.m_value.c_short;
            }
            case C_DATATYPE_INT:
            {
                return m_value.c_int==value.m_value.c_int;
            }
            case C_DATATYPE_FLOAT:
            {
                return m_value.c_float==value.m_value.c_float;
            }
            case C_DATATYPE_DOUBLE:
            {
                return m_value.c_double==value.m_value.c_double;
            }
            case C_DATATYPE_DEFAULT:
            {
                return m_value.c_default==value.m_value.c_default;
            }
            case C_DATATYPE_UINT:
            {
                return m_value.c_uint==value.m_value.c_uint;
            }
            case C_DATATYPE_LONG:
            {
                return m_value.c_long==value.m_value.c_long;
            }
            default:
            {
                return false;
            }

            }
        }
        return false;
    }
    void CUDataValue::clear()
    {
        if (!m_init)
        {
            return;
        }
        if (m_type == C_DATATYPE_STRING)
        {
            if (m_value.c_string != NULL)
            {
                delete []m_value.c_string;
                m_value.c_string = NULL;
            }
            return;
        }
    }
    short CUDataValue::dataType()
    {
        return m_type;
    }
    bool CUDataValue::isInit()
    {
        return m_init;
    }
    void CUDataValue::c_string(const char* value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_STRING;
        m_value.c_string = new char[strlen(value)+1];
        strcpy(m_value.c_string,value);
    }
    void CUDataValue::c_string(const string& value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_STRING;
        m_value.c_string = new char[value.length()+1];
        strcpy(m_value.c_string,value.c_str());
    }
    const char* CUDataValue::c_string()const
    {
        assert(m_init && m_type==C_DATATYPE_STRING);
        return m_value.c_string;
    }

    const CUDataValue& CUDataValue::c_uchar(const unsigned char value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_UCHAR;
        m_value.c_uchar = value;

        return *this;
    }
    const unsigned char CUDataValue::c_uchar()const
    {
        assert(m_init && m_type==C_DATATYPE_UCHAR);
        return m_value.c_uchar;
    }

    void CUDataValue::c_short(const short value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_SHORT;
        m_value.c_short = value;
    }
    const short CUDataValue::c_short()const
    {
        assert(m_init && m_type==C_DATATYPE_SHORT);
        return m_value.c_short;
    }

    const CUDataValue& CUDataValue::c_int(const int value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_INT;
        m_value.c_int = value;
        return *this;
    }
    const int CUDataValue::c_int()const
    {
        assert(m_init && m_type==C_DATATYPE_INT);
        return m_value.c_int;
    }

    void CUDataValue::c_float(const float value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_FLOAT;
        m_value.c_float = value;
    }
    const float CUDataValue::c_float()const
    {
        assert(m_init && m_type==C_DATATYPE_FLOAT);
        return m_value.c_float;
    }

    void CUDataValue::c_double(const double value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_DOUBLE;
        m_value.c_double = value;
    }
    const double CUDataValue::c_double()const
    {
        assert(m_init && m_type==C_DATATYPE_DOUBLE);
        return m_value.c_double;
    }

    void CUDataValue::c_default(const char value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_DEFAULT;
        m_value.c_default = value;
    }
    const char CUDataValue::c_default()const
    {
        assert(m_init && m_type==C_DATATYPE_DEFAULT);
        return m_value.c_default;
    }

    void CUDataValue::c_uint(const unsigned int value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_UINT;
        m_value.c_uint = value;
    }
    const unsigned int CUDataValue::c_uint()const
    {
        assert(m_init && m_type==C_DATATYPE_UINT);
        return m_value.c_uint;
    }

    const CUDataValue& CUDataValue::c_long(const long value)
    {
        clear();
        m_init = true;
        m_type = C_DATATYPE_LONG;
        m_value.c_long = value;

        return *this;
    }
    const long CUDataValue::c_long()const
    {
        assert(m_init && m_type==C_DATATYPE_LONG);
        return m_value.c_long;
    }



} /* namespace SCADA_ALG */

