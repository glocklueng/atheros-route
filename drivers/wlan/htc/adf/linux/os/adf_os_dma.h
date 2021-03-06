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

#ifndef ADF_CMN_OS_DMA_H
#define ADF_CMN_OS_DMA_H

#include <adf_os_types.h>
#include <adf_os_mem.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/cache.h>
#include <asm/io.h>

#include <adf_os_types.h>
#include <adf_os_util.h>

/**
 * XXX:error handling
 * 
 * @brief allocate a DMA buffer mapped to local bus Direction
 *        doesnt matter, since this API is called at init time.
 *
 * @param size
 * @param coherent SMP_CACHE_BYTES
 * @param dmap
 * 
 * @return void*
 */
static inline void *
adf_os_dmamem_alloc(adf_os_device_t     osdev, 
                    size_t       size, 
                    a_bool_t            coherent, 
                    adf_os_dma_map_t   *dmap)
{
    void               *vaddr;
    adf_os_dma_map_t  lmap;

   lmap = kzalloc(sizeof(struct adf_os_dma_map), GFP_KERNEL);

   adf_os_assert(lmap);

   lmap->nsegs = 1;
   lmap->coherent = coherent;

   if(coherent)
       vaddr = dma_alloc_coherent(osdev->bdev, size, &lmap->seg[0].daddr, 
                                  GFP_ATOMIC);
   else
       vaddr = dma_alloc_noncoherent(osdev->bdev, size, &lmap->seg[0].daddr,
                                     GFP_ATOMIC);

   adf_os_assert(vaddr);

   lmap->seg[0].len = size;
   lmap->mapped = 1;

   (*dmap) = lmap;
   
   return vaddr;
}

/* 
 * Free a previously mapped DMA buffer 
 * Direction doesnt matter, since this API is called at closing time.
 */
static inline void
adf_os_dmamem_free(adf_os_device_t osdev, adf_os_size_t size,
                   a_bool_t coherent, void *vaddr, adf_os_dma_map_t dmap)
{
    adf_os_assert(dmap->mapped);

    if(coherent)
        dma_free_coherent(osdev->bdev, size, vaddr, dmap->seg[0].daddr);
    else
        dma_free_noncoherent(osdev->bdev, size, vaddr, dmap->seg[0].daddr);

    kfree(dmap);
}


#define adf_os_dmamem_map2addr(_dmap)    ((_dmap)->seg[0].daddr)

static inline void 
adf_os_dmamem_cache_sync(adf_os_device_t osdev, adf_os_dma_map_t dmap, 
                         adf_os_cache_sync_t sync)
{
    if(!dmap->coherent){
        dma_sync_single(osdev->bdev, dmap->seg[0].daddr, dmap->seg[0].len,
                        DMA_BIDIRECTIONAL);
    }
}

static inline adf_os_size_t
adf_os_cache_line_size(void)
{
    return SMP_CACHE_BYTES;
}


#endif /*_ADF_CMN_OS_DMA_PVT_H*/
