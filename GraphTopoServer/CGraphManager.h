/*
 * CGraphManager.h
 *
 *  Created on: 2018年2月7日
 *      Author: Ge.Wenlin
 */

#ifndef CGRAPHMANAGER_H_
#define CGRAPHMANAGER_H_

namespace SCADA_ALG
{
class CModelMapper;
class CModelContainer;
/*图管理类，为单例
 * 负责调用动态库中的工具进行模型加载、变更、切分、并行拓扑分析、电气岛融合等主要工作
 * 是服务程序的核心类，为服务类提供可用的拓扑模型*/
class CGraphManager
{
private:
	CGraphManager();
public:
	CGraphManager* inst();
	virtual ~CGraphManager();

private:
	CModelMapper *m_modelMapper;//模型分配器
	CModelContainer *m_modelContainer;//模型容器
};

} /* namespace SCADA_ALG */

#endif /* CGRAPHMANAGER_H_ */
