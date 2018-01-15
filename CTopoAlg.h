/*
 * CTopoAlg.h
 *
 *  Created on: 2016年10月13日
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
         *功能：最短路径分析
         *输入：起点和终点
         *输出：路径上的点
         */
        vector<CVertex*> searchShortestPath(const CVertex* s_vertex,const CVertex* e_vertex);
        /*
         *功能：连通子图查找
         *输入：边界
         *输出：返回值为连通子图的个数
         */
        int searchConnectedGraph(vector<CEdge*> vec_border = vector<CEdge*>());
        int getConnectedGraphWithinEdge(map<int,vector<CEdge*> >& map_edge);
        int getConnectedGraphWithinVertex(map<int,vector<CVertex*> >& map_vertex);

        void setConnectedGraphName(string graph_name = "connected_graph_no");

    private:
        void Dfs(CVertex* const v,const int no);//深度优先遍历算法
        void Bfs(CVertex* const v,const int no);//广度优先遍历算法
        void addBorders(vector<CEdge*>& vec_border);//添加边界
        void delBorders(vector<CEdge*>& vec_border);//删除边界

    private:
        map<int,vector<CVertex*> > m_mapConnectedGraphVertex;//连通子图号与连通域内的点对应关系
        map<int,vector<CEdge*> > m_mapConnectedGraphEdge;//连通子图号与连通域内的边对应关系
        int m_connectedGraphNum;
        string m_connectedGraphName;
    };

} /* namespace SCADA_ALG */
#endif /* CTOPOALG_H_ */
