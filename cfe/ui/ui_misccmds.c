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


static int ui_cmd_write_I2C(ui_cmdline_t *cmd, int argc, char *argv[]);

static int ui_cmd_LED(ui_cmdline_t *cmd,int argc,char *argv[]);
static int ui_cmd_LEDG(ui_cmdline_t *cmd, int argc, char *argv[]);
static int ui_cmd_LEDO(ui_cmdline_t *cmd, int argc, char *argv[]);
static int ui_cmd_LEDB(ui_cmdline_t *cmd, int argc, char *argv[]);

static int ui_cmd_I2C(ui_cmdline_t *cmd, int argc, char *argv[]);


static int ui_cmd_joystick(ui_cmdline_t *cmd, int argc, char *argv[]);

static int display_I2C(ui_cmdline_t *cmd, int argc, char *argv[]);
static int ui_cmd_write_I2C_IO2(ui_cmdline_t *cmd, int argc, char *argv[]);
static int SysTick_Init(ui_cmdline_t *cmd, int argc, char *argv[]);

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

    cmd_addcmd("ledg",
	       ui_cmd_LEDG,
	       NULL,
	       "1 to turn on light",
	       "0 to turn off light",
	       "");
    cmd_addcmd("joystick",
	       ui_cmd_joystick,
	       NULL,
	       "1 to turn on light",
	       "0 to turn off light",
	       "");

	cmd_addcmd("ledo",
			   ui_cmd_LEDO,
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

	cmd_addcmd("i2c",
			   ui_cmd_I2C,
			   NULL,
			   "",
			   "",
			   "");

	cmd_addcmd("writei2c",
	           ui_cmd_write_I2C,
	           NULL,
	           "Write to an I2C device",
	           "write_i2c <reg_address> <value>\n"
	           "  <reg_address>  Register address to write to (hex)\n"
	           "  <value>        Value to write (hex)",
	           "");

	cmd_addcmd("displayi2c",
	           display_I2C,
	           NULL,
	           "Write to an I2C device",
	           "write_i2c <reg_address> <value>\n"
	           "  <reg_address>  Register address to write to (hex)\n"
	           "  <value>        Value to write (hex)",
	           "");

	cmd_addcmd("writei2cio2",
	           ui_cmd_write_I2C_IO2,
	           NULL,
	           "Write to an I2C device",
	           "write_i2c <reg_address> <value>\n"
	           "  <reg_address>  Register address to write to (hex)\n"
	           "  <value>        Value to write (hex)",
	           "");
	cmd_addcmd("systick",
			   SysTick_Init,
	           NULL,
	           "init systick",
	           ""
	           ""
	           "",
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

void LEDG_Init(void) {

    *(volatile uint32_t *)(0x40007004) = 0x200;

    volatile uint32_t *RCC_AHB2ENR = (uint32_t *)(0x40021000 + 0x4C);
    *RCC_AHB2ENR = 0xf;

    volatile uint32_t *RCC_APB1ENR1 = (uint32_t *)(0x40021000 + 0x58);
    *RCC_APB1ENR1 |= (1 << 28);


    *(volatile uint32_t *)(GPIOB_BASE + 0)  |= 0x10; //

    *(volatile uint32_t *)(GPIOB_BASE + 0x14) = 0x0;
}


static int ui_cmd_LEDG(ui_cmdline_t *cmd, int argc, char *argv[]) {
    char *state_str;
    int state;

    state_str = cmd_getarg(cmd, 0);
    state = atoi(state_str);

    LEDG_Init();
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


#define IOEXPANDER_ADDRESS 0x82  // I2C address of the IO expander
#define IOEXPANDER_LED2_PIN 0    // GPIO0 is used for LED2


static int ui_cmd_write_I2C(ui_cmdline_t *cmd, int argc, char *argv[])
{


    char *reg_input;
    char *val_input;

    int reg_address;
    int value_to_send;

    reg_input = cmd_getarg(cmd, 0);
    reg_address = atoi(reg_input);

    val_input  = cmd_getarg(cmd, 1);
    value_to_send = atoi(val_input);


    // Initialization and clock configuration
    I2C_Init_INIT();
    I2C_Init();

    // Write to I2C

	// Corrections for printing function
	//*(volatile uint32_t *)(0x40021088) = 0x2;

    //printf("Writing 0x%02X to register 0x%02X\n", value_to_send, reg_address);

    // RECorrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection
    uint32_t temp = 0;

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
   // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2022082; //7217,      82 device address


    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = value_to_send;
    // Wait for STOPF
     temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}



    //*(volatile uint32_t *)(0x40005404) |= 0x80000000; // Set STOP bit in I2C_CR2 to clear STOPF flag

    // Read back the written value to verify
	// Corrections for printing function
	//*(volatile uint32_t *)(0x40021088) = 0x2;

    //printf("Reading back register 0x%02X\n", reg_address);


    // RECorrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
      // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2012082; //7217,      82 device address

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

       // Wait for STOPF
	temp = 0;
	while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}


    *(volatile uint32_t *)(0x40005404) = 0x2012482; //7217 update CR2 register */

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);

	// Corrections for printing function
	*(volatile uint32_t *)(0x40021088) = 0x2;
	printf("Writing 0x%02X to register 0x%02X\n", value_to_send, reg_address);
    printf("Received data: 0x%08X\n", received_data);



    return 0;

}


