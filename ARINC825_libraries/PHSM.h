/* 
 * Author: Shabbir Hussain 
 * Email: shabbir.hussain@mail.mcgill.ca
 * Date: Nov 9 2016
 * Desc: This header encodes and decodes Periodic Health
 *       Status Messages
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

void PHSMEncode(const uint16_T *NB_ERR_RX,
                const uint16_T *NB_ERR_TX,
                const uint16_T *NB_ERR_ACK,
                const uint8_T *NB_BUS_OFF,
                const uint8_T *REC_STATE,
                const uint8_T *TEC_STATE,
                uint8_T *Message);

void PHSMDecode(uint16_T *NB_ERR_RX,
                uint16_T *NB_ERR_TX,
                uint16_T *NB_ERR_ACK,
                uint8_T *NB_BUS_OFF,
                uint8_T *REC_STATE,
                uint8_T *TEC_STATE,
                const uint8_T *Message);
