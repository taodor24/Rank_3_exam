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
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(int ac, char **av)
{
    if (ac != 2 || !*av[1])
        return 1;

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