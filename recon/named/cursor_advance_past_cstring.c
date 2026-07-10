/* named: cursor_advance_past_cstring */
/* Reconstructed cursor_advance_past_cstring @ 0x84f16  (parity: 300/300 trials, PROVEN) */

extern int strlen(int a);
void cursor_advance_past_cstring(int *param_1) {
    if (param_1 != (int*)0 && *param_1 != 0) {
        int iVar2 = param_1[2];
        int iVar1 = strlen(*param_1 + iVar2);
        param_1[2] = iVar2 + iVar1;
    }
}

