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
    ssize_t r = 0;

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




/*
OTHER VERSIONS: 

 #define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 42

#endif

int main(int ac, char **av)
{
	if (ac!=2 || !*av[1]) return 1;
	char buf[BUFFER_SIZE];
	char *cuv = av[1];
	char *input = NULL;
	size_t total = 0;
	size_t len = strlen(cuv);
	ssize_t lire;

	while((lire = read(0, buf, BUFFER_SIZE)) > 0)
	{
		char *tmp = realloc(input, total + lire);
		if(!tmp) { perror("Error"); free(input); return 1;}
	       	input = tmp;
		memmove(input + total, buf, lire);
		total += lire;
	}
	if(lire < 0) { perror("Error"); free(input); return 1;}
	size_t pos = 0;
	while( pos < total)
	{
		char *m = memmem(input + pos, total - pos, cuv, len);
		if(!m)
		{
			write(1, input + pos, total - pos);
			break;
		}
		size_t off = m - input;
		write(1, input + pos, off - pos);
		for(size_t i = 0; i < len; i++)
			write(1, "*", 1);
		pos = off + len;
	}
	free(input);
	return 0;
}
*/







/*
#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

int main(int ac, char **av)
{
    if (ac != 2 || !*av[1]) {
        return 1;
    }
    
    char *pat = av[1];
    size_t plen = strlen(pat);
    char buf[BUFFER_SIZE];
    char *input = NULL;
    size_t total = 0;
    ssize_t r;

    while((r = read(0, buf, BUFFER_SIZE)) > 0)
    {
        char *tmp = realloc(input, total + r + 1);
        if(!tmp) {
            perror("Error");
            free(input);
            return 1;
        }
        input = tmp;
        memmove(input + total, buf, r);
        total += r;
    }
    if (r < 0) {
        perror("Error");
        free(input);
        return 1;
    }
    
    if (input) {
        input[total] = '\0';
    }

    size_t pos = 0;
    while(pos < total)
    {
        char *m = memmem(input + pos, total - pos, pat, plen);
        if (!m)
        {
            write(1, input + pos, total - pos);
            break;
        }
        
        size_t off = m - input;
        write(1, input + pos, off - pos);
        
        for(size_t i = 0; i < plen; i++) {
            write(1, "*", 1);
        }
        
        pos = off + plen;
    }
    
    free(input);
    
    return 0;
}
*/




/*
ANOTHER VERSION:

#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BUFFER_SIZE 
#define BUFFER_SIZE 42

#endif

int main(int ac, char **av)
{
    if (ac != 2 || !*av[1]) return 1;
    
    char *pat = av[1]; 
    size_t plen = strlen(pat);
    char buf[BUFFER_SIZE]; 
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
*/



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

