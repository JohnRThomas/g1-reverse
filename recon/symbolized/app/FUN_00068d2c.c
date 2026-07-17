#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00068d2c @ 0x00068d2c
 * public-name: FUN_00068d2c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ldexpf                                   <= FUN_00086976 @ 0x00086976
 */
/* Full reconstruction FUN_00068d2c @ 0x68d2c, exact extent 98 bytes. */
#include <stdint.h>
extern float ldexpf(float,int32_t);
void FUN_00068d2c(uint8_t *state,const uint8_t *input,int stride){
 unsigned lanes=state[2]+1u;if(state[2]==4)lanes=6;
 int16_t *pcm=(int16_t*)(uintptr_t)(*(uint32_t*)(state+0x4a0));
 float *scaled=(float*)(uintptr_t)(*(uint32_t*)(state+0x4a4));
 int16_t *end=pcm+(state[0]+3u)*lanes*20u;
 do{
  int32_t sample=(int32_t)(((uint32_t)input[1]<<16)|((uint32_t)input[0]<<8)|((uint32_t)input[2]<<24));
  *pcm++=(int16_t)(sample>>16);
  *scaled++=ldexpf((float)sample,-16);
  input+=stride*3;
 }while(pcm!=end);
}
