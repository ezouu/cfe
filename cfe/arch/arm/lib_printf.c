/*  *********************************************************************
    *  Broadcom Common Firmware Environment (CFE)
    *
    *  simple printf				File: lib_printf.c
    *
    *  Author:  Mitch Lichtenberg
    *
    *  This module contains a very, very, very simple printf
    *  suitable for use in the boot ROM.
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003
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

#include <stdarg.h>
//#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#define NULL 0

/*  *********************************************************************
    *  Externs								*
    ********************************************************************* */

/*  *********************************************************************
    *  Globals								*
    ********************************************************************* */

static const char digits[17] = "0123456789ABCDEF";
static const char ldigits[17] = "0123456789abcdef";

int (*xprinthook)(const char *str) = NULL;

/*  *********************************************************************
    *  __atox(buf,num,radix,width)
    *
    *  Convert a number to a string
    *
    *  Input Parameters:
    *      buf - where to put characters
    *      num - number to convert
    *      radix - radix to convert number to (usually 10 or 16)
    *      width - width in characters
    *
    *  Return Value:
    *      number of digits placed in output buffer
    ********************************************************************* */
static int __atox(char *buf,unsigned int num,unsigned int radix,int width,
		     const char *digits)
{
    char buffer[16];
    char *op;
    int retval;

    op = &buffer[0];
    retval = 0;

    do {
	*op++ = digits[num % radix];
	retval++;
	num /= radix;
	} while (num != 0);

    if (width && (width > retval)) {
	width = width - retval;
	while (width) {
	    *op++ = '0';
	    retval++;
	    width--;
	    }
	}

    while (op != buffer) {
	op--;
	*buf++ = *op;
	}

    return retval;
}


/*  *********************************************************************
    *  __llatox(buf,num,radix,width)
    *
    *  Convert a long number to a string
    *
    *  Input Parameters:
    *      buf - where to put characters
    *      num - number to convert
    *      radix - radix to convert number to (usually 10 or 16)
    *      width - width in characters
    *
    *  Return Value:
    *      number of digits placed in output buffer
    ********************************************************************* */
static int __llatox(char *buf,unsigned long long num,unsigned int radix,
		    int width,const char *digits)
{
    char buffer[16];
    char *op;
    int retval;

    op = &buffer[0];
    retval = 0;

#if CPUCFG_REGS32
    /*
     * Hack: to avoid pulling in the helper library that isn't necessarily
     * compatible with PIC code, force radix to 16, use shifts and masks
     */
    do {
	*op++ = digits[num & 0x0F];
	retval++;
	num >>= 4;
	} while (num != 0);
#else
    do {
	*op++ = digits[num % radix];
	retval++;
	num /= radix;
	} while (num != 0);
#endif

    if (width && (width > retval)) {
	width = width - retval;
	while (width) {
	    *op++ = '0';
	    retval++;
	    width--;
	    }
	}

    while (op != buffer) {
	op--;
	*buf++ = *op;
	}

    return retval;
}

/*  *********************************************************************
    *  xvsprintf(outbuf,template,arglist)
    *
    *  Format a string into the output buffer
    *
    *  Input Parameters:
    *	   outbuf - output buffer
    *      template - template string
    *      arglist - parameters
    *
    *  Return Value:
    *      number of characters copied
    ********************************************************************* */
