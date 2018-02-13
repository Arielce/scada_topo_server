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
#include "PThreads.h"
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
        CGraph* getGraph();
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
        CIsland* belongToIsland(CGraph* const g);
        void addIsland(CIsland* island);

    private:
        void freeVertex();

        CVertex* addEdge(CEdge* const eptr);
        CVertex* delEdge(CEdge* const eptr);
    private:
        SCA_ND_ID m_vetexId;
        vector<CEdge*> m_vecEdge;
        int m_iDegree;
        map<CGraph*,CIsland*> m_mapGraphIsland;
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
 * 岛必须属于某一幅图
 * */
    class CIsland : public CPropertyContainer
    {
    public:
    		friend class CVertex;
    	    friend class CEdge;
    	    friend class CGraph;
    	    typedef int ISLAND_ID;

    		virtual ~CIsland();
    		/*
    		 * 岛合并，合并后的岛放在图graph中
    		 * */
    		void mergeIsland(CIsland* t_island,CGraph* graph);
    		void appendVertex(CVertex* v);
    		void appendVertexs(vector<CVertex*>& vec_vetex);
    		int getAllVertex(vector<CVertex*>& vec_vertex);

    		CIsland* getParent();
    		void setParent(CIsland* island);

    		vector<CIsland*> getSubIsland();
    		void addSubIsland(CIsland* island);

    		inline const int& getId()const {return m_islandId;};

    private:
    		//不允许在外部创建
    		CIsland();
		CIsland(CGraph* graph);
		CIsland(CGraph* graph,const int island_no = 0);

    private:
    		CIsland* m_parentIsland;//唯一的父岛,如果没有则为空
    		vector<CIsland*> m_subIsland;//多个子岛
    		vector<CVertex*> m_vecVertex;
    		ISLAND_ID m_islandId;
    };

    class SCADA_ALG_API CGraph
    {
    public:
        friend class CVertex;
        friend class CEdge;
        CGraph(const std::string& name);
        virtual ~CGraph();
        /*
         * 创建图中的节点，指定节点关键字为id
         * */
        virtual CVertex* createVertex(const SCA_ND_ID id);
        /*
         * 释放图中的节点
         * */
        //virtual void releaseVertex(const SCA_ND_ID id);
        /*
         * 释放图中的边
         * */
        virtual void releaseEdge(const SCA_ID id);

        CVertex* findVertexById(const SCA_ND_ID id);
        CEdge* findEdgeById(const SCA_ID id);

        vector<CVertex*> getAllVertex();
        vector<CEdge*> getAllEdge();
        void mergeGraph(const CGraph* graph);//合并图

        /*
         * 创建岛
         * */
        CIsland* createIsland( const int island_no = -1 );
        /*
         * 创建标签
         * */
        CLabel* createLabel(const string& name);
        /*
         * 清空图中的数据，由客户端自己调用，因此在析构前需要手动调用
         * */
        virtual void freeGraph();

        static CGraph* getGraph(const std::string& name);
        inline const std::string& getName() const { return _name; };
        inline const int& getId()const {return _graphId;};

        void debugPrintGraph();

    private:
		typedef std::map<std::string, CGraph*> GraphMap;

		static GraphMap& _getAllGraphs();
		static void _deleteAllGraphs();
		static void _deleteAllGraphsWOLock(std::vector<CGraph*> &graphs);
		static void _addGraph(CGraph* graph);
		static void _removeGraph(CGraph* graph);

		const std::string _name;
		int _graphId;
		const int _island_base_no;

	public:
		class GraphMapStorage
		{
		public:
			CGraph::GraphMap* _allgraphs;// single shared instance, nifty-counter defensed
			threading::Mutex _graphMapMutex;	// mutex protecting map from multiple thread access

			GraphMapStorage();
			~GraphMapStorage();
		};
		class SCADA_ALG_API GraphMapStorageInitializer
		{
		public:
			GraphMapStorageInitializer();
			~GraphMapStorageInitializer();
		};
	private:
		static GraphMapStorage &_graphMapStorageInstance;

    protected:
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
        map<string,CLabel*> m_mapIndexLabel;
        typedef map<string,CLabel*>::iterator IterLabelIdx;
        //电气岛
        vector<CIsland*> m_vecIsland;
        map<CIsland::ISLAND_ID,unsigned int> m_mapIndexIsland;
        typedef map<CIsland::ISLAND_ID,unsigned int>::iterator IterIslandIdx;
    };

    static CGraph::GraphMapStorageInitializer graphMapStorageInitializer; // static initializer for every translation unit

    class SCADA_ALG_API CSubGraph : public CGraph
    {
    public:
    		CSubGraph(const std::string& name);
    	    virtual ~CSubGraph();
    	    /*
    	     * 子图中不允许创建点、边
    	     * */
    	    CVertex* createVertex(const SCA_ND_ID id);
    	    void releaseVertex(const SCA_ND_ID id);
    	    void releaseEdge(const SCA_ID id);
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
    	    void freeGraph();
    };

} /* namespace SCADA_ALG */
#endif /* CGRAPH_H_ */
