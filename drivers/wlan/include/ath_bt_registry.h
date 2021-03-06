/*
 * Copyright (c) 2010, Atheros Communications Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Public Interface for Bluetooth coexistence Registry params.
 */

#ifndef _ATH_BT_REGISTRY_H_
#define _ATH_BT_REGISTRY_H_

#ifdef WIN32
#pragma pack(push, spectral_data, 1)
#define __ATTRIB_PACK
#else
#ifndef __ATTRIB_PACK
#define __ATTRIB_PACK __attribute__ ((packed))
#endif  /* __ATTRIB_PACK */
#endif /* WIN32 */

struct ath_bt_registry {    
    u_int8_t             btCoexEnable;                    /* Enable btCoex */
    u_int8_t             btActiveGpio;                    /* GPIO for bt_active */
    u_int8_t             wlanActiveGpio;                  /* GPIO for wlan_active */
    u_int8_t             btPriorityGpio;                  /* GPIO for bt_priority */
    u_int8_t             btActivePolarity;                /* Polarity of bt_active */
    u_int8_t             btModule;                        /* Co-located BT module */
    u_int8_t             btScheme;                        /* BT coexistence scheme */
    u_int8_t             btPeriod;                        /* Time sharing period in ms */
    u_int8_t             btDutyCycle;                     /* Duty cycle in % for BT */
    u_int16_t            btSingleAnt;                     /* Single antenna configuration */
    u_int16_t            btCoexAgent;                     /* Coex agent enable */
    u_int32_t            btCoexLowACKPwr;                 /* Low ACK power */
    u_int8_t             btCoexStompType;                 /* Stomp type */
    u_int8_t             btCoexAggrLimit;                 /* Aggr limit in 0.25ms */
    u_int32_t            btCoexWeight;                    /* Forced weight table */
    u_int32_t            btCoexDisablePTA;                /* Disable PTA mode */
    u_int8_t             btWlanIsolation;                 /* Isolation between BT and WLAN in dB */
    u_int32_t            btCoexAntDivEnable;              /* Rx Antenna diversity */    
     u_int32_t           btCoexMaxHT40RateKbps;           /* Workaround for Helius hardware issue */
    u_int32_t            btCoexRSSIModeProfile;           /* Change Profile based on mode and RSSI */
    u_int32_t            btCoexEnhanceA2DP;               /* A2DP Enhancement */
}__ATTRIB_PACK;

#ifdef WIN32
#pragma pack(pop, spectral_data)
#endif  /* WIN32 */
#ifdef __ATTRIB_PACK
#undef __ATTRIB_PACK
#endif   /* __ATTRIB_PACK */

#endif /* end of _ATH_BT_REGISTRY_H_ */
