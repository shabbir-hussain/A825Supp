/*
 * Author: Shabbir Hussain 
 * Email: shabbir.hussain@mail.mcgill.ca
 * Date: DEC 5 2016
 * Desc: This source contains the implementations of the Arinc 825 protocol
 *

 Copyright 2017 Shabbir Hussain 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "ARINC825.h"

// Assumes header starts zeroed
void assignLCC(const uint32_T *LCC, uint32_T *Header){
     switch(*LCC){
        case EEC:
            //Exeption Event Channel
            *Header |= EEC_H;
            break;
        case NOC:
            *Header |= NOC_H;
            break;
        case DMC:
            *Header |= DMC_H;
            break;
        case NSC:
            *Header |= NSC_H;
            break;
        case UDC:
            *Header |= UDC_H;
            break;
        case TMC:
            *Header |= TMC_H;
            break;
        case FMC:
            *Header |= FMC_H;
            break;
            //TODO: Handle error case
    }   
}

void assignField(const uint32_T *field, uint32_T *Header, enum FieldName fieldName){
    //truncate bits to mask errors
    uint32_T mask;
    
    switch(fieldName){
        
        // 1 TO MANY FIELDS
        case _SourceFID:
            mask = *field & 0x7F;
            mask = mask << SOURCE_FID_START_BIT;
            break;
        case _FSB:
            mask = *field & 0x1; 
            mask = mask << FSB_START_BIT;
            break;
        case _LCL:
            mask = *field & 0x1;
            mask = mask << LCL_START_BIT;
            break;
        case _PVT:
            mask = *field & 0x01;
            mask = mask << PVT_START_BIT;
            break;
        case _DOC:
            mask = *field & 0x3FFF;
            mask = mask << DOC_START_BIT;
            break;
        case _RCI:
            mask = *field & 0x3;
            mask = mask << RCI_START_BIT;  
            break;
            
        // Directed messages 
        case _SourceAddress:
            mask = *field & 0x7f;
            mask = mask << SOURCE_ADDRESS_START_BIT;  
            break;
        case _DestinationAddress:
            mask = *field & 0x7f;
            mask = mask << DESTINATION_ADDRESS_START_BIT;  
            break;
        case _SourcePortID:
            mask = *field & 0x3f;
            mask = mask << SOURCE_PORT_ID_START_BIT;  
            break;
        case _DestinationPortID:
            mask = *field & 0x3f;
            mask = mask << DESTINATION_PORT_ID_START_BIT;  
            break;
            
        // Peer to Peer
        case _ClientFID:
            mask = *field & 0x7f;
            mask = mask << CLIENT_FID_START_BIT;  
            break;
        case _SMT:
            mask = *field & 0x1;
            mask = mask << SMT_START_BIT;  
            break;
        case _ServerFID:
            mask = *field & 0x7f;
            mask = mask << SERVER_FID_START_BIT;  
            break;
        case _SID:
            mask = *field & 0x7f;
            mask = mask << SID_START_BIT;  
            break;
    }           
    *Header |= mask;
}

void decodeLCC(uint32_T *LCC, const uint32_T *Header){
 switch(*Header & 0x1C000000){
        case EEC_H:
            //Exeption Event Channel
            *LCC = EEC;
            break;
        case NOC_H:
            *LCC = NOC;
            break;
        case DMC_H:
            *LCC = DMC;
            break;
        case NSC_H:
            *LCC = NSC;
            break;
        case UDC_H:
            *LCC = UDC;
            break;
        case TMC_H:
            *LCC = TMC;
            break;
        case FMC_H:
            *LCC = FMC;
            break;
            //TODO: Handle error case
    }   
}
void decodeField(uint32_T *field, const uint32_T *Header, enum FieldName fieldName){
    //truncate bits to mask errors
    uint32_T mask;
    
    switch(fieldName){
        
        // 1 TO MANY FIELDS
        case _SourceFID:
            mask = *Header >> SOURCE_FID_START_BIT;
            mask = mask & 0x7F;            
            break;
        case _FSB:
            mask = *Header >> FSB_START_BIT;
            mask = mask & 0x1;             
            break;
        case _LCL:
            mask = *Header >> LCL_START_BIT;
            mask = mask & 0x1;            
            break;
        case _PVT:
            mask = *Header >> PVT_START_BIT;
            mask = mask & 0x01;            
            break;
        case _DOC:
            mask = *Header >> DOC_START_BIT;
            mask = mask & 0x3FFF;            
            break;
        case _RCI:
            mask = *Header >> RCI_START_BIT; 
            mask = mask & 0x3;             
            break;
            
        // Directed messages 
        case _SourceAddress:
            mask = *Header >> SOURCE_ADDRESS_START_BIT; 
            mask = mask & 0x7f;             
            break;
        case _DestinationAddress:
            mask = *Header >> DESTINATION_ADDRESS_START_BIT;
            mask = mask & 0x7f;
            break;
        case _SourcePortID:
            mask = *Header >> SOURCE_PORT_ID_START_BIT;
            mask = mask & 0x3f;
            break;
        case _DestinationPortID:
            mask = *Header >> DESTINATION_PORT_ID_START_BIT;
            mask = mask & 0x3f;              
            break;
            
        // Peer to Peer
        case _ClientFID:
            mask = *Header >> CLIENT_FID_START_BIT;
            mask = mask & 0x7f;              
            break;
        case _SMT:
            mask = *Header >> SMT_START_BIT; 
            mask = mask & 0x1;
            break;
        case _ServerFID:
            mask = *Header >> SERVER_FID_START_BIT;
            mask = mask & 0x7f;
            break;
        case _SID:
            mask = *Header >> SID_START_BIT; 
            mask = mask & 0x7f;
             
            break;
    }           
    *field = mask;
}


