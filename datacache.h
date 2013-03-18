/*

Copyright (c) '1999' RICE UNIVERSITY. All rights reserved 
Created by Vivek Sadananda Pai [vivek@cs.rice.edu], Departments of
Electrical and Computer Engineering and of Computer Science


This software, "Flash", is distributed to individuals for personal
non-commercial use and to non-profit entities for non-commercial
purposes only.  It is licensed on a non-exclusive basis, free of
charge for these uses.  All parties interested in any other use of the
software should contact the Rice University Office of Technology
Transfer [techtran@rice.edu]. The license is subject to the following
conditions:

1. No support will be provided by the developer or by Rice University.
2. Redistribution is not permitted. Rice will maintain a copy of Flash
   as a directly downloadable file, available under the terms of
   license specified in this agreement.
3. All advertising materials mentioning features or use of this
   software must display the following acknowledgment: "This product
   includes software developed by Rice University, Houston, Texas and
   its contributors."
4. Neither the name of the University nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY WILLIAM MARSH RICE UNIVERSITY, HOUSTON,
TEXAS, AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL RICE UNIVERSITY OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTIONS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE), PRODUCT LIABILITY, OR OTHERWISE ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.

This software contains components from computer code originally
created and copyrighted by Jef Poskanzer (C) 1995. The license under
which Rice obtained, used and modified that code is reproduced here in
accordance with the requirements of that license:

** Copyright (C) 1995 by Jef Poskanzer <jef@acme.com>.  All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
** OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
*/


typedef struct CacheEntry {
  char *ce_filename;		
  struct CacheEntry *ce_nextInHash;
  struct CacheEntry **ce_prevInHash;
  struct CacheEntry *ce_nextInLRU; /* not impl */
  int ce_size;
  int ce_numRefs;
  int ce_isInvalid;
  int ce_file_fd;
  int ce_numChunks;
  int ce_numChunksInMem;
  struct ReadInfoRec *ce_dataChunks;	
  time_t ce_lastValidation;	
  char *ce_encodings;		/* from figure_mime call */
  char *ce_type;		/* from figure_mime call */
  time_t ce_modTime;
  char *ce_respHeader;	/* memory allocated for mime */
  int ce_respHeaderLen;
  time_t ce_respHeaderTime;	/* date field in resp header */
  char *ce_200Resp;		/* cached response for log */
  int ce_200RespLen;		/* length of 200 response */
} CacheEntry;

void *GetDataToSend(struct CacheEntry *ent, int position, int desiredSize, 
		    int maxSize, int *actualSize, int *startOffset);

int AddEntryToDataCache(CacheEntry *ce);

CacheEntry *CheckCache(char *exName);

CacheEntry *GetEmptyCacheEntry(void);

void ReleaseCacheEntry(CacheEntry **entP);

int CalcRespHeader(CacheEntry *ce, int status, char* title);

int IncChunkLock(struct CacheEntry *ent, int bytes);
int DecChunkLock(struct CacheEntry *ent, int bytes);
int ReadChunkIfNeeded(struct CacheEntry *ent, int position);
void DumpDataCacheStats(void);

