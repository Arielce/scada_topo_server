#ifndef CDMSTOPOIMPL_H
#define CDMSTOPOIMPL_H

#include "DmsTopoData_m.h"
#include "graphcore_global.h"
using namespace SCADA_ALG;

//class CGraph;
class CDmsTopoImpl
{
public:
    CDmsTopoImpl(CGraph* g);

    int getConnectedDev(const TRequestDmsTopo& in_para,TRespondDmsTopo& out_para);
private:
    CGraph* m_graph;
};

#endif // CDMSTOPOIMPL_H
