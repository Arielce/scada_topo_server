/*
 * CGraph.cpp
 *
 *  Created on: 2016年9月29日
 *      Author: Administrator
 */

#include "CGraph.h"
#include <iostream>
#include <assert.h>
namespace SCADA_ALG
{
CPropertyContainer::CPropertyContainer() :
		m_graph(NULL)
{

}
CPropertyContainer::~CPropertyContainer()
{

}
CPropertyContainer* CPropertyContainer::addProperty(const string pname, const CUDataValue pvalue)
{
	//m_mapProperty.insert( make_pair(pname,pvalue) );
	//todo 加锁
	m_mapProperty[pname] = pvalue;
	return this;
}
CUDataValue CPropertyContainer::getProperty(const string pname)
{
	map<string, CUDataValue>::iterator it_map = m_mapProperty.find(pname);
	if (it_map != m_mapProperty.end())
	{
		return it_map->second;
	}
	return CUDataValue();
}
bool CPropertyContainer::hasProperty(const string pname)
{
	map<string, CUDataValue>::iterator it_map = m_mapProperty.find(pname);
	if (it_map != m_mapProperty.end())
	{
		return true;
	}
	return false;
}
void CPropertyContainer::setGraph(CGraph* graph)
{
	m_graph = graph;
}
CGraph* CPropertyContainer::getGraph()
{
	return m_graph;
}

//CVertex
CVertex::CVertex() :
		m_vetexId(-1), m_iDegree(0)
{

}
CVertex::CVertex(const SCA_ND_ID id) :
		m_vetexId(id), m_iDegree(0)
{

}
CVertex::~CVertex()
{

}
CEdge* CVertex::createEdgeTo(const SCA_ND_ID id, const SCA_ID edgeId)
{
	if (!m_graph)
	{
		return NULL;
	}
	CVertex* vertex = m_graph->findVertexById(id);
	if (vertex)
	{
		CEdge* edge = new CEdge(this, vertex, edgeId);
		m_graph->m_vecEdge.push_back(edge);
		m_graph->m_mapIndexEdge.insert(make_pair(edgeId, (unsigned int) m_graph->m_vecEdge.size() - 1));

		//this->m_vecEdge.push_back( edge );
		//m_iDegree++;
		this->addEdge(edge);
		vertex->addEdge(edge);

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
	vector<CEdge*>::iterator it = std::find(m_vecEdge.begin(), m_vecEdge.end(), eptr);
	if (it != m_vecEdge.end())
	{
		m_vecEdge.erase(it);
		m_iDegree--;
	}
	return this;
}
void CVertex::addIsland(CIsland* island)
{
	assert(island);
	map<CGraph*, CIsland*>::iterator it_map = m_mapGraphIsland.find(island->getGraph());
	if (it_map != m_mapGraphIsland.end())
	{
		it_map->second = island;
	}
	else
	{
		m_mapGraphIsland.insert(make_pair(island->getGraph(), island));
	}
	return;
}
CIsland* CVertex::belongToIsland(CGraph* const g)
{
	map<CGraph*, CIsland*>::iterator it_map = m_mapGraphIsland.find(g);
	if (it_map != m_mapGraphIsland.end())
	{
		return it_map->second;
	}
	return NULL;
}
//不要直接调用freeVertex释放vertex，由edge调用（即：图管理时仅需释放边，无需释放点）
void CVertex::freeVertex()
{
	if (m_iDegree == 0)
	{
		delete this;
	}
}

//CEdge
CEdge::CEdge(const SCA_ID id) :
		m_sVertex(NULL), m_eVertex(NULL), m_bEdgeOpen(false), m_edgeId(id), m_bEdgeBorder(false)
{

}
CEdge::CEdge(CVertex* const s_vertex, CVertex* const e_vertex, const SCA_ID id) :
		m_sVertex(s_vertex), m_eVertex(e_vertex), m_bEdgeOpen(false), m_edgeId(id), m_bEdgeBorder(false)
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
	if (!(m_sVertex && m_eVertex))
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
	//把两端点中所包含的本边删除
	if (m_sVertex)
	{
		m_sVertex->delEdge(this);
		m_sVertex->freeVertex();
		m_sVertex = NULL;
	}
	if (m_eVertex)
	{
		m_eVertex->delEdge(this);
		m_eVertex->freeVertex();
		m_eVertex = NULL;
	}
	vector<CLabel*>::iterator it;
	for (it = m_vecLabels.begin(); it != m_vecLabels.end(); it++)
	{
		(*it)->delEdge(this);
	}
	//delete this;
	//if ( m_sVertex == NULL && m_eVertex == NULL )
	//{
	//    delete this;
	//}
}
void CEdge::addLabel(CLabel* label)
{
	if (label != NULL)
	{
		vector<CLabel*>::iterator it = std::find(m_vecLabels.begin(), m_vecLabels.end(), label);
		if (it == m_vecLabels.end())
		{
			m_vecLabels.push_back(label);
			label->addEdge(this);
		}
	}
}
void CEdge::delLabel(CLabel* label)
{
	if (label != NULL)
	{
		vector<CLabel*>::iterator it = std::find(m_vecLabels.begin(), m_vecLabels.end(), label);
		if (it != m_vecLabels.end())
		{
			m_vecLabels.erase(it);
			label->delEdge(this);
		}
	}
}
int CEdge::getLabels(vector<CLabel*>& vec_label)
{
	vec_label = m_vecLabels;
	return m_vecLabels.size();
}
//island
CIsland::CIsland() :
		m_islandId(-1), m_parentIsland(NULL)
{
	setGraph(NULL);
}
CIsland::CIsland(CGraph* g) :
		m_islandId(-1), m_parentIsland(NULL)
{
	setGraph(g);
}
CIsland::CIsland(CGraph* g, const int island_no) :
		m_islandId(island_no), m_parentIsland(NULL)
{
	setGraph(g);
}
CIsland::~CIsland()
{

}
int CIsland::getAllVertex(vector<CVertex*>& vec_vertex)
{
	vec_vertex = m_vecVertex;
	return m_vecVertex.size();
}
CIsland* CIsland::getParent()
{
	return m_parentIsland;
}
void CIsland::setParent(CIsland* island)
{
	m_parentIsland = island;
	island->addSubIsland(this);
}
void CIsland::addSubIsland(CIsland* island)
{
	m_subIsland.push_back(island);
}
vector<CIsland*> CIsland::getSubIsland()
{
	return m_subIsland;
}
void CIsland::mergeIsland(CIsland* t_island, CGraph* graph)
{
	if (m_parentIsland == NULL && t_island->getParent() == NULL)
	{
		//CIsland* parent = new CIsland();
		CIsland* parent = graph->createIsland();        //用大图来创建岛
		setParent(parent);
		t_island->setParent(parent);
		parent->appendVertexs(m_vecVertex);
		vector<CVertex*> vec_vertex;
		int num = t_island->getAllVertex(vec_vertex);
		parent->appendVertexs(vec_vertex);
		return;
	}
	else if (m_parentIsland)
	{
		CIsland* parent = m_parentIsland;
		vector<CVertex*> vec_vertex;
		int num = t_island->getAllVertex(vec_vertex);
		parent->appendVertexs(vec_vertex);
		CIsland* t_parent = t_island->getParent();
		if (t_parent)
		{
			vector<CIsland*>::iterator it_sub;
			vector<CIsland*> vec_sub = t_island->getParent()->getSubIsland();
			for (it_sub = vec_sub.begin(); it_sub != vec_sub.end(); it_sub++)   //合并与t_island相连子岛的节点
			{
				if (*it_sub == t_island)
					continue;
				(*it_sub)->setParent(parent);
				vector<CVertex*> vec_vertex;
				(*it_sub)->getAllVertex(vec_vertex);
				parent->appendVertexs(vec_vertex);
			}
			delete t_parent;
			t_parent = NULL;

		}
		t_island->setParent(parent);
		return;
	}
	else
	{
		CIsland* parent = t_island->getParent();
		setParent(parent);
		parent->appendVertexs(m_vecVertex);
	}
}
void CIsland::appendVertex(CVertex* v)
{
	if (v != NULL)
	{
		m_vecVertex.push_back(v);
		v->addIsland(this);
	}
}
void CIsland::appendVertexs(vector<CVertex*>& vec_vertex)
{
//m_vecVertex.insert( m_vecVertex.end(),vec_vertex.begin(),vec_vertex.end() );
	vector<CVertex*>::iterator it;
	for (it = vec_vertex.begin(); it != vec_vertex.end(); it++)
	{
		appendVertex(*it);
	}
}
//label
CLabel::CLabel(const string name) :
		m_labelName(name)
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
void CLabel::addEdge(CEdge* e)
{
	m_vecEdge.push_back(e);
}
void CLabel::delEdge(CEdge* e)
{
	vector<CEdge*>::iterator it;
	it = std::find(m_vecEdge.begin(), m_vecEdge.end(), e);
	if (it != m_vecEdge.end())
	{
		m_vecEdge.erase(it);
	}
}

//CGraph
static int graph_id;
static int graphs_nifty_counter; // zero initialized at load time
static char graphMapStorage_buf[sizeof(CGraph::GraphMapStorage)]; // memory for the nifty-counter singleton object
CGraph::GraphMapStorage &CGraph::_graphMapStorageInstance = reinterpret_cast<CGraph::GraphMapStorage&>(graphMapStorage_buf); // memory for placement new

CGraph::GraphMapStorage::GraphMapStorage()
{
	_allgraphs = new GraphMap();
}
CGraph::GraphMapStorage::~GraphMapStorage()
{
	_deleteAllGraphs();
	delete _allgraphs;
}

CGraph::GraphMapStorageInitializer::GraphMapStorageInitializer()
{
	if (graphs_nifty_counter++ == 0)
	{
		// MSVC's <crtdbg.h> requires redefinition of the new operator, but could not deal with placement new form of it
#ifdef MSVC_MEMORY_LEAK_CHECK
#pragma push_macro("new")
#define new new
#endif // MSVC_MEMORY_LEAK_CHECK
		new (&_graphMapStorageInstance) GraphMapStorage(); // placement new
#ifdef MSVC_MEMORY_LEAK_CHECK
#pragma pop_macro("new")
#endif // MSVC_MEMORY_LEAK_CHECK
	}
}
CGraph::GraphMapStorageInitializer::~GraphMapStorageInitializer()
{
	if (--graphs_nifty_counter == 0)
	{
		(&_graphMapStorageInstance)->~GraphMapStorage();
	}
}

/* assume _appenderMapMutex locked */
CGraph::GraphMap& CGraph::_getAllGraphs()
{
	return *_graphMapStorageInstance._allgraphs;
}

CGraph* CGraph::getGraph(const std::string& name)
{
	threading::ScopedLock lock(_graphMapStorageInstance._graphMapMutex);
	GraphMap& allGraphs = CGraph::_getAllGraphs();
	GraphMap::iterator i = allGraphs.find(name);
	return (allGraphs.end() == i) ? NULL : ((*i).second);
}

void CGraph::_addGraph(CGraph* graph)
{
//REQUIRE(_allAppenders.find(appender->getName()) == _getAllAppenders().end())
	threading::ScopedLock lock(_graphMapStorageInstance._graphMapMutex);
	_getAllGraphs()[graph->getName()] = graph;
}

void CGraph::_removeGraph(CGraph* appender)
{
	threading::ScopedLock lock(_graphMapStorageInstance._graphMapMutex);
//private called from destructor only, but may be triggered by client code in several treads
	_getAllGraphs().erase(appender->getName());
}
void CGraph::_deleteAllGraphs()
{
// deleting each appenders will cause a lock on Appender::_appenderMapMutex to be obtained again within destructor. to avoid nested locks:
	std::vector<CGraph*> appenders;
	{
		threading::ScopedLock lock(_graphMapStorageInstance._graphMapMutex);
		GraphMap& allGraphs = _getAllGraphs();
		appenders.reserve(allGraphs.size());
		for (GraphMap::iterator i = allGraphs.begin(); i != allGraphs.end();)
		{
			CGraph* app = (*i).second;
			++i;
			appenders.push_back(app);
		}
		allGraphs.clear();
	}
	_deleteAllGraphsWOLock(appenders);
}

void CGraph::_deleteAllGraphsWOLock(std::vector<CGraph*> &graphs)
{
	/* assume Appender::_appenderMapMutex not locked */
	GraphMap& allGraphs = _getAllGraphs();
	for (std::vector<CGraph*>::iterator i = graphs.begin(); i != graphs.end(); ++i)
	{
		CGraph *app = (*i);
		delete (app);
	}
}
CGraph::CGraph(const std::string& name) :
		_name(name), _island_base_no(1000000)
{
// TODO Auto-generated constructor stub
	printf("this is constructor of CGraph\n");
	_graphId = ++graph_id;
	_addGraph(this);
}

CGraph::~CGraph()
{
// TODO Auto-generated destructor stub
//freeGraph();
	_removeGraph(this);
}

CVertex* CGraph::createVertex(const SCA_ND_ID id)
{
	CVertex* vptr = findVertexById(id);
	if (vptr == NULL)
	{
		vptr = new CVertex(id);
		vptr->setGraph(this);
		m_vecVertex.push_back(vptr);
		m_mapIndexVertex.insert(make_pair(id, m_vecVertex.size() - 1));
	}
	return vptr;
}
/*
 void CGraph::releaseVertex(const SCA_ND_ID id)
 {
 CVertex* v = findVertexById(id);
 if (v)
 {
 v->freeVertex();
 }
 }
 */
void CGraph::releaseEdge(const SCA_ID id)
{
	CEdge* e = findEdgeById(id);
	if (e)
	{
		e->freeEdge();
	}
}
CVertex* CGraph::findVertexById(const SCA_ND_ID id)
{
	IterVertexIdx it = m_mapIndexVertex.find(id);
	if (it != m_mapIndexVertex.end())
	{
		if (it->second < 0 || it->second >= m_vecVertex.size())
			return NULL;
		return m_vecVertex[it->second];
	}
	return NULL;
}
CEdge* CGraph::findEdgeById(const SCA_ID id)
{
	IterEdgeIdx it = m_mapIndexEdge.find(id);
	if (it != m_mapIndexEdge.end())
	{
		if (it->second < 0 || it->second >= m_vecEdge.size())
			return NULL;
		return m_vecEdge[it->second];
	}
	return NULL;
}
CIsland* CGraph::createIsland(const int island_no)
{
	CIsland::ISLAND_ID local_island_no = island_no < 0 ? _graphId * _island_base_no + m_vecIsland.size() : _graphId * _island_base_no + island_no;
	IterIslandIdx it = m_mapIndexIsland.find(local_island_no);
	if (it != m_mapIndexIsland.end())
	{
		return m_vecIsland[it->second];
	}
	CIsland* island = new CIsland(this, local_island_no);
	m_vecIsland.push_back(island);
	m_mapIndexIsland.insert(make_pair(local_island_no, m_vecIsland.size() - 1));
	return island;
}
CLabel* CGraph::createLabel(const string& name)
{
	IterLabelIdx it = m_mapIndexLabel.find(name);
	if (it != m_mapIndexLabel.end())
	{
		return it->second;
	}
	CLabel *label = new CLabel(name);
	m_vecLabel.push_back(label);
	m_mapIndexLabel.insert(make_pair(name, label));
	return label;
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
//free edge
	vector<CEdge*>::iterator it_e = m_vecEdge.begin();
	for (; it_e != m_vecEdge.end(); it_e++)
	{
		if (*it_e)
		{
			printf("free edge %ld\n", (*it_e)->getId());
			delete *it_e;
			*it_e = NULL;
		}
	}
	m_vecEdge.clear();
//free label
	vector<CLabel*>::iterator it_l = m_vecLabel.begin();
	for (; it_l != m_vecLabel.end(); it_l++)
	{
		if (*it_l)
		{
			printf("free label %s\n", (*it_l)->name().c_str());
			delete *it_l;
			*it_l = NULL;
		}
	}
//free island
	vector<CIsland*>::iterator it_i = m_vecIsland.begin();
	for (; it_i != m_vecIsland.end(); it_i++)
	{
		if (*it_i)
		{
			delete *it_i;
			*it_i = NULL;
		}
	}
}

void CGraph::debugPrintGraph()
{
	printf("Graph name is %s \n", this->_name.c_str());
	vector<CEdge*>::iterator it_e = m_vecEdge.begin();
	for (; it_e != m_vecEdge.end(); it_e++)
	{
		if (*it_e)
		{
			printf("graph edge %ld\n", (*it_e)->getId());
			CVertex* sv = (*it_e)->getStartVertex();
			if (sv)
			{
				printf("		vertex start : %ld  ", sv->getId());
				if (sv->belongToIsland(this))
				{
					printf("		island : %ld\n", sv->belongToIsland(this)->getId());
				}
				else
				{
					printf("no island in this graph\n");
				}
			}
			CVertex* ev = (*it_e)->getEndVertex();
			if (ev)
			{
				printf("		vertex end   : %ld   ", ev->getId());
				//printf("		island : %ld\n",(*it_e)->getEndVertex()->belongToIsland(this)->getId());
				if (ev->belongToIsland(this))
				{
					printf("		island : %ld\n", ev->belongToIsland(this)->getId());
				}
				else
				{
					printf("no island in this graph\n");
				}
			}

			vector<CLabel*>::iterator it;
			vector<CLabel*> vec_labels;
			(*it_e)->getLabels(vec_labels);
			for (it = vec_labels.begin(); it != vec_labels.end(); it++)
			{
				printf("		label is %s \n", (*it)->name().c_str());
			}
		}
	}
	m_vecEdge.clear();
//free label
	vector<CLabel*>::iterator it_l = m_vecLabel.begin();
	for (; it_l != m_vecLabel.end(); it_l++)
	{
		if (*it_l)
		{
			printf("graph label %s\n", (*it_l)->name().c_str());
		}
	}
//free island
	vector<CIsland*>::iterator it_i = m_vecIsland.begin();
	for (; it_i != m_vecIsland.end(); it_i++)
	{
		if (*it_i)
		{
			printf("graph island %d\n", (*it_i)->getId());
		}
	}
}

//sub graph
CSubGraph::CSubGraph(const std::string& name) :
		CGraph(name)
{

}
CSubGraph::~CSubGraph()
{

}

int CSubGraph::addVertex(CVertex* v)
{
	CVertex* vptr = findVertexById(v->getId());
	if (vptr == NULL)
	{
		m_vecVertex.push_back(v);
		m_mapIndexVertex.insert(make_pair(v->getId(), (unsigned int) m_vecVertex.size() - 1));
	}
	else if (vptr != v)
	{
		return -1;
	}
	return m_vecVertex.size();
}
void CSubGraph::delVertex(CVertex* v)
{
	SCA_ND_ID id = v->getId();
	CVertex* vptr = findVertexById(id);
	if (vptr == v)
	{
		map<SCA_ND_ID, unsigned int>::iterator it_map;
		it_map = m_mapIndexVertex.find(id);
		if (it_map != m_mapIndexVertex.end())
		{
			int pos = it_map->second;
			vector<CVertex*>::iterator it_v = m_vecVertex.begin() + pos;
			m_vecVertex.erase(it_v);
			m_mapIndexVertex.erase(it_map);
		}
	}
}
int CSubGraph::addEdge(CEdge* e)
{
	CEdge* eptr = findEdgeById(e->getId());
	if (eptr == NULL)
	{
		m_vecEdge.push_back(e);
		m_mapIndexEdge.insert(make_pair(e->getId(), (unsigned int) m_vecEdge.size() - 1));
	}
	else if (eptr != e)
	{
		return -1;
	}
	return m_vecEdge.size();
}
void CSubGraph::delEdge(CEdge* e)
{
	SCA_ID id = e->getId();
	CEdge* eptr = findEdgeById(id);
	if (eptr == e)
	{
		map<SCA_ID, unsigned int>::iterator it_map;
		it_map = m_mapIndexEdge.find(id);
		if (it_map != m_mapIndexEdge.end())
		{
			int pos = it_map->second;
			vector<CEdge*>::iterator it_e = m_vecEdge.begin() + pos;
			m_vecEdge.erase(it_e);
			m_mapIndexEdge.erase(it_map);
		}
	}
}
CVertex* CSubGraph::createVertex(const SCA_ND_ID id)
{
	return NULL;
}
void CSubGraph::releaseVertex(const SCA_ND_ID id)
{
	return;
}
void CSubGraph::releaseEdge(const SCA_ID id)
{
	return;
}
void CSubGraph::freeGraph()
{
//free island
	vector<CIsland*>::iterator it_i = m_vecIsland.begin();
	for (; it_i != m_vecIsland.end(); it_i++)
	{
		if (*it_i)
		{
			delete *it_i;
			*it_i = NULL;
		}
	}
}

} /* namespace SCADA_ALG */
