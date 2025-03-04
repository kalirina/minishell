/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:13:27 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/04 13:57:44 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


bool	is_space(char str)
{
	if (!str)
		return (NULL);
	if (str == ' ' || (str >= 9 && str <= 13))
		return (true);
	return (false);
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (s[i] && i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
