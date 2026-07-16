/* Full reconstruction FUN_00068d2c @ 0x68d2c, exact extent 98 bytes. */
#include <stdint.h>
extern float FUN_00086976(float,int32_t);
void FUN_00068d2c(uint8_t *state,const uint8_t *input,int stride){
 unsigned lanes=state[2]+1u;if(state[2]==4)lanes=6;
 int16_t *pcm=(int16_t*)(uintptr_t)(*(uint32_t*)(state+0x4a0));
 float *scaled=(float*)(uintptr_t)(*(uint32_t*)(state+0x4a4));
 int16_t *end=pcm+(state[0]+3u)*lanes*20u;
 do{
  int32_t sample=(int32_t)(((uint32_t)input[1]<<16)|((uint32_t)input[0]<<8)|((uint32_t)input[2]<<24));
  *pcm++=(int16_t)(sample>>16);
  *scaled++=FUN_00086976((float)sample,-16);
  input+=stride*3;
 }while(pcm!=end);
}
