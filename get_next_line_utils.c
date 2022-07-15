/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:07:48 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/06/18 12:22:42 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*cs;

	i = 0;
	cs = (char *)str;
	while (i < n)
	{
		cs[i] = 0;
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int			i;
	const char	*p;

	i = 0;
	while ((unsigned char)s[i] != (unsigned char)c && s[i] != '\0')
		i++;
	if ((unsigned char)s[i] == (unsigned char)c)
	{
		p = &s[i];
		return ((char *)p);
	}
	else
		return (0);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;
	int		len;

	len = ft_strlen(s);
	dst = (char *)malloc(len + 1);
	i = 0;
	if (!dst)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	dst_len;

	if (!dst)
		dst_len = 0;
	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i] != 0)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	ft_bzero(src, BUFFER_SIZE + 1);
	dst[dst_len + i] = 0;
	return (dst);
}
