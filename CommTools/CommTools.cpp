#include "CommTools.h"

CCommTools::CCommTools()
{

}

CCommTools::~CCommTools()
{

}

void CCommTools::ExchangeInt(int& _int_a)
{
	unsigned int& tmp1 = (unsigned int&)_int_a;
	tmp1 = ((tmp1 << 24) | ((tmp1 & 0xff00) << 8) | ((tmp1 >> 8) & 0xff00) | (tmp1 >> 24));
}
