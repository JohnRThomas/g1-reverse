/* readable reconstruction; identity: FUN_00068d90 @ 0x00068d90
 * public-name: lc3_load_s24
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_load_s24                             <= FUN_00068d90 @ 0x00068d90
 *   ldexpf                                   <= FUN_00086976 @ 0x00086976
 */
/* Full reconstruction FUN_00068d90 @ 0x68d90, exact extent 88 bytes. */
#include <stdint.h>
extern float ldexpf(float,int32_t);
void lc3_load_s24(uint8_t *state,const int32_t *input,int stride){
 unsigned lanes=state[2]+1u;if(state[2]==4)lanes=6;
 int16_t *pcm=(int16_t*)(uintptr_t)(*(uint32_t*)(state+0x4a0));
 float *scaled=(float*)(uintptr_t)(*(uint32_t*)(state+0x4a4));
 int16_t *end=pcm+(state[0]+3u)*lanes*20u;
 do{int32_t sample=*input;*pcm++=(int16_t)(sample>>8);*scaled++=ldexpf((float)sample,-8);input+=stride;}while(pcm!=end);
}
