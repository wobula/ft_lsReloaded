/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include <stddef.h>
# include <locale.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include "printf.h"

# define BUFF_SIZE 32

typedef struct				s_list
{
	void					*content;
	size_t					content_size;
	struct s_list			*next;
}							t_list;

typedef struct				s_vlist
{
	bool					safe;
	void					*content;
	size_t					content_size;
	struct s_vlist			*next;
	struct s_vlist			*prev;
}							t_vlist;

typedef struct 				s_vhead
{
	struct s_vlist			*first;
	struct s_vlist			*last;
	size_t					count;
}							t_vhead;

typedef struct 				s_hshnode
{
	size_t					count;
	struct s_list			*first;
	struct s_list			*last;
}							t_hshnode;

typedef struct 				s_hsh
{
	size_t					size;
	size_t 					count;
	t_hshnode				**data;
}							t_hsh;

typedef struct s_memnode	t_memnode;
typedef struct s_heap_man	t_heap_man;
typedef struct s_vheap_man	t_vheap_man;
typedef struct s_vector		t_vector;
typedef struct s_vmemnode	t_vmemnode;

struct						s_memnode
{
	void					*ptr;
	t_memnode				*prev;
	t_memnode				*next;
};

struct						s_heap_man
{
	t_memnode				*first;
	t_memnode				*last;
};

struct 						s_vheap_man
{
	size_t					count;
	t_heap_man				**nodes;
};

struct 						s_vector
{
	size_t					count;
	void					**ptrs;
};

int					ft_printf(const char *format, ...);
int					ft_dprintf(int fd, const char *format, ...);
int					get_next_line(const int fd, char **line);

void				ft_bzero(void *s, size_t n);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_itoa(int nbr);

void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				*ft_memcpy(void *d, const void *s, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memalloc(size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_hmalloc(size_t size);
void				*ft_hmemalloc(size_t size);
char				*ft_hstrdup(char *hstr);
char				*ft_hstrndup(char *hstr, size_t size);
char				*ft_hstrjoin(char *s1, char *s2);
char				*ft_vhstrdup(char *hstr, size_t channel);
char				*ft_vhstrjoin(const char *s1, const char *s2, size_t channel);
int					ft_hfree(void *ptr);
int					ft_heap_clear(void);
t_heap_man			*ft_heap_singleton(void);

void				**ft_vecgetptr_dynamic(t_vector *this, size_t get);
void				**ft_vecgetptr(t_vector *this, size_t get);
t_vector			*ft_vecmake(size_t size);
void				ft_vecexpand(t_vector **this, size_t count);

void				ft_putchar(char c);
void				ft_putnbr(int nbr);
void				ft_putstr(char *str);
void				ft_fputstr(char *str);
void				ft_fputstr_fd(char *str, int fd);
void				ft_fputstrn_fd(char *str, int max, int fd);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);

void				ft_strclr(char *s);
size_t				ft_strlen(const char *str);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strnstr(const char *big, const char *l, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strchrrev(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s1);
char				*ft_strtrim(char const *s);
char				*ft_strnew(size_t size);
char				*ft_strndup(const char *s1, size_t offset);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strxjoin(char *s1, char *s2, size_t opt);
char				**ft_strsplit(char const *s, char c);

void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int start, size_t len);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));
t_list				*ft_lstnew(void const *content, size_t content_size);

t_heap_man			*ft_vget_singleton_node(size_t channel);
t_vheap_man			*ft_vheap_singleton(void);
void				*ft_vhmalloc(size_t size, size_t channel);
void				*ft_vhmemalloc(size_t size, size_t channel);
int					ft_vheap_clear(void);

void				ft_vheadaddend(t_vhead **head, t_vlist *new);
void				ft_vheadaddpoint(t_vhead **head, void *ptr, size_t channel);
t_vhead				*ft_vheadnew(size_t channel);

t_vlist				*ft_vlstmap(t_vlist *lst, t_vlist *(*f)(t_vlist *));
t_vlist				*ft_vlstnew(void const *content, size_t content_size, size_t channel);
t_vlist				*ft_vlstpoint(void *content, size_t channel);

t_hsh				*ft_hshnew(size_t count, size_t size);
bool				ft_hshremove(t_hsh *table, void *data);
void				ft_hshadd(t_hsh *table, void *content);
void				ft_hshprint(t_hsh *table);

#endif
