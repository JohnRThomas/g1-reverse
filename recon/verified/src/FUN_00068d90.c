/* Full reconstruction FUN_00068d90 @ 0x68d90, exact extent 88 bytes. */
#include <stdint.h>
extern float FUN_00086976(float,int32_t);
void FUN_00068d90(uint8_t *state,const int32_t *input,int stride){
 unsigned lanes=state[2]+1u;if(state[2]==4)lanes=6;
 int16_t *pcm=(int16_t*)(uintptr_t)(*(uint32_t*)(state+0x4a0));
 float *scaled=(float*)(uintptr_t)(*(uint32_t*)(state+0x4a4));
 int16_t *end=pcm+(state[0]+3u)*lanes*20u;
 do{int32_t sample=*input;*pcm++=(int16_t)(sample>>8);*scaled++=FUN_00086976((float)sample,-8);input+=stride;}while(pcm!=end);
}
