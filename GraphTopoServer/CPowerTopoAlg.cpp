/*
 * CPowerTopoAlg.cpp
 *
 *  Created on: 2016年10月13日
 *      Author: Administrator
 */

#include "CTopoAlg.h"
#include "CPowerTopoAlg.h"
#include "CPowerDevice.h"
#include "db_def/sys_menu_info.h"

namespace SCADA_ALG
{

    CPowerTopoAlg::CPowerTopoAlg()
    {
        // TODO Auto-generated constructor stub
        m_topoAlg = new CTopoAlg();
    }

    CPowerTopoAlg::~CPowerTopoAlg()
    {
        // TODO Auto-generated destructor stub
        if (m_topoAlg)
        {
            delete m_topoAlg;
        }
    }
    void
    CPowerTopoAlg::islandAnalysis(map<int, vector<CEdge*> >& map_island_dev) //电气岛分析
    {
        //todo 调用CTopoAlg中提供的联通区域查找算法进行电气岛分析
        m_topoAlg->setGraph(m_graph);
        vector<CEdge*> vec_border;
        int island_num = m_topoAlg->searchConnectedGraph(vec_border);
        m_topoAlg->getConnectedGraphWithinEdge(map_island_dev);
    }
    CVertex*
    CPowerTopoAlg::searchPower(const CVertex* vertex) //电源点查找
    {

    }
    vector<CVertex*>
    CPowerTopoAlg::searchSupplyRange(const CVertex* vertex) //供电范围查找
    {

    }

    void
    CPowerTopoAlg::addAclnInfo(const CPowerDevice* devs)
    {
        //add acline
        CPowerDevice::EmsAclnIterator it_acln;
        for (it_acln = devs->emsAclnBegin(); it_acln != devs->emsAclnEnd(); it_acln++)
        {
            if (2 != devs->emsDotNumberOfAclnId(it_acln->id))
            {
                //todo log error
                continue;
            }
            CPowerDevice::EmsAclnToDotIterator it_dot = devs->emsDotOfAclnBegin(it_acln->id);
            SCA_ND_ID ind = (*it_dot)->nd;
            it_dot++;
            SCA_ND_ID jnd = (*it_dot)->nd;
            if (isEmsNdValid(ind , jnd))
            {
                addAcline(it_acln->id , ind , jnd);
            }
            else if (it_acln->eq_fg && isEmsNdValid(ind))
            {
                if (it_acln->eq_fg == MENU_LN_EQFG_LD)
                {
                    addEnergyConsumer(it_acln->id , ind)->addProperty("is_equal" ,
                            CUDataValue().c_uchar(1));
                }
                else if (it_acln->eq_fg == MENU_LN_EQFG_UN)
                {
                    addGeneratingUnit(it_acln->id , ind)->addProperty("is_equal" ,
                            CUDataValue().c_uchar(1));
                }
            }
            else if (it_acln->eq_fg && isEmsNdValid(jnd))
            {
                if (it_acln->eq_fg == MENU_LN_EQFG_LD)
                {
                    addEnergyConsumer(it_acln->id , jnd)->addProperty("is_equal" ,
                            CUDataValue().c_uchar(1));
                }
                else if (it_acln->eq_fg == MENU_LN_EQFG_UN)
                {
                    addGeneratingUnit(it_acln->id , jnd)->addProperty("is_equal" ,
                            CUDataValue().c_uchar(1));
                }
            }
        }
    }

    void
    CPowerTopoAlg::addGDDiscrInfo(const CPowerDevice* devs)
    {
        //add gddiscr
        CPowerDevice::EmsGDDiscrIterator it_gddiscr;
        for (it_gddiscr = devs->emsGDDiscrBegin(); it_gddiscr != devs->emsGDDiscrEnd();
                it_gddiscr++)
        {
            addGDDisconnector(it_gddiscr->id , it_gddiscr->nd)->addProperty("st_id" ,
                    CUDataValue().c_long(it_gddiscr->st_id));
        }
    }

    void
    CPowerTopoAlg::addDiscrInfo(const CPowerDevice* devs)
    {
        //add discr
        CPowerDevice::EmsDiscrIterator it_discr;
        for (it_discr = devs->emsDiscrBegin(); it_discr != devs->emsDiscrEnd(); it_discr++)
        {
            addDisconnector(it_discr->id , it_discr->ind , it_discr->jnd)->addProperty("st_id" ,
                    CUDataValue().c_long(it_discr->st_id));
        }
    }

