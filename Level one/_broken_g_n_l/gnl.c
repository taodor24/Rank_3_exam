#include <unistd.h>
#include <stdlib.h>

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 1024
// #endif

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	if (!s)
		return (NULL);
	ch = (char)c;
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
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
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (NULL);
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static int	read_and_stash(int fd, char **stash)
{
	char	*buffer;
	int		bytes_read;
	char	*temp_stash;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	bytes_read = 1;
	while (!ft_strchr(*stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			temp_stash = *stash;
			*stash = ft_strjoin(temp_stash, buffer);
			free(temp_stash);
			if (!*stash)
			{
				free(buffer);
				return (-1);
			}
		}
	}
	free(buffer);
	return (0);
}

static char	*extract_line(char **stash)
{
	char	*line;
	char	*newline_pos;
	size_t	line_len;
	char	*temp_stash;

	if (!*stash || ft_strlen(*stash) == 0)
		return (NULL);
	newline_pos = ft_strchr(*stash, '\n');
	if (newline_pos)
	{
		line_len = newline_pos - *stash + 1;
		line = ft_substr(*stash, 0, line_len);
		if (!line) return (NULL);
		temp_stash = *stash;
		*stash = ft_substr(temp_stash, line_len, ft_strlen(temp_stash) - line_len);
		free(temp_stash);
		if (!*stash && (ft_strlen(temp_stash) - line_len > 0))
		{
			free(line);
			return (NULL);
		}
	}
	else
	{
		line = ft_substr(*stash, 0, ft_strlen(*stash));
		if (!line) return (NULL);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (read_and_stash(fd, &stash[fd]) == -1)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		return (NULL);
	}
	line = extract_line(&stash[fd]);
	return (line);
}