/* rodata_0x9f6c6 : IPC service string pool (app core)
 *
 * String-literal pool referenced by FUN_00025d40 (IPC / serialization init path).
 * Contains symbol/endpoint names and printf-style log format strings used by the
 * IPC service registration and ipc0 endpoint receive handler.
 *
 * span = 123 bytes, base VA = 0x9f6c6.
 * The final entry "%s()" occupies the last 4 bytes of the span with NO trailing
 * NUL inside this object (its terminator lives in the adjacent rodata object),
 * so the pool is emitted as a raw byte array to guarantee byte-exactness.
 */

const unsigned char rodata_0x9f6c6[123] = {
    /* 0x9f6c6: "register_ipc_service_context\0" */
    'r','e','g','i','s','t','e','r','_','i','p','c','_','s','e','r',
    'v','i','c','e','_','c','o','n','t','e','x','t','\0',
    /* 0x9f6e3: "ipc0_ept_recv\0" */
    'i','p','c','0','_','e','p','t','_','r','e','c','v','\0',
    /* 0x9f6f1: "serialization_init\0" */
    's','e','r','i','a','l','i','z','a','t','i','o','n','_','i','n','i','t','\0',
    /* 0x9f704: "global_ipc_service_send\0" */
    'g','l','o','b','a','l','_','i','p','c','_','s','e','r','v','i',
    'c','e','_','s','e','n','d','\0',
    /* 0x9f71c: "ipc0\0" */
    'i','p','c','0','\0',
    /* 0x9f721: "%s(): %d(ms)\n\0" */
    '%','s','(',')',':',' ','%','d','(','m','s',')','\n','\0',
    /* 0x9f72f: "%s(): enter!\n\0" */
    '%','s','(',')',':',' ','e','n','t','e','r','!','\n','\0',
    /* 0x9f73d: "%s()" (no NUL terminator within this object) */
    '%','s','(',')',
};
