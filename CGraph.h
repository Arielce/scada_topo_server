/*
 * CGraph.h
 *
 *  Created on: 2016��9��29��
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
 * ��ǩ����ʾ�ߵ�����
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
 * ������ʾͨ������ͨ�ı�������һ��ĵ㼯
 * ����������ĳһ��ͼ
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
    		 * ���ϲ����ϲ���ĵ�����ͼgraph��
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
    		//���������ⲿ����
    		CIsland();
		CIsland(CGraph* graph);
		CIsland(CGraph* graph,const int island_no = 0);

    private:
    		CIsland* m_parentIsland;//Ψһ�ĸ���,���û����Ϊ��
    		vector<CIsland*> m_subIsland;//����ӵ�
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
         * ����ͼ�еĽڵ㣬ָ���ڵ�ؼ���Ϊid
         * */
        virtual CVertex* createVertex(const SCA_ND_ID id);
        /*
         * �ͷ�ͼ�еĽڵ�
         * */
        //virtual void releaseVertex(const SCA_ND_ID id);
        /*
         * �ͷ�ͼ�еı�
         * */
        virtual void releaseEdge(const SCA_ID id);

        CVertex* findVertexById(const SCA_ND_ID id);
        CEdge* findEdgeById(const SCA_ID id);

        vector<CVertex*> getAllVertex();
        vector<CEdge*> getAllEdge();
        void mergeGraph(const CGraph* graph);//�ϲ�ͼ

        /*
         * ������
         * */
        CIsland* createIsland( const int island_no = -1 );
        /*
         * ������ǩ
         * */
        CLabel* createLabel(const string& name);
        /*
         * ���ͼ�е����ݣ��ɿͻ����Լ����ã����������ǰ��Ҫ�ֶ�����
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
        //��
        vector<CVertex*> m_vecVertex;
        map<SCA_ND_ID,unsigned int> m_mapIndexVertex;
        typedef map<SCA_ND_ID,unsigned int>::iterator IterVertexIdx;
        //��
        vector<CEdge*> m_vecEdge;
        map<SCA_ID,unsigned int> m_mapIndexEdge;
        typedef map<SCA_ID,unsigned int>::iterator IterEdgeIdx;
        //��ǩ
        vector<CLabel*> m_vecLabel;
        map<string,CLabel*> m_mapIndexLabel;
        typedef map<string,CLabel*>::iterator IterLabelIdx;
        //������
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
    	     * ��ͼ�в��������㡢��
    	     * */
    	    CVertex* createVertex(const SCA_ND_ID id);
    	    void releaseVertex(const SCA_ND_ID id);
    	    void releaseEdge(const SCA_ID id);
    	    /*
    	     * ��ͼ����Ӻ�ɾ���Ѵ����Ľڵ㣬���ڵ�������ͼ�б����������뵽��ͼ�У�������ͼ�ķ���
    	     * */
    	    int addVertex(CVertex* v);
    	    void delVertex(CVertex* v);
    	    /*
    	     * ��ͼ����Ӻ�ɾ���Ѵ����ıߣ�����������ͼ�б����������뵽��ͼ�У�������ͼ�ķ���
    	     * */
    	    int addEdge(CEdge* e);
    	    void delEdge(CEdge* e);
    	    void freeGraph();
    };

} /* namespace SCADA_ALG */
#endif /* CGRAPH_H_ */
