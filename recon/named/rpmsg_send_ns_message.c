/* readable reconstruction; identity: FUN_00085898 @ 0x00085898
 * public-name: rpmsg_send_ns_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_send_offchannel_raw                <= FUN_00070f1c @ 0x00070f1c
 *   rpmsg_send_ns_message                    <= FUN_00085898 @ 0x00085898
 *   strncpy_zero_pad                         <= FUN_0008705a @ 0x0008705a
 */
/* Reconstructed FUN_00085898 @ 0x85898  (parity: 300/300 trials, PROVEN) */

extern void strncpy_zero_pad(void*, int, int);
extern unsigned int rpmsg_send_offchannel_raw(int, unsigned int, int, void*, int, int);

unsigned int rpmsg_send_ns_message(int param_1, unsigned int param_2)
{
    unsigned int uVar2 = *(volatile unsigned int*)(param_1 + 0x24);
    unsigned char buf[32];
    volatile unsigned int local_18;
    volatile unsigned int local_14;
    local_18 = uVar2;
    local_14 = param_2;
    strncpy_zero_pad(buf, param_1, 0x20);
    unsigned int uVar1 = rpmsg_send_offchannel_raw(param_1, uVar2, 0x35, buf, 0x28, 1);
    return uVar1 & ((int)uVar1 >> 31);
}
