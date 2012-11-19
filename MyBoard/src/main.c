/*
 * main.c
 *
 *  Created on: Jul 8, 2012
 *      Author: sanju
 */
#include <lpc214x.h>
#include<timer0.h>
#include <asm.h>
uint8_t count=0;
void wait(int val)
{
  unsigned long i;
  i =val + timeval;
  while(timeval < i);
  count++;
  if(count ==16)
    uninstallInterrupt(0,TIMER0_INT);
}
int main()
{
  IODIR0 =(1<<21);
   enableIRQ();
   init_timer();
  // setUpEINT();
 //  IOSET0=(1<<21);
   while(1)
   {
     IOCLR0=(1<<21);
     wait(50);
     IOSET0=(1<<21);
     wait(50);
   }
  return 0;
}

