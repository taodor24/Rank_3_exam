#ifndef GNL_FIXED_H
# define GNL_FIXED_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif


# include <unistd.h>
# include <stdlib.h>

// --- Main function ---
char    *get_next_line(int fd);

// --- Utils ---
size_t   ft_strlen(char *s);
char    *ft_strchr(char *s, char c);
void    *ft_memcpy(void *dest, const void *src, size_t n);
int      str_append_mem(char **s1, char *s2, size_t size2);
int      str_append_str(char **s1, char *s2);

#endif