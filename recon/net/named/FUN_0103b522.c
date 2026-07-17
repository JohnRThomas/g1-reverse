/* readable reconstruction; identity: FUN_0103b522 @ 0x0103b522
 * public-name: FUN_0103b522
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103b522 @ 0x103b522
 * True extent: 14-byte null-check/tail-call wrapper ending at 0x103b52f.
 * The former 134-byte Ghidra body overlapped the independent functions that
 * start at 0x103b530, 0x103b53a, and later addresses. CFG parity: PASS. */
extern void FUN_01035e1c(int, int);

void FUN_0103b522(int param_1)
{
  int v;
  if (param_1 == 0) {
    return;
  }
  v = *(int *)(param_1 - 4);
  FUN_01035e1c(v, param_1 - 4);
}