    void
    CPowerTopoAlg::addBreakerInfo(const CPowerDevice* devs)
    {
        //add breaker
        CPowerDevice::EmsBrkIterator it_brk;
        for (it_brk = devs->emsBrkBegin(); it_brk != devs->emsBrkEnd(); it_brk++)
        {
            addBreaker(it_brk->id , it_brk->ind , it_brk->jnd)->addProperty("st_id" ,
                    CUDataValue().c_long(it_brk->st_id));
        }
    }

    void
    CPowerTopoAlg::addDmsCbInfo(const CPowerDevice* devs)
    {
        CPowerDevice::DmsCbIterator it_cb;
        for (it_cb = devs->dmsCbBegin(); it_cb != devs->dmsCbEnd(); it_cb++)
        {
            addDmsCb(it_cb->id , it_cb->ind , it_cb->jnd)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_cb->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_cb->combined_id));
        }
    }

    void
    CPowerTopoAlg::addDmsDiscrInfo(const CPowerDevice* devs)
    {
        //add dms discr
        CPowerDevice::DmsDiscrIterator it_discr;
        for (it_discr = devs->dmsDiscrBegin(); it_discr != devs->dmsDiscrEnd(); it_discr++)
        {
            addDmsDiscr(it_discr->id , it_discr->ind , it_discr->jnd)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_discr->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_discr->combined_id));
        }
    }

    void
    CPowerTopoAlg::addDmsGDDiscrInfo(const CPowerDevice* devs)
    {
        //add dms gddiscr
        CPowerDevice::DmsGDDiscrIterator it_gddiscr;
        for (it_gddiscr = devs->dmsGDDiscrBegin(); it_gddiscr != devs->dmsGDDiscrEnd();
                it_gddiscr++)
        {
            addDmsGDDiscr(it_gddiscr->id , it_gddiscr->nd)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_gddiscr->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_gddiscr->combined_id));
        }
    }

    void
    CPowerTopoAlg::addDmsSectionInfo(const CPowerDevice* devs)
    {
        //add dms section
        CPowerDevice::DmsSectionIterator it_sec;
        for (it_sec = devs->dmsSectionBegin(); it_sec != devs->dmsSectionBegin(); it_sec++)
        {
            addDmsSection(it_sec->id , it_sec->ind , it_sec->jnd)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_sec->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_sec->combined_id));
        }
    }

    void
    CPowerTopoAlg::addDmsLoadInfo(const CPowerDevice* devs)
    {
        //add dms ld
        CPowerDevice::DmsLdIterator it_ld;
        for (it_ld = devs->dmsLdBegin(); it_ld != devs->dmsLdEnd(); it_ld++)
        {
            addDmsLoad(it_ld->id , it_ld->nd_no)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_ld->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_ld->combined_id));
            addDmsLoad(it_ld->id , it_ld->nd2_no)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_ld->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_ld->combined_id));
            addDmsLoad(it_ld->id , it_ld->nd3_no)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_ld->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_ld->combined_id));
            addDmsLoad(it_ld->id , it_ld->nd4_no)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_ld->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_ld->combined_id));
        }
    }

    void
    CPowerTopoAlg::addDmsBsInfo(const CPowerDevice* devs)
    {
        //add dms bs
        CPowerDevice::DmsBsIterator it_bs;
        for (it_bs = devs->dmsBsBegin(); it_bs != devs->dmsBsEnd(); it_bs++)
        {
            addDmsBs(it_bs->id , it_bs->nd)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_bs->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_bs->combined_id));
        }
    }

    void
    CPowerTopoAlg::addDmsTrInfo(const CPowerDevice* devs)
    {
        //add dms tr
        CPowerDevice::DmsTrIterator it_tr;
        for (it_tr = devs->dmsTrBegin(); it_tr != devs->dmsTrEnd(); it_tr++)
        {
            addDmsTr(it_tr->id , it_tr->bs_id_h , it_tr->bs_id_l)->addProperty("feeder_id" ,
                    CUDataValue().c_long(it_tr->feeder_id))->addProperty("combined_id" ,
                    CUDataValue().c_long(it_tr->combined_id));
        }
    }

    int
    CPowerTopoAlg::addModel(const CPowerDevice* devs)
    {
        //add breaker
        addBreakerInfo(devs);
        //add discr
        addDiscrInfo(devs);
        //add gddiscr
        addGDDiscrInfo(devs);
        //add acline
        addAclnInfo(devs);
        //todo add tr
        //todo add bus
        //todo add src
        //todo add prc
        //todo add term
        //add dms cb
        addDmsCbInfo(devs);
        //add dms discr
        addDmsDiscrInfo(devs);
        //add dms gddiscr
        addDmsGDDiscrInfo(devs);
        //add dms section
        addDmsSectionInfo(devs);
        //add dms ld
        addDmsLoadInfo(devs);
        //add dms bs
        addDmsBsInfo(devs);
        //add dms tr
        addDmsTrInfo(devs);
    }
    int
    CPowerTopoAlg::delModel(const CPowerDevice* devs)
    {

    }

    CEdge*
    CPowerTopoAlg::addBreaker(const SCA_ID id, const SCA_ID ind, const SCA_ID jnd)
    {
        if (!isEmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        CEdge* eptr = m_graph->createVertex(ind)->createEdgeTo(id , jnd);
        eptr->addProperty("is_breaker" , CUDataValue().c_uchar(1));
        return eptr;
    }
    CEdge*
    CPowerTopoAlg::addDisconnector(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isEmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        CEdge* eptr = m_graph->createVertex(ind)->createEdgeTo(id , jnd);
        eptr->addProperty("is_cb" , CUDataValue().c_uchar(1));
        return eptr;
    }
    CVertex*
    CPowerTopoAlg::addGDDisconnector(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isEmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("ground_id" , CUDataValue().c_long(id))->addProperty("is_grounded" ,
                CUDataValue().c_uchar(0));
        return vptr;
    }
    CEdge*
    CPowerTopoAlg::addAcline(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isEmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        return m_graph->createVertex(ind)->createEdgeTo(id , jnd);
    }
    CEdge*
    CPowerTopoAlg::addTransformer(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isEmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        return m_graph->createVertex(ind)->createEdgeTo(id , jnd);
    }
    CVertex*
    CPowerTopoAlg::addBusbarsection(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isEmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("bs_id" , CUDataValue().c_long(id));
        return vptr;
    }
    CVertex*
    CPowerTopoAlg::addGeneratingUnit(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isEmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("gn_id" , CUDataValue().c_long(id));
        vptr->addProperty("is_gn" , CUDataValue().c_uchar(1));
        return vptr;
    }
    CVertex*
    CPowerTopoAlg::addEnergyConsumer(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isEmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("ld_id" , CUDataValue().c_long(id));
        vptr->addProperty("is_ld" , CUDataValue().c_uchar(1));
        return vptr;
    }
    CVertex*
    CPowerTopoAlg::addCompensatorP(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isEmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("prc_id" , CUDataValue().c_long(id));
        vptr->addProperty("is_ld" , CUDataValue().c_uchar(1));
        return vptr;
    }
    CEdge*
    CPowerTopoAlg::addCompensatorS(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isEmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        CEdge* eptr = m_graph->createVertex(ind)->createEdgeTo(id , jnd);
        eptr->addProperty("is_scp" , CUDataValue().c_uchar(1));
        return eptr;
    }
    CVertex*
    CPowerTopoAlg::addSingleTerm(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isEmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("term_id" , CUDataValue().c_long(id));
        return vptr;
    }
    //DMS
    CEdge*
    CPowerTopoAlg::addDmsCb(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isDmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        return m_graph->createVertex(ind)->createEdgeTo(id , jnd);
    }
    CEdge*
    CPowerTopoAlg::addDmsSection(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isDmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        return m_graph->createVertex(ind)->createEdgeTo(id , jnd);
    }
    CVertex*
    CPowerTopoAlg::addDmsLoad(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isDmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("ld_id" , CUDataValue().c_long(id));
        vptr->addProperty("is_dms_ld" , CUDataValue().c_uchar(1));
        return vptr;
    }
    CEdge*
    CPowerTopoAlg::addDmsTr(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isDmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        return m_graph->createVertex(ind)->createEdgeTo(id , jnd);
    }
    CVertex*
    CPowerTopoAlg::addDmsBs(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isDmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("bs_id" , CUDataValue().c_long(id));
        vptr->addProperty("is_dms_bs" , CUDataValue().c_uchar(1));
        return vptr;
    }
    CEdge*
    CPowerTopoAlg::addDmsDiscr(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {
        if (!isDmsNdValid(ind , jnd))
            return NULL;
        m_graph->createVertex(jnd);
        return m_graph->createVertex(ind)->createEdgeTo(id , jnd);
    }
    CVertex*
    CPowerTopoAlg::addDmsGDDiscr(const SCA_ID id, const SCA_ND_ID nd)
    {
        if (!isDmsNdValid(nd))
            return NULL;
        CVertex* vptr = m_graph->createVertex(nd);
        vptr->addProperty("ground_id" , CUDataValue().c_long(id))->addProperty("is_grounded" ,
                CUDataValue().c_uchar(0));
        return vptr;
    }
    CEdge*
    CPowerTopoAlg::addJumper(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {

    }
    CEdge*
    CPowerTopoAlg::addLinker(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd)
    {

    }

} /* namespace SCADA_ALG */
