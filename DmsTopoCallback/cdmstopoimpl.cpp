#include "cdmstopoimpl.h"

CDmsTopoImpl::CDmsTopoImpl(CGraph* g)
	:m_graph(g)
{
	printf("gewenlin debug graph addres is %x\n",m_graph);
}
int CDmsTopoImpl::getConnectedDev(const TRequestDmsTopo& in_para,TRespondDmsTopo& out_para)
{
    printf("call getConnectedDev...\n");

    int req_key_num = in_para.vec_key.size();
    if (req_key_num != 1)
    {
    		//todo log
    		printf("error...\n");
    		return -1;
    }

    printf("start to topo\n");

    m_graph->debugPrintGraph();

    CEdge* e = m_graph->findEdgeById(in_para.vec_key[0]);

    printf("start v id is %ld\n",e->getStartVertex()->getId());
    printf("end v id is %ld\n",e->getEndVertex()->getId());



    return 1;
}
