#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cf34 @ 0x0007cf34
 * public-name: flash_data_checksum_neg_sum
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_data_checksum_neg_sum              <= FUN_0007cf34 @ 0x0007cf34
 */
/* Reconstructed FUN_0007cf34 @ 0x7cf34 */
#include <stdint.h>
unsigned int flash_data_checksum_neg_sum(const unsigned char*data, unsigned int length, unsigned int padded_length) {
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
