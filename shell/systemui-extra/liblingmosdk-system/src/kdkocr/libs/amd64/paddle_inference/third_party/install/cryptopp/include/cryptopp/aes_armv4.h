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
/* Header file for use with Cryptogam's ARMv4 AES.         */
/* Also see http://www.openssl.org/~appro/cryptogams/ and  */
/* https://wiki.openssl.org/index.php?title=Cryptogams_AES */

#ifndef CRYPTOGAMS_AES_ARMV4_H
#define CRYPTOGAMS_AES_ARMV4_H

#ifdef __cplusplus
extern "C" {
#endif

//#define AES_MAXNR 14
//typedef struct AES_KEY_st {
//    unsigned int rd_key[4 * (AES_MAXNR + 1)];
//    int rounds;
//} AES_KEY;

// Instead of AES_KEY we use a 'word32 rkey[4*15+4]'. It has space for
// both the AES_MAXNR round keys and the number of rounds in the tail.

int AES_set_encrypt_key(const unsigned char *userKey, const int bits, unsigned int *rkey);
int AES_set_decrypt_key(const unsigned char *userKey, const int bits, unsigned int *rkey);
void AES_encrypt(const unsigned char in[16], unsigned char out[16], const unsigned int *rkey);
void AES_decrypt(const unsigned char in[16], unsigned char out[16], const unsigned int *rkey);

#ifdef __cplusplus
}
#endif

#endif  /* CRYPTOGAMS_AES_ARMV4_H */