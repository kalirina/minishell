/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:10:15 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/27 03:24:48 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Sorting
static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_env_array(char **array, int count)
{
	int	i;
	int	j;
	int	swapped;

	i = 0;
	if (!array || count < 2)
		return ;
	while (i < count - 1)
	{
		swapped = 0;
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j + 1])) > 0)
			{
				ft_swap(&array[j], &array[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}

char	*get_var(char *arg)
{
	char	*var;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		var = ft_substr(arg, 0, equal_sign - arg);
	else
		var = ft_strdup(arg);
	if (!var)
		perror("minishell: export: malloc failed in get_var");
	return (var);
}

char	*get_val(char *arg)
{
	char	*val;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (NULL);
	val = ft_strdup(equal_sign + 1);
	if (!val)
		perror("minishell: export: malloc failed in get_val");
	return (val);
}
