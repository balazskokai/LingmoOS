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

// aria.h - written and placed in the public domain by Jeffrey Walton

/// \file aria.h
/// \brief Classes for the ARIA block cipher
/// \details The Crypto++ ARIA implementation is based on the 32-bit implementation by Aaram Yun
///   from the National Security Research Institute, KOREA. Aaram Yun's implementation is based on
///   the 8-bit implementation by Jin Hong. The source files are available in ARIA.zip from the Korea
///   Internet & Security Agency website.
/// \sa <A HREF="http://tools.ietf.org/html/rfc5794">RFC 5794, A Description of the ARIA Encryption Algorithm</A>,
///   <A HREF="http://seed.kisa.or.kr/iwt/ko/bbs/EgovReferenceList.do?bbsId=BBSMSTR_000000000002">Korea
///   Internet & Security Agency homepage</A>

#ifndef CRYPTOPP_ARIA_H
#define CRYPTOPP_ARIA_H

#include "config.h"
#include "seckey.h"
#include "secblock.h"

NAMESPACE_BEGIN(CryptoPP)

/// \brief ARIA block cipher information
/// \since Crypto++ 6.0
struct ARIA_Info : public FixedBlockSize<16>, public VariableKeyLength<16, 16, 32, 8>
{
	CRYPTOPP_STATIC_CONSTEXPR const char* StaticAlgorithmName() {return "ARIA";}
};

/// \brief ARIA block cipher
/// \details The Crypto++ ARIA implementation is based on the 32-bit implementation by Aaram Yun
///   from the National Security Research Institute, KOREA. Aaram Yun's implementation is based on
///   the 8-bit implementation by Jin Hong. The source files are available in ARIA.zip from the Korea
///   Internet & Security Agency website.
/// \sa <A HREF="http://tools.ietf.org/html/rfc5794">RFC 5794, A Description of the ARIA Encryption Algorithm</A>,
///   <A HREF="http://seed.kisa.or.kr/iwt/ko/bbs/EgovReferenceList.do?bbsId=BBSMSTR_000000000002">Korea
///   Internet & Security Agency homepage</A>
/// \sa <a href="http://www.cryptopp.com/wiki/ARIA">ARIA</a>
/// \since Crypto++ 6.0
class ARIA : public ARIA_Info, public BlockCipherDocumentation
{
public:
	class CRYPTOPP_NO_VTABLE Base : public BlockCipherImpl<ARIA_Info>
	{
	public:
		Base() : m_rounds(0) {}

	protected:
		void UncheckedSetKey(const byte *key, unsigned int keylen, const NameValuePairs &params);
		void ProcessAndXorBlock(const byte *inBlock, const byte *xorBlock, byte *outBlock) const;

	private:
		// Reference implementation allocates a table of 17 round keys.
		typedef SecBlock<byte, AllocatorWithCleanup<byte, true> >     AlignedByteBlock;
		typedef SecBlock<word32, AllocatorWithCleanup<word32, true> > AlignedWordBlock;

		AlignedByteBlock  m_rk;  // round keys
		AlignedWordBlock  m_w;   // w0, w1, w2, w3, t and u
		unsigned int m_rounds;
	};

public:
	typedef BlockCipherFinal<ENCRYPTION, Base> Encryption;
	typedef BlockCipherFinal<DECRYPTION, Base> Decryption;
};

typedef ARIA::Encryption ARIAEncryption;
typedef ARIA::Decryption ARIADecryption;

NAMESPACE_END

#endif