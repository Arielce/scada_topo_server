/*
 * CGraph.h
 *
 *  Created on: 2016年9月29日
 *      Author: Administrator
 */

#ifndef CGRAPH_H_
#define CGRAPH_H_
//#define _WINDOWS64
//#define SCADA_ALG_EXPORTS
#ifdef _WINDOWS64
#ifdef SCADA_ALG_EXPORTS
#define SCADA_ALG_API __declspec(dllexport)
#else
#define SCADA_ALG_API __declspec(dllimport)
#endif
#else
#define SCADA_ALG_API
#endif

typedef long SCA_ID;
typedef long SCA_ND_ID;
#include <pthread.h>
#include <vector>
#include <map>
#include <queue>
#include <string>

#include "CUDataValue.h"


using namespace std;

#ifndef NULL
#define NULL 0
#endif

namespace SCADA_ALG
{
    class CGraph;
    class CEdge;
    class CLabel;
    class CIsland;
    class CPropertyContainer
    {
    public:
        CPropertyContainer();
        virtual ~CPropertyContainer();
        CPropertyContainer* addProperty(const string pname,const CUDataValue pvalue);
        CUDataValue getProperty(const string pname);
        bool hasProperty(const string pname);

        void setGraph(CGraph* graph);
    protected:
        map<string,CUDataValue> m_mapProperty;
        CGraph* m_graph;
    };
    class SCADA_ALG_API CVertex : public CPropertyContainer
    {
    public:
    		friend class CEdge;
        CVertex();
        CVertex(const SCA_ND_ID id);
        virtual ~CVertex();

        CEdge* createEdgeTo(const SCA_ND_ID otherId,const SCA_ID edgeId);
        SCA_ND_ID getId();
        vector<CEdge*>& getEdges();
        int getDegree();
        CIsland* belongToIsland();

    private:
        void freeVertex();

        CVertex* addEdge(CEdge* const eptr);
        CVertex* delEdge(CEdge* const eptr);
    private:
        SCA_ND_ID m_vetexId;
        vector<CEdge*> m_vecEdge;
        int m_iDegree;
        CIsland* m_island;
    };
    class SCADA_ALG_API CEdge : public CPropertyContainer
    {
    public:
        CEdge(const SCA_ID id);
        virtual ~CEdge();
        CEdge( CVertex* const s_vertex, CVertex* const e_vertex,const SCA_ID id);
        void freeEdge();
        CVertex* getOppVertex( CVertex* const vptr);
        vector<CVertex*> getAllVertex();
        CVertex* getStartVertex();
        CVertex* getEndVertex();
        void setOpen(const bool open = true);
        bool isOpen();
        void setBorder(const bool border = true);
        bool isBorder();
        SCA_ID getId();

        void addLabel(CLabel* label);
        void delLabel(CLabel* label);
        int getLabels(vector<CLabel*>& vec_label);

    private:
        SCA_ID m_edgeId;
        CVertex *m_sVertex;
        CVertex *m_eVertex;
        bool m_bEdgeOpen;
        bool m_bEdgeBorder;

        vector<CLabel*> m_vecLabels;

    };
/*
 * 标签，表示边的类型
 * */
    class CLabel
    {
    public:
        CLabel(const string name);
        virtual ~CLabel();
        string name();
        int getAllEdges(vector<CEdge*>& vec_edges);
    private:
        string m_labelName;
        vector<CEdge*> m_vecEdge;
    };
/*
 * 岛，表示通过可联通的边连接在一起的点集
 * */
    class CIsland : public CPropertyContainer
    {
    public:
    		friend class CVertex;
    	    friend class CEdge;
    		CIsland();
    		CIsland(const int island_no);
    		virtual ~CIsland();
    		void mergeIsland(CIsland* t_island);
    		void appendVertex(CVertex* v);
    		int getAllVertex(vector<CVertex*>& vec_vertex);

    private:
    		int m_islandId;
    		vector<CVertex*> m_vecVertex;
    };

    class SCADA_ALG_API CGraph
    {
    public:
        friend class CVertex;
        friend class CEdge;
        CGraph();
        virtual ~CGraph();
        /*
         * 创建图中的节点，指定节点关键字为id
         * */
        CVertex* createVertex(const SCA_ND_ID id);
        /*
         * 释放图中的节点，
         * */
        void releaseVertex(const SCA_ND_ID id);
		/*
		 * 向图中添加和删除已创建的节点，即节点在其它图中被创建，加入到此图中，用于子图的分析
		 * */
        int addVertex(CVertex* v);
        void delVertex(CVertex* v);
        /*
         * 向图中添加和删除已创建的边，即边在其它图中被创建，加入到此图中，用于子图的分析
         * */
        int addEdge(CEdge* e);
        void delEdge(CEdge* e);

        CVertex* findVertexById(const SCA_ND_ID id);
        CEdge* findEdgeById(const SCA_ID id);

        vector<CVertex*> getAllVertex();
        vector<CEdge*> getAllEdge();
        void mergeGraph(const CGraph* graph);//合并图

        void freeGraph();
    private:
        //点
        vector<CVertex*> m_vecVertex;
        map<SCA_ND_ID,unsigned int> m_mapIndexVertex;
        typedef map<SCA_ND_ID,unsigned int>::iterator IterVertexIdx;
        //边
        vector<CEdge*> m_vecEdge;
        map<SCA_ID,unsigned int> m_mapIndexEdge;
        typedef map<SCA_ID,unsigned int>::iterator IterEdgeIdx;
        //标签
        vector<CLabel*> m_vecLabel;
        //电气岛
        vector<CIsland*> m_vecIsland;
    };

} /* namespace SCADA_ALG */
#endif /* CGRAPH_H_ */
