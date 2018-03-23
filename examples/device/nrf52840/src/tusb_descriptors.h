/**************************************************************************/
/*!
    @file     tusb_descriptors.h
    @author   hathach (tinyusb.org)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, hathach (tinyusb.org)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    This file is part of the tinyusb stack.
*/
/**************************************************************************/

#ifndef _TUSB_DESCRIPTORS_H_
#define _TUSB_DESCRIPTORS_H_

#include "tusb.h"

//--------------------------------------------------------------------+
// Descriptors Value (calculated by enabled Classes)
//--------------------------------------------------------------------+
#define CFG_VENDORID            0xCAFE
//#define CFG_PRODUCTID           0x4567 // use auto product id to prevent conflict with pc's driver

// each combination of interfaces need to have a unique productid, as windows will bind & remember device driver after the first plug.
// Auto ProductID layout's Bitmap: (MSB) MassStorage | Generic | Mouse | Key | CDC (LSB)
#ifndef CFG_PRODUCTID
  #define PRODUCTID_BITMAP(interface, n)  ( (TUSB_CFG_DEVICE_##interface) << (n) )
  #define CFG_PRODUCTID                   (0x4000 | ( PRODUCTID_BITMAP(CDC, 0) | PRODUCTID_BITMAP(HID_KEYBOARD, 1) | \
                                           PRODUCTID_BITMAP(HID_MOUSE, 2) | PRODUCTID_BITMAP(HID_GENERIC, 3) | \
                                           PRODUCTID_BITMAP(MSC, 4) ) )
#endif

#define INTERFACE_NO_CDC          0
#define TOTAL_INTEFACES           2

//--------------------------------------------------------------------+
// Endpoints Address & Max Packet Size
//--------------------------------------------------------------------+
#define EDPT_IN(x)    (0x80 | (x))
#define EDPT_OUT(x)   (x)

#define CDC_EDPT_NOTIFICATION_ADDR            EDPT_IN (1)
#define CDC_EDPT_NOTIFICATION_PACKETSIZE      64

#define CDC_EDPT_DATA_OUT_ADDR                EDPT_OUT(2)
#define CDC_EDPT_DATA_IN_ADDR                 EDPT_IN (2)
#define CDC_EDPT_DATA_PACKETSIZE              64


//--------------------------------------------------------------------+
// CONFIGURATION DESCRIPTOR
//--------------------------------------------------------------------+
typedef struct ATTR_PACKED
{
  tusb_desc_configuration_t           configuration;

  struct ATTR_PACKED
  {
    tusb_desc_interface_assoc_t       iad;

    //CDC Control Interface
    tusb_desc_interface_t             comm_itf;
    cdc_desc_func_header_t            header;
    cdc_desc_func_call_management_t   call;
    cdc_desc_func_acm_t               acm;
    cdc_desc_func_union_t             union_func;
    tusb_desc_endpoint_t              ep_notif;

    //CDC Data Interface
    tusb_desc_interface_t             data_itf;
    tusb_desc_endpoint_t              ep_out;
    tusb_desc_endpoint_t              ep_in;
  }cdc;

} app_descriptor_configuration_t;

#endif
