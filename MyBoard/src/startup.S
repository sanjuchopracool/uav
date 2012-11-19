   .code 32  @means we are using arm mode not the thumb
   .align 4
.set IODIR0  ,0xE0028008
.set IOSET0  ,0xE0028004
.set IOCLR0  ,0xE002800c
.set LED     ,0x00200000

.equ  I_BIT, 0x80               @when I bit is set, IRQ is disabled
.equ  F_BIT, 0x40               @ when F bit is set, FIQ is disabled
/*
Set the modes of processro i need only irq and sys modes
*/
.set USR_MODE  ,0x10
.set FIQ_MODE  ,0x11
.set IRQ_MODE  ,0x12
.set SVC_MODE  ,0x13
.set ABRT_MODE ,0x17
.set UND_MODE  ,0x1B
.set SYS_MODE  ,0x1F

/*
set the stack sizes
*/
.set UND_STACK  ,0x08
.set IRQ_STACK  ,0x80
.set FIQ_STACK  ,0x08
.set SVC_STACK  ,0x08
.set ABRT_STACK  ,0x08
.set USR_STACK  ,0x400

.section "vectors"
reset:	b  start	@jump to start
undef: 	b     undef
swi:    b     swi
pabt:   b     pabt
dabt:   b     dabt
        nop
irq:   ldr   pc,[pc,#-0xFF0]            
fiq:    b    error
	.text
start:
	@@copy data to ram
	LDR	 	r0,=flash_sdata   @start of ram data in flash
	LDR		r1,=ram_sdata		@address of ram
	LDR		r2,=data_size

	@@handle zero data size
	CMP 	r2,#0
	BEQ		init_bss	@@ branch if equal to  either jump to init_bss

copy:

	LDRB	r4,[r0],#1    	@ r4 =mem[r0++]
	STRB	r4,[r1],#1		@ mem[r1++]=r4
	SUBS	r2,r2,#1		@ r2-- ; and update the flags
	BNE		copy			@branch ifnot equal to zero

init_bss:
	@@copy .bssto ram
	LDR	 	r0,=sbss   @start of bss data in flash
	LDR		r1,=ebss		@address of ram
	LDR		r2,=bss_size

	@@handle zero data size
	CMP 	r2,#0
	BEQ		init_stack	@@ branch if equal to  either jumpto init_stack

	MOV 	r4,#0

zero:
	@@make all bss data zero
	@LDRB	r4,[r0],#1    	@ r4 =mem[r0++]
	STRB	r4,[r0],#1		@ mem[r1++]=r4
	SUBS	r2,r2,#1		@ r2-- ; and update the flags
	BNE		zero			@branch ifnot equal to zero

init_stack:
        @@ Initialize the stack pointer
        @change ti irq mode  ,disable interrupt,set stack pointer
        LDR  r0 ,=0x40008000
        MSR  CPSR_c ,#IRQ_MODE|I_BIT|F_BIT
        MOV sp,r0 
        SUB r0,r0,#IRQ_STACK
        
        @change ti fiq mode  ,disable interrupt,set stack pointer
        MSR  CPSR_c ,#FIQ_MODE|I_BIT|F_BIT
        MOV sp,r0 
        SUB r0,r0,#FIQ_STACK
        
        @change ti svc mode  ,disable interrupt,set stack pointer
        MSR  CPSR_c ,#SVC_MODE|I_BIT|F_BIT
        MOV sp,r0 
        SUB r0,r0,#SVC_STACK
        
        @change ti abort mode  ,disable interrupt,set stack pointer
        MSR  CPSR_c ,#ABRT_MODE|I_BIT|F_BIT
        MOV sp,r0 
        SUB r0,r0,#ABRT_STACK
        
        @change ti undefined  mode  ,disable interrupt,set stack pointer
        MSR  CPSR_c ,#UND_MODE|I_BIT|F_BIT
        MOV sp,r0 
        SUB r0,r0,#UND_STACK

        @come back to system mode and set stack pointer
        MSR  CPSR_c ,#USR_MODE
        MOV sp,r0    @because we use full descending stack first it will decrement and store val
/*
Branch to c codes first go to the low level initialization so that clock , peripheral clock and MAM can se configured
*/
								 
								 
        bl    lowLevelInit     @low level initialization
        bl    main 

stop:   b     stop
@@This is how we can call assembly function in c 
  .global    wait_asm
wait_asm:
	LDR  r3 , =0x78B00     @ for c function only r1,r0,r2,r3 can be usedas argument
loop: 
	SUBS r3 ,r3 ,#1 
	BNE  loop
	MOV pc ,lr  
	
	.global error
error:
	LDR  r0 ,=LED
	LDR  r1 ,=IODIR0
	STR  r0,[r1]
main_asm:
	LDR  r1 ,=IOSET0
	STR  r0,[r1]
	bl wait_asm
	LDR  r1 ,=IOCLR0
	STR  r0,[r1]
	bl wait_asm
	b main_asm
	
    .global enableIRQ
enableIRQ:
	MRS r0,CPSR
	BIC  r0,r0,#I_BIT|F_BIT      @only irq 
	MSR CPSR ,r0
	MOV pc,lr
	    .global disableIRQ
disableIRQ:
	MRS r0,CPSR
	ORR  r0,r0,#I_BIT|F_BIT
	MSR CPSR ,r0
	MOV pc,lr