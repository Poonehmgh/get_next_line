/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 21:13:14 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/06/13 20:11:57 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAXSIZE 20000
# define FDMAX 1024

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

void	ft_bzero(void *str, size_t n);
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strdup(const char *s);
char	*ft_strcpy(char *dest, const char *src);

#endif