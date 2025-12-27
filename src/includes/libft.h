/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:13:55 by hkonte            #+#    #+#             */
/*   Updated: 2024/11/29 13:14:27 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

unsigned long long	ft_atoull(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_isdigit(int c);
void				*ft_memset(void	*s, int c, size_t n);
void				ft_putchar_fd(const char c, int fd);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(unsigned long long nb, int fd);
void				ft_putstr_fd(const char *s, int fd);
char				**ft_split(const char *s, const char c);
char				*ft_strchr(const char *str, const char c);
char				*ft_strdup(const char *s);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*add_word(char const *s, int i, int k);
void				free_split(char **res, int j);

#endif