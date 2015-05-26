#include <lpc17xx.h>
#include "glcd.h"
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include "sw_timer.h"

int main(void)
{
SystemInit();
GLCD_Init();
GLCD_Clear(White);

GLCD_DisplayString(0, 0, 1, "Software Timer");
sw_timer(10);	
	
return 0;
}
