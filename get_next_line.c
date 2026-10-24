/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkuay <wkuay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 21:19:55 by wkuay             #+#    #+#             */
/*   Updated: 2026/10/24 18:09:39 by wkuay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_store(int fd, char *saved_str)
{
	char	*new_str;
	char	*temp;
	ssize_t	bytes_read;

	new_str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (new_str == NULL)
		return (free_str(&saved_str));
	bytes_read = 1;
	while (ft_strchr(saved_str, '\n') == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, new_str, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(new_str), free_str(&saved_str));
		if (bytes_read > 0)
		{
			new_str[bytes_read] = '\0';
			temp = ft_strjoin(saved_str, new_str);
			if (temp == NULL)
				return (free(new_str), free_str(&saved_str));
			free(saved_str);
			saved_str = temp;
		}
	}
	free(new_str);
	return (saved_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	str_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
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

char	*free_str(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*saved_str;
	char		*str;
	char		*temp;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved_str = read_and_store(fd, saved_str);
	if (saved_str == NULL || saved_str[0] == '\0')
		return (free_str(&saved_str));
	i = line_separator(saved_str, '\n');
	str = ft_substr(saved_str, 0, i);
	if (str == NULL)
		return (free_str(&saved_str));
	temp = ft_substr(saved_str, i, ft_strlen(saved_str) - i);
	if (temp == NULL)
		return (free(str), free_str(&saved_str));
	free(saved_str);
	saved_str = temp;
	if (saved_str != NULL && saved_str[0] == '\0')
		free_str(&saved_str);
	return (str);
}
