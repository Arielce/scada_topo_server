/*
 * CPowerDevice.cpp
 *
 *  Created on: 2016年10月18日
 *      Author: Administrator
 */

#include "CPowerDevice.h"
#include "GetAllRecFromRealdb.h"//从实时库取模型
//#include "GetModelFromRdb.h"//从关系库取模型

#include "db_def/db_define.h"

namespace SCADA_ALG
{

    CPowerDevice::CPowerDevice()
    {
        // TODO Auto-generated constructor stub

    }

    CPowerDevice::~CPowerDevice()
    {
        // TODO Auto-generated destructor stub
    }

    CPowerDevice::CPowerDevice(const MODE_TYPE type)
    {
        m_modeType = type;
    }
    void CPowerDevice::refreshTabModel(const int tab_no)
    {
        switch(tab_no)
        {
        case BREAKER_NO:
        {
            //m_vecBrk.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_BRK_COLUMN_NAME, m_vecBrk);
            break;
        }
        case DISCONNECTOR_NO:
        {
            //m_vecDiscr.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_DISCR_COLUMN_NAME, m_vecDiscr);
            break;
        }
        case GROUNDDISCONNECTOR_NO:
        {
            //m_vecGDDiscr.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_GDDISCR_COLUMN_NAME, m_vecGDDiscr);
            break;
        }
        case GENERATINGUNIT_NO:
        {
            //m_vecGn.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_GN_COLUMN_NAME, m_vecGn);
            break;
        }
        case ENERGYCONSUMER_NO:
        {
            //m_vecLd.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_LD_COLUMN_NAME, m_vecLd);
            break;
        }
        case ACLINESEGMENT_NO:
        {
            //m_vecAcln.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_ACLN_COLUMN_NAME, m_vecAcln);
            break;
        }
        case ACLINEEND_NO:
        {
            //m_vecAclnDot.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_ACLN_DOT_COLUMN_NAME, m_vecAclnDot);
            break;
        }
        case POWERTRANSFORMER_NO:
        {
            //m_vecTr.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_TR_COLUMN_NAME, m_vecTr);
            break;
        }
        case TRANSFORMERWINDING_NO:
        {
            //m_vecTrwd.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_TRWD_COLUMN_NAME, m_vecTrwd);
            break;
        }
        case COMPENSATOR_S_NO:
        {
            //m_vecSrc.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_SRC_COLUMN_NAME, m_vecSrc);
            break;
        }
        case COMPENSATOR_P_NO:
        {
            //m_vecPrc.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_PRC_COLUMN_NAME, m_vecPrc);
            break;
        }
        case SINGLETERM_NO:
        {
            //m_vecTerm.clear();
            GetAllRec<ODB::CTableOp>(m_emsAppNo, tab_no, EMS_TERM_COLUMN_NAME, m_vecTerm);
            break;
        }
        //dms
        case DMS_CB_DEVICE_NO:
        {
            //m_vecDmsCb.clear();
            GetAllRec<ODB::CTableOp>(m_dmsAppNo, tab_no, DMS_CB_COLUMN_NAME, m_vecDmsCb);
            break;
        }
        case DMS_DISCONNECTOR_DEVICE_NO:
        {
            //m_vecDmsDiscr.clear();
            GetAllRec<ODB::CTableOp>(m_dmsAppNo, tab_no, DMS_DISCR_COLUMN_NAME, m_vecDmsDiscr);
            break;
        }
        case DMS_GROUND_DISCONNECTOR_NO:
        {
            //m_vecDmsGDDiscr.clear();
            GetAllRec<ODB::CTableOp>(m_dmsAppNo, tab_no, DMS_GDDISCR_COLUMN_NAME, m_vecDmsGDDiscr);
            break;
        }
        case DMS_SECTION_DEVICE_NO:
        {
            //m_vecDmsSection.clear();
            GetAllRec<ODB::CTableOp>(m_dmsAppNo, tab_no, DMS_SECTION_COLUMN_NAME, m_vecDmsSection);
            break;
        }
        case DMS_LD_DEVICE_NO:
        {
            //m_vecDmsLd.clear();
            GetAllRec<ODB::CTableOp>(m_dmsAppNo, tab_no, DMS_LD_COLUMN_NAME, m_vecDmsLd);
            break;
        }
        case DMS_TR_DEVICE_NO:
        {
            //m_vecDmsCb.clear();
            GetAllRec<ODB::CTableOp>(m_dmsAppNo, tab_no, DMS_TR_COLUMN_NAME, m_vecDmsCb);
            break;
        }
        case DMS_BS_DEVICE_NO:
        {
            //m_vecDmsBs.clear();
            GetAllRec<ODB::CTableOp>(m_dmsAppNo, tab_no, DMS_BS_COLUMN_NAME, m_vecDmsBs);
            break;
        }


        }
    }

