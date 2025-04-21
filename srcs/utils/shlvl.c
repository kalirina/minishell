/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 09:31:44 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/21 18:45:25 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_shlv_flag(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SECRET_F=", 9) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	add_shlv_flag(t_shell *shell)
{
	char	*shlvl_flag;

	shlvl_flag = ft_strdup("SECRET_F=1");
	if (!shlvl_flag)
	{
		perror("shlvl dup");
		return ;
	}
	if (export_add_var(shell, shlvl_flag) != 0)
	{
		free(shlvl_flag);
		return ;
	}
}

char	*augment_shlvl(t_shell *shell, int i)
{
	char	*env;
	char	*res;
	char	*new;
	char	*old;
	int		j;

	env = shell->my_environ[i];
	if (!env[6])
		return (NULL);
	old = ft_strdup(&env[6]);
	if (!old)
		return (NULL);
	j = ft_atoi(old) + 1;
	free(old);
	new = ft_itoa(j);
	res = new_strjoin("SHLVL=", new);
	free(new);
	if (!res)
		return (perror("Error shlvl strjoin"), NULL);
	printf("res: %s\n", res);
	return (res);
}

void	handle_shlvl(t_shell *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!check_shlv_flag(shell->my_environ))
		add_shlv_flag(shell);
	else
	{
		while (shell->my_environ[i])
		{
			if (ft_strncmp(shell->my_environ[i], "SHLVL=", 6) == 0)
			{	
				tmp = augment_shlvl(shell, i);
				free(shell->my_environ[i]);
				shell->my_environ[i] = tmp;
				break;
			}
			i++;
		}	
	}
	}
