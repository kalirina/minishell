/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:38:07 by irkalini          #+#    #+#             */
/*   Updated: 2024/06/06 12:57:07 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	lens;

	i = start;
	j = 0;
	lens = ft_strlen(s);
	if (!s)
		return (0);
	if (i >= lens)
		return (ft_strdup(""));
	else if (len > lens - start)
		len = lens - start;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	while (i < lens && j < len)
		ptr[j++] = s[i++];
	ptr[j] = '\0';
	return (ptr);
}