#define isdigit(x) (((x) >= '0') && ((x) <= '9'))
int xvsprintf(char *outbuf,const char *templat,va_list marker)
{
    char *optr;
    const char *iptr;
    unsigned char *tmpptr;
    long x;
    unsigned long ux;
    unsigned long long ulx;
    int i;
    long long ll;
    int leadingzero;
    int leadingnegsign;
    int islong;
    int width;
    int width2 = 0;
    int hashash = 0;

    optr = outbuf;
    iptr = templat;

    while (*iptr) {
	if (*iptr != '%') {*optr++ = *iptr++; continue;}

	iptr++;

	if (*iptr == '#') { hashash = 1; iptr++; }
	if (*iptr == '-') {
	    leadingnegsign = 1;
	    iptr++;
	    }
	else leadingnegsign = 0;

	if (*iptr == '0') leadingzero = 1;
	else leadingzero = 0;

	width = 0;
	while (*iptr && isdigit(*iptr)) {
	    width += (*iptr - '0');
	    iptr++;
	    if (isdigit(*iptr)) width *= 10;
	    }
	if (*iptr == '.') {
	    iptr++;
	    width2 = 0;
	    while (*iptr && isdigit(*iptr)) {
		width2 += (*iptr - '0');
		iptr++;
		if (isdigit(*iptr)) width2 *= 10;
		}
	    }

	islong = 0;
	if (*iptr == 'l') { islong++; iptr++; }
	if (*iptr == 'l') { islong++; iptr++; }

	switch (*iptr) {
	    case 'I':
		tmpptr = (unsigned char *) va_arg(marker,unsigned char *);
		optr += __atox(optr,*tmpptr++,10,0,digits);
		*optr++ = '.';
		optr += __atox(optr,*tmpptr++,10,0,digits);
		*optr++ = '.';
		optr += __atox(optr,*tmpptr++,10,0,digits);
		*optr++ = '.';
		optr += __atox(optr,*tmpptr++,10,0,digits);
		break;
	    case 's':
		tmpptr = (unsigned char *) va_arg(marker,unsigned char *);
		if (!tmpptr) tmpptr = (unsigned char *) "(null)";
		if ((width == 0) & (width2 == 0)) {
		    while (*tmpptr) *optr++ = *tmpptr++;
		    break;
		    }
		while (width && *tmpptr) {
		    *optr++ = *tmpptr++;
		    width--;
		    }
		while (width) {
		    *optr++ = ' ';
		    width--;
		    }
		break;
	    case 'a':
		tmpptr = (unsigned char *) va_arg(marker,unsigned char *);
		for (x = 0; x < 5; x++) {
		    optr += __atox(optr,*tmpptr++,16,2,digits);
		    *optr++ = '-';
		    }
		optr += __atox(optr,*tmpptr++,16,2,digits);
		break;
	    case 'd':
		switch (islong) {
		    case 0:
		    case 1:
			i = va_arg(marker,int);
			if (i < 0) { *optr++='-'; i = -i;}
			optr += __atox(optr,i,10,width,digits);
			break;
		    case 2:
			ll = va_arg(marker,long long int);
			if (ll < 0) { *optr++='-'; ll = -ll;}
			optr += __llatox(optr,ll,10,width,digits);
			break;
		    }
		break;
	    case 'u':
		switch (islong) {
		    case 0:
		    case 1:
			ux = va_arg(marker,unsigned int);
			optr += __atox(optr,ux,10,width,digits);
			break;
		    case 2:
			ulx = va_arg(marker,unsigned long long);
			optr += __llatox(optr,ulx,10,width,digits);
			break;
		    }
		break;
	    case 'X':
	    case 'x':
		switch (islong) {
		    case 0:
		    case 1:
			ux = va_arg(marker,unsigned int);
			optr += __atox(optr,ux,16,width,
				       (*iptr == 'X') ? digits : ldigits);
			break;
		    case 2:
			ulx = va_arg(marker,unsigned long long);
			optr += __llatox(optr,ulx,16,width,
				       (*iptr == 'X') ? digits : ldigits);
			break;
		    }
		break;
	    case 'p':
	    case 'P':
#ifdef __long64
		lx = va_arg(marker,long long);
		optr += __llatox(optr,lx,16,16,
				 (*iptr == 'P') ? digits : ldigits);
#else
		x = va_arg(marker,long);
		optr += __atox(optr,x,16,8,
			       (*iptr == 'P') ? digits : ldigits);
#endif
		break;
	    case 'w':
		x = va_arg(marker,unsigned int);
	        x &= 0x0000FFFF;
		optr += __atox(optr,x,16,4,digits);
		break;
	    case 'b':
		x = va_arg(marker,unsigned int);
	        x &= 0x0000FF;
		optr += __atox(optr,x,16,2,digits);
		break;
	    case 'Z':
		x = va_arg(marker,unsigned int);
		tmpptr = va_arg(marker,unsigned char *);
		while (x) {
		    optr += __atox(optr,*tmpptr++,16,2,digits);
		    x--;
		    }
		break;
	    case 'c':
		x = va_arg(marker, int);
		*optr++ = x & 0xff;
		break;

	    default:
		*optr++ = *iptr;
		break;
	    }
	iptr++;
	}

 //   *optr++ = '\r';
 //   *optr++ = '\n';
    *optr = '\0';

    return (optr - outbuf);
}


