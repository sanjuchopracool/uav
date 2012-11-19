#ifndef __IRQ_H 
#define __IRQ_H
#include <type.h>

#define	WDT_INT			0
#define SWI_INT			1
#define ARM_CORE0_INT		2
#define	ARM_CORE1_INT		3
#define	TIMER0_INT		4
#define TIMER1_INT		5
#define UART0_INT		6
#define	UART1_INT		7
#define	PWM0_INT		8
#define I2C0_INT		9
#define SPI0_INT		10
#define	SPI1_INT		11
#define	PLL_INT			12
#define RTC_INT			13
#define EINT0_INT		14
#define EINT1_INT		15
#define EINT2_INT		16
#define EINT3_INT		17
#define	ADC0_INT		18
#define I2C1_INT		19
#define BOD_INT			20
#define ADC1_INT		21
#define USB_INT			22
#define IRQ_SLOT_EN		0x20	/* bit 5 in Vector control register */

#define VIC_BASE_ADDR	0xFFFFF000
#define VECT_ADDR_INDEX	0x100
#define VECT_CNTL_INDEX 0x200

extern void installInterrupt(uint8_t irqPriority, uint8_t interrupt, void* irqHandler);
extern void uninstallInterrupt(uint8_t irqPriority, uint8_t interrupt);
#endif /* end __IRQ_H */