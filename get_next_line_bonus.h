/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkuay <wkuay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 14:24:42 by wkuay             #+#    #+#             */
/*   Updated: 2026/10/24 14:24:42 by wkuay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_gnl
{
	int				fd;
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

t_gnl	*gnl_new_node(t_gnl **lst, int fd);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void	*dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*read_and_store(int fd, char *saved_str);
void	*remove_file_node(t_gnl **lst, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	line_separator(char *saved_str, int c);
char	*get_next_line(int fd);

#endif