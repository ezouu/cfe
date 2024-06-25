/*
 * stm32_board.c
 *
 *  Created on: Jun 23, 2024
 *      Author:
 */

#include "cfe.h"

static void
stm32_uart_probe(cfe_driver_t *drv,
		    unsigned long probe_a, unsigned long probe_b,
		    void *probe_ptr);
static int stm32_uart_open(cfe_devctx_t *ctx);
static int stm32_uart_read(cfe_devctx_t *ctx,iocb_buffer_t *buffer);
static int stm32_uart_inpstat(cfe_devctx_t *ctx,iocb_inpstat_t *inpstat);
static int stm32_uart_write(cfe_devctx_t *ctx,iocb_buffer_t *buffer);

const static cfe_devdisp_t stm32_uart_dispatch = {
	stm32_uart_open,
	stm32_uart_read,
	stm32_uart_inpstat,
	stm32_uart_write

};


/* CFE Device Driver descriptor */

cfe_driver_t stm32_uart = {
    "STM32 UART",
    "uart",
    CFE_DEV_SERIAL,
    &stm32_uart_dispatch,
	stm32_uart_probe

};

static void
stm32_uart_probe(cfe_driver_t *drv,
		    unsigned long probe_a, unsigned long probe_b,
		    void *probe_ptr)
{
    cfe_attach(drv, NULL, NULL, NULL);
}

static int
stm32_uart_open(cfe_devctx_t *ctx) {

   return 0;
}


static int
stm32_uart_read(cfe_devctx_t *ctx, iocb_buffer_t *buffer)
{
    volatile uint32_t *LPUART_ISR = (uint32_t *)(0x40013800 + 0x1C);
    volatile uint32_t *LPUART_RDR = (uint32_t *)(0x40013800 + 0x24);
    char *ptr = buffer->buf_ptr;
    uint32_t len = buffer->buf_length;
    uint32_t read_len = 0;

    while (len > 0)
    {
        if (*LPUART_ISR & (1 << 5) )
        {
        	*ptr = (*LPUART_RDR);
        	len--;

        }
        else
        {
            break;
        }
    }
    buffer-> buf_retlen =  buffer->buf_length;


    return 0;
}
static int
stm32_uart_inpstat(cfe_devctx_t *ctx, iocb_inpstat_t *inpstat)
{

	volatile uint32_t *LPUART_ISR  = (volatile uint32_t *)(0x40013800 + 0x1C);


	if (*LPUART_ISR & (1 << 5))
	{
		inpstat->inp_status = 1;
	}
	else
	{
		inpstat->inp_status = 0;
	}

	return 0;
}

static int
stm32_uart_write(cfe_devctx_t *ctx, iocb_buffer_t *buffer)
{
    char* ptr = buffer->buf_ptr;
    uint32_t len = buffer->buf_length;
    for(int i =0; i< len; i++)
    	putchar(*ptr++);

    buffer->buf_retlen = len;
    return 0;
}

void board_init() {
	cfe_add_device(&stm32_uart, 0, 0, 0);
	cfe_set_console("uart0");
}
