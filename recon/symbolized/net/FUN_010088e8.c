#include "g1_net_symbols.h"
/* net-core FUN_010088e8 @ 0x10088e8  (parity 300 trials PROVEN) */
#include <stdint.h>

#define CARRY4(a,b) (((uint32_t)(a) + (uint32_t)(b)) < (uint32_t)(a))

void FUN_010088e8(int32_t *param_1, uint32_t *param_2, uint32_t *param_3)
{
    uint32_t uVar5,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13,uVar14,uVar15,uVar16,uVar17,uVar18;
    uint32_t bVar1,bVar2,bVar3,bVar4,bVar19,bVar20;

    uVar6 = param_2[0];
    uVar8 = param_2[1];
    uVar10 = param_2[2];
    uVar11 = param_2[3];
    uVar12 = param_2[4];
    uVar13 = param_2[5];
    uVar14 = param_2[6];
    uVar15 = param_2[7];
    uVar5 = param_3[0];
    uVar16 = param_3[1];
    uVar7 = uVar6 - uVar5;
    bVar2 = (uVar8 - uVar16) < (uint32_t)(uVar5 <= uVar6);
    uVar9 = (uVar8 - uVar16) - (uint32_t)(uVar5 > uVar6);
    uVar5 = param_3[2];
    uVar6 = param_3[3];
    bVar3 = (uVar10 - uVar5) < (uint32_t)(uVar16 < uVar8 || bVar2);
    uVar16 = (uVar10 - uVar5) - (uint32_t)(uVar16 >= uVar8 && !bVar2);
    bVar2 = (uVar11 - uVar6) < (uint32_t)(uVar5 < uVar10 || bVar3);
    uVar10 = (uVar11 - uVar6) - (uint32_t)(uVar5 >= uVar10 && !bVar3);
    uVar5 = param_3[4];
    uVar17 = param_3[5];
    bVar3 = (uVar12 - uVar5) < (uint32_t)(uVar6 < uVar11 || bVar2);
    uVar11 = (uVar12 - uVar5) - (uint32_t)(uVar6 >= uVar11 && !bVar2);
    bVar2 = (uVar13 - uVar17) < (uint32_t)(uVar5 < uVar12 || bVar3);
    uVar12 = (uVar13 - uVar17) - (uint32_t)(uVar5 >= uVar12 && !bVar3);
    uVar8 = param_3[6];
    uVar18 = param_3[7];
    bVar4 = (uVar14 - uVar8) < (uint32_t)(uVar17 < uVar13 || bVar2);
    uVar13 = (uVar14 - uVar8) - (uint32_t)(uVar17 >= uVar13 && !bVar2);
    uVar6 = -(uint32_t)(uVar15 <= uVar18 && (uint32_t)(uVar8 < uVar14 || bVar4) <= uVar15 - uVar18);
    bVar19 = CARRY4(uVar9,uVar6) || CARRY4(uVar9+uVar6,(uint32_t)CARRY4(uVar7,uVar6));
    bVar20 = CARRY4(uVar16,uVar6) || CARRY4(uVar16+uVar6,(uint32_t)bVar19);
    bVar2 = CARRY4(uVar10,(uint32_t)bVar20);
    bVar3 = CARRY4(uVar11,(uint32_t)bVar2);
    bVar1 = CARRY4(uVar12,(uint32_t)bVar3);
    uVar5 = -(uint32_t)((int32_t)uVar6 >> 31);
    *(volatile int32_t *)&param_1[0] = uVar7 + uVar6;
    *(volatile int32_t *)&param_1[1] = uVar9 + uVar6 + (uint32_t)CARRY4(uVar7,uVar6);
    *(volatile int32_t *)&param_1[2] = uVar16 + uVar6 + (uint32_t)bVar19;
    *(volatile int32_t *)&param_1[3] = uVar10 + bVar20;
    *(volatile int32_t *)&param_1[4] = uVar11 + bVar2;
    *(volatile int32_t *)&param_1[5] = uVar12 + bVar3;
    *(volatile int32_t *)&param_1[6] = uVar13 + uVar5 + bVar1;
    *(volatile int32_t *)&param_1[7] = ((uVar15 - uVar18) - (uint32_t)(uVar8 >= uVar14 && !bVar4)) + uVar6 +
                 (CARRY4(uVar13,uVar5) || CARRY4(uVar13+uVar5,(uint32_t)bVar1));
}
