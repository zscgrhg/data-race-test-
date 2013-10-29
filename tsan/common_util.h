/* Copyright (c) 2010-2011, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TSAN_COMMON_UTIL__
#define TSAN_COMMON_UTIL__

#include "ts_util.h"

#if defined(__GNUC__)
  typedef int TS_FILE;
  #define TS_FILE_INVALID (-1)
  #define read_ret_t ssize_t
#ifdef TS_LLVM
  #define read(fd, buf, size) __real_read(fd, buf, size)
#endif
#elif defined(_MSC_VER)
  typedef FILE *TS_FILE;
  #define TS_FILE_INVALID (NULL)
  #define read_ret_t size_t
  #define read(fd, buf, size) fread(buf, 1, size, fd)
  #define close fclose
#endif

bool ThreadSanitizerStringMatch(const string& wildcard, const string& text);
string ThreadSanitizerConvertToPlatformIndependentPath(const string &s);
TS_FILE ThreadSanitizerOpenFileReadOnly(const string &file_name,
    bool die_if_failed);
string ThreadSanitizerReadFileToString(const string &file_name,
    bool die_if_failed);

#endif