## review group param_0027  (1 cluster(s), kinds=param)

### proposal for param_0027
struct_name: g1_system_runtime_state | is_library: False | library_name:  | is_array: False | confidence: low
purpose: Central G1-original device runtime/context struct (~0x4244 bytes) threaded through runtime_info_sync, user settings load/save, ESB comms, display/key/touch dispatch threads, task/message queue processing, and screen state — the shared 'global device state' object.
fields:
  0x1  uint8_t      field_0x1  
  0x2  uint8_t      field_0x2  
  0x3  uint8_t      field_0x3  
  0x4  uint32_t     field_0x4  
  0x8  uint32_t     field_0x8  
  0x40  uint32_t     field_0x40  
  0x58  uint32_t     field_0x58  
  0xc9  uint32_t     field_0xc9  
  0xcd  uint32_t     field_0xcd  
  0xd1  uint16_t     field_0xd1  
  0xd4  uint8_t      field_0xd4  
  0xd5  uint8_t      field_0xd5  
  0xd6  uint16_t     field_0xd6  
  0xd8  uint16_t     brightness_level  near brightness_level() member
  0xdf  uint32_t     field_0xdf  
  0xe5  uint32_t     field_0xe5  
  0xec  uint8_t      field_0xec  
  0xed  uint16_t     field_0xed  
  0x324  uint32_t     field_0x324  
  0x328  uint32_t     field_0x328  
  0x32c  uint32_t     field_0x32c  
  0x330  uint32_t     field_0x330  
  0x334  uint32_t     field_0x334  
  0x338  uint32_t     field_0x338  
  0x33c  uint32_t     field_0x33c  
  0x34c  uint32_t     field_0x34c  
  0x350  uint32_t     field_0x350  
  0x354  uint32_t     field_0x354  
  0x368  uint32_t     field_0x368  
  0x36c  uint32_t     field_0x36c  
  0x370  uint32_t     field_0x370  
  0x374  uint32_t     field_0x374  
  0x378  uint32_t     field_0x378  
  0x38c  uint32_t     field_0x38c  
  0x390  uint32_t     field_0x390  
  0x394  uint32_t     field_0x394  
  0x398  uint32_t     field_0x398  
  0x3a4  uint32_t     field_0x3a4  
  0x3a8  uint32_t     field_0x3a8  
  0x3ac  uint32_t     field_0x3ac  
  0x3b0  uint32_t     field_0x3b0  
  0x6cc  uint8_t      screen_state_flag  written; near trigger_screen_state_change/update_imu_trigger_status members
  0x6cd  uint8_t      field_0x6cd  
  0x6ce  uint8_t      field_0x6ce  
  0x6cf  uint8_t      field_0x6cf  
  0x6d0  uint8_t      field_0x6d0  
  0x6d8  uint32_t     field_0x6d8  
  0x6dc  uint16_t     field_0x6dc  
  0x6e1  uint8_t      persist_task_status  near now_has_persist_task/update_persist_task_status members
  0x774  void *       field_0x774  
  0x9b4  uint32_t     field_0x9b4  
  0xae4  uint32_t     field_0xae4  
  0xb0c  uint8_t      field_0xb0c  
  0xb0d  uint8_t      field_0xb0d  
  0xb8c  void *       field_0xb8c  
  0xeb4  uint32_t     field_0xeb4  
  0xeb8  uint32_t     field_0xeb8  
  0xec0  uint16_t     field_0xec0  
  0xec8  uint32_t     field_0xec8  
  0xed5  uint8_t      field_0xed5  
  0xed7  uint8_t      field_0xed7  
  0xee4  uint8_t      field_0xee4  
  0xee8  uint32_t     field_0xee8  
  0xef4  uint16_t     field_0xef4  
  0xf60  uint8_t      field_0xf60  
  0xf68  uint32_t     field_0xf68  
  0xf6c  uint32_t     field_0xf6c  
  0xf90  uint32_t     field_0xf90  
  0xf98  uint8_t      field_0xf98  
  0xfc0  uint8_t      field_0xfc0  
  0xfcf  uint8_t      field_0xfcf  
  0xfd0  uint8_t      field_0xfd0  
  0xfd1  uint8_t      field_0xfd1  
  0xfda  uint32_t     field_0xfda  
  0xfde  uint16_t     field_0xfde  
  0xfe0  uint32_t     field_0xfe0  
  0xfe4  uint16_t     field_0xfe4  
  0xfe6  uint8_t      field_0xfe6  
  0xfe7  uint8_t      field_0xfe7  
  0xfe8  uint8_t      field_0xfe8  
  0xfe9  uint8_t      field_0xfe9  
  0xfea  uint8_t      field_0xfea  
  0xfec  void *       task_cb_0  start of dense pointer table 0xfec-0x102c, likely task/message dispatch callback array
  0xff0  void *       task_cb_1  
  0xff4  void *       task_cb_2  
  0xff8  void *       task_cb_3  
  0xffc  void *       task_cb_4  
  0x1000  void *       task_cb_5  
  0x1004  void *       task_cb_6  
  0x1008  void *       task_cb_7  
  0x100c  void *       task_cb_8  
  0x1010  void *       task_cb_9  
  0x1014  void *       task_cb_10  
  0x1018  void *       task_cb_11  
  0x101c  void *       task_cb_12  
  0x1020  void *       task_cb_13  
  0x1024  void *       task_cb_14  
  0x1028  void *       task_cb_15  
  0x102c  void *       task_cb_16  
  0x1040  void *       field_0x1040  
  0x104c  uint32_t     field_0x104c  
  0x1054  void *       field_0x1054  
  0x105a  uint8_t      field_0x105a  
  0x105c  uint16_t     field_0x105c  
  0x1060  uint64_t     field_0x1060  64-bit, likely timestamp
  0x1069  uint32_t     field_0x1069  
  0x106d  uint16_t     field_0x106d  
  0x106f  uint8_t      field_0x106f  
  0x1070  uint8_t      field_0x1070  
  0x1071  uint8_t      field_0x1071  
  0x1072  uint16_t     field_0x1072  
  0x1074  uint16_t     field_0x1074  
  0x1078  uint32_t     field_0x1078  
  0x108d  uint8_t      field_0x108d  
  0x108f  uint8_t      field_0x108f  
  0x1090  uint16_t     field_0x1090  
  0x1b78  uint32_t     field_0x1b78  
  0x1b7c  uint32_t     field_0x1b7c  
  0x2b88  uint32_t     field_0x2b88  
  0x2b8c  uint32_t     field_0x2b8c  
  0x2c30  uint32_t     field_0x2c30  
  0x2c34  uint32_t     field_0x2c34  
  0x3ad0  uint32_t     field_0x3ad0  
  0x3ad4  uint32_t     field_0x3ad4  
  0x3ad8  uint32_t     field_0x3ad8  
  0x3adc  uint32_t     field_0x3adc  
  0x3b00  uint32_t     field_0x3b00  
  0x3b04  uint32_t     field_0x3b04  
  0x3b30  uint32_t     field_0x3b30  
  0x3b34  uint32_t     field_0x3b34  
  0x3b38  uint32_t     field_0x3b38  
  0x3b3c  uint32_t     field_0x3b3c  
  0x3b54  uint32_t     field_0x3b54  
  0x3b58  uint32_t     field_0x3b58  
  0x3b90  uint32_t     field_0x3b90  
  0x3ba0  uint32_t     field_0x3ba0  
  0x3ba4  uint32_t     field_0x3ba4  
  0x3ba8  uint32_t     field_0x3ba8  
  0x3bac  uint32_t     field_0x3bac  
  0x3bd0  uint32_t     field_0x3bd0  
  0x3bd4  uint32_t     field_0x3bd4  
  0x3d80  uint32_t     field_0x3d80  
  0x3e60  uint32_t     field_0x3e60  
  0x3f00  uint32_t     field_0x3f00  
  0x3f04  uint32_t     field_0x3f04  
  0x3f08  uint32_t     field_0x3f08  
  0x3f10  uint32_t     field_0x3f10  
  0x3f14  uint32_t     field_0x3f14  
  0x3f18  uint32_t     field_0x3f18  
  0x3f98  uint32_t     field_0x3f98  
  0x3f9c  uint32_t     field_0x3f9c  
  0x3fa0  uint32_t     field_0x3fa0  
  0x3fa4  uint32_t     field_0x3fa4  
  0x3fa8  uint32_t     field_0x3fa8  
  0x4130  uint32_t     field_0x4130  
  0x4134  uint32_t     field_0x4134  
  0x4138  uint32_t     field_0x4138  
  0x413c  uint32_t     field_0x413c  
  0x4168  uint32_t     field_0x4168  
  0x41a0  uint32_t     field_0x41a0  
  0x41c0  uint32_t     field_0x41c0  
  0x4238  uint32_t     field_0x4238  
  0x423c  uint32_t     field_0x423c  