/*  *********************************************************************
    *  xsprintf(buf,template,params..)
    *
    *  format messages from template into a buffer.
    *
    *  Input Parameters:
    *      buf - output buffer
    *      template - template string
    *      params... parameters
    *
    *  Return Value:
    *      number of bytes copied to buffer
    ********************************************************************* */
int xsprintf(char *buf,const char *templat,...)
{
    va_list marker;
    int count;

    va_start(marker,templat);
    count = xvsprintf(buf,templat,marker);
    va_end(marker);

    return count;
}

/*  *********************************************************************
    *  xprintf(template,...)
    *
    *  A miniature printf.
    *
    *      %a - Ethernet address (16 bytes)
    *      %s - unpacked string, null terminated
    *      %x - hex word (machine size)
    *      %w - hex word (16 bits)
    *      %b - hex byte (8 bits)
    *      %Z - buffer (put length first, then buffer address)
    *
    *  Return value:
    *  	   number of bytes written
    ********************************************************************* */

int printf(const char *templat,...)
{
    va_list marker;
    int count;
    char buffer[512];

    va_start(marker,templat);
    count = xvsprintf(buffer,templat,marker);
    va_end(marker);


    for(int i = 0; i< count; i++){
    	putc(buffer[i]);
    }

    putc('\r');
    putc('\n');

    return count;
}


int xvprintf(const char *templat,va_list marker)
{
    int count;
    char buffer[512];

    count = xvsprintf(buffer,templat,marker);

    if (xprinthook) (*xprinthook)(buffer);

    return count;
}

void putstring(char* str)
{
	for(int i = 0; i< strlen(str); i++)
		putc(*str++);
}


void putc(char c) {
    volatile uint32_t *usart_isr = (volatile uint32_t *)(0x40013800 + 0x1C);
    volatile uint32_t *usart_tdr = (volatile uint32_t *)(0x40013800 + 0x28);

    while((*usart_isr & (1 << 7)) == 0);


    *usart_tdr = c;
}

void puts(const char *templat,...) {
    printf(templat);
}

void putchar(char c) {
    volatile uint32_t *usart_isr = (volatile uint32_t *)(0x40013800 + 0x1C);
    volatile uint32_t *usart_tdr = (volatile uint32_t *)(0x40013800 + 0x28);

    while((*usart_isr & (1 << 7)) == 0);


    *usart_tdr = c;
}


#if 0

