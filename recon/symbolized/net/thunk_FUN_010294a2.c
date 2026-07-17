#include "g1_net_symbols.h"
/* net-core thunk_FUN_010294a2 @ 0x01026842: exact tail alias of FUN_010294a2. */
#include <stdint.h>
extern uint32_t FUN_010294a2(volatile uint16_t*,volatile uint16_t*);
uint32_t thunk_FUN_010294a2(volatile uint16_t *a,volatile uint16_t *b){return FUN_010294a2(a,b);}
