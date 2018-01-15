/*
 * CCommunityDetectAlg.h
 *
 *  Created on: 2016��9��29��
 *      Author: Administrator
 */

#ifndef CCOMMUNITYDETECTALG_H_
#define CCOMMUNITYDETECTALG_H_

#include "CScadaAlg.h"
#include "CGraph.h"

namespace SCADA_ALG
{

    class SCADA_ALG_API CCommunityDetectAlg : public CScadaAlg
    {
    public:
        CCommunityDetectAlg();
        virtual ~CCommunityDetectAlg();
        /*
         * ���ܣ�����Qֵ,AijΪij�ڵ�֮�����ߵ�Ȩ�أ�ki��ʾ��i��Ȩ�أ�i�Ķȣ���m��ʾ��������(ci,cj)��ʾ�ڵ�ij�Ƿ�����ͬһ����
         * ���룺��
         * �����Qֵ
         * ���أ���
         */
        float calQValue();//Q=1/2m ��(i,j)[A(i,j)-(ki kj)/2m]*��(ci,cj)
        /*
        * ���ܣ���������֮��ıߵ�Ȩ��
        * ���룺����ָ��
        * �����Ȩ��
        * ���أ���
        */
        float calWeight(  CVertex* const sv, CVertex* const ev );
        /*
         * ���ܣ����ڵ�v��������community_no
         * ���룺Ŀ��ڵ�v�����ź�community_no
         * �������
         * ���أ���
         */
        void mergeToCommunity(CVertex* v,const int community_no);
        /*
         * ���ܣ��жϽڵ��Ƿ�����ͬһ����
         * ���룺���ڵ�ָ��
         * �������/��
         * ���أ���
         */
        bool isSameCommunity(CVertex* const sv,CVertex* const ev);
    };

} /* namespace SCADA_ALG */
#endif /* CCOMMUNITYDETECTALG_H_ */
