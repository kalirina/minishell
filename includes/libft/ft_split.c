/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:29:38 by irkalini          #+#    #+#             */
/*   Updated: 2025/02/21 19:04:46 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(const char *s, char c)
{
	int	e;
	int	words;

	e = 0;
	words = 0;
	while (s[e])
	{
		if (s[e] != c)
		{
			words++;
			while (s[e] != c && s[e])
				e++;
		}
		else
			e++;
	}
	return (words);
}

static void	ft_free_all(char **dest, int i)
{
	while (i > 0)
		free(dest[--i]);
	free(dest);
}

static char	**ft_size(const char *s, char c, char **dest)
{
	int	i;
	int	size;

	i = 0;
	while (*s)
	{
		size = 0;
		if (*s != c)
		{
			while (*s != c && *s && s++)
				size++;
			dest[i] = (char *)malloc(sizeof(char) * (size + 1));
			if (!dest[i])
			{
				ft_free_all(dest, i);
				return (0);
			}
			i++;
		}
		else
			s++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	dest = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!dest)
		return (0);
	dest = ft_size(s, c, dest);
	if (!dest)
		return (0);
	while (*s)
	{
		j = 0;
		if (*s != c)
		{
			while (*s != c && *s)
				dest[i][j++] = *s++;
			dest[i++][j] = '\0';
		}
		else
			s++;
	}
	dest[i] = NULL;
	return (dest);
}
