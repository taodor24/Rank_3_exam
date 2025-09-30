
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

#include <unistd.h>
#include <stdlib.h>

char *ft_strchr(char *s, char c)
{
    int i = 0;                     //    needs a NULL check!
    while (s[i] && s[i] != c)
        i++;
    if (s[i] == c)
        return (s + i);
    return NULL;
}


size_t ft_strlen(char *s)
{
    size_t ret = 0;                 //      needs a NULL check!
    while (s[ret])
        ret++;
    return ret;
}


void *ft_memcpy(void *dest, const void *src, size_t n)
{                                                           //       needs a   NULL check!
    while (n-- > 0)                                        // rewrite a whole function
        ((char *)dest)[n] = ((char *)src)[n];
    return dest;
}





int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);                       //    add a NULL check!
    char *tmp = malloc(size1 + size2 + 1);                // Modified function 
    if (!tmp)
        return 0;
    ft_memcpy(tmp, *s1, size1);
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = 0;
    free(*s1);
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, char *s2)
{
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
        if (read_ret == -1)                                    // add a EOF processing
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
                                                        // add a buffer clean after return of a string
    return ret;
}





#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    // --- Test 1: NULL checks ---
    printf("ft_strlen(NULL) = %zu (expected 0)\n", ft_strlen(NULL));
    printf("ft_strchr(NULL,'a') = %p (expected NULL)\n", ft_strchr(NULL, 'a'));
    printf("ft_memcpy(NULL,NULL,5) = %p (expected NULL)\n\n", ft_memcpy(NULL, NULL, 5));

    // --- Test 2: empty file ---
    int fd = open("empty.txt", O_RDONLY);
    printf("Empty file -> %s\n\n", get_next_line(fd)); // должно быть NULL
    close(fd);

    // --- Test 3: file without newline ---
    fd = open("no_newline.txt", O_RDONLY);
    char *line = get_next_line(fd);
    printf("No newline -> %s\n\n", line); // должен вернуть всю строку
    free(line);
    close(fd);

    // --- Test 4: normal file with multiple lines ---
    if (ac > 1)
    {
        fd = open(av[1], O_RDONLY);
        int i = 1;
        while ((line = get_next_line(fd)))
        {
            printf("Line %d: %s", i++, line); // проверим построчное чтение
            free(line);
        }
        close(fd);
    }
    return 0;
}