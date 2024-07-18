
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

	.section	.isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
 	 .long 0x20002000
  	.long Reset_Handler
 	 .long 0x11
 	 .long 0x22
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	mytest

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


     /*uart, tx data */
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
.global mytest
.type mytest, %function
mytest:

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


/*
.type create_node, %function
create_node:


    str r0, [r1]     @ Store
    mov r0, #0


    mov r0, r1
    pop {lr}
    bx lr

.type add_node, %function
add_node:
    cmp r0, #0
    beq

add_node_empty:


*/












