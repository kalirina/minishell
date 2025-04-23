/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:16:57 by irkalini          #+#    #+#             */
/*   Updated: 2025/04/23 13:06:15 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_all_digits(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	res;
	int			sign;
	int			i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
			return (LLONG_MAX);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1 && res > (LLONG_MAX / 2) + 1)
		return (LLONG_MIN);
	return (res * sign);
}

int	exit_cmd(t_shell *shell, char **args, t_executer *ex)
{
	int			exit_code;
	long long	arg_val;

	if (!shell->cmd->next)
		ft_putstr_fd("exit\n", 1);
	exit_code = shell->exit_status;
	if (args[1])
	{
		if (!is_all_digits(args[1]))
		{
			print_error("exit", args[1], "numeric argument required");
			exit_code = 2;
		}
		else if (args[2])
			return (print_error("exit", NULL, "too many arguments"));
		else
		{
			arg_val = ft_atoll(args[1]);
			exit_code = (int)(arg_val & 255);
		}
	}
	cleanup_shell(shell);
	free_executer(ex);
	exit(exit_code);
}
