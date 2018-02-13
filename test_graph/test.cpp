#include "../CGraph.h"
#include "../CTopoAlg.h"
#include "../CPropertyReader.h"
#include "../CModelLoaderFactory.h"
#include "../CModelContainer.h"
#include "../CRtModelContainer.h"
#include "../CConfigurationInfo.h"

using namespace SCADA_ALG;

int main(int argc, char** argv)
{
	CGraph* graph = new CGraph("graph");
	CSubGraph* graph1 = new CSubGraph("graph1");
	CSubGraph* graph2 = new CSubGraph("graph2");
	CSubGraph* graph3 = new CSubGraph("graph3");

	printf("graph id = %d \n", graph->getId());
	printf("graph1 id = %d \n", graph1->getId());
	printf("graph2 id = %d \n", graph2->getId());
	printf("graph3 id = %d \n", graph3->getId());

	CVertex* va = graph->createVertex(100);
	CVertex* vb = graph->createVertex(101);
	CVertex* vc = graph->createVertex(102);
	CVertex* vd = graph->createVertex(103);
	CVertex* ve = graph->createVertex(104);
	CVertex* vf = graph->createVertex(105);
	CVertex* vg = graph->createVertex(106);
	CVertex* vh = graph->createVertex(107);

	CEdge* ac = va->createEdgeTo(vc->getId(), 2);
	CEdge* ad = va->createEdgeTo(vd->getId(), 3);
	CEdge* cd = vc->createEdgeTo(vd->getId(), 1);

	CEdge* ae = va->createEdgeTo(ve->getId(), 4);
	CEdge* ef = ve->createEdgeTo(vf->getId(), 5);
	CEdge* fb = vf->createEdgeTo(vb->getId(), 6);

	CEdge* bg = vb->createEdgeTo(vg->getId(), 7);
	CEdge* gh = vg->createEdgeTo(vh->getId(), 8);

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
	for (int i = 0; i < vecV.size(); i++)
	{
		if (vecV[i]->hasProperty("graph1"))
		{
			int sub_island_no = vecV[i]->getProperty("graph1").c_int();
			printf("id = %ld , island is %d \n", vecV[i]->getId(), sub_island_no);
			CIsland* island = graph1->createIsland(sub_island_no);
			island->appendVertex(vecV[i]);
		}
	}
	printf("ae->getOppVertex(va)->getId() = %ld\n", ae->getOppVertex(va)->getId());
	CTopoAlg topo_alg2;
	topo_alg2.setConnectedGraphName("graph2");
	topo_alg2.setGraph(graph2);
	topo_alg2.searchConnectedGraph();
	vector<CVertex*> vecV2 = graph2->getAllVertex();
	for (int i = 0; i < vecV2.size(); i++)
	{
		if (vecV2[i]->hasProperty("graph2"))
		{
			int sub_island_no = vecV2[i]->getProperty("graph2").c_int();
			printf("id = %ld , island is %d \n", vecV2[i]->getId(), sub_island_no);
			CIsland* island = graph2->createIsland(sub_island_no);
			island->appendVertex(vecV2[i]);
		}
	}
	CTopoAlg topo_alg3;
	topo_alg3.setConnectedGraphName("graph3");
	topo_alg3.setGraph(graph3);
	topo_alg3.searchConnectedGraph();
	vector<CVertex*> vecV3 = graph3->getAllVertex();
	for (int i = 0; i < vecV3.size(); i++)
	{
		if (vecV3[i]->hasProperty("graph3"))
		{
			int sub_island_no = vecV3[i]->getProperty("graph3").c_int();
			printf("id = %ld , island is %d \n", vecV3[i]->getId(), sub_island_no);
			CIsland* island = graph3->createIsland(sub_island_no);
			island->appendVertex(vecV3[i]);
		}
	}

	printf("before merge island \n");

	printf("======graph1=====\n");
	printf("va island addr is %x , id = %d\n", va->belongToIsland(graph1),
			va->belongToIsland(graph1)->getId());
	//printf("vb island addr is %x , id = %d\n",vb->belongToIsland(graph1),vb->belongToIsland(graph1)->getId());
	printf("vc island addr is %x , id = %d\n", vc->belongToIsland(graph1),
			vc->belongToIsland(graph1)->getId());
	printf("vd island addr is %x , id = %d\n", vd->belongToIsland(graph1),
			vd->belongToIsland(graph1)->getId());
	//printf("ve island addr is %x , id = %d\n",ve->belongToIsland(graph1),ve->belongToIsland(graph1)->getId());
	//printf("vf island addr is %x , id = %d\n",vf->belongToIsland(graph1),vf->belongToIsland(graph1)->getId());
	//printf("vg island addr is %x , id = %d\n",vg->belongToIsland(graph1),vg->belongToIsland(graph1)->getId());
	//printf("vh island addr is %x , id = %d\n",vh->belongToIsland(graph1),vh->belongToIsland(graph1)->getId());

	printf("======graph2=====\n");
	printf("va island addr is %x , id = %d\n", va->belongToIsland(graph2),
			va->belongToIsland(graph2)->getId());
	printf("vb island addr is %x , id = %d\n", vb->belongToIsland(graph2),
			vb->belongToIsland(graph2)->getId());
	//printf("vc island addr is %x , id = %d\n",vc->belongToIsland(graph2),vc->belongToIsland(graph2)->getId());
	//printf("vd island addr is %x , id = %d\n",vd->belongToIsland(graph2),vd->belongToIsland(graph2)->getId());
	printf("ve island addr is %x , id = %d\n", ve->belongToIsland(graph2),
			ve->belongToIsland(graph2)->getId());
	printf("vf island addr is %x , id = %d\n", vf->belongToIsland(graph2),
			vf->belongToIsland(graph2)->getId());
	//printf("vg island addr is %x , id = %d\n",vg->belongToIsland(graph2),vg->belongToIsland(graph2)->getId());
	//printf("vh island addr is %x , id = %d\n",vh->belongToIsland(graph2),vh->belongToIsland(graph2)->getId());

	printf("======graph3=====\n");
	//printf("va island addr is %x , id = %d\n",va->belongToIsland(graph3),va->belongToIsland(graph3)->getId());
	printf("vb island addr is %x , id = %d\n", vb->belongToIsland(graph3),
			vb->belongToIsland(graph3)->getId());
	//printf("vc island addr is %x , id = %d\n",vc->belongToIsland(graph3),vc->belongToIsland(graph3)->getId());
	//printf("vd island addr is %x , id = %d\n",vd->belongToIsland(graph3),vd->belongToIsland(graph3)->getId());
	//printf("ve island addr is %x , id = %d\n",ve->belongToIsland(graph3),ve->belongToIsland(graph3)->getId());
	//printf("vf island addr is %x , id = %d\n",vf->belongToIsland(graph3),vf->belongToIsland(graph3)->getId());
	//printf("vg island addr is %x , id = %d\n",vg->belongToIsland(graph3),vg->belongToIsland(graph3)->getId());
	printf("vh island addr is %x , id = %d\n", vh->belongToIsland(graph3),
			vh->belongToIsland(graph3)->getId());

	printf("start merge\n");

	//ºÏ²¢
	va->belongToIsland(graph1)->mergeIsland(va->belongToIsland(graph2), graph);
	vb->belongToIsland(graph2)->mergeIsland(vb->belongToIsland(graph3), graph);

	printf("======graph=====\n");
	printf("va island addr is %x , id = %d\n", va->belongToIsland(graph),
			va->belongToIsland(graph)->getId());
	printf("vb island addr is %x , id = %d\n", vb->belongToIsland(graph),
			vb->belongToIsland(graph)->getId());
	printf("vc island addr is %x , id = %d\n", vc->belongToIsland(graph),
			vc->belongToIsland(graph)->getId());
	printf("vd island addr is %x , id = %d\n", vd->belongToIsland(graph),
			vd->belongToIsland(graph)->getId());
	printf("ve island addr is %x , id = %d\n", ve->belongToIsland(graph),
			ve->belongToIsland(graph)->getId());
	printf("vf island addr is %x , id = %d\n", vf->belongToIsland(graph),
			vf->belongToIsland(graph)->getId());
	printf("vg island addr is %x , id = %d\n", vg->belongToIsland(graph),
			vg->belongToIsland(graph)->getId());
	printf("vh island addr is %x , id = %d\n", vh->belongToIsland(graph),
			vh->belongToIsland(graph)->getId());

	printf("======graph1=====\n");
	printf("va island addr is %x , id = %d\n", va->belongToIsland(graph1),
			va->belongToIsland(graph1)->getId());
	//printf("vb island addr is %x , id = %d\n",vb->belongToIsland(graph1),vb->belongToIsland(graph1)->getId());
	printf("vc island addr is %x , id = %d\n", vc->belongToIsland(graph1),
			vc->belongToIsland(graph1)->getId());
	printf("vd island addr is %x , id = %d\n", vd->belongToIsland(graph1),
			vd->belongToIsland(graph1)->getId());
	//printf("ve island addr is %x , id = %d\n",ve->belongToIsland(graph1),ve->belongToIsland(graph1)->getId());
	//printf("vf island addr is %x , id = %d\n",vf->belongToIsland(graph1),vf->belongToIsland(graph1)->getId());
	//printf("vg island addr is %x , id = %d\n",vg->belongToIsland(graph1),vg->belongToIsland(graph1)->getId());
	//printf("vh island addr is %x , id = %d\n",vh->belongToIsland(graph1),vh->belongToIsland(graph1)->getId());

	printf("======graph2=====\n");
	printf("va island addr is %x , id = %d\n", va->belongToIsland(graph2),
			va->belongToIsland(graph2)->getId());
	printf("vb island addr is %x , id = %d\n", vb->belongToIsland(graph2),
			vb->belongToIsland(graph2)->getId());
	//printf("vc island addr is %x , id = %d\n",vc->belongToIsland(graph2),vc->belongToIsland(graph2)->getId());
	//printf("vd island addr is %x , id = %d\n",vd->belongToIsland(graph2),vd->belongToIsland(graph2)->getId());
	printf("ve island addr is %x , id = %d\n", ve->belongToIsland(graph2),
			ve->belongToIsland(graph2)->getId());
	printf("vf island addr is %x , id = %d\n", vf->belongToIsland(graph2),
			vf->belongToIsland(graph2)->getId());
	//printf("vg island addr is %x , id = %d\n",vg->belongToIsland(graph2),vg->belongToIsland(graph2)->getId());
	//printf("vh island addr is %x , id = %d\n",vh->belongToIsland(graph2),vh->belongToIsland(graph2)->getId());

	printf("======graph3=====\n");
	//printf("va island addr is %x , id = %d\n",va->belongToIsland(graph3),va->belongToIsland(graph3)->getId());
	printf("vb island addr is %x , id = %d\n", vb->belongToIsland(graph3),
			vb->belongToIsland(graph3)->getId());
	//printf("vc island addr is %x , id = %d\n",vc->belongToIsland(graph3),vc->belongToIsland(graph3)->getId());
	//printf("vd island addr is %x , id = %d\n",vd->belongToIsland(graph3),vd->belongToIsland(graph3)->getId());
	//printf("ve island addr is %x , id = %d\n",ve->belongToIsland(graph3),ve->belongToIsland(graph3)->getId());
	//printf("vf island addr is %x , id = %d\n",vf->belongToIsland(graph3),vf->belongToIsland(graph3)->getId());
	printf("vg island addr is %x , id = %d\n", vg->belongToIsland(graph3),
			vg->belongToIsland(graph3)->getId());
	printf("vh island addr is %x , id = %d\n", vh->belongToIsland(graph3),
			vh->belongToIsland(graph3)->getId());

	//É¾³ýÍ¼
	graph->freeGraph();
	//delete graph;
	graph1->freeGraph();
	//delete graph1;
	graph2->freeGraph();
	//delete graph2;
	graph3->freeGraph();
	//delete graph3;

	CPropertyReader::loadConfigure("/home/d5000/hs3/conf/topo_model_rtdb.xml");
	int ret = CPropertyReader::getAllPropertyInfo(CConfigurationInfo::getInst()->getAllProperty());

	printf("------------------------start---------------------------------\n");
	IPropertyInfo::PropertyTypeInfoMapIterator it;
	IPropertyInfo::PropertyTypeInfoMap& appProperty = CConfigurationInfo::getInst()->getAppProperty("ems");
	for (it = appProperty.begin();
			it != appProperty.end(); it++)
	{
		CModelObj::ObjType obj_type = it->first;
		vector<int> vec_fields;
		CPropertyInfo* p = dynamic_cast<CPropertyInfo*>(it->second["tab"]);
		int tab = p->tabNo();
		printf("tab_no is %d \n", tab);
		IPropertyInfo::PropertyInfoMap pinfo = it->second;
		IPropertyInfo::PropertyInfoMapIterator itp;
		int record_size = 0;
		for (itp = pinfo.begin(); itp != pinfo.end(); itp++)
		{
			p = dynamic_cast<CPropertyInfo*>(itp->second);
			//field_name += p->name();
			vec_fields.push_back(p->fieldNo());
			printf("field_name is  %s , field_no  is %d ,len is %d, link is %d\n",
					p->name().c_str(), p->fieldNo(), p->len(), p->isLink() == true ? 1 : 0);
			record_size += p->len();
		}

	}
	printf("-------------------------end--------------------------------\n");
	CGraph* test_graph = new CGraph("test");
	CRtModelContainer container(test_graph);
	std::auto_ptr<IModelLoader> loader_aptr = CModelLoaderFactory::getInstance().create("rt");
	loader_aptr->loadModelTo(container, "ems");

	container.debugPrint();

	container.transAllModelToGraph();

	//test_graph->debugPrintGraph();
	return 1;
}
