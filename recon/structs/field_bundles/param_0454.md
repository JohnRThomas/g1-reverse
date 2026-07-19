### struct aes_key_context  (library:AES context (CryptoCell/mbedtls))  cid=param_0454

purpose: AES key-loading context read by LoadAesKey: eight key words, a rounds/length word, a status byte, and a trailing word.

This object is accessed by these functions (read their fully-named source):
  - LoadAesKey  (as param_1)  [no source file]

Current layout — fields named `field_0xNN` NEED names; keep offsets unchanged:
```c
struct aes_key_context {
    uint32_t     key_word_0;  /* +0x10  rw=r sz=4 */
    uint32_t     key_word_1;  /* +0x14  rw=r sz=4 */
    uint32_t     key_word_2;  /* +0x18  rw=r sz=4 */
    uint32_t     key_word_3;  /* +0x1c  rw=r sz=4 */
    uint32_t     key_word_4;  /* +0x20  rw=r sz=4 */
    uint32_t     key_word_5;  /* +0x24  rw=r sz=4 */
    uint32_t     key_word_6;  /* +0x28  rw=r sz=4 */
    uint32_t     key_word_7;  /* +0x2c  rw=r sz=4 */
    uint32_t     rounds_or_len;  /* +0x30  rw=r sz=4 */
    uint8_t      status;  /* +0x3c  rw=r sz=1 */
    uint32_t     field_0x40;  /* +0x40  rw=r sz=4 */   <-- NAME ME
};
```