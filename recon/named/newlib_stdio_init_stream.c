/* readable reconstruction; identity: FUN_00076b48 @ 0x00076b48
 * public-name: newlib_stdio_init_stream
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   newlib_stdio_init_stream                 <= FUN_00076b48 @ 0x00076b48
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_86f35                             @ 0x00086f35
 *   ADDR_libc_stream_write_syscall_THUMB     @ 0x00086f5b
 *   ADDR_gatt_sub_resolve_handle_THUMB       @ 0x00086f93
 *   rodata_86fb7                             @ 0x00086fb7
 */
/* Reconstructed FUN_00076b48 @ 0x76b48  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);

void newlib_stdio_init_stream(unsigned int *param_1, unsigned int param_2, unsigned int param_3)
{
  volatile unsigned int *vp = (volatile unsigned int *)param_1;
  vp[2] = 0;
  *(volatile unsigned short *)(param_1 + 3) = (unsigned short)param_2;
  vp[0x19] = 0;
  *(volatile unsigned short *)((char *)param_1 + 0xe) = (unsigned short)param_3;
  vp[6] = 0;
  vp[0] = 0;
  vp[1] = 0;
  vp[4] = 0;
  vp[5] = 0;
  memset_bytes((unsigned int *)((char *)param_1 + 0x5c), 0, 8);
  vp[8] = (unsigned int)param_1;
  vp[9] = 0x86f35;
  vp[10] = 0x86f5b;
  vp[0xb] = 0x86f93;
  vp[0xc] = 0x86fb7;
}
