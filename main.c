#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
  void *p;

  p = malloc(50);
  memcpy(p, "test", 4);
}
