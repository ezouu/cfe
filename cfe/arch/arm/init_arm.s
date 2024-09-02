
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
	.long 0x20002000       //0
	.long Reset_Handler    //1
	.long 0x11             //2
	.long 0x22             //3
	.word 0                //4
	.word 0                //5
	.word 0                //6
	.word 0                //7
	.word 0                //8
	.word 0                //9
	.word 0                //10
	.word 0                //11
	.word 0                //12
	.word 0                //13
	.word 0                //14
	.word SysTick_Handler  //15
	.word 0                //16
	.word 0                //17
	.word 0                //18
	.word 0                //19
	.word 0                //20
	.word 0                //21
	.word 0                //22
	.word 0                //23
	.word 0                //24
	.word 0                //25
	.word 0                //26
	.word 0                //27
	.word 0                //28
	.word 0                //29
	.word 0                //30
	.word 0                //31
	.word 0                //32
	.word 0                //33
	.word 0                //34
	.word 0                //35
	.word 0                //36
	.word 0                //37
	.word 0                //38
	.word 0                //39
	.word 0                //40
	.word 0                //41
	.word 0                //42
	.word 0                //43
	.word 0                //44
	.word 0                //45
	.word 0                //46
	.word 0                //47
	.word 0                //48
	.word 0                //49
	.word 0                //50
	.word 0                //51
	.word 0                //52
	.word USART1_IRQHandler //53

.section	.text.Reset_Handler
	.weak	Reset_Handler
	.type	Reset_Handler, %function



Reset_Handler:

 ldr   sp, =_estack    /* Set stack pointer */

/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0

1:
  cmp r2, r4
  beq 2f

  str  r3, [r2]
  adds r2, r2, #4
  b  1b

2:

  /* enable gpio clk from bus */
  ldr   r0, L__rcc_ahb2enr
  mov   r1, 0x2
  str   r1, [r0]

  /* enable hsi 16M OSC */
  ldr   r0, L__rcc_cr
  mov   r1, 0xf00
  str   r1, [r0]

  /* choose uart clk source as hsi 16Mhz */
  ldr   r0, L__rcc_ccipr
  mov   r1, 0x2
  str   r1, [r0]


  /* enable uart clk from bus */
  ldr   r0, L__rcc_apb2enr
  mov   r1, 0x4000
  str   r1, [r0]


  /*gpio, set as alt */
  ldr   r0, L__gpio_moder
  mov   r1, 0xa000
  str   r1, [r0]

   /*gpio, set as alt 7 */
  ldr   r0, L__gpio_afrl
  mov   r1, 0x77000000
  str   r1, [r0]


    /*uart, control, enable */
  ldr   r0, L__usart_cr1
  mov   r1, 0xd
  str   r1, [r0]

   /*uart, baudrate */
  ldr   r0, L__usart_brr
  mov   r1, 0x8b
  str   r1, [r0]

  ldr   r0, L__usart_isr
1:
  ldr   r1, [r0]
  and   r1,  1<<7
  cmp   r1,  1<<7
  bne   1b


     /*uart, tx data
  ldr   r0, L__usart_tdr
  mov   r1, 0x59
  str   r1, [r0]



  ldr   r0, L__usart_isr
1:
  ldr   r1, [r0]
  and   r1, 1<<7
  cmp   r1, 1<<7
  bne   1b

  ldr   r0, L__usart_tdr
  mov   r1, 0x58
  str   r1, [r0]
  mov r0, #1
  mov r1, #2

*/

     /*uart, tx data */
  ldr   r0, L__usart_tdr
  mov   r1, 0x0A  // Changed from 0x59 (Y) to 0x0A (newline)
  str   r1, [r0]

  ldr   r0, L__usart_isr
1:
  ldr   r1, [r0]
  and   r1, 1<<7
  cmp   r1, 1<<7
  bne   1b

  ldr   r0, L__usart_tdr
  mov   r1, 0x58  // This line can be kept as it is or changed based on what character you want to print next
  str   r1, [r0]
  mov r0, #1
  mov r1, #2


compute:
  add r2, r1, r0
  mov r0, r2
  add r1, r1, #1

  cmp r1, #101
  bne compute

//mov r4, 0x1234

//bl start

//mov r2, 0xAAAAAAAA
//bl start

//mov  r2, 0x8800
//bl start


bl cfe_main



