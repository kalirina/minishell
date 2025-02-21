/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:13:27 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/21 18:58:44 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Returns a pointer to the first instance of a char (to_peek)
//inside the given string (sp), if nothing is found it returns sp
char	*peek(char  *sp, char *es, char *to_peek)     // IS THIS THE SAME AS STRSRCH?????
{
	int 	i;
	char	*start;
	
	start = sp;
	while (*sp && sp < es)
	{
		i = 0;
		while (to_peek[i])
		{
			if (*sp == to_peek[i++])
				return (sp);	
		}
		sp++;
	}
	return (start);
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	return (str);
}