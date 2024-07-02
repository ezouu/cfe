/*  *********************************************************************
    *  Broadcom Common Firmware Environment (CFE)
    *  
    *  Miscellaneous commands			File: ui_misccmds.c
    *  
    *  Some small but useful commands
    *  
    *  Author:  Mitch Lichtenberg
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


#include "cfe.h"
#include "ui_command.h"

static int ui_cmd_loop(ui_cmdline_t *cmd,int argc,char *argv[]);
static int ui_cmd_sleep(ui_cmdline_t *cmd,int argc,char *argv[]);
#ifdef _FUNCSIM_
static int ui_cmd_exit(ui_cmdline_t *cmd,int argc,char *argv[]);
#endif
static int ui_cmd_console(ui_cmdline_t *cmd,int argc,char *argv[]);
static int ui_cmd_display(ui_cmdline_t *cmd,int argc,char *argv[]);

static int ui_cmd_edit(ui_cmdline_t *cmd,int argc,char *argv[]);
static int ui_cmd_printten(ui_cmdline_t *cmd,int argc,char *argv[]);


static int ui_cmd_LED(ui_cmdline_t *cmd,int argc,char *argv[]);
static int ui_cmd_LEDB(ui_cmdline_t *cmd, int argc, char *argv[]);
static int ui_cmd_LEDO(ui_cmdline_t *cmd, int argc, char *argv[]) ;

static int ui_cmd_I2C(ui_cmdline_t *cmd, int argc, char *argv[]);


//static int ui_cmd_joystick(ui_cmdline_t *cmd, int argc, char *argv[]);


int ui_init_misccmds(void);

int ui_init_misccmds(void)
{

    cmd_addcmd("loop",
	       ui_cmd_loop,
	       NULL,
	       "Loop a command",
	       "loop \"command\" [-count=*]\n"
	       "The 'loop' command causes the specified command or list of commands\n"
	       "to be repeated 'count' times or forever, or until a character is typed",
	       "-count=*;Specifies number of iterations|"
	       "-forever;Loops forever");

    cmd_addcmd("sleep",
	       ui_cmd_sleep,
	       NULL,
	       "Wait for some period of time",
	       "sleep [time]\n"
	       "The 'sleep' command pauses CFE's execution for the specified number\n"
	       "of seconds.  Without any arguments, CFE will wait one second.\n",
	       "");

#ifdef _FUNCSIM_
    cmd_addcmd("exit",
	       ui_cmd_exit,
	       NULL,
	       "exit from the functional simulator",
	       "exit [n]\n\n"
	       "This command is useful only when running under the functional\n"
	       "simulator.   It causes the simulator to exit and return to the\n"
	       "operating system.  If specified, 'n' will be placed in $4 as a\n"
	       "return code.",
	       "");
#endif

    cmd_addcmd("set console",
	       ui_cmd_console,
	       NULL,
	       "Change the active console device",
	       "set console device-name\n\n"
	       "Changes the console device to the specified device name.  The console\n"
	       "must be a serial-style device.  Be careful not to change the console\n"
	       "to a device that is not connected!",
	       "");


    cmd_addcmd("display",
	       ui_cmd_display,
	       NULL,
	       "enter a address display <addr>",
	       "",
	       "");

    cmd_addcmd("edit",
	       ui_cmd_edit,
	       NULL,
	       "edit a specific addr edit <addr> <newvalue> ",
	       "",
	       "");
    cmd_addcmd("printten",
	       ui_cmd_printten,
	       NULL,
	       "printten",
	       "",
	       "");

    cmd_addcmd("led",
	       ui_cmd_LED,
	       NULL,
	       "1 to turn on light",
	       "0 to turn off light",
	       "");

    cmd_addcmd("ledb",
	       ui_cmd_LEDB,
	       NULL,
	       "1 to turn on light",
	       "0 to turn off light",
	       "");
    /*cmd_addcmd("joystick",
	       ui_cmd_joystick,
	       NULL,
	       "1 to turn on light",
	       "0 to turn off light",
	       "");
     */
cmd_addcmd("ledo",
	       ui_cmd_LEDO,
	       NULL,
	       "1 to turn on light",
	       "0 to turn off light",
	       "");


cmd_addcmd("i2c",
	       ui_cmd_I2C,
	       NULL,
	       "1 to turn on light",
	       "0 to turn off light",
	       "");
    return 0;

}

