/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:02:12 by enrmarti          #+#    #+#             */
/*   Updated: 2025/04/10 14:40:03 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*echo_env_val(t_shell *shell, char *var)
{
	int		i;
	char	*value;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var);
	value = NULL;
	while (shell->my_environ[i] && !value)
	{
		if (ft_strncmp(shell->my_environ[i], var, var_len) == 0
			&& shell->my_environ[i][var_len] == '=')
		{
			value = ft_strdup(shell->my_environ[i] + var_len + 1);
			break ;
		}
		i++;
	}
	return (value);
}

//INITIALISE THE t_expansion STRUCT
t_expansion	*init_expansion(char *token)
{
	t_expansion	*exp;

	exp = malloc(sizeof(t_expansion));
	if (!exp)
		return (NULL);
	exp->in_single_quote = false; 
	exp->in_double_quote = false;
	exp->i = 0;
	exp->len = ft_strlen(token);
	exp->token = token; 
	exp->res = ft_strdup("");
	return (exp);
}

//APPEND THE GIVEN CHAR AT THE END OF THE STR
char	*append_char(char *str, char c)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(str);
	res = malloc(len + 2 * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(str);
	return (res);
}

//JUST TO MAKE STRNJOIN SHORTER 
char	*util_strnjoin(char *ptr, char *s1, char *s2, int i, int j)
{
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

//JUST LIKE ft_strjoin, EXTRA CHECK FOR EMPTY STRING AT THE START
char	*new_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *)malloc(sizeof(char) * len);
	if (!ptr || !s1 || !s2)
		return (0);
	ptr = util_strnjoin(ptr, s1, s2, i, j);
	free(s1);
	return (ptr);
}
