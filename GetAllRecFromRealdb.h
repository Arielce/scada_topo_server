#ifndef _GET_ALL_REC_H
#define _GET_ALL_REC_H

#include <assert.h>
#include <vector>
#include <string>

#include "db_api/odb_tableop.h"
#include "db_api/odb_tablenet.h"

/*
����������Ŵ�ʵʱ����ȡ�豸���м�¼ģ�档ģ���������ʹ�ñ��ؽӿڻ�������ӿڡ�
�ֱ��ṩ�˽�Ӧ�úźͱ�ŷ���ģ��ͺ��������еĽӿڡ�
��������������: CBuffer��const�ṹָ�롢vector��
����ֵ��int >=0 ��õļ�¼��,<0 ����
*/

template<class DB_MODE, int app_no, int table_id>
int GetAllRec(const std::string& field_name, CBuffer &get_result)
{
    static DB_MODE table(app_no, table_id);
    return table.TableGet(field_name.c_str(), get_result);
}

template<class DB_MODE, int app_no, int table_id>
int GetAllRec(const std::vector<int> column_id_vec, CBuffer &get_result)
{
    static DB_MODE table(app_no, table_id);
    return table.TableGet(column_id_vec, get_result);
}

template<class DB_MODE, int app_no, int table_id, class DATA_STRUCT>
int GetAllRec(const std::string& field_name, const DATA_STRUCT *buffer_ptr)
{
    CBuffer get_result;
    int rec_num = GetAllRec<DB_MODE, app_no, table_id>(field_name, get_result);
    if(rec_num >= 0)
    {
        assert(rec_num == get_result.GetLength()/sizeof(DATA_STRUCT));
        get_result.Detach();
        buffer_ptr = (const DATA_STRUCT*)get_result.GetBufPtr();
        return rec_num;
    }
    else
    {
        return -1;
    }
}

template<class DB_MODE, int app_no, int table_id, class DATA_STRUCT>
int GetAllRec(const std::string& field_name, std::vector<DATA_STRUCT> &result_vec)
{
    CBuffer get_result;
    int rec_num = GetAllRec<DB_MODE, app_no, table_id>(field_name, get_result);
    if(rec_num >= 0)
    {
        result_vec.assign((DATA_STRUCT*)get_result.GetBufPtr(), (DATA_STRUCT*)get_result.GetBufPtr() + get_result.GetLength()/sizeof(DATA_STRUCT));
        assert(rec_num == result_vec.size());
        return result_vec.size();
    }
    else
    {
        return -1;
    }
}

template<class DB_MODE>
int GetAllRec(const int app_no, const int table_id, const std::string& field_name, CBuffer &get_result)
{
    static DB_MODE table;
    table.Open(app_no, table_id);

    return table.TableGet(field_name.c_str(), get_result);
}

template<class DB_MODE, class DATA_STRUCT>
int GetAllRec(const int app_no, const int table_id, const std::string& field_name, DATA_STRUCT *&data_buffer)
{
	static DB_MODE table;
	table.Open(app_no, table_id);

	int buf_len(0);
	int ret_code = table.TableGet(field_name.c_str(), (char**)&data_buffer, buf_len);
	return ret_code >= 0 ? buf_len/sizeof(DATA_STRUCT) : 0;
}

template<class DB_MODE , class DATA_STRUCT>
int GetAllRec(const int app_no, const int table_id, const std::string& field_name, std::vector<DATA_STRUCT> &result_vec)
{

    CBuffer get_result;
    unsigned int rec_num = GetAllRec<DB_MODE>(app_no, table_id, field_name, get_result);
    if(rec_num >= 0)
    {
        result_vec.assign((DATA_STRUCT*)get_result.GetBufPtr(), (DATA_STRUCT*)get_result.GetBufPtr() + get_result.GetLength()/sizeof(DATA_STRUCT));
        assert(rec_num == result_vec.size());
        return result_vec.size();
    }
    else
    {
        return -1;
    }
}

#endif
