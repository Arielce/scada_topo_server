/*
 * CGraph.cpp
 *
 *  Created on: 2016��9��29��
 *      Author: Administrator
 */

#include "CGraph.h"
#include <iostream>
namespace SCADA_ALG
{
    CPropertyContainer::CPropertyContainer()
        :m_graph(NULL)
    {

    }
    CPropertyContainer::~CPropertyContainer()
    {

    }
    CPropertyContainer* CPropertyContainer::addProperty(const string pname,const CUDataValue pvalue)
    {
        //m_mapProperty.insert( make_pair(pname,pvalue) );
    		//todo ����
        m_mapProperty[pname] = pvalue;
        return this;
    }
    CUDataValue CPropertyContainer::getProperty(const string pname)
    {
        map<string,CUDataValue>::iterator it_map = m_mapProperty.find(pname);
        if ( it_map != m_mapProperty.end() )
        {
            return it_map->second;
        }
        return CUDataValue();
    }
    bool CPropertyContainer::hasProperty(const string pname)
    {
        map<string,CUDataValue>::iterator it_map = m_mapProperty.find(pname);
        if ( it_map != m_mapProperty.end() )
        {
            return true;
        }
        return false;
    }
    void CPropertyContainer::setGraph(CGraph* graph)
    {
        m_graph = graph;
    }

    //CVertex
    CVertex::CVertex()
        :m_vetexId(-1),m_iDegree(0),m_island(NULL)
    {

    }
    CVertex::CVertex(const SCA_ND_ID id)
        :m_vetexId(id),m_iDegree(0),m_island(NULL)
    {

    }
    CVertex::~CVertex()
    {

    }
    CEdge* CVertex::createEdgeTo(const SCA_ND_ID id,const SCA_ID edgeId)
    {
        if (!m_graph)
        {
            return NULL;
        }
        CVertex* vertex = m_graph->findVertexById( id );
        if (vertex)
        {
            CEdge* edge = new CEdge(this,vertex,edgeId);
            m_graph->m_vecEdge.push_back( edge );
            m_graph->m_mapIndexEdge.insert( make_pair(edgeId,(unsigned int)m_graph->m_vecEdge.size()-1) );

            //this->m_vecEdge.push_back( edge );
            //m_iDegree++;
            this->addEdge( edge );
            vertex->addEdge( edge );

            return edge;
        }
        return NULL;
    }
    SCA_ND_ID CVertex::getId()
    {
        return m_vetexId;
    }
    vector<CEdge*>& CVertex::getEdges()
    {
        return m_vecEdge;
    }
    int CVertex::getDegree()
    {
        return m_iDegree;
    }
    CVertex* CVertex::addEdge(CEdge* const eptr)
    {
        m_iDegree++;
        m_vecEdge.push_back(eptr);
        return this;
    }
    CVertex* CVertex::delEdge(CEdge* const eptr)
    {
    		vector<CEdge*>::iterator it = std::find(m_vecEdge.begin(),m_vecEdge.end(),eptr);
        if ( it != m_vecEdge.end() )
        {
        		m_vecEdge.erase(it);
        	    m_iDegree--;
        }
        return this;
    }
    CIsland* CVertex::belongToIsland()
    {
    		return m_island;
    }
    //��Ҫֱ�ӵ���freeVertex�ͷ�vertex����edge���ã�����ͼ����ʱ�����ͷűߣ������ͷŵ㣩
    void CVertex::freeVertex()
    {
        if (m_iDegree == 0)
        {
            delete this;
        }
    }

