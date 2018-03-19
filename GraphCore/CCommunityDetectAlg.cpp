/*
 * CCommunityDetectAlg.cpp
 *
 *  Created on: 2016Äê9ÔÂ29ÈÕ
 *      Author: Administrator
 */

#include "CCommunityDetectAlg.h"
#include <stdio.h>
namespace SCADA_ALG
{

CCommunityDetectAlg::CCommunityDetectAlg()
{
	// TODO Auto-generated constructor stub

}

CCommunityDetectAlg::~CCommunityDetectAlg()
{
	// TODO Auto-generated destructor stub
}
float CCommunityDetectAlg::calQValue()
{
	if (m_graph == NULL)
	{
		printf("calQValue...graph is null\n");
		return 0.0;
	}
	float q_value = 0.0;
	int edge_num = m_graph->getAllEdge().size();
	vector<CVertex*> vec_vertex;
	vec_vertex = m_graph->getAllVertex();
	int vertex_num = vec_vertex.size();
	int i = 0, j = 0;
	for (i = 0; i < vertex_num; i++)
	{
		CVertex* sv = vec_vertex[i];
		for (j = i + 1; j < vertex_num; j++)
		{
			CVertex* ev = vec_vertex[j];
			if (!isSameCommunity(sv, ev))
			{
				continue;
			}
			q_value += calWeight(sv, ev)
					- sv->getDegree() * ev->getDegree() / (2.0 * edge_num);
		}
	}
	q_value /= edge_num;
	return q_value;
}
float CCommunityDetectAlg::calWeight(CVertex* const sv, CVertex* const ev)
{
	vector<CEdge*>::iterator it;
	vector<CEdge*> sv_edges = sv->getEdges();
	//printf("sv id is %ld , edge size is %d\n",sv->getId(),sv_edges.size());
	for (it = sv_edges.begin(); it != sv_edges.end(); it++)
	{
		if ((*it)->getOppVertex(sv) == ev)
		{
			return 1.0; //gewl
			//return (*it)->getProperty("weight").c_float();
		}
	}
	return 0.0;
}
bool CCommunityDetectAlg::isSameCommunity(CVertex* const sv, CVertex* const ev)
{
	CUDataValue svalue = sv->getProperty("community");
	CUDataValue evalue = ev->getProperty("community");

	if (svalue == evalue)
	{
		printf("%ld and %ld is in same community \n", sv->getId(), ev->getId());
		return true;
	}
	return false;
}
void CCommunityDetectAlg::mergeToCommunity(CVertex* v, const int community_no)
{
	v->addProperty("community", CUDataValue().c_int(community_no));
	printf("mergeToCommunity %d \n", v->getProperty("community").c_int());
}

} /* namespace SCADA_ALG */
