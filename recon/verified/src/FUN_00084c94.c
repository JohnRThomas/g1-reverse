/* Reconstructed FUN_00084c94 @ 0x84c94  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083dc8(unsigned int, unsigned int,
                        unsigned int, unsigned int);

struct request {
  unsigned int reserved_00;
  unsigned int *value;
  unsigned int reserved_08;
  unsigned int reserved_0c;
  unsigned char *completion;
};

void FUN_00084c94(struct request *request)
{
  int status = FUN_00083dc8(*request->value, 7, 1, 1);
  if (status >= 0) {
    *request->completion = 0;
  }
}
