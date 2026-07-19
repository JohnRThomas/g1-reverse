/* readable reconstruction; identity: FUN_0005af8c @ 0x0005af8c
 * public-name: gatt_ccc_settings_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ccc_set_direct                           <= FUN_00059edc @ 0x00059edc
 *   gatt_ccc_settings_set                    <= FUN_0005af8c @ 0x0005af8c
 *   strtoul                                  <= FUN_00077c1c @ 0x00077c1c
 *   settings_name_steq                       <= FUN_0007f1a0 @ 0x0007f1a0
 *   settings_name_next                       <= FUN_0007f1e8 @ 0x0007f1e8
 *   bt_settings_decode_key                   <= FUN_00080cf2 @ 0x00080cf2
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 *   bt_gatt_foreach_attr_0                   <= FUN_00082c9c @ 0x00082c9c
 * address symbols (name @ address):
 *   ADDR_gatt_ccc_write_store_cb_THUMB       @ 0x00059ded
 *   rodata_88128                             @ 0x00088128
 *   rodata_f2b65                             @ 0x000f2b65
 *   rodata_f472a                             @ 0x000f472a
 *   rodata_f4746                             @ 0x000f4746
 *   rodata_f4783                             @ 0x000f4783
 *   rodata_f4a9e                             @ 0x000f4a9e
 */
/* Reconstructed FUN_0005af8c @ 0x5af8c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int ccc_set_direct(void);
extern int strtoul(int,...);
extern int settings_name_steq(int,...);
extern int settings_name_next(int,...);
extern int bt_settings_decode_key(int,...);
extern int log_msg_create_3arg(int,...);
extern int bt_gatt_foreach_attr_0(int,...);
typedef int (*codeptr)(int,...);
unsigned int gatt_ccc_settings_set(int param_1,int param_2,codeptr param_3,int param_4,int param_5)
{
  int iVar1;
  unsigned int uVar2;
  struct request_frame {
    int object;
    int identity;
    unsigned char address[8];
    unsigned char *address_ptr;
    unsigned char kind;
    unsigned char kind_pad[3];
    unsigned char *payload_ptr;
    unsigned int payload_words;
    unsigned char payload[192];
    unsigned char compiler_frame_pad[8];
  } frame;
  unsigned int lookup_result;
  iVar1 = settings_name_steq(param_5, 0xf4a9e, &frame.object);
  if (iVar1 == 0) {
    uVar2 = ccc_set_direct();
  } else {
    settings_name_next(frame.object, &frame.identity);
    if (frame.object == 0) {
      struct { unsigned level, message; } log = { 2, 0x000f2b65 };
      log_msg_create_3arg(0x88128, 0x1040, &log);
    } else {
      if ((frame.identity == 0) ||
          (lookup_result = strtoul(frame.identity,0,10), lookup_result == 0)) {
        frame.kind = 0;
        iVar1 = bt_settings_decode_key(frame.object, frame.address);
        if (iVar1 == 0) {
          frame.address_ptr = frame.address;
          if (param_2 == 0) {
            frame.payload_ptr = 0;
            frame.payload_words = 0;
          } else {
            int payload_bytes = param_3(param_4, (int)frame.payload, 0xc0);
            if (payload_bytes < 0) {
              struct { unsigned level, message; int error; } log = {
                3, 0x000f4783, payload_bytes
              };
              log_msg_create_3arg(0x88128, 0x1840, &log);
              return (unsigned int)payload_bytes;
            }
            frame.payload_words = (unsigned int)payload_bytes >> 2;
            frame.payload_ptr = frame.payload;
          }
          bt_gatt_foreach_attr_0(1, 0xffff, 0x59ded, &frame.address_ptr);
          return 0;
        }
        struct { unsigned type, message; int value; unsigned short flags; } log = {
          0x01000003, 0x000f472a, frame.object, 0x200
        };
        log_msg_create_3arg(0x88128, 0x1c40, &log);
      } else {
        struct { unsigned level, message; int error; } log = {
          3, 0x000f4746, (int)lookup_result
        };
        log_msg_create_3arg(0x88128, 0x1840, &log);
      }
    }
    uVar2 = 0xffffffea;
  }
  return uVar2;
}
