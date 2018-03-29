#ifndef _COMMTOOLS_H
#define _COMMTOOLS_H


class CCommTools
{
public:
	static CCommTools* getInst()
	{
		static CCommTools inst;
		return &inst;
	}

	~CCommTools();

	void ExchangeInt(int& int_a);

private:
	CCommTools();
};


#endif