static int ui_cmd_sleep(ui_cmdline_t *cmd,int argc,char *argv[])
{
    int seconds = 1;
    char *x;
    cfe_timer_t timer;

    if ((x = cmd_getarg(cmd,0))) seconds = atoi(x);

    TIMER_SET(timer,seconds*CFE_HZ);
    while (!TIMER_EXPIRED(timer)) {
	POLL();
	}

    return 0;
}

static int ui_cmd_loop(ui_cmdline_t *cmd,int argc,char *argv[])
{
    int count = 10;
    char *x;
    int res;
    int forever;

    if (cmd_sw_value(cmd,"-count",&x)) count = atoi(x);
    
    forever = cmd_sw_isset(cmd,"-forever");

    x = cmd_getarg(cmd,0);
    if (!x) return ui_showusage(cmd);

    res = 0;
    while (count || forever) {
	if (console_status()) break;
	res = ui_docommands(x);
	if (res != 0) break;
	count--;
	}

    return res;
}


#ifdef _FUNCSIM_
static int ui_cmd_exit(ui_cmdline_t *cmd,int argc,char *argv[])
{
    int val = 0;
    char *x;

    x = cmd_getarg(cmd,0);
    if (x) val = atoi(x);

    __asm __volatile ("move $4,%0 ; li $2,1 ; syscall 0xca" : "=r"(val));

    return -1;
}
#endif


static int ui_cmd_console(ui_cmdline_t *cmd,int argc,char *argv[])
{
    int res;
    char *dev;

    dev = cmd_getarg(cmd,0);
    if (!dev) return -1; 	/* XXX usage */

    res = cfe_getdevinfo(dev);
    if (res < 0) {
	printf("Device '%s' is not valid\n",dev);
	return CFE_ERR_DEVNOTFOUND;
	}

    if ((res & CFE_DEV_MASK) != CFE_DEV_SERIAL) {
	printf("Device '%s' is not the appropriate type to be a console\n",
		dev);
	return CFE_ERR_WRONGDEVTYPE;
	}

    cfe_set_console(dev);

    return 0;
}

static int ui_cmd_display(ui_cmdline_t *cmd,int argc,char *argv[])
{

    printf("Printing out Memory Contents:\n");
    char *addr_str;
    uint32_t address;
    volatile uint32_t *ptr;
    uint32_t value;


    addr_str = cmd_getarg(cmd, 0);


    address = atoi(addr_str);

    volatile uint32_t *ADDRESS_END = (uint32_t *)(address + 0x32);

	for (address; address <= ADDRESS_END; address= address + 0x4) {
	    ptr = (volatile uint32_t *)address;
	    value = *ptr;

		printf("0x%08X", address);
		printf("0x%08X\n", value);
	    }
/*
    printf("input address");
    printf("0x%08X", address);
    printf("input value");
    printf("0x%08X\n", value);





    volatile uint32_t *LPUART_ISR_START = (uint32_t *)(0x40013800);
	volatile uint32_t *LPUART_ISR_END = (uint32_t *)(0x40013800 + 0x32);


	for (volatile uint32_t *address = LPUART_ISR_START; address <= LPUART_ISR_END; address++) {
	        uint32_t value = *address;


	        printf("0x%08X", address);
	        printf("0x%08X\n", value);
	    }

*/
    return 0;
}


static int ui_cmd_edit(ui_cmdline_t *cmd,int argc,char *argv[])
{
	char *addr_str;
	char *value_str;
	uint32_t address;
	volatile uint32_t *ptr;
	uint32_t value;


	addr_str = cmd_getarg(cmd, 0);
	address = atoi(addr_str);

	value_str = cmd_getarg(cmd, 1);
	value = atoi(value_str);

    ptr = (volatile uint32_t *)address;
    *ptr = value;

    printf("new value:");

    printf("0x%08X", address);

    printf("0x%08X\n", value);


	return 0;
}

static int ui_cmd_printten(ui_cmdline_t *cmd,int argc,char *argv[])
{
	for(int i = 1; i< 10; i++){
		printf("hello world");
	}
	return 0;
}

#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800

#define PWR_BASE 0x40007000



void LED_Init(void) {

    *(volatile uint32_t *)(0x40007004) = 0x200;

    volatile uint32_t *RCC_AHB2ENR = (uint32_t *)(0x40021000 + 0x4C);
    *RCC_AHB2ENR = 0xf;


    volatile uint32_t *RCC_APB1ENR1 = (uint32_t *)(0x40021000 + 0x58);
    *RCC_APB1ENR1 |= (1 << 28);


    *(volatile uint32_t *)(GPIOC_BASE) = 0x4; // turn on


    *(volatile uint32_t *)(GPIOC_BASE + 0x14) = 0x0; // turn off
}

