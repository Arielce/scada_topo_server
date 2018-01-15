/*
 * CScadaAlg.h
 *
 *  Created on: 2016年9月29日
 *      Author: Administrator
 */

#ifndef CSCADAALG_H_
#define CSCADAALG_H_

#include "CGraph.h"

#include <vector>
using namespace std;

namespace SCADA_ALG
{
    class SCADA_ALG_API CScadaAlg
    {
    public:
        CScadaAlg();
        virtual
        ~CScadaAlg();
        virtual CGraph* createGraph();
        /*
         * 算法用的图最好通过外部传入
         * */
        void setGraph(CGraph* graph);
        CGraph* getGraph();

    protected:
        CGraph* m_graph;
    };
} /* namespace SCADA_ALG */
#endif /* CSCADAALG_H_ */