start:
    ldr   r1, [r0]
    ands  r1, r1, 1<<7
    beq   start
    ldr   r0, L__usart_tdr
    mov   r1, #48
    str   r1, [r0]


stop:
    ldr   r1, [r0]
    ands  r1, r1, 1<<7
    beq   stop
    ldr   r0, L__usart_tdr
    mov   r1, #49
    str   r1, [r0]

/*
start:

push {r4}

  mov r0, r2
  mov r6, #28
  mov r4, #8
  b stop

stop:
  //ldr   r0, L__usart_tdr
  //mov
  //push {r0, r1 - r3}



  ldr   r0, L__usart_tdr
  mov r3, r2

  mov r3, r3, ROR r6
  sub r6, r6, #4
  and   r3, 0xf // 0xf
  cmp r3, #9
  bge greater

  cmp r4, 0
  beq exit


  add r3, r3, 0x30

    ldr   r0, L__usart_isr
1:
  ldr   r1, [r0]
  and   r1, 1<<7
  cmp   r1, 1<<7
  bne   1b

   ldr   r0, L__usart_tdr
  str   r3, [r0]
  // lsr r2, 4


  sub r4, r4, #1


  b stop

greater:
  add r3, r3, 0x37
  sub r4, r4, #1

  cmp r4, 0
  beq exit

    ldr   r0, L__usart_isr
1:
  ldr   r1, [r0]
  and   r1, 1<<7
  cmp   r1, 1<<7
  bne   1b

   ldr   r0, L__usart_tdr
  str r3, [r0]
  // lsr r2, 4
  b stop

exit:
  // exit code
      ldr   r0, L__usart_isr
1:
  ldr   r1, [r0]
  and   r1, 1<<7
  cmp   r1, 1<<7
  bne   1b

  ldr   r0, L__usart_tdr
  mov r7, 0xa
  str r7, [r0]
      ldr   r0, L__usart_isr

1:
  ldr   r1, [r0]
  and   r1, 1<<7
  cmp   r1, 1<<7
  bne   1b

  ldr   r0, L__usart_tdr
  mov r7, 0xd
  str r7, [r0]

  pop {r4}

  bx lr
*/

 L__rcc_cr:
       .long  0x40021000

 L__rcc_ahb2enr:
       .long  0x4002104c

 L__rcc_ccipr:
       .long  0x40021088

 L__rcc_apb2enr:
       .long  0x40021060

 L__gpio_moder:
       .long  0x48000400

 L__gpio_afrl:
       .long  0x48000420

 L__gpio_ospeedr:
       .long  0x48000408

 L__gpio_pupdr:
       .long  0x4800040c

 L__usart_cr1:
       .long  0x40013800

 L__usart_otyper:
       .long  0x40013804

 L__usart_brr:
       .long  0x4001380c

 L__usart_isr:
       .long  0x4001381c

 L__usart_tdr:
       .long  0x40013828

.section .text
.global SysTick_Handler
.type SysTick_Handler, %function
SysTick_Handler:

    push {r0}
    push {r1}
    push {r2}
    push {r3}
    push {r4}
    push {r5}
    push {r6}
    push {r7}
    push {r8}
    push {r9}
    push {r10}
    push {r11}
    push {r12}
    push {lr}


	bl mytest_1
//
    pop {lr}
    pop {r12}
    pop {r11}
    pop {r10}
    pop {r9}
    pop {r8}
    pop {r7}
    pop {r6}
    pop {r5}
    pop {r4}
    pop {r3}
    pop {r2}
    pop {r1}
    pop {r0}

    bx lr

.section .text
.global add_function

.type add_function, %function
add_function:

    add r0, r0, r1
    add r0, r0, r2
    add r0, r0, r3
    add r0, r0, r4

	//push r1
    ldr r1, [sp, #0]
    add r0, r0, r1


    ldr r1, [sp, #4]
    add r0, r0, r1
    bx lr


.section .text
.global USART1_IRQHandler
.type USART1_IRQHandler, %function
USART1_IRQHandler:

 	push {r0-r12, lr}


	bl mytest_1

    //ldr r0, =0x40013800      // USART1 base address
    //ldr r1, [r0, #0x1C]      // Read USART1 status register (SR)
    //ldr r2, [r0, #0x24]      // Read USART1 data register (DR)


	pop {r0-r12, lr}

    bx lr













