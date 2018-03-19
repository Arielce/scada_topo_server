/*
 * CCommunityDetectAlg.h
 *
 *  Created on: 2016年9月29日
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
         * 功能：计算Q值,Aij为ij节点之间连边的权重，ki表示点i的权重（i的度），m表示边数，δ(ci,cj)表示节点ij是否属于同一社团
         * 输入：无
         * 输出：Q值
         * 返回：无
         */
        float calQValue();//Q=1/2m ∑(i,j)[A(i,j)-(ki kj)/2m]*δ(ci,cj)
        /*
        * 功能：计算两点之间的边的权重
        * 输入：两点指针
        * 输出：权重
        * 返回：无
        */
        float calWeight(  CVertex* const sv, CVertex* const ev );
        /*
         * 功能：将节点v划入社团community_no
         * 输入：目标节点v，社团号community_no
         * 输出：无
         * 返回：无
         */
        void mergeToCommunity(CVertex* v,const int community_no);
        /*
         * 功能：判断节点是否属于同一社团
         * 输入：两节点指针
         * 输出：是/否
         * 返回：无
         */
        bool isSameCommunity(CVertex* const sv,CVertex* const ev);
    };

} /* namespace SCADA_ALG */
#endif /* CCOMMUNITYDETECTALG_H_ */
