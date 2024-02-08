/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfazaz <hfazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:00:17 by hfazaz            #+#    #+#             */
/*   Updated: 2024/01/09 16:18:09 by hfazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(int fd, char *str)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = malloc((size_t)BUFFER_SIZE + 1);
	if (!tmp)
	{
		return (NULL);
	}
	while (i != 0 && !ft_strchr(str, '\n'))
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
		{
			free(tmp);
			free(str);
			return (NULL);
		}
		tmp[i] = '\0';
		str = ft_strjoin(str, tmp);
		if (!str)
			return (NULL);
	}
	free(tmp);
	return (str);
}

char	*read_line(char *str)
{
	char	*p;
	long	i;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i])
		i++;
	p = malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		p[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		p[i++] = '\n';
	p[i] = '\0';
	return (p);
}

char	*get_next(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	line = malloc(ft_strlen(str) - i + 1);
	if (!line)
		return (NULL);
	if (str[i] == '\n')
		i++;
	while (str[i])
		line[j++] = str[i++];
	line[j] = '\0';
	free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = get_line(fd, str);
	if (!str)
		return (NULL);
	line = read_line(str);
	str = get_next(str);
	return (line);
}
// int main(void)
// {
//     int fd = open("file.txt",O_RDONLY);
//     // int fd2 = open("get_next_line.c",O_RDONLY);
//     char *line;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         // line = get_next_line_bonus(fd2);
//         // printf("%s", line);
//     }
//     }
