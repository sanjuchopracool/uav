#include <irq.h>
#include <lpc214x.h>
void installInterrupt(uint8_t irqPriority, uint8_t interrupt,void* irqHandler)
{
  ///find the vector address of that priority slot
    uint32_t* vect_addr =(uint32_t*)(VIC_BASE_ADDR + VECT_ADDR_INDEX + 4*irqPriority);
    uint32_t* vect_cntl= (uint32_t*)(VIC_BASE_ADDR + VECT_CNTL_INDEX + 4*irqPriority);
  
  ///set the value and enable it
  *vect_addr= (uint32_t)irqHandler;
  *vect_cntl= interrupt|IRQ_SLOT_EN;
  
  //enable the interrupt ,use or operator so that other interrupts are also enabled
  VICIntEnable |=(1 <<interrupt);
}
void uninstallInterrupt(uint8_t irqPriority, uint8_t interrupt)
{
  ///find the vector address of that priority slot
    uint32_t* vect_addr =(uint32_t*)(VIC_BASE_ADDR + VECT_ADDR_INDEX + 4*irqPriority);
    uint32_t* vect_cntl= (uint32_t*)(VIC_BASE_ADDR + VECT_CNTL_INDEX + 4*irqPriority);
  
  ///clear the value and disable  it
  *vect_addr=(uint32_t)NULL;
  *vect_cntl &= ~IRQ_SLOT_EN;
  
  //disable the interrupt ,use or operator so that other interrupts are also enabled
  VICIntEnClr |=(1 <<interrupt);
}