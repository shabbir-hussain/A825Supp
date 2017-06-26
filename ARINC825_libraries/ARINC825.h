/* Author: Shabbir Hussain 
* Email: shabbir.hussain@mail.mcgill.ca
* Date: Nov 4 2016
* Desc: This header contains the definitions of ARINC 825 fields
*          and provides an interface to them

 Copyright 2017 Shabbir Hussain 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

#define EEC 0 // Exception Event Channel
#define NOC 2 // Normal Operation Channel
#define DMC 3 // Directed Message Channel
#define NSC 4 // Node Service Channel
#define UDC 5 // User-defined Channel
#define TMC 6 // Test and Maintenance
#define FMC 7 // CAN Base Frame Mitigation Channel

#define EEC_H 0
#define NOC_H 0x08000000
#define DMC_H 0x0C000000
#define NSC_H 0x10000000
#define UDC_H 0x14000000
#define TMC_H 0x18000000
#define FMC_H 0x1C000000

#define SOURCE_FID_START_BIT 19
#define FSB_START_BIT 18
#define LCL_START_BIT 17
#define PVT_START_BIT 16
#define DOC_START_BIT 2
#define RCI_START_BIT 0

#define SOURCE_ADDRESS_START_BIT 19
#define DESTINATION_ADDRESS_START_BIT 12
#define SOURCE_PORT_ID_START_BIT 6
#define DESTINATION_PORT_ID_START_BIT 0

#define CLIENT_FID_START_BIT 19
#define SMT_START_BIT 18
#define SERVER_FID_START_BIT 9
#define SID_START_BIT 2

enum FieldName{
    _SourceFID,
    _FSB,
    _LCL,
    _PVT,
    _DOC,
    _RCI,
    
    _SourceAddress,
    _DestinationAddress,
    _SourcePortID,
    _DestinationPortID,
    
    _ClientFID,
    _SMT,
    _ServerFID,
    _SID,
};

// Encodes the LCC
void assignLCC(const uint32_T *LCC, uint32_T *Header);

// Encodes the header field
void assignField(const uint32_T *field, uint32_T *Header, enum FieldName fieldName);

// Decodes the LCC
void decodeLCC(uint32_T *LCC, const uint32_T *Header);

// Decodes the header field
void decodeField(uint32_T *field, const uint32_T *Header, enum FieldName fieldName);