<ground-truth bundle for param_0027>
### cluster param_0027  (param, 31 members, 173 fields, size>=0x4244)

Shared pointer-parameter object unified across call-argument flow.

library hint: likely G1-original

members (31 shown of 31):
  - runtime_info_sync @ 0x16268  as param_1  [APPLICATION]
  - reset_usr_setting @ 0x22ddc  as param_1  [APPLICATION]
  - load_usr_setting @ 0x22e78  as param_1  [APPLICATION]
  - try_to_save_file @ 0x23634  as param_1  [APPLICATION]
  - brightness_level @ 0x23844  as param_1  [APPLICATION]
  - check_bind_status @ 0x26b88  as param_1  [APPLICATION]
  - sync_to_slave @ 0x26f74  as param_1  [APPLICATION]
  - esb_send_command_and_wait_ack @ 0x27448  as param_1  [APPLICATION]
  - FUN_00027cfe @ 0x27cfe  as param_1  [APPLICATION]
  - display_dispatch_thread @ 0x28bec  as param_1  [APPLICATION]
  - key_event_thread @ 0x2955c  as param_1  [APPLICATION]
  - touch_key_thread @ 0x2a0d8  as param_1  [APPLICATION]
  - low_speed_peripheral_dispatch_thread @ 0x2a8d8  as param_1  [APPLICATION]
  - master_process_audio_fw_load_req @ 0x2af4c  as param_1  [APPLICATION]
  - trigger_screen_state_change @ 0x2bc2c  as param_2  [APPLICATION]
  - update_imu_trigger_status @ 0x2bcbc  as param_2  [APPLICATION]
  - now_has_persist_task @ 0x2be64  as param_1  [APPLICATION]
  - display_panel_is_secondary @ 0x2bed0  as param_1  [APPLICATION]
  - update_persist_task_status @ 0x2bef4  as param_1  [APPLICATION]
  - update_temp_task_status @ 0x2bffc  as param_1  [APPLICATION]
  - update_persist_task_status_to_idle @ 0x2c0e8  as param_1  [APPLICATION]
  - process_for_new_message_come_on @ 0x2c498  as param_1  [APPLICATION]
  - process_for_message_show @ 0x2c714  as param_1  [APPLICATION]
  - process_for_new_task @ 0x2c99c  as param_1  [APPLICATION]

