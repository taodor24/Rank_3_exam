<<<<<<< HEAD
#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 2 || !*av[1]) return 1;
    
    char *pat = av[1]; 
    size_t plen = strlen(pat);
    char buf[1024]; 
    ssize_t r;

    while ((r = read(0, buf, sizeof(buf))) > 0) 
    {
        ssize_t i = 0;
        while (i <= r - plen) 
        {
            if (!memcmp(buf + i, pat, plen))
                memset(buf + i, '*', plen);
            i++;
        }
        if (write(1, buf, r) != r) { perror("Error"); return 1; }
    }
    if (r < 0) { perror("Error"); return 1; }
    return 0;
}




/*
ANOTHER VERSION:

#define _GNU_SOURCE
=======
>>>>>>> 41238ce80c3dcd7573a4ce1802e61578e5d943c3
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

<<<<<<< HEAD
=======
#define BUF_SIZE 1024

>>>>>>> 41238ce80c3dcd7573a4ce1802e61578e5d943c3
int main(int ac, char **av)
{
    if (ac != 2 || !*av[1])
        return 1;

<<<<<<< HEAD
    char *pat = av[1];
    size_t plen = strlen(pat);
    size_t bufsize = 1024;
    char *buf = malloc(bufsize);
    if (!buf) { perror("Error"); return 1; }

    ssize_t r;
    while ((r = read(0, buf, bufsize)) > 0)
    {
        char *p;
        ssize_t offset = 0;
        while ((p = memmem(buf + offset, r - offset, pat, plen)))
        {
            memset(p, '*', plen);
            offset = (p - buf) + plen;
        }
        if (write(1, buf, r) != r) { perror("Error"); free(buf); return 1; }
    }

    if (r < 0) { perror("Error"); free(buf); return 1; }

    free(buf);
    return 0;
}
*/
=======
    char *s = av[1];
    size_t len = strlen(s);
    char buf[BUF_SIZE];
    ssize_t r;

    while ((r = read(0, buf, BUF_SIZE)) > 0)
    {
        size_t i = 0;
        
        while (i < (size_t)r)
        {
            char *match = memmem(buf + i, r - i, s, len);
            if (!match)
            {
                write(1, buf + i, r - i);
                break;
            }
            write(1, buf + i, match - (buf + i));

            size_t j = 0;
            while (j < len)
            {
                write(1, "*", 1);
                j++;
            }

            i = (match - buf) + len;
        }
    }

    if (r < 0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return 1;
    }

    return 0;
}

>>>>>>> 41238ce80c3dcd7573a4ce1802e61578e5d943c3
