/* named: cjson_strdup */
/* globals referenced:
//   0x20002bac  g_cjson_hooks                
*/
/* Reconstructed cjson_strdup @ 0x64640  (parity: 300/300 trials, PROVEN) */

extern int strlen(void);
extern int memcpy(int a, int b, int c);

int cjson_strdup(int param_1)
{
    int iVar1;
    int iVar2;
    if (param_1 != 0) {
        iVar1 = strlen();
        iVar2 = ((int(*)(int))(*(volatile unsigned int*)0x20002bacUL))(iVar1 + 1);
        if (iVar2 != 0) {
            memcpy(iVar2, param_1, iVar1 + 1);
            return iVar2;
        }
    }
    return 0;
}

