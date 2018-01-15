/*
 * CScadaAlg.cpp
 *
 *  Created on: 2016Äê9ÔÂ29ÈÕ
 *      Author: Administrator
 */

#include "CGraph.h"
#include "CScadaAlg.h"

namespace SCADA_ALG
{

    CScadaAlg::CScadaAlg()
    {
        // TODO Auto-generated constructor stub

    }

    CScadaAlg::~CScadaAlg()
    {
        // TODO Auto-generated destructor stub
    }
    CGraph* CScadaAlg::createGraph()
    {
        return NULL;
    }
    void CScadaAlg::setGraph(CGraph* graph)
    {
        m_graph = graph;
    }
    CGraph* CScadaAlg::getGraph()
    {
        return m_graph;
    }

} /* namespace SCADA_ALG */
