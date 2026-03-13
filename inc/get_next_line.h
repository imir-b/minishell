#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

char	*get_next_line(int fd);
size_t	ft_gnl_strlen(const char *str);
char	*ft_gnl_strchr(const char *s, int c);
char	*ft_gnl_realloc(char *s1, char *s2);

#endif
