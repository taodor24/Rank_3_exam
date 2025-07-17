#include <unistd.h> // read
#include <stdlib.h> // malloc, free

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// --- Вспомогательные функции ---

static size_t ft_strlen_gnl(const char *s)
{
    size_t i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

static char *ft_strchr_gnl(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}

static char *ft_strjoin_gnl(char *s1, char *s2)
{
    char    *new_str;
    size_t  len1;
    size_t  len2;
    size_t  i;
    size_t  j;

    len1 = ft_strlen_gnl(s1);
    len2 = ft_strlen_gnl(s2);
    new_str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!new_str)
    {
        free(s1);
        return (NULL);
    }
    i = 0;
    while (i < len1)
    {
        new_str[i] = s1[i];
        i++;
    }
    j = 0;
    while (j < len2)
    {
        new_str[i + j] = s2[j];
        j++;
    }
    new_str[i + j] = '\0';
    free(s1); // Освобождаем старую строку s1
    return (new_str);
}

// --- Основная функция GNL ---

static char *read_and_stash(int fd, char *stash)
{
    char    *buffer;
    int     bytes_read;

    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
    {
        free(stash);
        return (NULL);
    }
    bytes_read = 1;
    while (!ft_strchr_gnl(stash, '\n') && bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(buffer);
            free(stash);
            return (NULL);
        }
        buffer[bytes_read] = '\0';
        stash = ft_strjoin_gnl(stash, buffer);
        if (!stash) // Проверка на случай ошибки malloc в ft_strjoin_gnl
        {
            free(buffer);
            return (NULL);
        }
    }
    free(buffer);
    return (stash);
}

static char *extract_line(char *stash)
{
    char    *line;
    int     i;

    i = 0;
    if (!stash || stash[0] == '\0') // Если stash пуст или NULL, нет строки
        return (NULL);
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++; // Включаем '\n' в строку
    line = (char *)malloc(sizeof(char) * (i + 1));
    if (!line)
        return (NULL);
    i = 0;
    while (stash[i] && stash[i] != '\n')
    {
        line[i] = stash[i];
        i++;
    }
    if (stash[i] == '\n')
    {
        line[i] = stash[i];
        i++;
    }
    line[i] = '\0';
    return (line);
}

static char *clean_stash(char *stash)
{
    char    *new_stash;
    int     i;
    int     j;

    i = 0;
    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++; // Пропускаем '\n' и то, что до него
    if (!stash[i]) // Если после \n ничего не осталось или его не было
    {
        free(stash);
        return (NULL);
    }
    new_stash = (char *)malloc(sizeof(char) * (ft_strlen_gnl(stash) - i + 1));
    if (!new_stash) // Обработка ошибки malloc
    {
        free(stash);
        return (NULL);
    }
    j = 0;
    while (stash[i])
        new_stash[j++] = stash[i++];
    new_stash[j] = '\0';
    free(stash); // Освобождаем старый stash
    return (new_stash);
}

char *get_next_line(int fd)
{
    static char *stash = NULL; // Статический буфер для сохранения данных
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        if (stash)
        {
            free(stash);
            stash = NULL;
        }
        return (NULL);
    }

    stash = read_and_stash(fd, stash);
    if (!stash)
        return (NULL);

    line = extract_line(stash);
    if (!line && stash && stash[0] == '\0') // Если line пустая, но stash есть и пустой (т.е. был только '\0')
    {
        free(stash);
        stash = NULL;
        return (NULL);
    }

    stash = clean_stash(stash); // stash теперь содержит остаток или NULL

    return (line);
}