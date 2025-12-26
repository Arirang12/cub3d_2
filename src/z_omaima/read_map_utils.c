#include "../cub.h"

int ft_strlen(char *s1)
{
    int i;

    i = 0;
    while (s1[i])
        i++;
    return (i);
}

char	*ft_strdup(char *s1)
{
	char	*dup;
	int	len;
	int	i;

	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(dup));
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*strdup_map(char *s1, int len)
{
	char	*dup;
	int	i;

	dup = ft_calloc((len + 1), sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	// dup[i] = '\0';
	return (dup);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		s1[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc(count * size);
	if (!s)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(s));
	ft_bzero(s, (count * size));
	return (s);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		tl;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	tl = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(sizeof(char) * tl + 1);
	if (!s3)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(s3));
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

int	ft_atoi(char *str)
{
	int		sign;
	long	nb;

	nb = 0;
	sign = 1;
	while (*str == 32 || (*str <= 13 && *str >= 9))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

static	int	checker(char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		len;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	len = ft_strlen(s1) - 1;
	while (checker(s1[start], set))
		start++;
	if (start == len + 1)
		return (ft_strdup(""));
	while (checker(s1[len], set) && len > start)
		len--;
	ptr = ft_substr(s1, start, (len + 1) - start);
	return (ptr);
}
