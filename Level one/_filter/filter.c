#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BUF_SIZE 1024

int main(int ac, char **av)
{
    if (ac != 2 || !*av[1])
        return 1;

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

