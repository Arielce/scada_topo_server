#include "../CGraph.h"
#include "../CTopoAlg.h"

using namespace SCADA_ALG;

int main(int argc,char** argv)
{
	CGraph* graph = new CGraph();
	CSubGraph* graph1 = new CSubGraph();
	CSubGraph* graph2 = new CSubGraph();
	CSubGraph* graph3 = new CSubGraph();

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
			int sub_island_no = vecV[i]->getProperty("graph1").c_int();
			printf( "id = %ld , island is %d \n",vecV[i]->getId(), sub_island_no );
			CIsland* island = graph1->createIsland( 1000 + sub_island_no );
			island->appendVertex(vecV[i]);
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
			int sub_island_no = vecV2[i]->getProperty("graph2").c_int();
			printf( "id = %ld , island is %d \n",vecV2[i]->getId(), sub_island_no );
			CIsland* island = graph2->createIsland( 2000 + sub_island_no );
			island->appendVertex(vecV2[i]);
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
			int sub_island_no = vecV3[i]->getProperty("graph3").c_int();
			printf( "id = %ld , island is %d \n",vecV3[i]->getId(), sub_island_no  );
			CIsland* island = graph3->createIsland( 3000 + sub_island_no );
			island->appendVertex(vecV3[i]);
		}
	}

	//ºÏ²¢
	va->belongToIsland(graph1)->mergeIsland( va->belongToIsland(graph2),graph );
	vb->belongToIsland(graph2)->mergeIsland( vb->belongToIsland(graph3),graph );

	printf("======graph=====\n");
	printf("va island addr is %x\n",va->belongToIsland(graph));
	printf("vb island addr is %x\n",vb->belongToIsland(graph));
	printf("vc island addr is %x\n",vc->belongToIsland(graph));
	printf("vd island addr is %x\n",vd->belongToIsland(graph));
	printf("ve island addr is %x\n",ve->belongToIsland(graph));
	printf("vf island addr is %x\n",vf->belongToIsland(graph));
	printf("vg island addr is %x\n",vg->belongToIsland(graph));
	printf("vh island addr is %x\n",vh->belongToIsland(graph));

	printf("======graph1=====\n");
	printf("va island addr is %x\n",va->belongToIsland(graph1));
	printf("vb island addr is %x\n",vb->belongToIsland(graph1));
	printf("vc island addr is %x\n",vc->belongToIsland(graph1));
	printf("vd island addr is %x\n",vd->belongToIsland(graph1));
	printf("ve island addr is %x\n",ve->belongToIsland(graph1));
	printf("vf island addr is %x\n",vf->belongToIsland(graph1));
	printf("vg island addr is %x\n",vg->belongToIsland(graph1));
	printf("vh island addr is %x\n",vh->belongToIsland(graph1));

	printf("======graph2=====\n");
	printf("va island addr is %x\n",va->belongToIsland(graph2));
	printf("vb island addr is %x\n",vb->belongToIsland(graph2));
	printf("vc island addr is %x\n",vc->belongToIsland(graph2));
	printf("vd island addr is %x\n",vd->belongToIsland(graph2));
	printf("ve island addr is %x\n",ve->belongToIsland(graph2));
	printf("vf island addr is %x\n",vf->belongToIsland(graph2));
	printf("vg island addr is %x\n",vg->belongToIsland(graph2));
	printf("vh island addr is %x\n",vh->belongToIsland(graph2));

	printf("======graph3=====\n");
	printf("va island addr is %x\n",va->belongToIsland(graph3));
	printf("vb island addr is %x\n",vb->belongToIsland(graph3));
	printf("vc island addr is %x\n",vc->belongToIsland(graph3));
	printf("vd island addr is %x\n",vd->belongToIsland(graph3));
	printf("ve island addr is %x\n",ve->belongToIsland(graph3));
	printf("vf island addr is %x\n",vf->belongToIsland(graph3));
	printf("vg island addr is %x\n",vg->belongToIsland(graph3));
	printf("vh island addr is %x\n",vh->belongToIsland(graph3));

	//É¾³ýÍ¼
	graph->freeGraph();
	delete graph;
	graph1->freeGraph();
	delete graph1;
	graph2->freeGraph();
	delete graph2;
	graph3->freeGraph();
	delete graph3;

	return 1;
}
