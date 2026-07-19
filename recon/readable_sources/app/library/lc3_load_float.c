#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_lc3_bitstream_ctx__param_0372          [param_0372; library]
 * Raw function identity: 0x00068de8.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00068de8 @ 0x00068de8
 * public-name: lc3_load_float
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lc3_load_float                           <= FUN_00068de8 @ 0x00068de8
 *   ldexpf                                   <= FUN_00086976 @ 0x00086976
 */
/* Full reconstruction FUN_00068de8 @ 0x68de8, exact extent 86 bytes. */
#include <stdint.h>
extern float ldexpf(float,int32_t);
void lc3_load_float(uint8_t *state,const float *input,int stride){
 unsigned lanes=state[2]+1u;if(state[2]==4)lanes=6;
 float *scaled=(float*)(uintptr_t)(*(uint32_t*)(state+0x4a4));
 int16_t *pcm=(int16_t*)(uintptr_t)(*(uint32_t*)(state+0x4a0));
 float *end=scaled+(state[0]+3u)*lanes*20u;
 do{float value=ldexpf(*input,15);*scaled++=value;int32_t q=(int32_t)value;if(q>32767)q=32767;else if(q<-32768)q=-32768;*pcm++=(int16_t)q;input+=stride;}while(scaled!=end);
}
