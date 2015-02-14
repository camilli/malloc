#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
  void *p;
  void *p2;

  p = malloc(50);
  p2 = malloc(50);
  memcpy(p, "test", 4);
  memcpy(p2, "test", 4);

}
