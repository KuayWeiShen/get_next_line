/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkuay <wkuay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 14:41:16 by wkuay             #+#    #+#             */
/*   Updated: 2026/10/24 19:15:51 by wkuay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_store(int fd, char *saved_str)
{
	char	*new_str;
	char	*temp;
	ssize_t	bytes_read;

	new_str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (new_str == NULL)
		return (free(saved_str), saved_str = NULL, NULL);
	bytes_read = 1;
	while (ft_strchr(saved_str, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, new_str, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(new_str), free(saved_str), saved_str = NULL, NULL);
		if (bytes_read > 0)
		{
			new_str[bytes_read] = '\0';
			temp = ft_strjoin(saved_str, new_str);
			if (temp == NULL)
				return (free(new_str), free(saved_str), saved_str = NULL, NULL);
			free(saved_str);
			saved_str = temp;
		}
	}
	free(new_str);
	return (saved_str);
}

void	*remove_file_node(t_gnl **lst, int fd)
{
	t_gnl	*current;
	t_gnl	*previous;

	if (lst == NULL || fd < 0)
		return (NULL);
	current = *lst;
	previous = NULL;
	while (current != NULL)
	{
		if (current->fd == fd)
		{
			if (previous == NULL)
				*lst = current->next;
			else
				previous->next = current->next;
			free(current->content);
			free(current);
			return (NULL);
		}
		previous = current;
		current = current->next;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	str_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	str_len = 0;
	while (s[str_len] != '\0')
		str_len++;
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	sub_str = (char *)malloc((len + 1) * sizeof(char));
	if (sub_str == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

size_t	line_separator(char *saved_str, int c)
{
	size_t	len;

	if (saved_str == NULL)
		return (0);
	len = 0;
	while (saved_str[len] != '\0' && saved_str[len] != (char)c)
		len++;
	if (saved_str[len] == (char)c)
		len++;
	return (len);
}

char	*get_next_line(int fd)
{
	static t_gnl	*lst;
	t_gnl			*node;
	char			*str;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = gnl_new_node(&lst, fd);
	if (node == NULL)
		return (NULL);
	node->content = read_and_store(fd, node->content);
	if (node->content == NULL || node->content[0] == '\0')
		return (remove_file_node(&lst, fd), NULL);
	str = ft_substr(node->content, 0, line_separator(node->content, '\n'));
	if (str == NULL)
		return (remove_file_node(&lst, fd), NULL);
	temp = ft_strdup(node->content + line_separator(node->content, '\n'));
	if (temp == NULL)
		return (free(str), remove_file_node(&lst, fd), NULL);
	free(node->content);
	node->content = temp;
	if (node->content != NULL && node->content[0] == '\0')
		remove_file_node(&lst, fd);
	return (str);
}
