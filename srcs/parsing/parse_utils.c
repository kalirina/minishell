/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:13:27 by enrmarti          #+#    #+#             */
/*   Updated: 2025/03/06 15:58:29 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*new;

	new = (char *)malloc(sizeof(char) * n + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

bool	is_space(char c)
{
	if (c && (c == ' ' || (c >= 9 && c <= 13)))
		return (true);
	return (false);
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}
