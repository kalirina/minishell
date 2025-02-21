/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:54:44 by irkalini          #+#    #+#             */
/*   Updated: 2024/06/03 19:10:57 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		start;
	int		end;
	int		len;

	start = 0;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	while (s1[start] && ft_char_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_set(s1[end - 1], set))
		end--;
	len = end - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, &s1[start], len + 1);
	return (ptr);
}
