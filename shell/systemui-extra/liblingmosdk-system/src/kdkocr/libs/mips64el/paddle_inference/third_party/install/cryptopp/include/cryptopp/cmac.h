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

// cmac.h - originally written and placed in the public domain by Wei Dai

/// \file cmac.h
/// \brief Classes for CMAC message authentication code
/// \since Crypto++ 5.6.0

#ifndef CRYPTOPP_CMAC_H
#define CRYPTOPP_CMAC_H

#include "seckey.h"
#include "secblock.h"

NAMESPACE_BEGIN(CryptoPP)

/// \brief CMAC base implementation
/// \since Crypto++ 5.6.0
class CRYPTOPP_DLL CRYPTOPP_NO_VTABLE CMAC_Base : public MessageAuthenticationCode
{
public:

	virtual ~CMAC_Base() {}

	CMAC_Base() : m_counter(0) {}

	void UncheckedSetKey(const byte *key, unsigned int length, const NameValuePairs &params);
	void Update(const byte *input, size_t length);
	void TruncatedFinal(byte *mac, size_t size);
	unsigned int DigestSize() const {return GetCipher().BlockSize();}
	unsigned int OptimalBlockSize() const {return GetCipher().BlockSize();}
	unsigned int OptimalDataAlignment() const {return GetCipher().OptimalDataAlignment();}
	std::string AlgorithmProvider() const {return GetCipher().AlgorithmProvider();}

protected:
	friend class EAX_Base;

	const BlockCipher & GetCipher() const {return const_cast<CMAC_Base*>(this)->AccessCipher();}
	virtual BlockCipher & AccessCipher() =0;

	void ProcessBuf();
	SecByteBlock m_reg;
	unsigned int m_counter;
};

/// \brief CMAC message authentication code
/// \tparam T block cipher
/// \details Template parameter T should be a class derived from BlockCipherDocumentation, for example AES, with a block size of 8, 16, or 32.
/// \sa <a href="http://www.cryptolounge.org/wiki/CMAC">CMAC</a>
/// \since Crypto++ 5.6.0
template <class T>
class CMAC : public MessageAuthenticationCodeImpl<CMAC_Base, CMAC<T> >, public SameKeyLengthAs<T>
{
public:
	/// \brief Construct a CMAC
	CMAC() {}
	/// \brief Construct a CMAC
	/// \param key the MAC key
	/// \param length the key size, in bytes
	CMAC(const byte *key, size_t length=SameKeyLengthAs<T>::DEFAULT_KEYLENGTH)
		{this->SetKey(key, length);}

	static std::string StaticAlgorithmName() {return std::string("CMAC(") + T::StaticAlgorithmName() + ")";}

private:
	BlockCipher & AccessCipher() {return m_cipher;}
	typename T::Encryption m_cipher;
};

NAMESPACE_END

#endif