    //CEdge
    CEdge::CEdge(const SCA_ID id)
        :m_sVertex(NULL),m_eVertex(NULL),m_bEdgeOpen(false),m_edgeId(id),m_bEdgeBorder(false)
    {

    }
    CEdge::CEdge(CVertex* const s_vertex,CVertex* const e_vertex,const SCA_ID id)
        :m_sVertex(s_vertex),m_eVertex(e_vertex),m_bEdgeOpen(false),m_edgeId(id),m_bEdgeBorder(false)
    {

    }
    CEdge::~CEdge()
    {
    		freeEdge();
    }
    SCA_ID CEdge::getId()
    {
    		return m_edgeId;
    }
    CVertex* CEdge::getOppVertex(CVertex* const vptr)
    {
        if ( !(m_sVertex && m_eVertex) )
        {
            return NULL;
        }
        if (m_sVertex == vptr)
        {
            return m_eVertex;
        }
        return m_sVertex;
    }
    vector<CVertex*> CEdge::getAllVertex()
    {
        vector<CVertex*> vec_vertex;
        vec_vertex.push_back(m_sVertex);
        vec_vertex.push_back(m_eVertex);

        return vec_vertex;
    }
    CVertex* CEdge::getStartVertex()
    {
        return m_sVertex;
    }
    CVertex* CEdge::getEndVertex()
    {
        return m_eVertex;
    }
    void CEdge::setOpen(const bool open)
    {
        m_bEdgeOpen = open;
    }
    bool CEdge::isOpen()
    {
        return m_bEdgeOpen;
    }
    void CEdge::setBorder(const bool border)
    {
        m_bEdgeBorder = border;
    }
    bool CEdge::isBorder()
    {
        return m_bEdgeBorder;
    }
    void CEdge::freeEdge()
    {
    		//�����˵����������ı���ɾ��
    		if ( m_sVertex )
    		{
    			m_sVertex->delEdge(this);
    			m_sVertex->freeVertex();
    			m_sVertex = NULL;
    		}
    		if ( m_eVertex )
    		{
    			m_eVertex->delEdge(this);
    			m_eVertex->freeVertex();
    			m_eVertex = NULL;
    		}
        //if ( m_sVertex == NULL && m_eVertex == NULL )
        //{
        //    delete this;
        //}
    }
    void CEdge::addLabel(CLabel* label)
    {
    		if (label != NULL)
    		{
    			vector<CLabel*>::iterator it = std::find(m_vecLabels.begin(),m_vecLabels.end(),label);
    			if (it == m_vecLabels.end())
    			{
    				m_vecLabels.push_back(label);
    			}
    		}
    }
    void CEdge::delLabel(CLabel* label)
    {
    		if (label != NULL)
		{
			vector<CLabel*>::iterator it = std::find(m_vecLabels.begin(),m_vecLabels.end(),label);
			if (it != m_vecLabels.end())
			{
				m_vecLabels.erase(it);
			}
		}
    }
    int CEdge::getLabels(vector<CLabel*>& vec_label)
    {
    		vec_label = m_vecLabels;
    		return m_vecLabels.size();
    }

    CIsland::CIsland():m_islandId(-1)
    {

    }
    CIsland::CIsland(const int island_no):m_islandId(island_no)
	{

	}
    CIsland::~CIsland()
    {

    }
    int CIsland::getAllVertex(vector<CVertex*>& vec_vertex)
    {
    		vec_vertex = m_vecVertex;
    		return m_vecVertex.size();
    }
    void CIsland::mergeIsland(CIsland* t_island)
    {
    		vector<CVertex*> vec_vertex;
    		int num = t_island->getAllVertex(vec_vertex);
    		if (num > 0)
    		{
    			m_vecVertex.insert(m_vecVertex.end(),vec_vertex.begin(),vec_vertex.end());
    		}
    }
    void CIsland::appendVertex(CVertex* v)
    {
    		if (v != NULL)
    		{
    			m_vecVertex.push_back(v);
    		}
    }
    //label
    CLabel::CLabel(const string name):m_labelName(name)
    {

    }
    CLabel::~CLabel()
    {

    }
    string CLabel::name()
    {
    		return m_labelName;
    }
    int CLabel::getAllEdges(vector<CEdge*>& vec_edges)
    {
    		vec_edges = m_vecEdge;
    		return m_vecEdge.size();
    }

    //CGraph
    CGraph::CGraph()
    {
        // TODO Auto-generated constructor stub
        printf("this is constructor of CGraph\n");
    }

    CGraph::~CGraph()
    {
        // TODO Auto-generated destructor stub
        freeGraph();
    }

