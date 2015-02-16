#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
   void *p;
   void *p2;
   int	i;
   void	*tmp;

   i = 0;
   while (i < 5)
     {
       p = malloc(50);
       p2 = malloc(75);
       memcpy(p, "test", 4);
       memcpy(p2, "test", 4);
       free (p);
       free (p2);
       ++i;
     }
 calloc(2, 4);
}
