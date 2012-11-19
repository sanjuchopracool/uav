#include <lpc214x.h>
///mulitplier is set to 5 at 12 MHZ crystal and divider of pll 2
#define  PLLCFG_VAL  0x00000024

///set the calueof VPB DIVider main clock is at 60MHz so VPB will be at 30MHz

#define VPBDIV_VAL   0x00000002

#define MAMTIM_VAL   0x03; ///for above 40MHz this MAMTM 3 is ideal

///lowlevel initialization function
extern void lowLevelInit();  