/*
 * CTopoAlg.cpp
 *
 *  Created on: 2016Äê10ÔÂ13ÈÕ
 *      Author: Administrator
 */

#include "CTopoAlg.h"

namespace SCADA_ALG
{

    CTopoAlg::CTopoAlg():m_connectedGraphName("connected_graph_no"),m_connectedGraphNum(-1)
    {
        // TODO Auto-generated constructor stub

    }

    CTopoAlg::~CTopoAlg()
    {
        // TODO Auto-generated destructor stub
    }

    void CTopoAlg::setConnectedGraphName(string graph_name)
    {
    		m_connectedGraphName = graph_name;
    }

    vector<CVertex*> CTopoAlg::searchShortestPath(const CVertex* s_vertex,const CVertex* e_vertex)
    {

    }

    void
    CTopoAlg::addBorders(vector<CEdge*>& vec_border)
    {
        if (!vec_border.empty())
        {
            vector<CEdge*>::iterator it;
            for (it = vec_border.begin(); it != vec_border.end(); ++it)
            {
                (*it)->setBorder(true);
            }
        }
    }
    void
    CTopoAlg::delBorders(vector<CEdge*>& vec_border)
    {
        if (!vec_border.empty())
        {
            vector<CEdge*>::iterator it;
            for (it = vec_border.begin(); it != vec_border.end(); ++it)
            {
                (*it)->setBorder(false);
            }
        }
    }


    int
    CTopoAlg::searchConnectedGraph(vector<CEdge*> vec_border)
    {

        addBorders(vec_border);

        m_connectedGraphNum = 0;
        m_mapConnectedGraphVertex.clear();
        m_mapConnectedGraphEdge.clear();
        vector<CVertex*> vec_vertex = m_graph->getAllVertex();
        for (vector<CVertex*>::iterator it=vec_vertex.begin();it!=vec_vertex.end();++it)
        {
            (*it)->addProperty(m_connectedGraphName,CUDataValue().c_int(-1));
        }
        for (vector<CVertex*>::iterator it=vec_vertex.begin();it!=vec_vertex.end();++it)
        {
            if ((*it)->getProperty(m_connectedGraphName).c_int() < 0)
            {
                Dfs(*it,m_connectedGraphNum++);
            }
        }
        return m_connectedGraphNum;

    }

    void CTopoAlg::Dfs(CVertex* const v,const int connected_graph_num)
    {
    		if (v == NULL)
    		{
    			return;
    		}
    		printf("vid===%ld\n",v->getId());
        CUDataValue connected_graph_no = v->getProperty(m_connectedGraphName);
        if ( !connected_graph_no.isInit()
            || connected_graph_no.c_int() == connected_graph_num )
        {
            return;
        }
        v->addProperty(m_connectedGraphName,CUDataValue().c_int(connected_graph_num));
        m_mapConnectedGraphVertex[connected_graph_num].push_back(v);
        vector<CEdge*> vec_edges = v->getEdges();
        for (vector<CEdge*>::iterator it=vec_edges.begin();it!=vec_edges.end();++it)
        {
        		printf("vid %ld ,edge id %ld \n",v->getId(),(*it)->getId());
            if (!( (*it)->isOpen() || (*it)->isBorder() ))
            {
            		printf(" dfs...\n");
                m_mapConnectedGraphEdge[connected_graph_num].push_back(*it);
                Dfs((*it)->getOppVertex(v),connected_graph_num);
            }
        }
    }

    void CTopoAlg::Bfs(CVertex* const v,const int connected_graph_num)
    {
		if (v == NULL)
		{
			return;
		}
    		queue<CVertex*> ver_que;
    		ver_que.push(v);
    		while(!ver_que.empty())
    		{
			CVertex* tv = ver_que.front();
			ver_que.pop();
			CUDataValue connected_graph_no = tv->getProperty(m_connectedGraphName);
			if (!connected_graph_no.isInit()
					|| connected_graph_no.c_int() == connected_graph_num)
			{
				continue;
			}
			tv->addProperty(m_connectedGraphName,CUDataValue().c_int(connected_graph_num));
			m_mapConnectedGraphVertex[connected_graph_num].push_back(tv);
			vector<CEdge*> vec_edges = tv->getEdges();
			for (vector<CEdge*>::iterator it = vec_edges.begin();
					it != vec_edges.end(); ++it)
			{
				if (!((*it)->isOpen() || (*it)->isBorder()))
				{
					ver_que.push( (*it)->getOppVertex(tv) );
					m_mapConnectedGraphEdge[connected_graph_num].push_back(*it);
				}
			}
    		}
    }
    int CTopoAlg::getConnectedGraphWithinEdge(map<int,vector<CEdge*> >& map_edge)
    {
        map_edge = m_mapConnectedGraphEdge;
    }
    int CTopoAlg::getConnectedGraphWithinVertex(map<int,vector<CVertex*> >& map_vertex)
    {
        map_vertex = m_mapConnectedGraphVertex;
    }
} /* namespace SCADA_ALG */