    CVertex* CGraph::createVertex(const SCA_ND_ID id)
    {
        CVertex* vptr = findVertexById(id);
        if (vptr == NULL)
        {
            vptr = new CVertex(id);
            vptr->setGraph(this);
            m_vecVertex.push_back(vptr);
            m_mapIndexVertex.insert( make_pair(id,m_vecVertex.size()-1) );
        }
        return vptr;
    }
    void CGraph::releaseVertex(const SCA_ND_ID id)
    {

    }
    CVertex* CGraph::findVertexById(const SCA_ND_ID id)
    {
        IterVertexIdx it = m_mapIndexVertex.find( id );
        if ( it != m_mapIndexVertex.end() )
        {
            if ( it->second<0 || it->second>=m_vecVertex.size() )
                return NULL;
            return m_vecVertex[it->second];
        }
        return NULL;
    }
    CEdge* CGraph::findEdgeById(const SCA_ID id)
    {
        IterEdgeIdx it = m_mapIndexEdge.find(id);
        if ( it != m_mapIndexEdge.end() )
        {
            if ( it->second<0 || it->second>=m_vecEdge.size() )
                return NULL;
            return m_vecEdge[it->second];
        }
        return NULL;
    }
    vector<CVertex*> CGraph::getAllVertex()
    {
        return m_vecVertex;
    }
    vector<CEdge*> CGraph::getAllEdge()
    {
        return m_vecEdge;
    }
    void CGraph::mergeGraph(const CGraph* graph)
    {

    }
    void CGraph::freeGraph()
    {
    		/*
        vector<CVertex*>::iterator it_v = m_vecVertex.begin();
        for (;it_v != m_vecVertex.end();it_v++)
        {
            delete *it_v;
        }
        m_vecVertex.clear();
    	 	 */
        vector<CEdge*>::iterator it_e = m_vecEdge.begin();
        for (;it_e != m_vecEdge.end();it_e++)
        {
            delete *it_e;
        }
        m_vecEdge.clear();
    }
    int CGraph::addVertex(CVertex* v)
    {
    		CVertex* vptr = findVertexById(v->getId());
    		if (vptr == NULL)
    		{
    			m_vecVertex.push_back(v);
    			m_mapIndexVertex.insert( make_pair(v->getId(),(unsigned int)m_vecVertex.size()-1) );
    		}
    		else if (vptr != v)
		{
			return -1;
		}
		return m_vecVertex.size();
    }
    void CGraph::delVertex(CVertex* v)
    {
    		SCA_ND_ID id = v->getId();
    		CVertex* vptr = findVertexById(id);
    		if (vptr == v)
    		{
    			map<SCA_ND_ID,unsigned int>::iterator it_map;
    			it_map = m_mapIndexVertex.find(id);
    			if(it_map != m_mapIndexVertex.end())
    			{
    				int pos = it_map->second;
    				vector<CVertex*>::iterator it_v = m_vecVertex.begin() + pos;
    				m_vecVertex.erase(it_v);
    				m_mapIndexVertex.erase(it_map);
    			}
    		}
    }
    int CGraph::addEdge(CEdge* e)
    {
    		CEdge* eptr = findEdgeById(e->getId());
    		if (eptr == NULL)
    		{
    			m_vecEdge.push_back( e );
    			m_mapIndexEdge.insert( make_pair(e->getId(),(unsigned int)m_vecEdge.size()-1) );
    		}
    		else if (eptr != e)
    		{
    			return -1;
    		}
    		return m_vecEdge.size();
    }
    void CGraph::delEdge(CEdge* e)
    {
    		SCA_ID id = e->getId();
    		CEdge* eptr = findEdgeById(id);
    		if(eptr == e)
    		{
    			map<SCA_ID,unsigned int>::iterator it_map;
    			it_map = m_mapIndexEdge.find(id);
    			if (it_map != m_mapIndexEdge.end())
    			{
    				int pos = it_map->second;
    				vector<CEdge*>::iterator it_e = m_vecEdge.begin()+pos;
    				m_vecEdge.erase(it_e);
    				m_mapIndexEdge.erase(it_map);
    			}
    		}
    }


} /* namespace SCADA_ALG */
