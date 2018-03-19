/*
 * CModelMapper.h
 *
 *  Created on: 2018年2月7日
 *      Author: Ge.Wenlin
 */

#ifndef CMODELMAPPER_H_
#define CMODELMAPPER_H_

namespace SCADA_ALG
{
/*模型切分器
 * 可将图模型根据策略进行切分，将大图切分成子图，便于并行分析
 * 切分策略由外部指定*/
class CModelMapper
{
public:
	CModelMapper();
	virtual ~CModelMapper();
};

} /* namespace SCADA_ALG */

#endif /* CMODELMAPPER_H_ */
