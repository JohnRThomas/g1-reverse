#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cab4 @ 0x0007cab4
 * public-name: quaternion_to_euler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   asinf                                    <= FUN_00075c2c @ 0x00075c2c
 *   quaternion_to_euler                      <= FUN_0007cab4 @ 0x0007cab4
 */
/* Reconstructed FUN_0007cab4 @ 0x7cab4 */
#include <stdint.h>
extern float thunk_FUN_00076154(float y,float x);
extern float asinf(float value);
void quaternion_to_euler(unsigned long object) {
  float q1=*(float*)(object+0x10),q2=*(float*)(object+0x14);
  float q3=*(float*)(object+0x18),q0=*(float*)(object+0x0c);
  *(volatile float *)(object+0x2c)=thunk_FUN_00076154(q2*q3+q0*q1,(0.5f-q1*q1)-q2*q2);
  *(volatile float *)(object+0x30)=asinf((q1*q3-q0*q2)*-2.0f);
  *(volatile float *)(object+0x34)=thunk_FUN_00076154(q0*q3+q1*q2,(0.5f-q2*q2)-q3*q3);
  *(volatile uint8_t *)(object+0x28)=1;
}
