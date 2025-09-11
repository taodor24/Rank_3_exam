#ifndef BUFFER_SIZE            // in notes you can see what i've changed compared to broken version
#define BUFFER_SIZE 32
#endif

#include <unistd.h>
#include <stdlib.h>

char *ft_strchr(char *s, char c)
{
	if(!s) return NULL; //    NULL check!
    int i = 0;
    while (s[i] && s[i] != c)
        i++;
    if (s[i] == c)
        return (s + i);
    return NULL;
}

size_t ft_strlen(char *s)
{
	if (!s) return 0;     //                       NULL check!
    size_t ret = 0;
    while (s[ret])
        ret++;
    return ret;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	if(!dest || !src) return dest; //               NULL check!
	int i = 0;                     // rewrite function
    while (i < n)
    {
	    ((char *)dest)[i] = ((char *)src)[i];
	    i++;
    }
    return dest;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	if(!s1) return 0;                         //    NULL check!
    size_t size1 = *s1 ? ft_strlen(*s1) : 0;  // Modified function
    char *tmp = malloc(size1 + size2 + 1);
    if (!tmp)
        return 0;
    if(*s1) ft_memcpy(tmp, *s1, size1);
    if(s2) ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = 0;
    free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, char *s2)
{
	if(!s2) return 1;
    return str_append_mem(s1, s2, ft_strlen(s2));
}

char *get_next_line(int fd)
{
    static char b[BUFFER_SIZE + 1] = "";
    char *ret = NULL;
    char *tmp = ft_strchr(b, '\n');

    while (!tmp)
    {
        if (!str_append_str(&ret, b))
            return NULL;

        int read_ret = read(fd, b, BUFFER_SIZE);
        if(read_ret == 0)                           // EOF processing is added
	{
		b[0] ='\0';
		if( !ret || !(*ret))
		{
			free(ret);
			return NULL;to test errors
		}
		return ret;
	}
	if (read_ret == -1)
        {
            free(ret);
            return NULL;
        }
        b[read_ret] = 0;
        tmp = ft_strchr(b, '\n');
    }

    if (!str_append_mem(&ret, b, tmp - b + 1))
    {
        free(ret);
        return NULL;
    }
    size_t i = 0;                                    // buffer clean after return of a string
    size_t j = tmp - b +1;
    while(b[j])
	   b[i++] = b[j++];
    b[i] ='\0';

    return ret;
}


/*
#include <stdio.h>
#include <fcntl.h>
int main(int ac, char **av)
{
	int fd;
	fd = open(av[1], O_RDONLY);
	if(fd < 0)
		return 1;
	char *lire;
	while((lire = get_next_line(fd)))
	{
		printf("%s", lire);
		free(lire);
	}
	close(fd);
}
*/






/// MAIN  to test errors: 
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{
    // --- Test 1: no file provided ---
    if (ac < 2)
    {
        printf("❌ Error: no file argument provided\n");
        return 1;
    }

    // --- Test 2: opening a non-existing file ---
    int fd = open("no_such_file.txt", O_RDONLY);
    if (fd < 0)
        printf("✅ Test: non-existing file handled correctly\n");

    // --- Test 3: empty file ---
    fd = open("empty.txt", O_RDONLY);
    if (fd >= 0)
    {
        char *line = get_next_line(fd);
        if (!line)
            printf("✅ Test: empty file -> returned NULL as expected\n");
        else
        {
            printf("❌ Error: empty file returned a line: %s\n", line);
            free(line);
        }
        close(fd);
    }

    // --- Test 4: file without a newline ---
    fd = open("no_newline.txt", O_RDONLY);
    if (fd >= 0)
    {
        char *line;
        while ((line = get_next_line(fd)))
        {
            printf("Line (no \\n): \"%s\"\n", line);
            free(line);
        }
        close(fd);
    }

    // --- Test 5: regular file with multiple lines ---
    fd = open(av[1], O_RDONLY);
    if (fd >= 0)
    {
        char *line;
        int i = 1;
        while ((line = get_next_line(fd)))
        {
            printf("Line %d: %s", i++, line);
            free(line);
        }
        close(fd);
    }

    // --- Test 6: functions called with NULL arguments ---
    printf("ft_strlen(NULL) = %zu (expected 0)\n", ft_strlen(NULL));
    printf("ft_strchr(NULL, 'a') = %p (expected NULL)\n", ft_strchr(NULL, 'a'));
    printf("ft_memcpy(NULL, NULL, 5) = %p (expected NULL)\n", ft_memcpy(NULL, NULL, 5));

    return 0;
}
