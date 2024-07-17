#include "config.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  const char *hello_world = "Hello, World!";
  const char *hello_world_encoded = "SGVsbG8sIFdvcmxkIQ==";
  printf("'%s', encoded: '%s'\n", hello_world, hello_world_encoded);

  uint8_t b64n[1024];
  char b64p[1024];

  int b64nlen = b64_pton(hello_world_encoded, b64n, sizeof(b64n));
  printf("wire length: %d\n", b64nlen);
  if (b64nlen == -1)
    exit(1);
  int b64plen = b64_ntop(b64n, b64nlen, b64p, sizeof(b64p));
  printf("text length: %d\n", b64plen);
  printf("encoded: %s\n", b64p);

  return 0;
}
