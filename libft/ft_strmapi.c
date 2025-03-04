/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:19:11 by irkalini          #+#    #+#             */
/*   Updated: 2024/05/29 13:29:13 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		len;
	int		i;

	if (!s || !f)
		return (0);
	len = 0;
	while (s[len])
		len++;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}
