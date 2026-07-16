/* Reconstructed FUN_0007cf34 @ 0x7cf34 */
#include <stdint.h>
uint32_t FUN_0007cf34(const uint8_t *data,uint32_t length,uint32_t padded_length){
  uint32_t sum=0,offset=0;
  for(uint32_t pos=0;pos<padded_length;pos+=4){
    uint32_t word=UINT32_MAX;
    if(pos<length){
      word=((uint32_t)data[offset]<<24)|((uint32_t)data[offset+1]<<16)|
           ((uint32_t)data[offset+2]<<8)|data[offset+3];
      offset+=4;
    }
    sum+=word;
  }
  return 0u-sum;
}
