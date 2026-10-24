/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkuay <wkuay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 14:45:07 by wkuay             #+#    #+#             */
/*   Updated: 2026/10/24 18:34:39 by wkuay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_gnl	*gnl_new_node(t_gnl **lst, int fd)
{
	t_gnl	*current;
	t_gnl	*new_node;

	if (lst == NULL || fd < 0)
		return (NULL);
	current = *lst;
	while (current != NULL)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_gnl));
	if (new_node == NULL)
		return (NULL);
	new_node->fd = fd;
	new_node->content = NULL;
	new_node->next = *lst;
	*lst = new_node;
	return (new_node);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

void	*ft_memcpy(void	*dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == NULL || src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		s1_len = 0;
	else
	{
		s1_len = 0;
		while (s1[s1_len] != '\0')
			s1_len++;
	}
	s2_len = 0;
	while (s2[s2_len] != '\0')
		s2_len++;
	new_str = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len + 1);
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s, len + 1);
	return (dup);
}
