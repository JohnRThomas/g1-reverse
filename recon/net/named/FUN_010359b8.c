/* readable reconstruction; identity: FUN_010359b8 @ 0x010359b8
 * public-name: FUN_010359b8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103c0c4                           @ 0x0103c0c4
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e921                           @ 0x0103e921
 *   rodata_103e929                           @ 0x0103e929
 *   rodata_103e951                           @ 0x0103e951
 *   rodata_103e972                           @ 0x0103e972
 *   rodata_103e98a                           @ 0x0103e98a
 */
/* net-core FUN_010359b8 @ 0x10359b8  (parity 300 trials PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void FUN_0102e284(unsigned int, unsigned int, void*, int);
extern void FUN_0102f580(int);
extern void FUN_01031820(unsigned int, int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern char *FUN_0103b15c(int);
extern int FUN_0103b650(void);

#define DAT_01035aa8 0x00000008u
#define DAT_01035aac 0x0103cb34u
#define DAT_01035ab0 0x0103e913u
#define DAT_01035ab4 0x0103e929u
#define DAT_01035ab8 0x01000005u
#define DAT_01035abc 0x0103c0c4u
#define DAT_01035ac0 0x0103e951u
#define DAT_01035ac4 0x0103e921u
#define DAT_01035ac8 0x0103e972u
#define DAT_01035acc 0x01000004u
#define DAT_01035ad0 0x0103e98au
#define DAT_01035ad4 0x0103d2a7u

void FUN_010359b8(unsigned int param_1, int param_2)
{
  int bVar2;
  unsigned int uVar3;
  int iVar3;
  unsigned int uVar4;
  char *local_44;
  unsigned char frameA[0x28];
  unsigned char frameB[0x18];

  /* Compiled image uses the BASEPRI_MAX critical-section sequence directly;
     there is no CONTROL privilege test in this build. */
  uVar4 = __get_BASEPRI();
  __set_BASEPRI_MAX(0x40u);
  __ISB();
  iVar3 = FUN_0103b650();
  iVar3 = *(int *)(DAT_01035aa8 + (unsigned int)iVar3);
  local_44 = (char *)DAT_01035ab0;
  if (param_1 < 5) {
    local_44 = *(char **)(DAT_01035aac + param_1 * 4);
  }

  *(unsigned short *)(frameA + 0x24) = 0x301;
  *(unsigned int *)(frameA + 0x14) = DAT_01035ab4;
  *(unsigned int *)(frameA + 0x18) = param_1;
  *(unsigned int *)(frameA + 0x20) = 0;
  *(char **)(frameA + 0x1c) = local_44;
  *(unsigned int *)(frameA + 0x10) = DAT_01035ab8;
  FUN_0102e284(DAT_01035abc, 0x2c40, frameA + 0x10, 0);

  if ((param_2 != 0) && ((*(unsigned int *)(param_2 + 0x1c) & 0x1ff) != 0)) {
    *(unsigned int *)(frameB + 0x14) = DAT_01035ac0;
    *(unsigned int *)(frameB + 0x10) = 2;
    FUN_0102e284(DAT_01035abc, 0x1040, frameB + 0x10, 0);
  }

  if (((iVar3 == 0) || (local_44 = FUN_0103b15c(iVar3), local_44 == (char *)0)) ||
      (*local_44 == '\0')) {
    local_44 = (char *)DAT_01035ac4;
  }

  *(char **)(frameA + 0x1c) = local_44;
  *(unsigned int *)(frameA + 0x14) = DAT_01035ac8;
  *(unsigned short *)(frameA + 0x20) = 0x301;
  *(unsigned int *)(frameA + 0x18) = (unsigned int)iVar3;
  *(unsigned int *)(frameA + 0x10) = DAT_01035acc;
  FUN_0102e284(DAT_01035abc, 0x2440, frameA + 0x10, 0);

  FUN_01031820(param_1, param_2);
  if (param_1 == 4) {
    FUN_01039bbe(DAT_01035ad4, DAT_01035ad0, 0x93);
    FUN_01039bb0(DAT_01035ad0, 0x93);
  }
  __set_BASEPRI(uVar4);
  __ISB();
  FUN_0102f580(iVar3);
  return;
}
