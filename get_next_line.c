/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 23:31:54 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/06/13 20:43:34 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		dst = malloc(1 * sizeof(char));
		if (!dst)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	i = 0;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < (unsigned int)len && s[i + start])
	{
		dst[i] = s[i + start];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

//This function gets buffer and returns the part of buffer located after \n. it first copies it to copy string and then copies back from the right index.
//if there is no \n, then it would return NULL. because it means that there is no part of buffer which is interesting for us and we are at end of the file.
//since I am using strdup and it has malloc, i free the space when i am done.

char	*ft_updatebuf(char *buffer)
{
	char	*copy;
	int		i;

	i = 0;
	copy = ft_strdup(buffer);
	if (ft_strchr(buffer, '\n'))
	{
		while (buffer[i] != '\n' && buffer[i] != '\0')
			i++;
		ft_strcpy(buffer, &copy[i + 1]);
	}
	if (!ft_strchr(copy, '\n'))
	{
		if (copy)
			free(copy);
		ft_bzero(buffer, MAXSIZE);
		return (buffer);
	}	
	if (copy)
		free(copy);
	return (buffer);
}

// this function gets beuffer2 (which is the accumulation of buffers) and returns the left string of it (which means the requested line).
// if there is no \n, it means the whole of this buffer should be returned as a line so it returns buf.
// since the line always have to be allocated memory (I dont know why, and the subject file doesnt emphasize on that, but i understood it from the tripoullie tester behavior), when I return
// buf, it is from an un-allocated memory. then the tester wants to free it and gives me extra freeing error. so, I use strdup, then an allocated memory will be returned and tester is fine with it!

char	*ft_leftstr(char *buf, ssize_t *counter)
{
	char	*ptr;
	char	*leftstr;
	size_t	i;

	i = *counter;
	leftstr = NULL;
	while (i < MAXSIZE)
	{
		buf[i] = '\0';
		i++;
	}
	ptr = ft_strchr(buf, '\n');
	if (ptr)
		leftstr = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(ptr) + 1);
	else
		return (ft_strdup(buf));
	return (leftstr);
}

//I allocate memory for buffer. but my buffer is forgeting the values in each call. So I have a static string which is a buffer, holding my different buffers.
// so as soon as there is no \n seen, or we are not reached end of the line, it will countinue reading. (because we wanna return a complete line obviousely!)
//if something is read, then I append the buffer to the previous read items (using strcat). I use strcat because I found it more convenient. It doesnt allocate memory so 
//you don't have to free stuff. Also it doesn't return value so you dont have to deal with other variables.
//then I check if we are end of the file, program returns null. otherwise, the ft_leftstr function extracts the line part and the ft_updatebuf function updates buffer.
// the point is, it is pretty necessary to null terminate the buf2 wherever it has no value from the read file in it, otherwise the other functions wont know when to stop searching through the buffer. 
//thats why I have a counter variable and I count the number of read chars. So I pass it to ft_leftstr to null terminate the buf2 at the exact point. (I could have done that in the below 
//function but the limitation of norminete didn't allow me!) 

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	static char		buf2[MAXSIZE];
	char			*line;
	ssize_t			n;
	static ssize_t	counter = 0;

	line = NULL;
	if (fd < 0 || fd > FDMAX || BUFFER_SIZE <= 0)
		return (NULL);
	ft_bzero(buf, BUFFER_SIZE + 1);
	n = 1;
	while (!ft_strchr(buf2, '\n') && n)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (0);
		counter = counter + n;
		if (n)
			ft_strcat(buf2, buf);
	}
	if ((n == 0 && !buf[0]) && !buf2[0])
		return (0);
	line = ft_leftstr(buf2, &counter);
	ft_updatebuf(buf2);
	return (line);
}
//also it is good to always close a file when you open it. I got some crazy results when I didnt close.
// int main()
// {
// 	int	fd;
// 	fd = open("poone.txt", O_RDONLY);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		printf("\n i: %d the function output: |%s|\n", i, get_next_line(fd));
// 	}
// 	close(fd);
// }
