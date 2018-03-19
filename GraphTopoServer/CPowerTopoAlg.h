/*
 * CPowerTopoAlg.h
 *
 *  Created on: 2016��10��13��
 *      Author: Administrator
 */

#ifndef CPOWERTOPOALG_H_
#define CPOWERTOPOALG_H_

#include "CScadaAlg.h"

namespace SCADA_ALG
{
    class CTopoAlg;
    class CPowerDevice;
    class SCADA_ALG_API CPowerTopoAlg : public CScadaAlg
    {
    public:
        enum {ND_NO_LIMIT = 0,DMS_ND_NO_LIMIT = -1};
        CPowerTopoAlg();
        virtual ~CPowerTopoAlg();

        //void refreshModel(const MODE_TYPE type = DEMS);
        int addModel(const CPowerDevice* devs);//��ͼ�м���ģ��
        int delModel(const CPowerDevice* devs);//��ͼ��ɾ��ģ��

        int refreshMode(const vector<SCA_ID>& cb);//���¿����豸��ʽ��ͨ������CPowerDevice�ӿ�ʵ��
        int refreshMode();//�������п����豸��ʽ

        void islandAnalysis(map<int,vector<CEdge*> >&);//����������
        void busAnalysis();//�߼�ĸ�߷���
        CVertex* searchPower(const CVertex* vertex);//��Դ�����
        vector<CVertex*> searchSupplyRange(const CVertex* vertex);//���緶Χ����

    private:
        //void loadEmsModel();
        //void loadDmsModel();
        //EMS interface
        CEdge* addBreaker(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd);
        CEdge* addDisconnector(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd);
        CVertex* addGDDisconnector(const SCA_ID id, const SCA_ND_ID nd);
        CEdge* addAcline(const SCA_ID id,const SCA_ND_ID ind,const SCA_ND_ID jnd);
        CEdge* addTransformer(const SCA_ID id,const SCA_ND_ID ind,const SCA_ND_ID jnd);
        CVertex* addBusbarsection(const SCA_ID id, const SCA_ND_ID nd);
        CVertex* addGeneratingUnit(const SCA_ID id, const SCA_ND_ID nd);
        CVertex* addEnergyConsumer(const SCA_ID id, const SCA_ND_ID nd);
        CVertex* addCompensatorP(const SCA_ID id, const SCA_ND_ID nd);
        CEdge* addCompensatorS(const SCA_ID id, const SCA_ND_ID ind, const SCA_ND_ID jnd);
        CVertex* addSingleTerm(const SCA_ID id, const SCA_ND_ID nd);

        //DMS interface
        CEdge* addDmsCb(const SCA_ID id, const SCA_ND_ID ind,const SCA_ND_ID jnd);
        CEdge* addDmsSection(const SCA_ID id,const SCA_ND_ID ind,const SCA_ND_ID jnd);
        CVertex* addDmsLoad(const SCA_ID id, const SCA_ND_ID nd);
        CEdge* addDmsTr(const SCA_ID id,const SCA_ND_ID ind,const SCA_ND_ID jnd);
        CVertex* addDmsBs(const SCA_ID id, const SCA_ND_ID nd);
        CEdge* addDmsDiscr(const SCA_ID id,const SCA_ND_ID ind,const SCA_ND_ID jnd);
        CVertex* addDmsGDDiscr(const SCA_ID id,const SCA_ND_ID nd);
        CEdge* addJumper(const SCA_ID id,const SCA_ND_ID ind,const SCA_ND_ID jnd);
        CEdge* addLinker(const SCA_ID id,const SCA_ND_ID ind,const SCA_ND_ID jnd);

        bool isEmsNdValid(const SCA_ND_ID nd)
        {
            return (nd > ND_NO_LIMIT );
        }
        bool isEmsNdValid(const SCA_ND_ID nd1,const SCA_ND_ID nd2)
        {
            return (isEmsNdValid(nd1)&&isEmsNdValid(nd2));
        }
        bool isEmsNdValid(const SCA_ND_ID nd1,const SCA_ND_ID nd2,const SCA_ND_ID nd3)
        {
            return (isEmsNdValid(nd1)&&isEmsNdValid(nd2)&&isEmsNdValid(nd3));
        }

        bool isDmsNdValid(const SCA_ND_ID nd)
        {
            return (nd < DMS_ND_NO_LIMIT );
        }
        bool isDmsNdValid(const SCA_ND_ID nd1,const SCA_ND_ID nd2)
        {
            return (isDmsNdValid(nd1)&&isDmsNdValid(nd2));
        }
        bool isDmsNdValid(const SCA_ND_ID nd1,const SCA_ND_ID nd2,const SCA_ND_ID nd3)
        {
            return (isDmsNdValid(nd1)&&isDmsNdValid(nd2)&&isDmsNdValid(nd3));
        }
        bool isDmsNdValid(const SCA_ND_ID nd1,const SCA_ND_ID nd2,const SCA_ND_ID nd3,const SCA_ND_ID nd4)
        {
            return (isDmsNdValid(nd1)&&isDmsNdValid(nd2)&&isDmsNdValid(nd3)&&isDmsNdValid(nd4));
        }

        void addAclnInfo(const CPowerDevice* devs);
        void addGDDiscrInfo(const CPowerDevice* devs);
        void addDiscrInfo(const CPowerDevice* devs);
        void addBreakerInfo(const CPowerDevice* devs);
        void addDmsCbInfo(const CPowerDevice* devs);
        void addDmsDiscrInfo(const CPowerDevice* devs);
        void addDmsGDDiscrInfo(const CPowerDevice* devs);
        void addDmsSectionInfo(const CPowerDevice* devs);
        void addDmsLoadInfo(const CPowerDevice* devs);
        void addDmsBsInfo(const CPowerDevice* devs);
        void addDmsTrInfo(const CPowerDevice* devs);

    private:
        //CPowerDevice *m_emsDevices;
        //CPowerDevice *m_dmsDevices;

        //MODE_TYPE m_modeType;//����������������һ��

        CTopoAlg* m_topoAlg;
    };

} /* namespace SCADA_ALG */
#endif /* CPOWERTOPOALG_H_ */
