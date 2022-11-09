/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:44:17 by hmaronen          #+#    #+#             */
/*   Updated: 2021/12/21 17:53:51 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../includes/get_next_line.h"
# include "../includes/ft_printf.h"

typedef struct s_list
{
	void			*content;	
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void	ft_putchar(char c);
void	ft_putstr(char const *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t len);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s);
char	*ft_itoa(int n);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
char	**ft_strsplit(char const *s, char c);
t_list	*ft_lstnew(void const *content, size_t content_size);
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void	ft_lstadd(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void	ft_print_list(t_list *list);

size_t	ft_word_count(const char *s, char c);
void	ft_print_array(char **arr);
int		ft_isspace(const char c);
int		ft_digit_counter(unsigned long n, int base);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lcase(char *s);
char	*ft_strndup(const char *str, size_t n);
size_t	find_eofl(char *str);
void	ft_realloc(char **s1, const char *s2);
int		get_next_line(const int fd, char **line);

char	**ft_arrnew(size_t str_count, size_t str_len);
void	ft_free_2d_array(char **array);

char	*ft_strrev(char *str);
char	*ft_strtoupper(char *string);
int		ft_isodd(int number);
int		ft_pow(int base, int exponent);
char	*ft_itoa_base(long dec, int base);
char	*ft_unsigned_itoa_base(unsigned long dec, int base);

void	ft_puterror(char *error_msg);
long	ft_atol(const char *str);
int		ft_isnumber(char *string);
int		ft_nbr_in_array(int number, int *array, int array_size);
int		ft_count_pointers(char **array);

int		ft_printf(const char *format, ...);

void	sort_int_tab(int *tab, int length);
void	ft_print_tab(int *tab, size_t tab_size);

#endif
