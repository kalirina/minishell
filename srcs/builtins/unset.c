/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irkalini <irkalini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:17:24 by irkalini          #+#    #+#             */
/*   Updated: 2025/03/17 19:44:41 by irkalini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	connect(char **environ, int j)
{
	while (environ[j])
	{
		environ[j] = environ[j+1];
		j++;
	}
	environ[j] = NULL;
}

int	is_valid_var(char *name)
{
	if (*name == '\0' || !(*name == '_' || ft_isalpha(*name)))
		return (0);
	name++;
	while (*name)
	{
		if (!(*name == '_' || ft_isalpha(*name)))
			return (0);
		name++;
	}
	return (1);
}

void	unset_cmd(char **args)
{
	extern char	**environ;
	int			i;
	int			j;

	i = 1;
	while (args[i])
	{
		if (!is_valid_var(args[i]))
			printf("Error\n");
		j = 0;
		while (environ[j])
		{
			if (strncmp(environ[j], args[i], ft_strlen(args[i])) == 0 &&
				environ[j][ft_strlen(args[i])] == '=')
				connect(environ,j);
			else
				j++;
		}
		i++;
	}
}

void main(int argc, char **argv)
{
	unset_cmd(argv);
}
