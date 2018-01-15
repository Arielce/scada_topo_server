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
         * ����ͼ�еĽڵ㣬ָ���ڵ�ؼ���Ϊid
         * */
        CVertex* createVertex(const SCA_ND_ID id);
        /*
         * �ͷ�ͼ�еĽڵ㣬
         * */
        void releaseVertex(const SCA_ND_ID id);
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

        CVertex* findVertexById(const SCA_ND_ID id);
        CEdge* findEdgeById(const SCA_ID id);

        vector<CVertex*> getAllVertex();
        vector<CEdge*> getAllEdge();
        void mergeGraph(const CGraph* graph);//�ϲ�ͼ

        void freeGraph();
    private:
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
        //������
        vector<CIsland*> m_vecIsland;
    };

} /* namespace SCADA_ALG */
#endif /* CGRAPH_H_ */
