
#include "../cub.h"

char	*ft_substr(char *s,  int start, int len)
{
	char	*ss;
	int	i;
	int	siz;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		siz = ft_strlen(s) - start;
	else
		siz = len;
	ss = malloc((siz + 1) * sizeof(char));
	if (!ss)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(ss));
	i = 0;
	while (i < siz)
	{
		ss[i] = s[start + i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

static int	ft_nworth(char *s, char c)
{
	int	count;
	
	count = 1;
	if (!s || !*s)
		return (1);
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count + 1);
}

// void	*free(char **a, int j)
// {
// 	while (j > 0)
// 	{
// 		free(a[j - 1]);
// 		j--;
// 	}
// 	free(a);
// 	return (NULL);
// }

static char	**ft_fill(char *s, char c, char **arr)
{
	int	start;
	int	i;
	int	j;

	start = 0;
	i = 0;
	j = 0;
	while (1)
	{
		if (s[i] == c || s[i] == '\0')
		{
			arr[j] = ft_substr(s, start, i - start);
			if (!arr[j])
				return (NULL);
			j++;
			if (s[i] == '\0')
				break;
			start = i + 1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char *s, char c)
{
	char	**a;

	if (!s)
		return (NULL);
	a = malloc(ft_nworth(s, c) * sizeof(char *));
	if (!a)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(a));
	return (ft_fill(s, c, a));
}