    void CPowerDevice::refreshAllModel()
    {
        clearAllModel();
        if ( m_modeType == EMS )
        {
            loadModelFromEms();
        }
        else if ( m_modeType == DMS )
        {
            loadModelFromDms();
        }
        else if ( m_modeType == DEMS )
        {
            loadModelFromEms();
            loadModelFromDms();
        }
    }
    void CPowerDevice::refreshRunMode(const SCA_ID dev_id,unsigned char &point,int &status)
    {

    }

    void CPowerDevice::clearAllModel()
    {
        m_vecBrk.clear();
        m_vecDiscr.clear();
        m_vecGDDiscr.clear();
        m_vecGn.clear();
        m_vecLd.clear();
        m_vecAcln.clear();
        m_vecAclnDot.clear();
        m_vecBs.clear();
        m_vecTr.clear();
        m_vecTrwd.clear();
        m_vecSrc.clear();
        m_vecPrc.clear();
        m_vecTerm.clear();

        m_vecDmsCb.clear();
        m_vecDmsDiscr.clear();
        m_vecDmsGDDiscr.clear();
        m_vecDmsSection.clear();
        m_vecDmsLd.clear();
        m_vecDmsTr.clear();
        m_vecDmsBs.clear();
    }
    void CPowerDevice::loadModelFromEms()
    {
        refreshTabModel(BREAKER_NO);
        refreshTabModel(DISCONNECTOR_NO);
        refreshTabModel(GROUNDDISCONNECTOR_NO);
        refreshTabModel(BUSBARSECTION_NO);
        refreshTabModel(GENERATINGUNIT_NO);
        refreshTabModel(ENERGYCONSUMER_NO);
        refreshTabModel(ACLINESEGMENT_NO);
        refreshTabModel(ACLINEEND_NO);
        refreshTabModel(POWERTRANSFORMER_NO);
        refreshTabModel(TRANSFORMERWINDING_NO);
        refreshTabModel(COMPENSATOR_P_NO);
        refreshTabModel(COMPENSATOR_S_NO);
        refreshTabModel(SINGLETERM_NO);

        refreshAclnToDot();
        refreshTrToTrwd();
    }
    void CPowerDevice::loadModelFromDms()
    {
        refreshTabModel(DMS_CB_DEVICE_NO);
        refreshTabModel(DMS_SECTION_DEVICE_NO);
        refreshTabModel(DMS_LD_DEVICE_NO);
        refreshTabModel(DMS_TR_DEVICE_NO);
        refreshTabModel(DMS_BS_DEVICE_NO);
        refreshTabModel(DMS_DISCONNECTOR_DEVICE_NO);
        refreshTabModel(DMS_GROUND_DISCONNECTOR_NO);

    }
    void CPowerDevice::refreshAclnToDot()
    {
        m_mapAclnToDot.clear();
        EmsAclnDotIterator dot_iter;
        for (dot_iter = emsAclnDotBegin();dot_iter != emsAclnDotEnd(); dot_iter++)
        {
            m_mapAclnToDot[ dot_iter->acln_id ].insert(dot_iter);
        }
    }
    void CPowerDevice::refreshTrToTrwd()
    {
        m_mapTrToTrwd.clear();
        EmsTrwdIterator trwd_iter;
        for (trwd_iter = emsTrwdBegin();trwd_iter != emsTrwdEnd(); trwd_iter++)
        {
            m_mapTrToTrwd[ trwd_iter->tr_id ].insert(trwd_iter);
        }

    }
} /* namespace SCADA_ALG */
