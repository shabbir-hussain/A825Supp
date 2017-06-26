/*
 * Author: Shabbir Hussain
 * Email: shabbir.hussain@mail.mcgill.ca
 * Date: Nov 8 2016
 * Desc: This header provides information to process High Integrity 
 *       Messages
 *

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

typedef uint16_T crc;

#define POLYNOMIAL 0x90D9 
#define FRAME_BYTES 10

#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

#define REFLECT_DATA(X)       ((uint8_T) reflect((X), 8))
#define REFLECT_REMAINDER(X)  ((crc) reflect((X), WIDTH))
#define INIT_CRC 0xFFFF
#define FINAL_CRC 0xFFFF


/*
 * Obtained from:
 * http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
 * The width of the CRC calculation and result.
 * Modify the typedef for a 16 or 32-bit CRC standard.
 */
uint32_T reflect(uint32_T data, uint8_T nBits);

crc crcSlow(uint8_T message[], int nBytes);

// This fucntion assumes a max of 5 bytes
// TODO: Extend for CAN FD
void pack_data( const uint32_T *CAN_ID,
                const uint8_T *Data_in,
                const uint8_T *DLC,
                const uint8_T *Sno,
                uint8_T *Data_out,
                uint16_T *MIC);

void unpack_data( const uint32_T *CAN_ID,
                  const uint8_T *Data_in,
                  const uint8_T *DLC,
                  uint8_T *Data_out,
                  uint8_T *Sno,
                  boolean_T *CAN_check);
