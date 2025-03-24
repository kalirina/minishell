/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:46:06 by irkalini          #+#    #+#             */
/*   Updated: 2024/05/29 13:28:59 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	s1;
	size_t	s2;

	i = 0;
	s1 = ft_strlen(dst);
	s2 = ft_strlen(src);
	if (siz <= s1)
		return (siz + s2);
	while (s1 + i < siz - 1 && src[i])
	{
		dst[s1 + i] = src[i];
		i++;
	}
	dst[s1 + i] = '\0';
	return (s1 + s2);
}
