#include "RELAY.H"
#define RELAY_NUM 3

typedef struct
{
	u8 state;
}Relay;

Relay relay[RELAY_NUM] ;
bit setRelay(u8 RELAY)
{
	relay[RELAY].state=ON;
	return 1;
}
bit unSetRelay(u8 RELAY)
{
	relay[RELAY].state=OFF;
  return 1;
}
void relay_Init(void)
{
	
}
