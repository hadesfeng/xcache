//  Copyright (c) 2017-present The slash Authors.  All rights reserved.
//  This source code is licensed under the BSD-style license found in the
//  LICENSE file in the root directory of this source tree. An additional grant
//  of patent rights can be found in the PATENTS file in the same directory.

/*
  Murmurhash from http://sites.google.com/site/murmurhash/

  All code is released to the public domain. For business purposes, Murmurhash
  is under the MIT license.
*/
#ifndef SLASH_MURMURHASH_H_
#define SLASH_MURMURHASH_H_

#include <stdint.h>
#include "slash/include/slash_slice.h"

#if defined(__x86_64__)
#define MURMUR_HASH MurmurHash64A
uint64_t MurmurHash64A(const void * key, int len, unsigned int seed);
#define MurmurHash MurmurHash64A
typedef uint64_t murmur_t;

#elif defined(__i386__)
#define MURMUR_HASH MurmurHash2
unsigned int MurmurHash2(const void * key, int len, unsigned int seed);
#define MurmurHash MurmurHash2
typedef unsigned int murmur_t;

#else
#define MURMUR_HASH MurmurHashNeutral2
unsigned int MurmurHashNeutral2(const void * key, int len, unsigned int seed);
#define MurmurHash MurmurHashNeutral2
typedef unsigned int murmur_t;
#endif

// Allow slice to be hashable by murmur hash.
namespace slash {
struct murmur_hash {
  size_t operator()(const Slice& slice) const {
    return MurmurHash(slice.data(), static_cast<int>(slice.size()), 0);
  }
};
}  // slash
#endif  // SLASH_MURMURHASH_H_
