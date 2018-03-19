/*
 * CPowerDevice.h
 *
 *  Created on: 2016年10月18日
 *      Author: Administrator
 */

#ifndef CPOWERDEVICE_H_
#define CPOWERDEVICE_H_

#include <string>
#include <set>
#include "CGraph.h"


using namespace std;

namespace SCADA_ALG
{
    struct TId
    {
        SCA_ID id;
        TId():id(0)
        {
        }
    };
    static const string ID_COLUMN_NAME("id ");

    struct TStId
    {
        SCA_ID st_id;
        TStId():st_id(0)
        {
        }
    };
    static const string ST_ID_COLUMN_NAME("st_id ");

    struct TOneNd
    {
        SCA_ND_ID nd;
        TOneNd():nd(-1)
        {
        }
    };
    static const string ONE_ND_COLUMN_NAME("nd ");

    struct TTwoNd
    {
        SCA_ND_ID ind;
        SCA_ND_ID jnd;
        TTwoNd():ind(-1),jnd(-1)
        {
        }
    };
    static const string TWO_ND_COLUMN_NAME("ind,jnd ");

    struct TEmsBrk : public TId,public TStId,public TTwoNd
    {
    };
    static const string EMS_BRK_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+TWO_ND_COLUMN_NAME);

    struct TEmsDiscr : public TId,public TStId,public TTwoNd
    {
    };
    static const string EMS_DISCR_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+TWO_ND_COLUMN_NAME);

    struct TEmsGDDiscr : public TId,public TStId,public TOneNd
    {
    };
    static const string EMS_GDDISCR_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME);

    struct TEmsGn : public TId,public TStId,public TOneNd
    {

    };
    static const string EMS_GN_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME);

    struct TEmsLd : public TId,public TStId,public TOneNd
    {

    };
    static const string EMS_LD_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME);

    struct TEmsAcln : public TId
    {
        int eq_fg;
        SCA_ID tln_id;//所属线路
        TEmsAcln():eq_fg(-1),tln_id(-1)
        {
        }
    };
    static const string EMS_ACLN_COLUMN_NAME(ID_COLUMN_NAME+"eq_flag acline_id ");

    struct TEmsAclnDot : public TId,public TStId,public TOneNd
    {
        SCA_ID acln_id;
    };
    static const string EMS_ACLN_DOT_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME+"aclnseg_id ");

    struct TEmsTr : public TId
    {
        unsigned char trty;
        unsigned char term_fg;
    };
    static const string EMS_TR_COLUMN_NAME(ID_COLUMN_NAME+"wind_type term ");

    struct TEmsTrwd : public TId,public TStId, public TOneNd
    {
        SCA_ID tr_id;
        float tap_pos;
        int tap_status;
        SCA_ND_ID nd0;
        unsigned char wind_type;
        SCA_ID vlty_id;
    };
    static const string EMS_TRWD_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME+"tr_id tap tap_qual knd wind_type bv_id ");

    struct TEmsBs : public TId,public TStId,public TOneNd
    {
        SCA_ID vlty_id;
        float vmax;
        float vmin;
        float v_value;
        int v_bdfg;
    };
    static const string EMS_BS_COLUMN_NAME(ID_COLUMN_NAME+ST_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME+"bv_id vmax vmin v v_qual ");

    struct TEmsSRc : public TId, public TStId,public TTwoNd
    {
        long vlty_id;
    };
    static const string EMS_SRC_COLUMN_NAME(ID_COLUMN_NAME + ST_ID_COLUMN_NAME+ TWO_ND_COLUMN_NAME + "bv_id ");
    struct TEmsPRc : public TId, public TStId,public TOneNd
    {
        long vlty_id;
    };
    static const string EMS_PRC_COLUMN_NAME(ID_COLUMN_NAME + ST_ID_COLUMN_NAME + ONE_ND_COLUMN_NAME + "bv_id ");

    struct TEmsTerm : public TId, public TStId,public TOneNd
    {
    };
    static const string EMS_TERM_COLUMN_NAME(ID_COLUMN_NAME+ ST_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME);

    //dms
    struct TFeederId
    {
        SCA_ID feeder_id;
    };
    static const string DMS_FEEDER_ID_COLUMN_NAME("feeder_id ");

    struct TCombinedId
    {
        SCA_ID combined_id;
    };
    static const string DMS_COMBINED_ID_COLUMN_NAME("combined_id ");

    struct TDmsCb : public TId,public TFeederId,public TCombinedId,public TTwoNd
    {
    };
    static const string DMS_CB_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+DMS_COMBINED_ID_COLUMN_NAME+TWO_ND_COLUMN_NAME);

    struct TDmsDiscr : public TId,public TFeederId,public TCombinedId,public TTwoNd
    {
    };
    static const string DMS_DISCR_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+DMS_COMBINED_ID_COLUMN_NAME+TWO_ND_COLUMN_NAME);

    struct TDmsGDDiscr : public TId,public TFeederId,public TCombinedId,public TOneNd
    {
    };
    static const string DMS_GDDISCR_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+DMS_COMBINED_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME);

    struct TDmsSection : public TId,public TFeederId,public TCombinedId,public TTwoNd
    {
    };
    static const string DMS_SECTION_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+DMS_COMBINED_ID_COLUMN_NAME+TWO_ND_COLUMN_NAME);

    struct TDmsLd : public TId,public TFeederId,public TCombinedId
    {
        SCA_ND_ID nd_no;
        SCA_ND_ID nd2_no;
        SCA_ND_ID nd3_no;
        SCA_ND_ID nd4_no;
    };
    static const string DMS_LD_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+"nd_no nd2_no nd3_no nd4_no ");

    struct TDmsTr : public TId,public TFeederId,public TCombinedId
    {
        SCA_ND_ID bs_id_h;
        SCA_ND_ID bs_id_l;
    };
    static const string DMS_TR_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+"bs_id_h bs_id_l ");

    struct TDmsBs : public TId,public TFeederId,public TCombinedId,public TOneNd
    {

    };
    static const string DMS_BS_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+ONE_ND_COLUMN_NAME);

    struct TDmsRc : public TId,public TFeederId,public TCombinedId
    {
        SCA_ND_ID nd1_no;
        SCA_ND_ID nd2_no;
        SCA_ND_ID nd3_no;
    };
    static const string DMS_RC_COLUMN_NAME(ID_COLUMN_NAME+DMS_FEEDER_ID_COLUMN_NAME+"nd1_no nd2_no nd3_no ");

    class SCADA_ALG_API CPowerDevice
    {
    public:
        enum MODE_TYPE{EMS,DMS,DEMS};//主网、配网、主配一体
        CPowerDevice();
        CPowerDevice(const MODE_TYPE type = DEMS);
        virtual ~CPowerDevice();

        void refreshAllModel();
        void refreshTabModel(const int tab_no);
        void refreshRunMode(const SCA_ID dev_id,unsigned char &point,int &status);

        typedef vector<TEmsBrk>::const_iterator EmsBrkIterator;
        EmsBrkIterator emsBrkBegin() const {return m_vecBrk.begin();}
        EmsBrkIterator emsBrkEnd() const {return m_vecBrk.end();}
        int emsBrkNumber() const {return m_vecBrk.size();}
        const TEmsBrk& emsBrkItem(const int sub){return m_vecBrk[sub];}

        typedef vector<TEmsDiscr>::const_iterator EmsDiscrIterator;
        EmsDiscrIterator emsDiscrBegin() const {return m_vecDiscr.begin();}
        EmsDiscrIterator emsDiscrEnd() const {return m_vecDiscr.end();}
        int emsDiscrNumber() const {return m_vecDiscr.size();}
        const TEmsDiscr& emsDiscrItem(const int sub){return m_vecDiscr[sub];}

        typedef vector<TEmsGDDiscr>::const_iterator EmsGDDiscrIterator;
        EmsGDDiscrIterator emsGDDiscrBegin() const {return m_vecGDDiscr.begin();}
        EmsGDDiscrIterator emsGDDiscrEnd() const {return m_vecGDDiscr.end();}
        int emsGDDiscrNumber() const {return m_vecGDDiscr.size();}
        const TEmsGDDiscr& emsGDDiscrItem(const int sub){return m_vecGDDiscr[sub];}

        typedef vector<TEmsGn>::const_iterator EmsGnIterator;
        EmsGnIterator emsGnBegin() const {return m_vecGn.begin();}
        EmsGnIterator emsGnEnd() const {return m_vecGn.end();}
        int emsGnNumber() const {return m_vecGn.size();}
        const TEmsGn& emsGnItem(const int sub){return m_vecGn[sub];}

        typedef vector<TEmsLd>::const_iterator EmsLdIterator;
        EmsLdIterator emsLdBegin() const {return m_vecLd.begin();}
        EmsLdIterator emsLdEnd() const {return m_vecLd.end();}
        int emsLdNumber() const {return m_vecLd.size();}
        const TEmsLd& emsLdItem(const int sub){return m_vecLd[sub];}

        typedef vector<TEmsAcln>::const_iterator EmsAclnIterator;
        EmsAclnIterator emsAclnBegin() const {return m_vecAcln.begin();}
        EmsAclnIterator emsAclnEnd() const {return m_vecAcln.end();}
        int emsAclnNumber() const {return m_vecAcln.size();}
        const TEmsAcln& emsAclnItem(const int sub){return m_vecAcln[sub];}

        typedef vector<TEmsAclnDot>::const_iterator EmsAclnDotIterator;
        EmsAclnDotIterator emsAclnDotBegin() const {return m_vecAclnDot.begin();}
        EmsAclnDotIterator emsAclnDotEnd() const {return m_vecAclnDot.end();}
        int emsAclnDotNumber() const {return m_vecAclnDot.size();}
        const TEmsAclnDot& emsAclnDotItem(const int sub){return m_vecAclnDot[sub];}

        typedef vector<TEmsTr>::const_iterator EmsTrIterator;
        EmsTrIterator emsTrBegin() const {return m_vecTr.begin();}
        EmsTrIterator emsTrEnd() const {return m_vecTr.end();}
        int emsTrNumber() const {return m_vecTr.size();}
        const TEmsTr& emsTrItem(const int sub){return m_vecTr[sub];}

        typedef vector<TEmsTrwd>::const_iterator EmsTrwdIterator;
        EmsTrwdIterator emsTrwdBegin() const {return m_vecTrwd.begin();}
        EmsTrwdIterator emsTrwdEnd() const {return m_vecTrwd.end();}
        int emsTrwdNumber() const {return m_vecTrwd.size();}
        const TEmsTrwd& emsTrwdItem(const int sub){return m_vecTrwd[sub];}

        typedef vector<TEmsBs>::const_iterator EmsBsIterator;
        EmsBsIterator emsBsBegin() const {return m_vecBs.begin();}
        EmsBsIterator emsBsEnd() const {return m_vecBs.end();}
        int emsBsNumber() const {return m_vecBs.size();}
        const TEmsBs& emsBsItem(const int sub){return m_vecBs[sub];}

        typedef vector<TEmsSRc>::const_iterator EmsSrcIterator;
        EmsSrcIterator emsSrcBegin() const {return m_vecSrc.begin();}
        EmsSrcIterator emsSrcEnd() const {return m_vecSrc.end();}
        int emsSrcNumber() const {return m_vecSrc.size();}
        const TEmsSRc& emsSrcItem(const int sub){return m_vecSrc[sub];}

        typedef vector<TEmsPRc>::const_iterator EmsPrcIterator;
        EmsPrcIterator emsPrcBegin() const {return m_vecPrc.begin();}
        EmsPrcIterator emsPrcEnd() const {return m_vecPrc.end();}
        int emsPrcNumber() const {return m_vecPrc.size();}
        const TEmsPRc& emsPrcItem(const int sub){return m_vecPrc[sub];}

        typedef vector<TEmsTerm>::const_iterator EmsTermIterator;
        EmsTermIterator emsTermBegin() const {return m_vecTerm.begin();}
        EmsTermIterator emsTermEnd() const {return m_vecTerm.end();}
        int emsTermNumber() const {return m_vecTerm.size();}
        const TEmsTerm& emsTermItem(const int sub){return m_vecTerm[sub];}

        typedef vector<TDmsCb>::const_iterator DmsCbIterator;
        DmsCbIterator dmsCbBegin() const {return m_vecDmsCb.begin();}
        DmsCbIterator dmsCbEnd() const {return m_vecDmsCb.end();}
        int dmsCbNumber() const {return m_vecDmsCb.size();}
        const TDmsCb& dmsCbItem(const int sub){return m_vecDmsCb[sub];}

        typedef vector<TDmsDiscr>::const_iterator DmsDiscrIterator;
        DmsDiscrIterator dmsDiscrBegin() const {return m_vecDmsDiscr.begin();}
        DmsDiscrIterator dmsDiscrEnd() const {return m_vecDmsDiscr.end();}
        int dmsDiscrNumber() const {return m_vecDmsDiscr.size();}
        const TDmsDiscr& dmsDiscrItem(const int sub){return m_vecDmsDiscr[sub];}

        typedef vector<TDmsGDDiscr>::const_iterator DmsGDDiscrIterator;
        DmsGDDiscrIterator dmsGDDiscrBegin() const {return m_vecDmsGDDiscr.begin();}
        DmsGDDiscrIterator dmsGDDiscrEnd() const {return m_vecDmsGDDiscr.end();}
        int dmsGDDiscrNumber() const {return m_vecDmsGDDiscr.size();}
        const TDmsGDDiscr& dmsGDDiscrItem(const int sub){return m_vecDmsGDDiscr[sub];}

        typedef vector<TDmsSection>::const_iterator DmsSectionIterator;
        DmsSectionIterator dmsSectionBegin() const {return m_vecDmsSection.begin();}
        DmsSectionIterator dmsSectionEnd() const {return m_vecDmsSection.end();}
        int dmsSectionNumber() const {return m_vecDmsSection.size();}
        const TDmsSection& dmsSectionItem(const int sub){return m_vecDmsSection[sub];}

        typedef vector<TDmsLd>::const_iterator DmsLdIterator;
        DmsLdIterator dmsLdBegin() const {return m_vecDmsLd.begin();}
        DmsLdIterator dmsLdEnd() const {return m_vecDmsLd.end();}
        int dmsLdNumber() const {return m_vecDmsLd.size();}
        const TDmsLd& dmsLdItem(const int sub){return m_vecDmsLd[sub];}

        typedef vector<TDmsTr>::const_iterator DmsTrIterator;
        DmsTrIterator dmsTrBegin() const {return m_vecDmsTr.begin();}
        DmsTrIterator dmsTrEnd() const {return m_vecDmsTr.end();}
        int dmsTrNumber() const {return m_vecDmsTr.size();}
        const TDmsTr& dmsTrItem(const int sub){return m_vecDmsTr[sub];}

        typedef vector<TDmsBs>::const_iterator DmsBsIterator;
        DmsBsIterator dmsBsBegin() const {return m_vecDmsBs.begin();}
        DmsBsIterator dmsBsEnd() const {return m_vecDmsBs.end();}
        int dmsBsNumber() const {return m_vecDmsBs.size();}
        const TDmsBs& dmsBsItem(const int sub){return m_vecDmsBs[sub];}

        typedef set<EmsAclnDotIterator>::const_iterator EmsAclnToDotIterator;
        const EmsAclnToDotIterator emsDotOfAclnBegin(const SCA_ID acln_id) { return m_mapAclnToDot[acln_id].begin(); }
        const EmsAclnToDotIterator emsDotOfAclnEnd(const SCA_ID acln_id) { return m_mapAclnToDot[acln_id].end(); }
        const int emsDotNumberOfAclnId(const SCA_ID acln_id){return m_mapAclnToDot[acln_id].size();}

        typedef set<EmsTrwdIterator>::const_iterator EmsTrToTrwdIterator;
        EmsTrToTrwdIterator emsTrwdOfTrBegin(const SCA_ID tr_id) { return m_mapTrToTrwd[tr_id].begin(); }
        EmsTrToTrwdIterator emsTrwdOfTrEnd(const SCA_ID tr_id) { return m_mapTrToTrwd[tr_id].end(); }
        int emsTrwdNumberOfTr(const SCA_ID tr_id){return m_mapTrToTrwd[tr_id].size();}

    private:
        void loadModelFromEms();
        void loadModelFromDms();
        void clearAllModel();
        void refreshAclnToDot();
        void refreshTrToTrwd();
    private:
        //ems
        vector<TEmsBrk> m_vecBrk;
        vector<TEmsDiscr> m_vecDiscr;
        vector<TEmsGDDiscr> m_vecGDDiscr;
        vector<TEmsGn> m_vecGn;
        vector<TEmsLd> m_vecLd;
        vector<TEmsAcln> m_vecAcln;
        vector<TEmsAclnDot> m_vecAclnDot;
        vector<TEmsTr> m_vecTr;
        vector<TEmsTrwd> m_vecTrwd;
        vector<TEmsBs> m_vecBs;
        vector<TEmsSRc> m_vecSrc;
        vector<TEmsPRc> m_vecPrc;
        vector<TEmsTerm> m_vecTerm;

        typedef map<SCA_ID,set<EmsAclnDotIterator> > EmsAclnMap;
        EmsAclnMap m_mapAclnToDot;

        typedef map<SCA_ID,set<EmsTrwdIterator> > EmsTrMap;
        EmsTrMap m_mapTrToTrwd;

        //dms
        vector<TDmsCb> m_vecDmsCb;
        vector<TDmsDiscr> m_vecDmsDiscr;
        vector<TDmsGDDiscr> m_vecDmsGDDiscr;
        vector<TDmsSection> m_vecDmsSection;
        vector<TDmsLd> m_vecDmsLd;
        vector<TDmsTr> m_vecDmsTr;
        vector<TDmsBs> m_vecDmsBs;

        MODE_TYPE m_modeType;
        bool m_isLocal;
        int m_sliceNo;
        int m_emsAppNo;
        int m_dmsAppNo;
    };

} /* namespace SCADA_ALG */
#endif /* CPOWERDEVICE_H_ */

