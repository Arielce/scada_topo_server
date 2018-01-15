/*
 * CTopoAlg.h
 *
 *  Created on: 2016��10��13��
 *      Author: Administrator
 */

#ifndef CTOPOALG_H_
#define CTOPOALG_H_

#include "CScadaAlg.h"
#include "CGraph.h"

namespace SCADA_ALG
{

    class SCADA_ALG_API CTopoAlg : public CScadaAlg
    {
    public:
        CTopoAlg();
        virtual ~CTopoAlg();
        /*
         *���ܣ����·������
         *���룺�����յ�
         *�����·���ϵĵ�
         */
        vector<CVertex*> searchShortestPath(const CVertex* s_vertex,const CVertex* e_vertex);
        /*
         *���ܣ���ͨ��ͼ����
         *���룺�߽�
         *���������ֵΪ��ͨ��ͼ�ĸ���
         */
        int searchConnectedGraph(vector<CEdge*> vec_border = vector<CEdge*>());
        int getConnectedGraphWithinEdge(map<int,vector<CEdge*> >& map_edge);
        int getConnectedGraphWithinVertex(map<int,vector<CVertex*> >& map_vertex);

        void setConnectedGraphName(string graph_name = "connected_graph_no");

    private:
        void Dfs(CVertex* const v,const int no);//������ȱ����㷨
        void Bfs(CVertex* const v,const int no);//������ȱ����㷨
        void addBorders(vector<CEdge*>& vec_border);//��ӱ߽�
        void delBorders(vector<CEdge*>& vec_border);//ɾ���߽�

    private:
        map<int,vector<CVertex*> > m_mapConnectedGraphVertex;//��ͨ��ͼ������ͨ���ڵĵ��Ӧ��ϵ
        map<int,vector<CEdge*> > m_mapConnectedGraphEdge;//��ͨ��ͼ������ͨ���ڵı߶�Ӧ��ϵ
        int m_connectedGraphNum;
        string m_connectedGraphName;
    };

} /* namespace SCADA_ALG */
#endif /* CTOPOALG_H_ */
