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

// ida.h - originally written and placed in the public domain by Wei Dai

/// \file ida.h
/// \brief Classes for Rabin's Information Dispersal and Shamir's Secret Sharing algorithms

#ifndef CRYPTOPP_IDA_H
#define CRYPTOPP_IDA_H

#include "cryptlib.h"
#include "mqueue.h"
#include "filters.h"
#include "channels.h"
#include "secblock.h"
#include "gf2_32.h"
#include "stdcpp.h"
#include "misc.h"

NAMESPACE_BEGIN(CryptoPP)

/// \brief Secret sharing and information dispersal base class
/// \since Crypto++ 1.0
class RawIDA : public AutoSignaling<Unflushable<Multichannel<Filter> > >
{
public:
	RawIDA(BufferedTransformation *attachment=NULLPTR)
		: m_channelsReady(0), m_channelsFinished(0), m_threshold (0)
			{Detach(attachment);}

	unsigned int GetThreshold() const {return m_threshold;}
	void AddOutputChannel(word32 channelId);
	void ChannelData(word32 channelId, const byte *inString, size_t length, bool messageEnd);
	lword InputBuffered(word32 channelId) const;

	void IsolatedInitialize(const NameValuePairs &parameters=g_nullNameValuePairs);
	size_t ChannelPut2(const std::string &channel, const byte *begin, size_t length, int messageEnd, bool blocking)
	{
		if (!blocking)
			throw BlockingInputOnly("RawIDA");
		ChannelData(StringToWord<word32>(channel), begin, length, messageEnd != 0);
		return 0;
	}

protected:
	virtual void FlushOutputQueues();
	virtual void OutputMessageEnds();

	unsigned int InsertInputChannel(word32 channelId);
	unsigned int LookupInputChannel(word32 channelId) const;
	void ComputeV(unsigned int);
	void PrepareInterpolation();
	void ProcessInputQueues();

	typedef std::map<word32, unsigned int> InputChannelMap;
	InputChannelMap m_inputChannelMap;
	InputChannelMap::iterator m_lastMapPosition;
	std::vector<MessageQueue> m_inputQueues;
	std::vector<word32> m_inputChannelIds, m_outputChannelIds, m_outputToInput;
	std::vector<std::string> m_outputChannelIdStrings;
	std::vector<ByteQueue> m_outputQueues;
	std::vector<SecBlock<word32> > m_v;
	SecBlock<word32> m_u, m_w, m_y;
	const GF2_32 m_gf32;
	unsigned int m_channelsReady, m_channelsFinished;
	int m_threshold;
};

/// \brief Shamir's Secret Sharing Algorithm
/// \details SecretSharing is a variant of Shamir's secret sharing algorithm
/// \sa SecretRecovery, SecretRecovery, InformationDispersal, InformationRecovery
/// \since Crypto++ 1.0
class SecretSharing : public CustomFlushPropagation<Filter>
{
public:
	/// \brief Construct a SecretSharing
	SecretSharing(RandomNumberGenerator &rng, int threshold, int nShares, BufferedTransformation *attachment=NULLPTR, bool addPadding=true)
		: m_rng(rng), m_ida(new OutputProxy(*this, true))
	{
		Detach(attachment);
		IsolatedInitialize(MakeParameters("RecoveryThreshold", threshold)("NumberOfShares", nShares)("AddPadding", addPadding));
	}

	void IsolatedInitialize(const NameValuePairs &parameters=g_nullNameValuePairs);
	size_t Put2(const byte *begin, size_t length, int messageEnd, bool blocking);
	bool Flush(bool hardFlush, int propagation=-1, bool blocking=true) {return m_ida.Flush(hardFlush, propagation, blocking);}

protected:
	RandomNumberGenerator &m_rng;
	RawIDA m_ida;
	bool m_pad;
};

/// \brief Shamir's Secret Sharing Algorithm
/// \details SecretSharing is a variant of Shamir's secret sharing algorithm
/// \sa SecretRecovery, SecretRecovery, InformationDispersal, InformationRecovery
/// \since Crypto++ 1.0
class SecretRecovery : public RawIDA
{
public:
	/// \brief Construct a SecretRecovery
	SecretRecovery(int threshold, BufferedTransformation *attachment=NULLPTR, bool removePadding=true)
		: RawIDA(attachment)
		{IsolatedInitialize(MakeParameters("RecoveryThreshold", threshold)("RemovePadding", removePadding));}

	void IsolatedInitialize(const NameValuePairs &parameters=g_nullNameValuePairs);

protected:
	void FlushOutputQueues();
	void OutputMessageEnds();

	bool m_pad;
};

/// a variant of Rabin's Information Dispersal Algorithm

/// \brief Rabin's Information Dispersal Algorithm
/// \details InformationDispersal is a variant of Rabin's information dispersal algorithm
/// \sa SecretRecovery, SecretRecovery, InformationDispersal, InformationRecovery
/// \since Crypto++ 1.0
class InformationDispersal : public CustomFlushPropagation<Filter>
{
public:
	/// \brief Construct a InformationDispersal
	InformationDispersal(int threshold, int nShares, BufferedTransformation *attachment=NULLPTR, bool addPadding=true)
		: m_ida(new OutputProxy(*this, true)), m_pad(false), m_nextChannel(0)
	{
		Detach(attachment);
		IsolatedInitialize(MakeParameters("RecoveryThreshold", threshold)("NumberOfShares", nShares)("AddPadding", addPadding));
	}

	void IsolatedInitialize(const NameValuePairs &parameters=g_nullNameValuePairs);
	size_t Put2(const byte *begin, size_t length, int messageEnd, bool blocking);
	bool Flush(bool hardFlush, int propagation=-1, bool blocking=true) {return m_ida.Flush(hardFlush, propagation, blocking);}

protected:
	RawIDA m_ida;
	bool m_pad;
	unsigned int m_nextChannel;
};

/// \brief Rabin's Information Dispersal Algorithm
/// \details InformationDispersal is a variant of Rabin's information dispersal algorithm
/// \sa SecretRecovery, SecretRecovery, InformationDispersal, InformationRecovery
/// \since Crypto++ 1.0
class InformationRecovery : public RawIDA
{
public:
	/// \brief Construct a InformationRecovery
	InformationRecovery(int threshold, BufferedTransformation *attachment=NULLPTR, bool removePadding=true)
		: RawIDA(attachment), m_pad(false)
		{IsolatedInitialize(MakeParameters("RecoveryThreshold", threshold)("RemovePadding", removePadding));}

	void IsolatedInitialize(const NameValuePairs &parameters=g_nullNameValuePairs);

protected:
	void FlushOutputQueues();
	void OutputMessageEnds();

	bool m_pad;
	ByteQueue m_queue;
};

class PaddingRemover : public Unflushable<Filter>
{
public:
	PaddingRemover(BufferedTransformation *attachment=NULLPTR)
		: m_possiblePadding(false), m_zeroCount(0) {Detach(attachment);}

	void IsolatedInitialize(const NameValuePairs &parameters)
		{CRYPTOPP_UNUSED(parameters); m_possiblePadding = false;}
	size_t Put2(const byte *begin, size_t length, int messageEnd, bool blocking);

	// GetPossiblePadding() == false at the end of a message indicates incorrect padding
	bool GetPossiblePadding() const {return m_possiblePadding;}

private:
	bool m_possiblePadding;
	lword m_zeroCount;
};

NAMESPACE_END

#endif
