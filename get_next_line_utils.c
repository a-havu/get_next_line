/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:41:41 by ahavu             #+#    #+#             */
/*   Updated: 2024/12/27 15:46:45 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	product;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	i = 0;
	product = nmemb * size;
	if ((product / size) != nmemb)
		return (NULL);
	ptr = malloc(product);
	if (ptr)
	{
		while (i < product)
		{
			ptr[i] = '\0';
			i++;
		}
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	total_len;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	k = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = ft_calloc((total_len + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[k])
		new_str[i++] = s2[k++];
	new_str[i] = '\0';
	return (new_str);
}