static int ui_cmd_I2C(ui_cmdline_t *cmd, int argc, char *argv[])
{

    *(volatile uint32_t *)(0x40021060) = 0x4001; // __HAL_RCC_SYSCFG_CLK_ENABLE();

    *(volatile uint32_t *)(0x40021058) = 0x10000000;//__HAL_RCC_PWR_CLK_ENABLE();


	*(volatile uint32_t *)(0x40021088) = 0; //RCC i2c clock selection

    *(volatile uint32_t *)(0x40007004) = 0x200;   // PWR_CR2 enable

    *(volatile uint32_t *)(0x4002104C) = 0x20ff;    // GPIOG_CLK_ENABLE

    *(volatile uint32_t *)(0x40021058) = 0x32200000;


    *(volatile uint32_t *)(0x48001808) = 0xc3c0fff; //GPIOx_OSPEEDR
    *(volatile uint32_t *)(0x48001804) = 0x2000; //GPIO port output type register (GPIOx_OTYPER)
    *(volatile uint32_t *)(0x4800180C) = 0x4000000; //GPIOG_PUPDR

    *(volatile uint32_t *)(0x48001824) = 0x400cc0;// Configure Alternate function mapped with the current IO
    *(volatile uint32_t *)(0x48001800) = 0x3bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)
    *(volatile uint32_t *)(0x48001808) = 0x3c3c0fff;  // Configure the IO Speed */
    *(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER
    *(volatile uint32_t *)(0x4800082C) = 0x4000000; // activate pull up or pull down GPIO_PUPDR

    *(volatile uint32_t *)(0x48001824) = 0x4400cc0;// Configure Alternate function mapped with the current IO
    *(volatile uint32_t *)(0x48001800) = 0x2bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)


    *(volatile uint32_t *)(0x48001808) = 0x3c3c0fff;  /* Configure the IO Speed */
    *(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER
    *(volatile uint32_t *)(0x4800082C) = 0x0; /* activate pull up or pull down GPIO_PUPDR */


    //*(volatile uint32_t *)(0x4800082C) = 1; /* Configure the IO Output Type */
    //*(volatile uint32_t *)(0x48000800) = 0xFFFE93EF; /* Configure IO Direction mode*/


    //*(volatile uint32_t *)(0x4800002C) = 32;
    //*(volatile uint32_t *)(0x48000000) = 0xACFF00FF;


    *(volatile uint8_t *)(0x48001841) = 0x24; //hi2c->State = HAL_I2C_STATE_BUSY;



	*(volatile uint32_t *)(0x40005400) = 0; //Disable the selected I2C peripheral
	*(volatile uint32_t *)(0x40005410) = 0x20303E5D; //Configure I2Cx: Frequency range
	*(volatile uint32_t *)(0x40005408) = 0; //I2Cx OAR1 Configuration
	*(volatile uint32_t *)(0x40005408) = 0x8000; //ack own address1 mode

	*(volatile uint32_t *)(0x40005404) = 0; //Clear the I2C ADD10 bit
	*(volatile uint32_t *)(0x4000540C) = 0; //I2Cx OAR2 Configuration
	*(volatile uint32_t *)(0x40005400) = 0; //Configure I2Cx: Generalcall and NoStretch mode
	*(volatile uint32_t *)(0x40005400) = 1; //Enable the selected I2C peripheral





// transmit
	*(volatile uint32_t *)(0x40005400) = 0; //I2C_CR1, clear
	*(volatile uint32_t *)(0x40005410) = 0x20303e5d; //595, timing
	*(volatile uint32_t *)(0x40005408) = 0; //595, OAR1
	*(volatile uint32_t *)(0x40005408) = 0x8000;
	*(volatile uint32_t *)(0x40005404) = 0; //616, CR2
	*(volatile uint32_t *)(0x40004404) = 0x2008000; //618, auto end, bit 15, NACK
	*(volatile uint32_t *)(0x4000540C) = 0;//623,  OAR2

	*(volatile uint32_t *)(0x40005400) = 1;//634, peripheral enable bit 0
	*(volatile uint32_t *)(0x40005428) = 2;//1162, TX reg,
	*(volatile uint32_t *)(0x40005404) = 0x2012082; //7217,      82 device address

	//receive

	uint32_t temp = 0; //I2C_ISR STOPF: STOP detection flag
	while(((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0){
	}

	*(volatile uint32_t *)(0x40005404) = 0x2012482; //7217 update CR2 register */

	uint32_t busy = 0; //I2C_ISR BUSY: BUSY detection flag
	while(((busy = *(volatile uint32_t *)(0x40005400)) & 0x8000) == 1){
	}

	uint32_t RXNE_BUSY = 0; //RXNE: Receive data register
	while(((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0){
	}


	/*
	 * corrections for printing function
	 */
	*(volatile uint32_t *)(0x40021088) = 0x2;


    uint32_t received_data = *(volatile uint32_t *)(0x40005424);
    printf("data");
    printf("Received data: 0x%08X\n", received_data);


    return 0;
}
#endif