void I2C_Init_INIT(void) {
    // Initialization and clock configuration



    *(volatile uint32_t *)(0x40021060) = 0x4001; // __HAL_RCC_SYSCFG_CLK_ENABLE();



    *(volatile uint32_t *)(0x40021058) = 0x10000000; // __HAL_RCC_PWR_CLK_ENABLE();

  //  *(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection

    *(volatile uint32_t *)(0x40007004) = 0x200; // PWR_CR2 enable


    *(volatile uint32_t *)(0x4002104C) = 0x20ff; // GPIOG_CLK_ENABLE


    *(volatile uint32_t *)(0x40021058) = 0x32200000;


    // GPIO configuration
    *(volatile uint32_t *)(0x48001808) = 0xc3c0fff; // GPIOx_OSPEEDR
    *(volatile uint32_t *)(0x48001804) = 0x2000; // GPIO port output type register (GPIOx_OTYPER)
    *(volatile uint32_t *)(0x4800180C) = 0x4000000; // GPIOG_PUPDR
    *(volatile uint32_t *)(0x48001824) = 0x400cc0; // Configure Alternate function mapped with the current IO
    *(volatile uint32_t *)(0x48001800) = 0x3bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)
    *(volatile uint32_t *)(0x48001808) = 0x3c3c0fff; // Configure the IO Speed
    *(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER
    *(volatile uint32_t *)(0x4800082C) = 0x4000000; // Activate pull up or pull down GPIO_PUPDR
    *(volatile uint32_t *)(0x48001824) = 0x4400cc0; // Configure Alternate function mapped with the current IO
    *(volatile uint32_t *)(0x48001800) = 0x2bebcaaa; // Configure IO Direction mode (Input, Output, Alternate or Analog)
    *(volatile uint32_t *)(0x48001808) = 0x3c3c0fff; // Configure the IO Speed
    *(volatile uint32_t *)(0x48001804) = 0x6000; // GPIO_OTYPER
    *(volatile uint32_t *)(0x4800082C) = 0x0; // Activate pull up or pull down GPIO_PUPDR
    *(volatile uint8_t *)(0x48001841) = 0x24; // hi2c->State = HAL_I2C_STATE_BUSY


    *(volatile uint32_t *)(0x40005400) = 0; // Disable the selected I2C peripheral
    *(volatile uint32_t *)(0x40005410) = 0x20303E5D; // Configure I2Cx: Frequency range
    *(volatile uint32_t *)(0x40005408) = 0; // I2Cx OAR1 Configuration
    *(volatile uint32_t *)(0x40005408) = 0x8000; // Ack own address1 mode
    *(volatile uint32_t *)(0x40005404) = 0; // Clear the I2C ADD10 bit
    *(volatile uint32_t *)(0x4000540C) = 0; // I2Cx OAR2 Configuration
    *(volatile uint32_t *)(0x40005400) = 0; // Configure I2Cx: Generalcall and NoStretch mode
    *(volatile uint32_t *)(0x40005400) = 1; // Enable the selected I2C peripheral

}


void I2C_Init(void) {



    // Transmit
    *(volatile uint32_t *)(0x40005400) = 0; // I2C_CR1, clear
    *(volatile uint32_t *)(0x40005410) = 0x20303e5d; // I2C timing configuration
    *(volatile uint32_t *)(0x40005408) = 0; // I2C OAR1 configuration
    *(volatile uint32_t *)(0x40005408) = 0x8000; // Ack own address1 mode
    *(volatile uint32_t *)(0x40005404) = 0; // I2C CR2 configuration
    *(volatile uint32_t *)(0x40004404) = 0x2008000; // Auto end, bit 15, NACK
    *(volatile uint32_t *)(0x4000540C) = 0; // I2C OAR2 configuration

    *(volatile uint32_t *)(0x40005400) = 1; // Enable the selected I2C peripheral
}

