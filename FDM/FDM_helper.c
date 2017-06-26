// Author: Shabbir Hussain 
// Email: shabbir.hussain@mail.mcgill.ca
// Date: DEC 5 2016
// Desc: This source contains the implementations of the FDM decoder

/*
 Copyright 2017 Shabbir Hussain 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "FDM_helper.h"

void populateUint32(const uint8_T *Input, int *offset, uint32_T *number)
{
    union {
    uint32_T d;
    uint8_T bytes[4];
    } u;
    u.bytes[3] = Input[*offset];
    u.bytes[2] = Input[*offset+1];
    u.bytes[1] = Input[*offset+2];
    u.bytes[0] = Input[*offset+3];
    
    *number = u.d;
    *offset += 4;
}
void populateReal(const uint8_T *Input, int *offset, real_T *number)
{
    union {
    real_T d;
    uint8_T bytes[8];
    } u;
    u.bytes[7] = Input[*offset];
    u.bytes[6] = Input[*offset+1];
    u.bytes[5] = Input[*offset+2];
    u.bytes[4] = Input[*offset+3]; 
    u.bytes[3] = Input[*offset+4];
    u.bytes[2] = Input[*offset+5];
    u.bytes[1] = Input[*offset+6];
    u.bytes[0] = Input[*offset+7];  
    *number = u.d;

    *offset += 8;
}
void populateReal32(const uint8_T *Input, int *offset, real32_T *number)
{
    union {
    real32_T d;
    uint8_T bytes[4];
    } u;
    u.bytes[3] = Input[*offset];
    u.bytes[2] = Input[*offset+1];
    u.bytes[1] = Input[*offset+2];
    u.bytes[0] = Input[*offset+3];
    *number = u.d;
    *offset += 4;
}

void populateUint32_arr(const uint8_T *Input, int *offset, uint32_T *number, int alen)
{
    int i = 0;
    while(i<alen){
        populateUint32(Input,offset, number + i);
        i++;
    }
}
void populateReal_arr(const uint8_T *Input, int *offset, real_T *number, int alen)
{
     int i = 0;
    while(i<alen){
        populateReal(Input,offset, number + i);
        i++;
    }
}
void populateReal32_arr(const uint8_T *Input, int *offset, real32_T *number, int alen)
{
    int i = 0;
    while(i<alen){
        populateReal32(Input,offset, number + i);
        i++;
    }
}
