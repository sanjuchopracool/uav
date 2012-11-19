#include <lowlevel.h>
/**
 * @brief initialize the pll .vpbdiv and the mam 
 *
 * @return void
 **/
void lowLevelInit()
{
  PLL0CFG =PLLCFG_VAL ; ///set valueof p and m
  PLL0CON =0x00000001;  ///enable the pll
  
  ///everytime feed the pll with same sequence  
  PLL0FEED=0xAA;
  PLL0FEED=0x55;
  
  while(!(PLL0STAT & 0x400)); ///wait untill pll gets locked
  PLL0CON =0x03;     ///connect the pll
  
  //feed again
  PLL0FEED=0xAA;
  PLL0FEED=0x55;
  
  VPBDIV=VPBDIV_VAL;   ///set the vpb divider
  
  MAMCR =0;  ///disable MAM 
  MAMTIM=MAMTIM_VAL;   ///set MAM timing
  MAMCR=2;   ///enable mam completely
}
