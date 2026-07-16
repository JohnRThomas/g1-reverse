/* net-core FUN_010091f8 @ 0x010091f8 */
#include <stdint.h>
typedef uint32_t (*callback4_t)(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t FUN_010091f8(uint32_t a,uint32_t b,uint32_t c,uint32_t d){
  callback4_t fn=*(callback4_t volatile*)0x21000a64u; return fn(a,b,c,d);
}