static int write_I2C(int reg_address, int value_to_send)
{

    I2C_Init();

    // Write to I2C

    // Corrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0x2;

    //printf("Writing 0x%02X to register 0x%02X", value_to_send, reg_address);

    // RECorrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection
    uint32_t temp = 0;

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2022082; // 7217, 82 device address

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = value_to_send;
    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    //*(volatile uint32_t *)(0x40005404) |= 0x80000000; // Set STOP bit in I2C_CR2 to clear STOPF flag

    // Read back the written value to verify
    // Corrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0x2;

    //printf("Reading back register 0x%02X", reg_address);

    // RECorrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2012082; // 7217, 82 device address

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    *(volatile uint32_t *)(0x40005404) = 0x2012482; // 7217 update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);

    // Corrections for printing function
	*(volatile uint32_t *)(0x40021088) = 0x2;
	printf("Writing 0x%02X to register 0x%02X\n", value_to_send, reg_address);
    printf("Received data: 0x%08X\n", received_data);



    return 0;
}

static int read_I2C(int reg_address)
{

    I2C_Init();
    uint32_t temp = 0;

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2012082; // 7217, 82 device address

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    *(volatile uint32_t *)(0x40005404) = 0x2012482; // 7217 update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);

    // Corrections for printing function
	*(volatile uint32_t *)(0x40021088) = 0x2;
    printf("Received data: 0x%08X\n", received_data);



    return received_data;
}
static int display_I2C(ui_cmdline_t *cmd, int argc, char *argv[]) {
    char *address;
    int reg_address;

    *address = cmd_getarg(cmd, 0);
    reg_address = atoi(*address);
    I2C_Init_INIT();
    I2C_Init();

    uint32_t temp = 0;

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    //*(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2012082; // 7217, 82 device address

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    *(volatile uint32_t *)(0x40005404) = 0x2012482; // 7217 update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);

    // Corrections for printing function
	*(volatile uint32_t *)(0x40021088) = 0x2;
    printf("Received data: 0x%08X\n", received_data);



    return 0;
}

static int ui_cmd_LEDO(ui_cmdline_t *cmd, int argc, char *argv[]) {
    char *state_str;
    int state;

    state_str = cmd_getarg(cmd, 0);
    state = atoi(state_str);
    I2C_Init_INIT();
    if (state == 1) { // turn on
        write_I2C(0x11, 0x1);
        write_I2C(0x17, 0x1);
        write_I2C(0x13, 0x1);
        printf("LEDs are ON\n");
    } else if (state == 0) { // turn off
        write_I2C(0x10, 0x1);
        printf("LEDs are OFF\n");
    }

    return 0;
}

static int ui_cmd_LEDB(ui_cmdline_t *cmd, int argc, char *argv[]) {
    char *state_str;
    int state;

    state_str = cmd_getarg(cmd, 0);
    state = atoi(state_str);
    I2C_Init_INIT();
    if (state == 1) { // turn on


    	write_I2C(0x11, 0x4);
        write_I2C(0x17, 0x4);
        write_I2C(0x13, 0x4);
        printf("Blue LED is ON\n");
    } else if (state == 0) { // turn off
        I2C_Init();

        // Disable Blue LED
        write_I2C(0x10, 0x4);
        printf("Blue LED is OFF\n");
    }

    return 0;
}


#define STMPE1600_I2C_ADDRESS
static int ui_cmd_write_I2C_IO2(ui_cmdline_t *cmd, int argc, char *argv[])
{
    char *address;
    int reg_address;

    address = cmd_getarg(cmd, 0);
    reg_address = atoi(address);
    I2C_Init_INIT();
    I2C_Init();
    uint32_t temp = 0;

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2012084; // 7217, 82 device address

    //while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    *(volatile uint32_t *)(0x40005404) = 0x2012484; // 7217 update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);

    // Corrections for printing function
	*(volatile uint32_t *)(0x40021088) = 0x2;
    printf("Received data: 0x%08X\n", received_data);



    return 0;
}

