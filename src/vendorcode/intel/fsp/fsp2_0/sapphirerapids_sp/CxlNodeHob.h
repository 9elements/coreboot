/** @file

Copyright (c) 2019-2023, Intel Corporation. All rights reserved.<BR>

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.
* Neither the name of Intel Corporation nor the names of its contributors may
  be used to endorse or promote products derived from this software without
  specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

**/

#ifndef _CXL_NODE_HOB_
#define _CXL_NODE_HOB_

#define CXL_NODE_HOB_GUID { 0xdd8ae009, 0xda5a, 0x44a3, { 0xbe, 0x18, 0xda, 0x0c, 0x16, 0xc5, 0xaf, 0x5c } }

#ifndef MAX_CXL_HDM_RANGES
#define MAX_CXL_HDM_RANGES        0x2        // Maximum number of CXL HDM ranges per CXL end device.
#endif

#ifndef MAX_CXL_PER_SOCKET
#define MAX_CXL_PER_SOCKET          8
#endif

#define CXL_NODE_ATTR_MEM           BIT0
#define CXL_NODE_ATTR_PERSISTENT    BIT1
#define CXL_NODE_ATTR_MEM_HW_INIT   BIT2
#define CXL_NODE_ATTR_ACCELERATOR   BIT3

typedef UINT32 CXL_NODE_ATTR;

#pragma pack(1)

//
// CDAT DSEMTS EFI Memory Type and Attribute
//
typedef enum {
  CxlEfiConventionalMemory        = 0x0,
  CxlEfiConventionalMemorySp      = 0x1,
  CxlEfiReservedMemoryType        = 0x2,
  MaxCxlEfiMemType
} CXL_EFI_MEM_TYPE;

typedef struct {
  UINT32              RdLatency;
  UINT32              WrLatency;
  UINT32              RdBandwidth;
  UINT32              WrBandwidth;
} CXL_PERF_DATA;

typedef struct {
  UINT64                       SerialNumber;
  UINT16                       VendorId;
  CXL_NODE_ATTR                Attr;
  UINT32                       Address;
  UINT32                       Size;
  UINT8                        Ways;
  UINT8                        SocketBitmap;
  CXL_EFI_MEM_TYPE             EfiMemType;
  CXL_PERF_DATA                InitiatorPerfData;        // Performance data between device egress and initiator.
  CXL_PERF_DATA                TargetPerfData;           // Performance data of entire target memory region.
  CXL_PERF_DATA                InitiatorTargetPerfData;  // performance data between initiator and the device memory.
} CXL_NODE_INFO;

typedef struct {
  UINT8            CxlNodeCount;
  //
  // CXL node info for UEFI memory map and ACPI tables construction
  //
  CXL_NODE_INFO    CxlNodeInfo[MAX_CXL_PER_SOCKET * MAX_CXL_HDM_RANGES];
} CXL_NODE_SOCKET;

#pragma pack()

#endif //#ifndef _CXL_NODE_HOB_
