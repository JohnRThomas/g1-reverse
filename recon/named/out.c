/* named: out */
/* Reconstructed out @ 0x7dd7e  (parity: 300/300 trials, PROVEN) */

void out(unsigned char param_1, int *param_2){
    int iVar1 = param_2[2];
    int iVar3 = param_2[0];
    int iVar4 = iVar1+1;
    if(iVar3==0 || param_2[1] <= iVar1){
        param_2[2]=iVar4;
    } else {
        int iVar2 = param_2[1]-1;
        int bVar5 = (iVar2==iVar1);
        if(bVar5) iVar1=0;
        param_2[2]=iVar4;
        if(bVar5) *(char*)(iVar3+iVar2) = (char)iVar1;
        if(!bVar5) *(unsigned char*)(iVar3+iVar1) = param_1;
    }
}

