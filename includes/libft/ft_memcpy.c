/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:49:30 by irkalini          #+#    #+#             */
/*   Updated: 2024/06/03 17:29:18 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_c;
	unsigned char		*dest_c;

	dest_c = dest;
	src_c = src;
	if (!dest && !src)
		return (0);
	while (n > 0)
	{
		*dest_c = *src_c;
		dest_c++;
		src_c++;
		n--;
	}
	return (dest);
}