static int ui_cmd_LED(ui_cmdline_t *cmd, int argc, char *argv[])
{
    char *state_str;
    int state;

    state_str = cmd_getarg(cmd, 0);
    state = atoi(state_str);

    LED_Init();
    volatile uint32_t *GPIOC_ODR = (uint32_t *)(GPIOC_BASE + 0x14);

    if (state == 0) {

        *GPIOC_ODR |= (1 << 1);
        printf("LED is OFF\n");
    }
    if (state == 1) {

        *GPIOC_ODR &= ~(1 << 1);
        printf("LED is ON\n");
    }

    return 0;
}

void LEDB_Init(void) {

    *(volatile uint32_t *)(0x40007004) = 0x200;

    volatile uint32_t *RCC_AHB2ENR = (uint32_t *)(0x40021000 + 0x4C);
    *RCC_AHB2ENR = 0xf;

    volatile uint32_t *RCC_APB1ENR1 = (uint32_t *)(0x40021000 + 0x58);
    *RCC_APB1ENR1 |= (1 << 28);


    *(volatile uint32_t *)(GPIOB_BASE + 0)  |= 0x10; //

    *(volatile uint32_t *)(GPIOB_BASE + 0x14) = 0x0;
}


static int ui_cmd_LEDB(ui_cmdline_t *cmd, int argc, char *argv[]) {
    char *state_str;
    int state;

    state_str = cmd_getarg(cmd, 0);
    state = atoi(state_str);

    LEDB_Init();
    volatile uint32_t *GPIOB_ODR = (uint32_t *)(GPIOB_BASE + 0x14);

    if (state == 0) {
        *GPIOB_ODR |= (1 << 2);
        printf("LED1 is OFF\n");
    }
    if (state == 1) {
        *GPIOB_ODR &= ~(1 << 2);
        printf("LED1 is ON\n");
    }

    return 0;
}




static int ui_cmd_I2C(ui_cmdline_t *cmd, int argc, char *argv[])
{
    //uint8_t device_address = 0x82;
    //uint8_t data[2];

	*(volatile uint32_t *)(0x40005400) = 0; //590
	*(volatile uint32_t *)(0x40005410) = 540032605; //590
	*(volatile uint32_t *)(0x40005408) = 0; //595
	//*(volatile uint32_t *)(0x40005408) = 32768;
	*(volatile uint32_t *)(0x40005404) = 0; //616
	*(volatile uint32_t *)(0x40004404) = 0x20008000; //618
	*(volatile uint32_t *)(0x4000540C) = 0;//623
	*(volatile uint32_t *)(0x4000540C) = 0;//626
	*(volatile uint32_t *)(0x40005400) = 0;//631
	*(volatile uint32_t *)(0x40005400) = 1;//634
	*(volatile uint32_t *)(0x40005428) = 2;//1162
	*(volatile uint32_t *)(0x40005404) = 33628290; //7217
	*(volatile uint32_t *)(0x4000541C) = 32; //1230

	*(volatile uint32_t *)(0x40005404) = 33629314; //7217

	*(volatile uint32_t *)(0x40005428) = 2; //1162

	*(volatile uint32_t *)(0x40005404) = 33628290; //7217


	*(volatile uint32_t *)(0x4000541C) = 32; //1230







}



void I2C_Write(){


}
void LEDO_Init(void) {


}


static int ui_cmd_LEDO(ui_cmdline_t *cmd, int argc, char *argv[]) {

}



#define JOYSTICK_SEL GPIO0
#define JOYSTICK_DOWN
#define JOYSTICK_LEFT
#define JOYSTICK_RIGHT
#define IOEXPANDER2

static int ui_cmd_joystick(ui_cmdline_t *cmd, int argc, char *argv[])
{
    /*
     uint8_t joystick_state;

    // Initialize the IOExpander2 if necessary
    if (io_expander_init(IOEXPANDER2) != 0) {
        return -1;  // Initialization failed
    }

    // Read the joystick state from IOExpander2
    joystick_state = io_expander_read(IOEXPANDER2, JOYSTICK_SEL) << 0 |
                     io_expander_read(IOEXPANDER2, JOYSTICK_DOWN) << 1 |
                     io_expander_read(IOEXPANDER2, JOYSTICK_LEFT) << 2 |
                     io_expander_read(IOEXPANDER2, JOYSTICK_RIGHT) << 3 |
                     io_expander_read(IOEXPANDER2, JOYSTICK_UP) << 4;

    // Output the joystick state
    printf("Joystick state: 0x%02X\n", joystick_state);
    */

    return 0;
}

