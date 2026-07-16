/* net-core FUN_01009204 @ 0x01009204 */
#include <stdint.h>
typedef uint32_t (*callback4_t)(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t FUN_01009204(uint32_t a,uint32_t b,uint32_t c,uint32_t d){
  callback4_t fn=*(callback4_t volatile*)0x21000a68u; return fn(a,b,c,d);
}
