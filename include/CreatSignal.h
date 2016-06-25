// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// --------------------------------------------------------------------------------------
// About  : Functions to generate test signals
// Date   : 2016-01-19 10:34:23
// Author : Xiang,Zuo
// Email  : xianglinks@gmail.com
// --------------------------------------------------------------------------------------

#ifndef CREATSIGNAL_H
#define CREATSIGNAL_H

#include <KL1pInclude.h>

namespace kl1p
{
void CreateGaussianSignal(klab::UInt32 size, klab::UInt32 sparsity, klab::DoubleReal mean, klab::DoubleReal sigma, arma::Col<klab::DoubleReal>& out);
}

// ---------------------------------------------------------------------------------------------------- //

/**
 * @brief Create Gaussian Signal with mean, sigmal and sparsity
 *
 * @param size
 * @param sparsity
 * @param mean
 * @param sigma
 * @param out
 */
void kl1p::CreateGaussianSignal(klab::UInt32 size, klab::UInt32 sparsity, klab::DoubleReal mean, klab::DoubleReal sigma, arma::Col<klab::DoubleReal>& out)
{
	out.set_size(size);
	out.fill(0.0);

	std::vector<klab::TArrayElement<klab::DoubleReal> > indices;
    for(klab::UInt32 i=0; i<size; ++i)
        indices.push_back(klab::TArrayElement<klab::DoubleReal>(i, klab::KRandom::Instance().generateDoubleReal(0.0, 1.0)));

    std::partial_sort(indices.begin(), indices.begin()+klab::Min(size, sparsity), indices.end(), std::greater<klab::TArrayElement<klab::DoubleReal> >());

	for(klab::UInt32 i=0; i<sparsity; ++i)
	{
		klab::DoubleReal u1 = klab::KRandom::Instance().generateDoubleReal(0.0, 1.0);
		klab::DoubleReal u2 = klab::KRandom::Instance().generateDoubleReal(0.0, 1.0);

		klab::DoubleReal sign = klab::KRandom::Instance().generateBool() ? -1.0 : 1.0;
		out[indices[i].i()] = sign * ((klab::Sqrt(-2.0*klab::Log(u1)) * klab::Cos(2.0*klab::PI*u2))*sigma + mean);
	}
}

// ---------------------------------------------------------------------------------------------------- //

#endif /* CREATSIGNAL_H */
