/*
 * Compilation Copyright (c) 1995-2019 by Wei Dai.  All rights reserved.
 *	This copyright applies only to this software distribution package
 *	as a compilation, and does not imply a copyright on any particular
 *	file in the package.
 * 
 *	Boost Software License - Version 1.0 - August 17th, 2003
 *
 *	Permission is hereby granted, free of charge, to any person or organization
 *	obtaining a copy of the software and accompanying documentation covered by
 *	this license (the "Software") to use, reproduce, display, distribute,
 *	execute, and transmit the Software, and to prepare derivative works of the
 *	Software, and to permit third-parties to whom the Software is furnished to
 *	do so, all subject to the following:
 * 
 *	The copyright notices in the Software and this entire statement, including
 *	the above license grant, this restriction and the following disclaimer,
 *	must be included in all copies of the Software, in whole or in part, and
 *	all derivative works of the Software, unless such copies or derivative
 *	works are solely in the form of machine-executable object code generated by
 *	a source language processor.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 *	SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 *	FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 *	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *	DEALINGS IN THE SOFTWARE.
 */

// rabbit.h - written and placed in the public domain by Jeffrey Walton
//            based on public domain code by Martin Boesgaard, Mette Vesterager,
//            Thomas Pedersen, Jesper Christiansen and Ove Scavenius.
//
//            The reference materials and source files are available at
//            The eSTREAM Project, http://www.ecrypt.eu.org/stream/e2-rabbit.html.

/// \file rabbit.h
/// \brief Classes for Rabbit stream cipher
/// \sa <A HREF="http://www.ecrypt.eu.org/stream/e2-rabbit.html">The
///   eSTREAM Project | Rabbit</A> and
///   <A HREF="https://www.cryptopp.com/wiki/Rabbit">Crypto++ Wiki | Rabbit</A>.
/// \since Crypto++ 8.0

#ifndef CRYPTOPP_RABBIT_H
#define CRYPTOPP_RABBIT_H

#include "strciphr.h"
#include "secblock.h"

// The library does not have a way to describe an optional IV. Rabbit takes
// an optional IV so two classes are offered to bridge the gap. One provides
// Rabbit without an IV and the second provides Rabbit with an IV.

NAMESPACE_BEGIN(CryptoPP)

/// \brief Rabbit stream cipher information
/// \since Crypto++ 8.0
struct RabbitInfo : public FixedKeyLength<16, SimpleKeyingInterface::NOT_RESYNCHRONIZABLE>
{
	CRYPTOPP_STATIC_CONSTEXPR const char* StaticAlgorithmName() { return "Rabbit"; }
};

/// \brief Rabbit stream cipher information
/// \since Crypto++ 8.0
struct RabbitWithIVInfo : public FixedKeyLength<16, SimpleKeyingInterface::UNIQUE_IV, 8>
{
	CRYPTOPP_STATIC_CONSTEXPR const char* StaticAlgorithmName() { return "RabbitWithIV"; }
};

/// \brief Rabbit stream cipher implementation
/// \since Crypto++ 8.0
class RabbitPolicy : public AdditiveCipherConcretePolicy<word32, 4>, public RabbitInfo
{
protected:
	void CipherSetKey(const NameValuePairs &params, const byte *key, size_t length);
	void OperateKeystream(KeystreamOperation operation, byte *output, const byte *input, size_t iterationCount);
	bool CanOperateKeystream() const { return true; }
	bool CipherIsRandomAccess() const { return false; }

private:
	// Master and working states
	FixedSizeSecBlock<word32, 8> m_mx, m_mc, m_wx, m_wc;
	// Workspace
	FixedSizeSecBlock<word32, 12> m_t;
	word32 m_mcy, m_wcy;  // carry
};

/// \brief Rabbit stream cipher implementation
/// \since Crypto++ 8.0
class RabbitWithIVPolicy : public AdditiveCipherConcretePolicy<word32, 4>, public RabbitWithIVInfo
{
protected:
	void CipherSetKey(const NameValuePairs &params, const byte *key, size_t length);
	void OperateKeystream(KeystreamOperation operation, byte *output, const byte *input, size_t iterationCount);
	void CipherResynchronize(byte *keystreamBuffer, const byte *iv, size_t length);
	bool CanOperateKeystream() const { return true; }
	bool CipherIsRandomAccess() const { return false; }

private:
	// Master and working states
	FixedSizeSecBlock<word32, 8> m_mx, m_mc, m_wx, m_wc;
	// Workspace
	FixedSizeSecBlock<word32, 12> m_t;
	word32 m_mcy, m_wcy;  // carry
};

/// \brief Rabbit stream cipher
/// \details Rabbit is a stream cipher developed by Martin Boesgaard, Mette Vesterager,
///   Thomas Pedersen, Jesper Christiansen and Ove Scavenius. Rabbit is one of the final four
///   Profile 1 (software) ciphers selected for the eSTREAM portfolio.
/// \details Crypto++ provides Rabbit and RabbitWithIV classes. Two classes are necessary
///   because the library lacks the means to describe and manage optional IVs.
/// \sa RabbitWithIV, <A HREF="http://www.ecrypt.eu.org/stream/e2-rabbit.html">The
///   eSTREAM Project | Rabbit</A> and
///   <A HREF="https://www.cryptopp.com/wiki/Rabbit">Crypto++ Wiki | Rabbit</A>.
/// \since Crypto++ 8.0
struct Rabbit : public RabbitInfo, public SymmetricCipherDocumentation
{
	typedef SymmetricCipherFinal<ConcretePolicyHolder<RabbitPolicy, AdditiveCipherTemplate<> >, RabbitInfo> Encryption;
	typedef Encryption Decryption;
};

/// \brief Rabbit stream cipher
/// \details Rabbit is a stream cipher developed by Martin Boesgaard, Mette Vesterager,
///   Thomas Pedersen, Jesper Christiansen and Ove Scavenius. Rabbit is one of the final four
///   Profile 1 (software) ciphers selected for the eSTREAM portfolio.
/// \details Crypto++ provides Rabbit and RabbitWithIV classes. Two classes are necessary
///   because the library lacks the means to describe and manage optional IVs.
/// \sa Rabbit, <A HREF="http://www.ecrypt.eu.org/stream/e2-rabbit.html">The
///   eSTREAM Project | Rabbit</A> and
///   <A HREF="https://www.cryptopp.com/wiki/Rabbit">Crypto++ Wiki | Rabbit</A>.
/// \since Crypto++ 8.0
struct RabbitWithIV : public RabbitWithIVInfo, public SymmetricCipherDocumentation
{
	typedef SymmetricCipherFinal<ConcretePolicyHolder<RabbitWithIVPolicy, AdditiveCipherTemplate<> >, RabbitWithIVInfo> Encryption;
	typedef Encryption Decryption;
};

NAMESPACE_END

#endif  // CRYPTOPP_RABBIT_H
