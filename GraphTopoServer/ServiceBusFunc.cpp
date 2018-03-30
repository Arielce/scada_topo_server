/*
 * ServiceBusFunc.cpp
 *
 *  Created on: 2018Äê3ÔÂ28ÈÕ
 *      Author: Ge.Wenlin
 */

#include "ServiceBusFunc.h"
#include "ITopoService.h"
extern map<unsigned char, ITopoService*> g_mapFuncServ;
void* ServiceBusFunc(char* requestBuffer, int requestlen, char** responseBuffer, int* responselen)
{
	int ret = 1;
	char *msgBuf = NULL;
	int msgOffset = 0;
	unsigned char srvid = 0;
	memcpy((char*) &srvid, requestBuffer, sizeof(unsigned char));
	msgOffset += sizeof(unsigned char);

	printf("recv req srvid is %d\n",srvid);

	map<unsigned char, ITopoService*>::iterator it_map;
	it_map = g_mapFuncServ.find(srvid);
	if (it_map != g_mapFuncServ.end())
	{
		printf("find the srvid map to serv\n");
		it_map->second->doService(requestBuffer + msgOffset, requestlen - msgOffset, responseBuffer, responselen);
	}
	else
	{
		int ret = -999;
		*responselen = sizeof(int);
		*responseBuffer = new char[*responselen];
		memcpy(*responseBuffer, &ret, sizeof(int));

		return (void*)ret;
	}

}
