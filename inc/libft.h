#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

int		ft_strlen(const char *str);
char	*ft_strdup(const char *src);
char	*ft_strndup(char *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*get_next_line(int fd);

#endif
