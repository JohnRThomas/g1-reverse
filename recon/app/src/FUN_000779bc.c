/* Reconstructed FUN_000779bc @ 0x779bc  (parity: 300/300 trials, PROVEN) */

extern int FUN_0000ef12(const char *text);
extern void FUN_00078f88(unsigned int a, void* b, unsigned int c, void* d);

struct format_record {
  unsigned int value;
  unsigned int text_length;
  unsigned int reserved_08;
  unsigned short type;
  unsigned short limit;
  unsigned int repeated_value;
  unsigned int repeated_length;
  unsigned int reserved_18[3];
  unsigned int formatter;
  unsigned int reserved_28[3];
  unsigned int state_34;
  unsigned int reserved_38[4];
  unsigned int state_48;
};

void FUN_000779bc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  struct format_record record;
  unsigned int arguments[2] = {param_3, param_4};

  record.type = 0x204;
  record.value = param_1;
  record.repeated_value = param_1;
  record.text_length = FUN_0000ef12((const char *)param_1);
  record.formatter = 0x86f57;
  record.limit = 0xffff;
  record.repeated_length = record.text_length;
  record.state_34 = 0;
  record.state_48 = 0;
  FUN_00078f88(*(volatile unsigned int *)0x20002d20UL, &record, param_2, arguments);
}
