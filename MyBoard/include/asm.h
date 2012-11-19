#ifndef __ASM_H_
#define __ASM_H_


/**
 * @brief Simple assembly Wait Function
 *
 * @return void
 **/
extern void wait_asm();

extern void error();    ///this function is defined in assembly to indicate error

extern void enableIRQ(); ///this function is defined in assembly to enable interrupts
#endif  /*_ASM_H_*/