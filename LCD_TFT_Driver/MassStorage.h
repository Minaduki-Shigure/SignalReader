/*******************************************************************************
 *
 *  MassStorage.h
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/


#ifndef MASSSTORAGE_H
#define MASSSTORAGE_H

#include <stdint.h>



////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define XT1_PORT_SEL      P5SEL
#define XT1_ENABLE        (BIT4 + BIT5)
#define XT2_PORT_SEL      P7SEL
#define XT2_ENABLE        (BIT2 + BIT3)

////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
  

////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Disable_USB_SD_Card_Reader(void);  //����:  "USB_SD_Card_Reader ������(USB-SD��)"


extern void Initial_USB_SD_Card_Reader(void);  //��ʼ������:  "USB_SD_Card_Reader ������(USB-SD��)"

extern void Initial_Osccon_USB(void); //��ʼ������--"USB_SD_Card_Reader ������(USB-SD��)"


extern void Deal_USB_SD_Card_Reader(void);  //����"USB_SD_Card_Reader ������(USB-SD��)"

#endif /* MASSSTORAGE_H */
