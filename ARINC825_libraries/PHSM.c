/* 
 * Author: Shabbir Hussain 
 * Email: shabbir.hussain@mail.mcgill.ca
 * Date: Dec 3 2016
 * Desc: This source implements the PHSM code
 *

 Copyright 2017 Shabbir Hussain 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "PHSM.h"

void PHSMEncode(const uint16_T *NB_ERR_RX,
                const uint16_T *NB_ERR_TX,
                const uint16_T *NB_ERR_ACK,
                const uint8_T *NB_BUS_OFF,
                const uint8_T *REC_STATE,
                const uint8_T *TEC_STATE,
                uint8_T *Message){
    
    Message[0] = (*NB_ERR_RX & 0xFF00) >> 8;
    Message[1] = (*NB_ERR_RX & 0xFF);
    Message[2] = (*NB_ERR_TX & 0xFF00) >> 8;
    Message[3] = (*NB_ERR_TX & 0xFF); 
    Message[4] = (*NB_ERR_ACK & 0xFF00) >> 8;
    Message[5] = (*NB_ERR_ACK & 0xFF);
    Message[6] = *NB_BUS_OFF;
    Message[7] = ((*REC_STATE & 0x0F) << 4) + (*TEC_STATE & 0x0F);
}

void PHSMDecode(uint16_T *NB_ERR_RX,
                uint16_T *NB_ERR_TX,
                uint16_T *NB_ERR_ACK,
                uint8_T *NB_BUS_OFF,
                uint8_T *REC_STATE,
                uint8_T *TEC_STATE,
                const uint8_T *Message){
    
    *NB_ERR_RX = (Message[0] << 8) + Message[1];
    *NB_ERR_TX = (Message[2] << 8) + Message[3];
    *NB_ERR_ACK = (Message[4] << 8) + Message[5];
    *NB_BUS_OFF = Message[6];
    *REC_STATE = (Message[7] & 0xF0) >> 4;
    *TEC_STATE = (Message[7] & 0x0F);            
}
