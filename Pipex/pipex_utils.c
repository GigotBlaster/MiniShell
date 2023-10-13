#include "pipex.h"

int	ft_counter(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			i++;
		if (s[i - 1] != c && i > 0)
			count++;
	}
	return (count);
}

void	ft_free(char **strs, int words_index)
{
	while (--words_index >= 0)
		free(strs[words_index]);
	free(strs);
}

char	**ft_split2(const char *s, char c, char **strs, int nb_words)
{
	int	i;
	int	j;
	int	words_index;

	i = 0;
	words_index = 0;
	while (words_index < nb_words)
	{
		while (s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		strs[words_index] = (char *)malloc(sizeof(char) * (j + 1));
		if (!strs[words_index])
		{
			ft_free(strs, words_index);
			return (NULL);
		}
		ft_strlcpy(strs[words_index], &(s[i]), j + 1);
		i += j;
		words_index++;
	}
	strs[words_index] = NULL;
	return (strs);
}

char	**ft_split(char *s, char c)
{
	char	**strs;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_counter(s, c);
	strs = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!strs)
		return (NULL);
	return (ft_split2(s, c, strs, nb_words));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
