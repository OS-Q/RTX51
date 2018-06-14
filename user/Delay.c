#include "Delay.h"
#include <intrins.h>
void Delay8us(void) //@24.000MHz
{
  unsigned char i;

  _nop_();
  _nop_();
  i = 45;
  while (--i)
    ;
}
void Delay88us(void) //@24.000MHz
{
  unsigned char i, j;

  i = 3;
  j = 10;
  do {
    while (--j)
      ;
  } while (--i);
}
