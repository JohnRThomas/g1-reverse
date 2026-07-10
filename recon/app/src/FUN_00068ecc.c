/* Reconstructed FUN_00068ecc @ 0x68ecc  (parity: 300/300 trials, PROVEN) */
int FUN_00068ecc(int param_1, int param_2){
  int iVar1, iVar2;
  if (param_1==0x1d4c){
    if(param_2==8000){iVar1=0x5f;iVar2=0x3c;}
    else { if(param_2!=16000) goto L_ef2; iVar1=0xbe;iVar2=0x78; }
   L_f5e:
    iVar2 = iVar2*0x17;
    iVar2 = ((iVar2 + (int)((unsigned long long)((long long)(int)0x88888889 * (long long)iVar2) >> 0x20)) >> 4) - (iVar2>>0x1f);
    return (iVar2+iVar1+300)*4;
  } else {
    if(param_1!=10000) return 0;
    if(param_2==8000){iVar1=0x7d;iVar2=0x50;}
    else if(param_2==16000){iVar1=0xfa;iVar2=0xa0;}
    else {
     L_ef2:
      if((param_2!=24000)&&(param_2!=32000)&&(param_2!=48000)) return 0;
      iVar2 = (int)(((long long)(int)0x431bde83 * (long long)(param_2*param_1)) >> 0x32) - ((param_2*param_1)>>0x1f);
      iVar1 = iVar2 + (((int)(((long long)(int)0x51eb851f * (long long)param_2) >> 0x28) - (param_2>>0x1f)) + iVar2)/2;
      if(param_1==0x1d4c) goto L_f5e;
    }
    iVar2 = iVar2*5;
    if(iVar2<0) iVar2+=7;
    iVar2 = iVar2>>3;
    return (iVar2+iVar1+300)*4;
  }
}

