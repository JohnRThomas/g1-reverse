#include "g1_net_symbols.h"
/* net-core FUN_010082b0 @ 0x10082b0  (parity 300 trials PROVEN) */

int FUN_010082b0(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3)
{
    unsigned int uVar11=param_2[0],uVar12=param_2[1],uVar13=param_2[2],uVar14=param_2[3];
    unsigned int uVar15=param_2[4],uVar16=param_2[5],uVar17=param_2[6],uVar18=param_2[7];
    unsigned int uVar7=param_3[0],uVar19=param_3[1];
    unsigned int uVar8,uVar20,uVar9,uVar21,uVar10,uVar22;
    int bVar1,bVar2,bVar3,bVar4,bVar5,bVar6;
    volatile unsigned int *vp = (volatile unsigned int *)param_1;
    bVar1 = (uVar12-uVar19) < (unsigned int)(uVar7<=uVar11);
    uVar8=param_3[2]; uVar20=param_3[3];
    bVar2 = (uVar13-uVar8) < (unsigned int)(uVar19<uVar12 || bVar1);
    bVar3 = (uVar14-uVar20) < (unsigned int)(uVar8<uVar13 || bVar2);
    uVar9=param_3[4]; uVar21=param_3[5];
    bVar4 = (uVar15-uVar9) < (unsigned int)(uVar20<uVar14 || bVar3);
    bVar5 = (uVar16-uVar21) < (unsigned int)(uVar9<uVar15 || bVar4);
    uVar10=param_3[6]; uVar22=param_3[7];
    bVar6 = (uVar17-uVar10) < (unsigned int)(uVar21<uVar16 || bVar5);
    vp[0]=uVar11-uVar7;
    vp[1]=(uVar12-uVar19)-(unsigned int)(uVar7>uVar11);
    vp[2]=(uVar13-uVar8)-(unsigned int)(uVar19>=uVar12 && !bVar1);
    vp[3]=(uVar14-uVar20)-(unsigned int)(uVar8>=uVar13 && !bVar2);
    vp[4]=(uVar15-uVar9)-(unsigned int)(uVar20>=uVar14 && !bVar3);
    vp[5]=(uVar16-uVar21)-(unsigned int)(uVar9>=uVar15 && !bVar4);
    vp[6]=(uVar17-uVar10)-(unsigned int)(uVar21>=uVar16 && !bVar5);
    vp[7]=(uVar18-uVar22)-(unsigned int)(uVar10>=uVar17 && !bVar6);
    return (uVar18<=uVar22) && ((unsigned int)(uVar10<uVar17 || bVar6) <= uVar18-uVar22);
}
