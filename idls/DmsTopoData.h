#include "public.h"

struct TRequestDmsTopo
{
	int req_id;
	vector<long> vec_key;
};

struct TRespondDmsTopo
{
	int req_id;
	int resp_code;
	varchar resp_msg;
	vector<long> rep_key;
};
