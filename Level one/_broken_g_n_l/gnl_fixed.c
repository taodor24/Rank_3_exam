
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

#include <unistd.h>
#include <stdlib.h>

char *ft_strchr(char *s, char c)
{
	if(!s) return NULL;	
    int i = 0;
    while (s[i] && s[i] != c)
        i++;
    if (s[i] == c)
        return (s + i);
    return NULL;
}

size_t ft_strlen(char *s)
{
	if (!s) return 0;
    size_t ret = 0;
    while (s[ret])
        ret++;
    return ret;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	if(!dest || !src) return dest;
	int i = 0;
    while (i < n)
    {
	    ((char *)dest)[i] = ((char *)src)[i];
	    i++;
    }
    return dest;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	if(!s1) return 0;
    size_t size1 = *s1 ? ft_strlen(*s1) : 0;
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
        if(read_ret == 0)
	{
		b[0] ='\0';
		if( !ret || !(*ret))
		{
			free(ret);
			return NULL;
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
    size_t i = 0;
    size_t j = tmp - b +1;
    while(b[j])
	   b[i++] = b[j++];
    b[i] ='\0';

    return ret;
}

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