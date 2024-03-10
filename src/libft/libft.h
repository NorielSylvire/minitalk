/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:44:21 by fhongu            #+#    #+#             */
/*   Updated: 2023/11/28 21:40:18 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# ifndef HASMAP_DEFAULT_SIZE
#  define HASHMAP_DEFAULT_SIZE 20
# endif
# ifndef HASHMAP_MAX_LOAD
#  define HASHMAP_MAX_LOAD 0.75f
# endif
# ifndef HASHMAP_RESIZE_FACTOR
#  define HASHMAP_RESIZE_FACTOR 2
# endif

typedef unsigned short	t_ushort;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_key_value
{
	void	*value;
	void	*key;
}	t_key_value;

typedef struct s_hashmap
{
	void	(*del)(void *);
	t_list	**map;
	int		size;
	int		count;

}	t_hashmap;

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isupper(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_free(void **ptr);
char		*ft_strdup(const char *s1);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_preppend(const char *str, const char *pre, int fr_s, int fr_p);
char		*ft_append(const char *str, const char *apd, int fr_s, int fr_a);
char		*ft_strinsert(const char *str, const char *ins, size_t pos);
char		**ft_split(const char *s, char c);
char		*ft_itoa(int n);
char		*ft_ltoa(long n);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char		*ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(const char *s, int fd);
/** @brief Prints a substring to the designated fd.
 *
 * Prints a subset of a string to the provided file descriptor.
 * The substring contains all characters from the start position to the
 * end position, both included.
 *
 * @param str the string from which to print the substring
 * @param start the index of the first char of the substring
 * @param end the index of the last char of the substring
 * @param fd the file destriptor to print to
 * @return The number of characters that where printed to the fd
 */
int			ft_putsubstr_fd(const char *str, size_t start, size_t end, int fd);
int			ft_putendl_fd(const char *s, int fd);
int			ft_putnbr_fd(int n, int fd);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new_lmn);
void		ft_lstadd_back(t_list **lst, t_list *new_lmn);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_hashmap	*ft_hmap_new(void (*del)(void *));
void		ft_hmap_free(t_hashmap *hmap);
t_hashmap	*ft_hmap_resize(t_hashmap *hmap);
void		ft_hmap_add(t_hashmap *hmap, void *key, void *value, size_t len);
void		ft_hmap_delete(t_hashmap *hmap, void *key, size_t len);
t_ushort	ft_hash(unsigned char *key, size_t nbytes);
void		*ft_hmap_get(t_hashmap *hmap, void *key, size_t len);
void		ft_hmap_edit(t_hashmap *hmap, void *key, void *value, size_t len);

#endif