static int write_I2C_IO2(int reg_address, int value_to_send)
{

    I2C_Init();

    // Write to I2C

    // Corrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0x2;

    //printf("Writing 0x%02X to register 0x%02X", value_to_send, reg_address);

    // RECorrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection
    uint32_t temp = 0;

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2022084; // 7217, 82 device address

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = value_to_send;
    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    //*(volatile uint32_t *)(0x40005404) |= 0x80000000; // Set STOP bit in I2C_CR2 to clear STOPF flag

    // Read back the written value to verify
    // Corrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0x2;

    //printf("Reading back register 0x%02X", reg_address);

    // RECorrections for printing function
    //*(volatile uint32_t *)(0x40021088) = 0; // RCC I2C clock selection

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2012084; // 7217, 82 device address

    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    *(volatile uint32_t *)(0x40005404) = 0x2012484; // 7217 update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);

    // Corrections for printing function
	*(volatile uint32_t *)(0x40021088) = 0x2;
	printf("Writing 0x%02X to register 0x%02X\n", value_to_send, reg_address);
    printf("Received data: 0x%08X\n", received_data);



    return 0;
}

static int READ_I2C_IO2(int reg_address)
{
    I2C_Init();
    uint32_t temp = 0;

    *(volatile uint32_t *)(0x40005428) = reg_address; // Register address
    // *(volatile uint32_t *)(0x40005428) = value_to_send; // Data to send

    *(volatile uint32_t *)(0x40005404) = 0x2012084; // 7217, 82 device address

    //while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x1) == 0) {}

    // Wait for STOPF
    temp = 0;
    while (((temp = *(volatile uint32_t *)(0x40005418)) & 0x20) == 0) {}

    *(volatile uint32_t *)(0x40005404) = 0x2012484; // 7217 update CR2 register

    // Wait for RXNE
    uint32_t RXNE_BUSY = 0;
    while (((RXNE_BUSY = *(volatile uint32_t *)(0x40005418)) & 0x4) == 0) {}

    uint32_t received_data = *(volatile uint32_t *)(0x40005424);

    // Corrections for printing function
//	*(volatile uint32_t *)(0x40021088) = 0x2;
    //printf("Received data: 0x%08X\n", received_data);

    return received_data;
}


static int ui_cmd_joystick(ui_cmdline_t *cmd, int argc, char *argv[])
{
/*
    char *state_str;
    int state;

    state_str = cmd_getarg(cmd, 0);
    state = atoi(state_str);

*/



    // *(volatile uint32_t *)(0x40005404) = 0x12084;
	I2C_Init_INIT();
	//*(volatile uint32_t *)(0x40021088) = 0x2;


    while(1){

    	if((READ_I2C_IO2(0x10) & 1) == 0){
    		printf("SEL\r");
    		break;
    	}
    	if((READ_I2C_IO2(0x10) & 2) == 0){
    		printf("DOWN\r");
    	}
    	if((READ_I2C_IO2(0x10) & 4) == 0){
    		printf("LEFT\r");
    	}
    	if((READ_I2C_IO2(0x10) & 8) == 0){
    		printf("RIGHT\r");
    	}
    	if((READ_I2C_IO2(0x10) & 16) == 0){
    		printf("UP\r");
    	}

    }
    printf("joystick end");
/*
    if (state == 1) { // turn on
    	printf("down:");
    	READ_I2C_IO2(0x10);
    	printf("down:");
    	READ_I2C_IO2(0x10);
    	printf("down:");
    	READ_I2C_IO2(0x10);
    	printf("down:");
    	READ_I2C_IO2(0x10);
        //write_I2C_IO2(0x3, 0x20);
        //write_I2C_IO2(0x17, 0x1);
        //write_I2C_IO2(0x13, 0x1);
        //printf("LEDs are ON\n");
    } else if (state == 0) { // turn off
        write_I2C_IO2(0x0, 0x1);
        //printf("LEDs are OFF\n");
    }

*/
    return 0;
}


static int SysTick_Init(ui_cmdline_t *cmd, int argc, char *argv[]){

	 *(volatile uint32_t *)0xE000ED08 = 0x20000000; // vtor

    *(volatile uint32_t *)0xE000E010 = 0x7; // 00000111

    *(volatile uint32_t *)0xE000E014 = 1000000;

    *(volatile uint32_t *)0xE000E018 = 0;

    *(volatile uint32_t *)0xE000ED20 = 0;

    volatile uint32_t *ptr;
    uint32_t value;




    uint32_t address = 0xE000E018;


	while (1) {
	    ptr = (volatile uint32_t *)address;
	    value = *ptr;
		printf("0x%08X\n", value);
	    }


    return 0;
}


void SysTick_Handler() {
	//while(1);
}
