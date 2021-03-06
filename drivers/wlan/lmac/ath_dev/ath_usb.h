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
 * Definitions for the USB module
 */
#ifndef ATH_USB_H
#define ATH_USB_H

#ifdef ATH_USB

#define ATH_USB_BCBUF   8   /* number of beacon buffers */

#define ATH_USB_SET_INVALID(_sc, _val)      (_sc->sc_usb_invalid = _val)

#define ATH_USB_TQUEUE_INIT(_sc, _func)     (ATHUSB_INIT_TQUEUE(_sc->sc_osdev, &_sc->sc_osdev->rx_tq, _func, _sc))
#define ATH_USB_TQUEUE_FREE(_sc)            (ATHUSB_FREE_TQUEUE(_sc->sc_osdev, &_sc->sc_osdev->rx_tq))

#ifdef ATH_HTC_TX_SCHED
#define ATH_HTC_TXTQUEUE_INIT(_sc, _func)     (ATHHTC_INIT_TXTQUEUE(_sc->sc_osdev, &_sc->sc_osdev->htctx_tq, _func, _sc))
#define ATH_HTC_TXTQUEUE_FREE(_sc)            (ATHHTC_FREE_TXTQUEUE(_sc->sc_osdev, &_sc->sc_osdev->htctx_tq))
#define ATH_HTC_TXTQUEUE_SCHEDULE(_osdev)           (ATHHTC_SCHEDULE_TXTQUEUE(&_osdev->htctx_tq))
#define ATH_HTC_UAPSD_CREDITUPDATE_INIT(_sc, _func)  (ATHHTC_INIT_UAPSD_CREDITUPDATE(_sc->sc_osdev, \
                                                       &_sc->sc_osdev->htcuapsd_tq, _func, _sc))
#define ATH_HTC_UAPSD_CREDITUPDATE_FREE(_sc)   (ATHHTC_FREE_UAPSD_CREDITUPDATE(_sc->sc_osdev,&_sc->sc_osdev->htcuapsd_tq))
#define ATH_HTC_UAPSD_CREDITUPDATE_SCHEDULE(_osdev)      (ATHHTC_SCHEDULE_UAPSD_CREDITUPDATE(&_osdev->htcuapsd_tq))
#else
#define ATH_HTC_TXTQUEUE_INIT(_sc, _func)     
#define ATH_HTC_TXTQUEUE_FREE(_sc)           
#define ATH_HTC_TXTQUEUE_SCHEDULE(_osdev)   
#define ATH_HTC_UAPSD_CREDITUPDATE_INIT(_sc, _func)     
#define ATH_HTC_UAPSD_CREDITUPDATE_FREE(_sc)           
#define ATH_HTC_UAPSD_CREDITUPDATE_SCHEDULE(_osdev)
#endif
#ifdef MAGPIE_HIF_GMAC
#define    ATH_HTC_RXBUF_LOCK_INIT(_sc)    spin_lock_init(&(_sc)->sc_rxbuflock)
#define    ATH_HTC_RXBUF_LOCK_DESTROY(_sc) spin_lock_destroy(&(_sc)->sc_rxbuflock)
#define    ATH_HTC_RXBUF_LOCK(_sc)         spin_lock_dpc(&(_sc)->sc_rxbuflock)
#define    ATH_HTC_RXBUF_UNLOCK(_sc)       spin_unlock_dpc(&(_sc)->sc_rxbuflock)
#endif
void ath_usb_suspend(ath_dev_t dev);
int ath_usb_set_tx(struct ath_softc *sc);
void ath_usb_rx_cleanup(ath_dev_t dev);
#define ATH_USB_TX_STOP(_osdev)    OS_Usb_Tx_Start_Stop(_osdev, AH_FALSE)
#define ATH_USB_TX_START(_osdev)    OS_Usb_Tx_Start_Stop(_osdev, AH_TRUE)


#else   /* ATH_USB */

#define ATH_USB_SET_INVALID(_sc, _val)

#define ATH_USB_TQUEUE_INIT(_sc, _func)
#define ATH_USB_TQUEUE_FREE(_sc)
#define ATH_HTC_TXTQUEUE_INIT(_sc, _func)     
#define ATH_HTC_TXTQUEUE_FREE(_sc)            
#define ATH_HTC_UAPSD_CREDITUPDATE_INIT(_sc, _func)     
#define ATH_HTC_UAPSD_CREDITUPDATE_FREE(_sc)           
#define ATH_HTC_UAPSD_CREDITUPDATE_SCHEDULE(_osdev)

#define ath_usb_suspend(dev)
#define ath_usb_set_tx(sc)                  (1)
//#define ath_usb_rx_cleanup(dev)
#define ATH_USB_TX_STOP(_osdev)
#define ATH_USB_TX_START(_osdev)
#endif  /* ATH_USB */

#endif /* ATH_USB_H */

