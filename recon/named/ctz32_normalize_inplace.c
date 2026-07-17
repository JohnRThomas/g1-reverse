/* readable reconstruction; identity: FUN_00087554 @ 0x00087554
 * public-name: ctz32_normalize_inplace
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ctz32_normalize_inplace                  <= FUN_00087554 @ 0x00087554
 */
/* Reconstructed FUN_00087554 @ 0x87554  (parity: 300/300 trials, PROVEN) */
int ctz32_normalize_inplace(unsigned* param_1){
    unsigned uVar2 = *param_1;
    int iVar1;
    if ((uVar2 & 7) == 0){
        iVar1 = 0;
        if ((uVar2 & 0xffff) == 0){ uVar2 >>= 0x10; iVar1 = 0x10; }
        if ((uVar2 & 0xff) == 0){ iVar1 += 8; uVar2 >>= 8; }
        if ((uVar2 & 0xf) == 0){ uVar2 >>= 4; iVar1 += 4; }
        if ((uVar2 & 3) == 0){ uVar2 >>= 2; iVar1 += 2; }
        if (-1 < (int)(uVar2 << 0x1f)){ uVar2 >>= 1; iVar1 += 1; if (uVar2 == 0) return 0x20; }
        *param_1 = uVar2;
        return iVar1;
    }
    if ((int)(uVar2 << 0x1f) < 0) return 0;
    if ((int)(uVar2 << 0x1e) < 0){ iVar1 = 1; *param_1 = uVar2 >> 1; }
    else { iVar1 = 2; *param_1 = uVar2 >> 2; }
    return iVar1;
}
