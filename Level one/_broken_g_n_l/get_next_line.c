<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feturbin <feturbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:51:00 by feturbin          #+#    #+#             */
/*   Updated: 2025/04/30 13:34:22 by feturbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*lire_et_allocate(int fd, char *storage)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(storage);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
	}
	free(buffer);
	return (storage);
}

static char	*extract_line(char *storage)
{
	size_t	len;
	char	*line;

	if (!storage || !*storage)
		return (NULL);
	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	if (storage[len] == '\n')
		len++;
	line = ft_substr(storage, 0, len);
	return (line);
}

static char	*trim_storage(char *storage)
{
	size_t	i;
	char	*new_storage;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_strdup(storage + i + 1);
	free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = lire_et_allocate(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	storage = trim_storage(storage);
	return (line);
}
=======
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

>>>>>>> 41238ce80c3dcd7573a4ce1802e61578e5d943c3
