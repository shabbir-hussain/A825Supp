/*
 * Author: Shabbir Hussain
 * Email: shabbir.hussain@mail.mcgill.ca
 * Date: Nov 8 2016
 * Desc: This file implement High Integrity Messages
 *

 Copyright 2017 Shabbir Hussain 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HighIntegrityMessage.h"



/*
 * Obtained from:
 * http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
 * The width of the CRC calculation and result.
 * Modify the typedef for a 16 or 32-bit CRC standard.
 */
uint32_T
reflect(uint32_T data, uint8_T nBits)
{
    uint32_T  reflection = 0;
    uint8_T bit; 


    /*
     * Reflect the data about the center bit.
     */
    for (bit = 0; bit < nBits; ++bit)
    {
        /*
         * If the LSB bit is set, set the reflection of it.
         */
        if (data & 0x01)
        {
            reflection |= (1 << ((nBits - 1) - bit));
        }

        data = (data >> 1);
    }

    return (reflection);

}   /* reflect() */



crc crcSlow(uint8_T message[], int nBytes)
{
    crc  remainder = INIT_CRC;	
    int byte;
    uint8_T bit;
    
    /*
     * Perform modulo-2 division, a byte at a time.
     */
    for (byte = 0; byte < nBytes; ++byte)
    {
        /*
         * Bring the next byte into the remainder.
         */
        remainder ^= (REFLECT_DATA(message[byte]) << (WIDTH - 8));

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /*
     * The final remainder is the CRC result.
     */
    return (REFLECT_REMAINDER(remainder) ^ FINAL_CRC);

}   /* crcSlow() */

// This fucntion assumes a max of 5 bytes
// TODO: Extend for CAN FD
void pack_data( const uint32_T *CAN_ID,
                const uint8_T *Data_in,
                const uint8_T *DLC,
                const uint8_T *Sno,
                uint8_T *Data_out,
                uint16_T *MIC){
    
    uint8_T frame[FRAME_BYTES];
    crc computed_crc;
    int i;
    int payloadLen = *DLC-3;
    
    // Pack data into buffer
    frame[0] = (*CAN_ID & 0xFF000000) >> 24;
    frame[1] = (*CAN_ID & 0x00FF0000) >> 16;
    frame[2] = (*CAN_ID & 0x0000FF00) >> 8;
    frame[3] = (*CAN_ID & 0x000000FF); 
    
    for( i=0; i<payloadLen; i++){
        frame[i+4] = Data_in[i];
    }
    i=i+4;
        
    frame[i] = *Sno;
    
    computed_crc = crcSlow(frame, i+1);
    
    for(i=0; i<payloadLen; i++){
        Data_out[i] = Data_in[i];
    }
    Data_out[i] = *Sno;
    Data_out[i+1] = (computed_crc & 0xFF00) >> 8;
    Data_out[i+2] = (computed_crc & 0xFF);
    
    *MIC = computed_crc;
    
}

void unpack_data( const uint32_T *CAN_ID,
                  const uint8_T *Data_in,
                  const uint8_T *DLC,
                  uint8_T *Data_out,
                  uint8_T *Sno,
                  boolean_T *CAN_check
                  ){
    
    uint8_T frame[FRAME_BYTES];
    crc computed_crc;
    crc received_crc;
    int i;
    int payloadLen = *DLC-3; //sub 3 for sno and CRC
    
    frame[0] = (*CAN_ID & 0xFF000000) >> 24;
    frame[1] = (*CAN_ID & 0x00FF0000) >> 16;
    frame[2] = (*CAN_ID & 0x0000FF00) >> 8;
    frame[3] = (*CAN_ID & 0x000000FF); 
        
    for(i=0; i<payloadLen; i++){
        frame[i+4] = Data_in[i];
    }
    *Sno = Data_in[i];
    frame[i+4] = *Sno;

    received_crc = (Data_in[i+1] << 8 ) + Data_in[i+2];
    
    // i+5 is the frame len
    computed_crc = crcSlow(frame, i+5);
    
    for(i=0; i<payloadLen; i++){
        Data_out[i] = Data_in[i];
    }
    
    //Check if Same
    if(received_crc == computed_crc){
        *CAN_check = true;
    }
    else{
        *CAN_check = false;
    }
}
