/* I used this version on my EXAM. It worked perfectly   */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

int main(int ac, char **av)
{
    if (ac != 2 || !*av[1]) return 1;
    char *needle = av[1];
    size_t nlen = strlen(needle), total = 0;
    char *data = NULL, buf[BUFFER_SIZE];
    ssize_t r;

    while ((r = read(0, buf, BUFFER_SIZE)) > 0) 
    {
        char *tmp = realloc(data, total + r);
        if (!tmp) { perror("Error"); free(data); return 1; }
        data = tmp;
        memcpy(data + total, buf, r);
        total += r;
    }
    
    if (r < 0) { perror("Error"); free(data); return 1; }

    size_t i = 0;
    while (i < total) {
        char *m = memmem(data + i, total - i, needle, nlen);
        if (!m) { write(1, data + i, total - i); break; }
        
        write(1, data + i, m - (data + i));

        size_t j = 0;
        while (j < nlen) {
            write(1, "*", 1);
            j++;
        }

        i = (m - data) + nlen;
    }
    free(data);
    return 0;
} 