layout notes: 0xc9: access width 4 exceeds gap 2 to next field (overlap/union); 0xcd: access width 4 exceeds gap 3 to next field (overlap/union); 0xd0: access width 4 exceeds gap 1 to next field (overlap/union); 0xe5: access width 4 exceeds gap 1 to next field (overlap/union); 0xec0: access width 2 exceeds gap 1 to next field (overlap/union); 0xef4: access width 2 exceeds gap 1 to next field (overlap/union); 0x1060: access width 8 exceeds gap 4 to next field (overlap/union); 0x1069: access width 4 exceeds gap 3 to next field (overlap/union); 0x106c: access width 4 exceeds gap 1 to next field (overlap/union); 0x1090: access width 2 exceeds gap 1 to next field (overlap/union)

candidate layout (offsets/sizes are GROUND TRUTH from Ghidra — do not change them; name the struct + fields, refine types, judge cohesion):
```c
struct param_0027 {
    uint8_t    _pad_0x0[0x1];   /* +0x0 pad */
    uint8_t    field_0x1;   /* +0x1  sz=1 rw=rw types=char,undefined1 */
    uint8_t    field_0x2;   /* +0x2  sz=1 rw=r types=byte */
    uint8_t    field_0x3;   /* +0x3  sz=1 rw=rw types=byte,undefined1 */
    uint32_t   field_0x4;   /* +0x4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x8;   /* +0x8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0xc[0x34];   /* +0xc pad */
    uint32_t   field_0x40;   /* +0x40  sz=4 rw=r types=int */
    uint8_t    _pad_0x44[0x14];   /* +0x44 pad */
    uint32_t   field_0x58;   /* +0x58  sz=4 rw=r types=int */
    uint8_t    _pad_0x5c[0x6d];   /* +0x5c pad */
    uint16_t   field_0xc9;   /* +0xc9  sz=4 rw=r types=undefined4 */
    uint8_t    field_0xcb;   /* +0xcb  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xcc[0x1];   /* +0xcc pad */
    uint8_t    field_0xcd[0x3];   /* +0xcd pad */
    uint8_t    field_0xd0;   /* +0xd0  sz=4 rw=rw types=undefined4 */
    uint16_t   field_0xd1;   /* +0xd1  sz=2 rw=r types=undefined2 */
    uint8_t    _pad_0xd3[0x1];   /* +0xd3 pad */
    uint8_t    field_0xd4;   /* +0xd4  sz=1 rw=rw types=byte */
    uint8_t    field_0xd5;   /* +0xd5  sz=1 rw=rw types=byte,char,undefined1 */
    uint16_t   field_0xd6;   /* +0xd6  sz=2 rw=w types=short,undefined2 */
    uint16_t   field_0xd8;   /* +0xd8  sz=2 rw=w types=short */
    uint8_t    _pad_0xda[0x5];   /* +0xda pad */
    uint32_t   field_0xdf;   /* +0xdf  sz=4 rw=rw types=uint,undefined4 */
    uint8_t    _pad_0xe3[0x2];   /* +0xe3 pad */
    uint8_t    field_0xe5;   /* +0xe5  sz=1,4 rw=rw types=char,undefined1,undefined4 */
    uint8_t    field_0xe6;   /* +0xe6  sz=1 rw=r types=byte,char,undefined1 */
    uint8_t    field_0xe7;   /* +0xe7  sz=1 rw=r types=byte,char,undefined1 */
    uint8_t    field_0xe8;   /* +0xe8  sz=1 rw=r types=byte,char */
    uint8_t    _pad_0xe9[0x3];   /* +0xe9 pad */
    uint8_t    field_0xec;   /* +0xec  sz=1 rw=w types=undefined1 */
    uint16_t   field_0xed;   /* +0xed  sz=2 rw=w types=short */
    uint8_t    _pad_0xef[0x235];   /* +0xef pad */
    uint32_t   field_0x324;   /* +0x324  sz=4 rw=r types=idx4 */
    uint32_t   field_0x328;   /* +0x328  sz=4 rw=r types=idx4 */
    uint32_t   field_0x32c;   /* +0x32c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x330;   /* +0x330  sz=4 rw=r types=idx4 */
    uint32_t   field_0x334;   /* +0x334  sz=4 rw=r types=idx4 */
    uint32_t   field_0x338;   /* +0x338  sz=4 rw=r types=idx4 */
    uint32_t   field_0x33c;   /* +0x33c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x340[0xc];   /* +0x340 pad */
    uint32_t   field_0x34c;   /* +0x34c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x350;   /* +0x350  sz=4 rw=r types=idx4 */
    uint32_t   field_0x354;   /* +0x354  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x358[0x10];   /* +0x358 pad */
    uint32_t   field_0x368;   /* +0x368  sz=4 rw=r types=idx4 */
    uint32_t   field_0x36c;   /* +0x36c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x370;   /* +0x370  sz=4 rw=r types=idx4 */
    uint32_t   field_0x374;   /* +0x374  sz=4 rw=r types=idx4 */
    uint32_t   field_0x378;   /* +0x378  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x37c[0x10];   /* +0x37c pad */
    uint32_t   field_0x38c;   /* +0x38c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x390;   /* +0x390  sz=4 rw=r types=idx4 */
    uint32_t   field_0x394;   /* +0x394  sz=4 rw=r types=idx4 */
    uint32_t   field_0x398;   /* +0x398  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x39c[0x8];   /* +0x39c pad */
    uint32_t   field_0x3a4;   /* +0x3a4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3a8;   /* +0x3a8  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3ac;   /* +0x3ac  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3b0;   /* +0x3b0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3b4[0x318];   /* +0x3b4 pad */
    uint8_t    field_0x6cc;   /* +0x6cc  sz=1 rw=w types=byte */
    uint8_t    field_0x6cd;   /* +0x6cd  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x6ce;   /* +0x6ce  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x6cf;   /* +0x6cf  sz=1 rw=w types=undefined1 */
    uint8_t    field_0x6d0;   /* +0x6d0  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0x6d1[0x7];   /* +0x6d1 pad */
    uint32_t   field_0x6d8;   /* +0x6d8  sz=4 rw=w types=undefined4 */
    uint16_t   field_0x6dc;   /* +0x6dc  sz=2 rw=w types=undefined2 */
    uint8_t    _pad_0x6de[0x3];   /* +0x6de pad */
    uint8_t    field_0x6e1;   /* +0x6e1  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x6e2[0x92];   /* +0x6e2 pad */
    void *     field_0x774;   /* +0x774  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x778[0x23c];   /* +0x778 pad */
    uint32_t   field_0x9b4;   /* +0x9b4  sz=4 rw=r types=int */
    uint8_t    _pad_0x9b8[0x12c];   /* +0x9b8 pad */
    uint32_t   field_0xae4;   /* +0xae4  sz=4 rw=rw types=int,undefined4 */
    uint8_t    _pad_0xae8[0x24];   /* +0xae8 pad */
    uint8_t    field_0xb0c;   /* +0xb0c  sz=1 rw=r types=char */
    uint8_t    field_0xb0d;   /* +0xb0d  sz=1 rw=w types=undefined1 */
    uint8_t    _pad_0xb0e[0x7e];   /* +0xb0e pad */
    void *     field_0xb8c;   /* +0xb8c  sz=4 rw=r types=ptr */
    uint8_t    _pad_0xb90[0x324];   /* +0xb90 pad */
    uint32_t   field_0xeb4;   /* +0xeb4  sz=4 rw=r types=undefined4 */
    uint32_t   field_0xeb8;   /* +0xeb8  sz=4 rw=r types=undefined4 */
    uint8_t    _pad_0xebc[0x4];   /* +0xebc pad */
    uint8_t    field_0xec0;   /* +0xec0  sz=1,2 rw=rw types=byte,undefined1,undefined2 */
    uint8_t    field_0xec1;   /* +0xec1  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0xec2[0x6];   /* +0xec2 pad */
    uint32_t   field_0xec8;   /* +0xec8  sz=4 rw=r types=int */
    uint8_t    _pad_0xecc[0x9];   /* +0xecc pad */
    uint8_t    field_0xed5;   /* +0xed5  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xed6[0x1];   /* +0xed6 pad */
    uint8_t    field_0xed7;   /* +0xed7  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xed8[0xc];   /* +0xed8 pad */
    uint8_t    field_0xee4;   /* +0xee4  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xee5[0x3];   /* +0xee5 pad */
    uint32_t   field_0xee8;   /* +0xee8  sz=4 rw=rw types=int */
    uint8_t    _pad_0xeec[0x8];   /* +0xeec pad */
    uint8_t    field_0xef4;   /* +0xef4  sz=1,2 rw=rw types=undefined1,undefined2 */
    uint8_t    field_0xef5;   /* +0xef5  sz=1 rw=rw types=undefined1 */
    uint8_t    _pad_0xef6[0x6a];   /* +0xef6 pad */
    uint8_t    field_0xf60;   /* +0xf60  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    _pad_0xf61[0x7];   /* +0xf61 pad */
    uint32_t   field_0xf68;   /* +0xf68  sz=4 rw=rw types=int,undefined4 */
    uint32_t   field_0xf6c;   /* +0xf6c  sz=4 rw=rw types=int,undefined4 */
    uint8_t    _pad_0xf70[0x20];   /* +0xf70 pad */
    uint32_t   field_0xf90;   /* +0xf90  sz=4 rw=r types=int */
    uint8_t    _pad_0xf94[0x4];   /* +0xf94 pad */
    uint8_t    field_0xf98;   /* +0xf98  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0xf99[0x27];   /* +0xf99 pad */
    uint8_t    field_0xfc0;   /* +0xfc0  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0xfc1[0xe];   /* +0xfc1 pad */
    uint8_t    field_0xfcf;   /* +0xfcf  sz=1 rw=r types=undefined1 */
    uint8_t    field_0xfd0;   /* +0xfd0  sz=1 rw=r types=undefined1 */
    uint8_t    field_0xfd1;   /* +0xfd1  sz=1 rw=r types=undefined1 */
    uint8_t    _pad_0xfd2[0x8];   /* +0xfd2 pad */
    uint32_t   field_0xfda;   /* +0xfda  sz=4 rw=r types=undefined4 */
    uint16_t   field_0xfde;   /* +0xfde  sz=2 rw=r types=undefined2 */
    uint32_t   field_0xfe0;   /* +0xfe0  sz=4 rw=r types=undefined4 */
    uint16_t   field_0xfe4;   /* +0xfe4  sz=2 rw=r types=undefined2 */
    uint8_t    field_0xfe6;   /* +0xfe6  sz=1 rw=r types=char */
    uint8_t    field_0xfe7;   /* +0xfe7  sz=1 rw=w types=undefined1 */
    uint8_t    field_0xfe8;   /* +0xfe8  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    field_0xfe9;   /* +0xfe9  sz=1 rw=w types=undefined1 */
    uint8_t    field_0xfea;   /* +0xfea  sz=1 rw=rw types=byte,char,undefined1 */
    uint8_t    _pad_0xfeb[0x1];   /* +0xfeb pad */
    void *     field_0xfec;   /* +0xfec  sz=4 rw=rw types=int,ptr,undefined4 */
    void *     field_0xff0;   /* +0xff0  sz=4 rw=rw types=int,ptr,undefined4 */
    void *     field_0xff4;   /* +0xff4  sz=4 rw=r types=int,ptr,undefined4 */
    void *     field_0xff8;   /* +0xff8  sz=4 rw=r types=int,ptr */
    void *     field_0xffc;   /* +0xffc  sz=4 rw=r types=int,ptr,undefined4 */
    void *     field_0x1000;   /* +0x1000  sz=4 rw=rw types=int,ptr */
    void *     field_0x1004;   /* +0x1004  sz=4 rw=r types=int,ptr,uint */
    void *     field_0x1008;   /* +0x1008  sz=4 rw=r types=int,ptr */
    void *     field_0x100c;   /* +0x100c  sz=4 rw=r types=int,ptr */
    void *     field_0x1010;   /* +0x1010  sz=4 rw=rw types=int,ptr */
    void *     field_0x1014;   /* +0x1014  sz=4 rw=rw types=int,ptr */
    void *     field_0x1018;   /* +0x1018  sz=4 rw=rw types=ptr */
    void *     field_0x101c;   /* +0x101c  sz=4 rw=r types=ptr */
    void *     field_0x1020;   /* +0x1020  sz=4 rw=rw types=int,ptr */
    void *     field_0x1024;   /* +0x1024  sz=4 rw=r types=ptr */
    void *     field_0x1028;   /* +0x1028  sz=4 rw=r types=ptr */
    void *     field_0x102c;   /* +0x102c  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x1030[0x10];   /* +0x1030 pad */
    void *     field_0x1040;   /* +0x1040  sz=4 rw=r types=ptr */
    uint8_t    _pad_0x1044[0x8];   /* +0x1044 pad */
    uint32_t   field_0x104c;   /* +0x104c  sz=4 rw=rw types=int,uint,undefined4 */
    uint8_t    _pad_0x1050[0x4];   /* +0x1050 pad */
    void *     field_0x1054;   /* +0x1054  sz=4 rw=rw types=int,ptr */
    uint8_t    _pad_0x1058[0x2];   /* +0x1058 pad */
    uint8_t    field_0x105a;   /* +0x105a  sz=1 rw=rw types=char,undefined1 */
    uint8_t    _pad_0x105b[0x1];   /* +0x105b pad */
    uint16_t   field_0x105c;   /* +0x105c  sz=2 rw=r types=ushort */
    uint8_t    _pad_0x105e[0x2];   /* +0x105e pad */
    uint32_t   field_0x1060;   /* +0x1060  sz=8 rw=rw types=longlong */
    uint32_t   field_0x1064;   /* +0x1064  sz=4 rw=r types=int */
    uint8_t    _pad_0x1068[0x1];   /* +0x1068 pad */
    uint8_t    field_0x1069[0x3];   /* +0x1069 pad */
    uint8_t    field_0x106c;   /* +0x106c  sz=4 rw=w types=undefined4 */
    uint16_t   field_0x106d;   /* +0x106d  sz=2 rw=rw types=undefined2 */
    uint8_t    field_0x106f;   /* +0x106f  sz=1 rw=rw types=undefined1 */
    uint8_t    field_0x1070;   /* +0x1070  sz=1 rw=rw types=undefined1 */
    uint8_t    field_0x1071;   /* +0x1071  sz=1 rw=rw types=char,undefined1 */
    uint16_t   field_0x1072;   /* +0x1072  sz=2 rw=r types=short,undefined2 */
    uint16_t   field_0x1074;   /* +0x1074  sz=2 rw=r types=short */
    uint8_t    _pad_0x1076[0x2];   /* +0x1076 pad */
    uint32_t   field_0x1078;   /* +0x1078  sz=4 rw=r types=int,undefined4 */
    uint8_t    _pad_0x107c[0x11];   /* +0x107c pad */
    uint8_t    field_0x108d;   /* +0x108d  sz=1 rw=rw types=undefined1 */
    uint8_t    _pad_0x108e[0x1];   /* +0x108e pad */
    uint8_t    field_0x108f;   /* +0x108f  sz=1 rw=rw types=byte,undefined1 */
    uint8_t    field_0x1090;   /* +0x1090  sz=1,2 rw=rw types=undefined1,undefined2 */
    uint8_t    field_0x1091;   /* +0x1091  sz=1 rw=rw types=undefined1 */
    uint8_t    _pad_0x1092[0xae6];   /* +0x1092 pad */
    uint32_t   field_0x1b78;   /* +0x1b78  sz=4 rw=r types=idx4 */
    uint32_t   field_0x1b7c;   /* +0x1b7c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x1b80[0x1008];   /* +0x1b80 pad */
    uint32_t   field_0x2b88;   /* +0x2b88  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2b8c;   /* +0x2b8c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x2b90[0xa0];   /* +0x2b90 pad */
    uint32_t   field_0x2c30;   /* +0x2c30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x2c34;   /* +0x2c34  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x2c38[0xe98];   /* +0x2c38 pad */
    uint32_t   field_0x3ad0;   /* +0x3ad0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3ad4;   /* +0x3ad4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3ad8;   /* +0x3ad8  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3adc;   /* +0x3adc  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3ae0[0x20];   /* +0x3ae0 pad */
    uint32_t   field_0x3b00;   /* +0x3b00  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3b04;   /* +0x3b04  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3b08[0x28];   /* +0x3b08 pad */
    uint32_t   field_0x3b30;   /* +0x3b30  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3b34;   /* +0x3b34  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3b38;   /* +0x3b38  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3b3c;   /* +0x3b3c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3b40[0x14];   /* +0x3b40 pad */
    uint32_t   field_0x3b54;   /* +0x3b54  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3b58;   /* +0x3b58  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3b5c[0x34];   /* +0x3b5c pad */
    uint32_t   field_0x3b90;   /* +0x3b90  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3b94[0xc];   /* +0x3b94 pad */
    uint32_t   field_0x3ba0;   /* +0x3ba0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3ba4;   /* +0x3ba4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3ba8;   /* +0x3ba8  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3bac;   /* +0x3bac  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3bb0[0x20];   /* +0x3bb0 pad */
    uint32_t   field_0x3bd0;   /* +0x3bd0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3bd4;   /* +0x3bd4  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3bd8[0x1a8];   /* +0x3bd8 pad */
    uint32_t   field_0x3d80;   /* +0x3d80  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3d84[0xdc];   /* +0x3d84 pad */
    uint32_t   field_0x3e60;   /* +0x3e60  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3e64[0x9c];   /* +0x3e64 pad */
    uint32_t   field_0x3f00;   /* +0x3f00  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3f04;   /* +0x3f04  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3f08;   /* +0x3f08  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3f0c[0x4];   /* +0x3f0c pad */
    uint32_t   field_0x3f10;   /* +0x3f10  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3f14;   /* +0x3f14  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3f18;   /* +0x3f18  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3f1c[0x7c];   /* +0x3f1c pad */
    uint32_t   field_0x3f98;   /* +0x3f98  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3f9c;   /* +0x3f9c  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3fa0;   /* +0x3fa0  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3fa4;   /* +0x3fa4  sz=4 rw=r types=idx4 */
    uint32_t   field_0x3fa8;   /* +0x3fa8  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x3fac[0x184];   /* +0x3fac pad */
    uint32_t   field_0x4130;   /* +0x4130  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4134;   /* +0x4134  sz=4 rw=r types=idx4 */
    uint32_t   field_0x4138;   /* +0x4138  sz=4 rw=r types=idx4 */
    uint32_t   field_0x413c;   /* +0x413c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4140[0x28];   /* +0x4140 pad */
    uint32_t   field_0x4168;   /* +0x4168  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x416c[0x34];   /* +0x416c pad */
    uint32_t   field_0x41a0;   /* +0x41a0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x41a4[0x1c];   /* +0x41a4 pad */
    uint32_t   field_0x41c0;   /* +0x41c0  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x41c4[0x74];   /* +0x41c4 pad */
    uint32_t   field_0x4238;   /* +0x4238  sz=4 rw=r types=idx4 */
    uint32_t   field_0x423c;   /* +0x423c  sz=4 rw=r types=idx4 */
    uint8_t    _pad_0x4240[0x4];   /* +0x4240 pad */
};
```
