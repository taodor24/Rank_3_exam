#include "get_next_line.h"
#include <string.h>

static size_t    ft_strlen(const char *s)
{
    size_t i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

static char    *ft_strjoin(char *s1, char *s2)
{
    size_t i = 0, j = 0;
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *res = malloc(len1 + len2 + 1);
    if (!res)
        return NULL;

    while (i < len1)
    {
        res[i] = s1[i];
        i++;
    }
    while (j < len2)
    {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';
    free(s1);
    return res;
}

static char    *ft_strchr(const char *s, int c)
{
    size_t i = 0;
    if (!s)
        return NULL;
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)&s[i]);
        i++;
    }
    if (c == '\0')
        return ((char *)&s[i]);
    return NULL;
}

static char    *get_line(char *buf)
{
    size_t i = 0;
    char *line;

    while (buf[i] && buf[i] != '\n')
        i++;
    if (buf[i] == '\n')
        i++;
    line = malloc(i + 1);
    if (!line)
        return NULL;
    i = 0;
    while (buf[i] && buf[i] != '\n')
    {
        line[i] = buf[i];
        i++;
    }
    if (buf[i] == '\n')
    {
        line[i] = '\n';
        i++;
    }
    line[i] = '\0';
    return line;
}

static char    *get_rest(char *buf)
{
    size_t i = 0, j = 0;
    char *rest;

    while (buf[i] && buf[i] != '\n')
        i++;
    if (!buf[i])
        return NULL;
    i++; // Пропустить '\n'
    rest = malloc(ft_strlen(buf + i) + 1);
    if (!rest)
        return NULL;
    while (buf[i])
    {
        rest[j] = buf[i];
        i++;
        j++;
    }
    rest[j] = '\0';
    return rest;
}

char    *get_next_line(int fd)
{
    static char *buf;
    char temp[BUFFER_SIZE + 1];
    ssize_t r;
    char *line;
    char *rest;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    while (!ft_strchr(buf, '\n'))
    {
        r = read(fd, temp, BUFFER_SIZE);
        if (r <= 0)
            break;
        temp[r] = '\0';
        buf = ft_strjoin(buf, temp);
        if (!buf)
            return NULL;
    }

    if (!buf || buf[0] == '\0')
    {
        free(buf);
        buf = NULL;
        return NULL;
    }

    line = get_line(buf);
    rest = get_rest(buf);
    free(buf);
    buf = rest;
    return line;
}


int main(void) {
    char *line;
    while ((line = get_next_line(0)))
    {
        write(1, line, strlen(line));
        free(line);
    }
    return 0;
}

