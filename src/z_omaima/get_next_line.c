#include "../cub.h"

char	*ft_read_buffer(char *remb, int fd)
{
	char	*buffer;
	int		i;
	int		size_read;

	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	size_read = 1;
	while (size_read > 0)
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read < 0)
			return (NULL);
		buffer[size_read] = '\0';
		remb = ft_strjoin(remb, buffer);
		if (!remb)
			return (NULL);
		i = 0;
		while ((buffer[i]) && (buffer[i] != '\n'))
			i++;
		if (buffer[i] == '\n')
			break ;
	}
	return (remb);
}

char	*ft_get_line(char *remb)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (remb[i] == '\0')
		return (NULL);
	while (remb[i] && remb[i] != '\n')
		i++;
	if (remb[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (remb[j] && j < i)
	{
		line[j] = remb[j];
		j++;
	}
	return (line);
}

char	*ft_remember(char *remb)
{
	char	*save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (remb[i] == '\0')
		return (NULL);
	while (remb[i] && remb[i] != '\n')
		i++;
	if (remb[i] == '\n')
		i++;
	save = ft_calloc((ft_strlen(remb) - i + 1), sizeof(char));
	if (!save)
		return (NULL);
	while (remb[i])
		save[j++] = remb[i++];
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*remb;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remb)
	{
		remb = ft_calloc(1, 1);
		if (!remb)
			return (NULL);
	}
	remb = ft_read_buffer(remb, fd);
	if (!remb)
		return (NULL);
	line = ft_get_line(remb);
	if (!line)
		return ((remb = NULL), NULL);
	remb = ft_remember(remb);
	if (!remb)
		return (NULL);
	if (!remb[0])
		return ((remb = NULL), line);
	return (line);
}
