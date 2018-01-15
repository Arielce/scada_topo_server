#include "../CGraph.h"
#include "../CTopoAlg.h"

using namespace SCADA_ALG;

int main(int argc,char** argv)
{
	CGraph* graph = new CGraph();
	CGraph* graph1 = new CGraph();
	CGraph* graph2 = new CGraph();
	CGraph* graph3 = new CGraph();

	CVertex* va = graph->createVertex(100);
	CVertex* vb = graph->createVertex(101);
	CVertex* vc = graph->createVertex(102);
	CVertex* vd = graph->createVertex(103);
	CVertex* ve = graph->createVertex(104);
	CVertex* vf = graph->createVertex(105);
	CVertex* vg = graph->createVertex(106);
	CVertex* vh = graph->createVertex(107);

	CEdge* ac = va->createEdgeTo(vc->getId(),2);
	CEdge* ad = va->createEdgeTo(vd->getId(),3);
	CEdge* cd = vc->createEdgeTo(vd->getId(),1);

	CEdge* ae = va->createEdgeTo(ve->getId(),4);
	CEdge* ef = ve->createEdgeTo(vf->getId(),5);
	CEdge* fb = vf->createEdgeTo(vb->getId(),6);

	CEdge* bg = vb->createEdgeTo(vg->getId(),7);
	CEdge* gh = vg->createEdgeTo(vh->getId(),8);

	//ef->setOpen(true);

	graph1->addVertex(va);
	graph1->addVertex(vc);
	graph1->addVertex(vd);
	graph1->addEdge(ac);
	graph1->addEdge(ad);
	graph1->addEdge(cd);

	graph2->addVertex(va);
	graph2->addVertex(ve);
	graph2->addVertex(vf);
	graph2->addVertex(vb);
	graph2->addEdge(ae);
	graph2->addEdge(ef);
	graph2->addEdge(fb);

	graph3->addVertex(vb);
	graph3->addVertex(vg);
	graph3->addVertex(vh);
	graph2->addEdge(bg);
	graph2->addEdge(gh);

	CTopoAlg topo_alg1;
	topo_alg1.setConnectedGraphName("graph1");
	topo_alg1.setGraph(graph1);
	topo_alg1.searchConnectedGraph();

	vector<CVertex*> vecV = graph1->getAllVertex();
	for (int i=0;i<vecV.size();i++)
	{
		if (vecV[i]->hasProperty("graph1"))
		{
			printf( "id = %ld , island is %d \n",vecV[i]->getId(),vecV[i]->getProperty("graph1").c_int()  );
		}
	}
	printf("ae->getOppVertex(va)->getId() = %ld\n",ae->getOppVertex(va)->getId());
	CTopoAlg topo_alg2;
	topo_alg2.setConnectedGraphName("graph2");
	topo_alg2.setGraph(graph2);
	topo_alg2.searchConnectedGraph();
	vector<CVertex*> vecV2 = graph2->getAllVertex();
	for (int i=0;i<vecV2.size();i++)
	{
		if (vecV2[i]->hasProperty("graph2"))
		{
			printf( "id = %ld , island is %d \n",vecV2[i]->getId(),vecV2[i]->getProperty("graph2").c_int()  );
		}
	}
	CTopoAlg topo_alg3;
	topo_alg3.setConnectedGraphName("graph3");
	topo_alg3.setGraph(graph3);
	topo_alg3.searchConnectedGraph();
	vector<CVertex*> vecV3 = graph3->getAllVertex();
	for (int i=0;i<vecV3.size();i++)
	{
		if (vecV3[i]->hasProperty("graph3"))
		{
			printf( "id = %ld , island is %d \n",vecV3[i]->getId(),vecV3[i]->getProperty("graph3").c_int()  );
		}
	}



	return 1;
}
