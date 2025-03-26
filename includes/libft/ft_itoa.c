/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:22:29 by irkalini          #+#    #+#             */
/*   Updated: 2024/05/29 13:27:38 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	if (n == 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*ptr;
	int				len;

	len = ft_len(n);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ptr[len--] = '\0';
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (len >= 0 && nb > 0)
	{
		ptr[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
