/*  *********************************************************************
    *  Broadcom Common Firmware Environment (CFE)
    *  
    *  Common SPI definitions			File: cfe_spi.c
    *  
    *  Driver common data structures for SPI devices.   The
    *  higher-level (device-specific) SPI drivers talk to this, and
    *  via these structures we end up at platform-specific SPI 
    *  handlers.
    *  
    *********************************************************************  
    *
    *  Copyright 2004
    *  Broadcom Corporation. All rights reserved.
    *  
    *  This software is furnished under license and may be used and 
    *  copied only in accordance with the following terms and 
    *  conditions.  Subject to these conditions, you may download, 
    *  copy, install, use, modify and distribute modified or unmodified 
    *  copies of this software in source and/or binary form.  No title 
    *  or ownership is transferred hereby.
    *  
    *  1) Any source code used, modified or distributed must reproduce 
    *     and retain this copyright notice and list of conditions 
    *     as they appear in the source file.
    *  
    *  2) No right is granted to use any trade name, trademark, or 
    *     logo of Broadcom Corporation.  The "Broadcom Corporation" 
    *     name may not be used to endorse or promote products derived 
    *     from this software without the prior written permission of 
    *     Broadcom Corporation.
    *  
    *  3) THIS SOFTWARE IS PROVIDED "AS-IS" AND ANY EXPRESS OR
    *     IMPLIED WARRANTIES, INCLUDING BUT NOT LIMITED TO, ANY IMPLIED
    *     WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
    *     PURPOSE, OR NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT 
    *     SHALL BROADCOM BE LIABLE FOR ANY DAMAGES WHATSOEVER, AND IN 
    *     PARTICULAR, BROADCOM SHALL NOT BE LIABLE FOR DIRECT, INDIRECT,
    *     INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
    *     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
    *     GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    *     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
    *     OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
    *     TORT (INCLUDING NEGLIGENCE OR OTHERWISE), EVEN IF ADVISED OF 
    *     THE POSSIBILITY OF SUCH DAMAGE.
    ********************************************************************* */

#include "lib_types.h"
#include "lib_malloc.h"
#include "lib_printf.h"

#include "cfe_error.h"

#include "cfe_spi.h"

/*  *********************************************************************
    *  Globals
    ********************************************************************* */

cfe_spi_channel_t *cfe_spi_channels[SPI_CHANNELS_MAX];

/*  *********************************************************************
    *  cfe_add_spi(ops,probe_a,probe_b)
    *  
    *  Add a SPI interface.
    *  
    *  Input parameters: 
    *  	   ops - pointer to low-level handlers
    *  	   probe_a,probe_b - specific to device driver, usually points at
    *  	       base address of device
    *  	   
    *  Return value:
    *  	   new channel number (0 is first channel)
    *  	   <0 if error occured
    ********************************************************************* */

int cfe_add_spi(cfe_spi_t *ops,uint64_t probe_a,uint64_t probe_b)
{
    int idx;

    for (idx = 0; idx < SPI_CHANNELS_MAX; idx++) {
	if (cfe_spi_channels[idx] == NULL) break;
	}
    if (idx == SPI_CHANNELS_MAX) return CFE_ERR_NOHANDLES;

    cfe_spi_channels[idx] = ops->attach(ops,probe_a,probe_b);

    if (cfe_spi_channels[idx] == NULL) return CFE_ERR_NOMEM;

    SPI_INIT(cfe_spi_channels[idx]);

    return idx;
}

