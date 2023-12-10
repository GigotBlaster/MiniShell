/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:23:14 by ibouhssi          #+#    #+#             */
/*   Updated: 2023/12/10 19:26:32 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int updateContext(char c, int context)
{
		if (c == context)
			context = 0;
		else if (!context && c == DQ)
			context = DQ;
		else if (!context && c == SQ)
			context = SQ;
		return context;
}

int	addlength(char *input)
{
	int	len;
	int	i;
	int context;

	len = 0;
	i = 0;
	context = 0;
	while (input[i])
	{
		if (!ft_strchr("<>|", input[i]))
			len++;
		else
		{
			if ((input[i] == '>' && input[i + 1] == '>') || \
			(input[i] == '<' && input[i + 1] == '<'))
			{
				len += 1;
				i++;
			}
			len += 3;
		}
		i++;
	}
	return (len);
}

char	*addspaces(char *input)
{
	int		i;
	int		j;
	char	*output;
	int		len;

	i = -1;
	j = 0;
	len = addlength(input);
	output = malloc(len + 1);
	if (!output)
		return (free(input), NULL);
	ft_memset(output, ' ', len);
	while (input[++i])
	{
		if (!ft_strchr("<>|", input[i]))
			output[j++] = input[i];
		else
		{
			output[++j] = input[i];
			if (!ft_strncmp(&input[i], "<<", 2) || \
			!ft_strncmp(&input[i], ">>",
					2))
				output[++j] = input[i++];
			j += 2;
		}
	}
	output[j] = 0;
	free(input);
	return (output);
}

char	*remspaces(char *str)
{
	size_t	i;
	int		j;
	int		nbspace_start;
	int		nbspace_end;
	char	*newstr;
	int		new_size; //trop de variable 
	int		end; //trop de variable
	i = 0;
	j = 0;
	nbspace_end = 0;
	nbspace_start = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		nbspace_start++;
		i++;
	}
	end = ft_strlen(str) - 1;
	while (end > 0 && (str[end] == ' ' || str[end] == '\t'))
	{
		nbspace_end++;
		end--;
	}
	new_size = ft_strlen(str) - nbspace_start - nbspace_end;
	newstr = (char *)malloc((new_size + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = nbspace_start;
	while (i < ft_strlen(str) - nbspace_end)
	{
		newstr[j] = str[i];
		i++;
		j++;
	}
	newstr[j] = '\0';
//	free(str);
	return (newstr);
}

char	**remspacetab(char **tab)
{
	int		i;
	char	*newstr;

	i = 0;
	while (tab[i])
	{
		newstr = remspaces(tab[i]);
		free(tab[i]);
		tab[i] = newstr;
		i++;
	}
	return (tab);
}
