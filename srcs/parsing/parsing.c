/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enrmarti <enrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:34:54 by enrmarti          #+#    #+#             */
/*   Updated: 2025/02/21 19:21:22 by enrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_command	init_command(char *ps, char *pe)
{
	t_command cmd;
	char	*pt1;
	char	*pt2;
	
	cmd = (t_command) malloc(sizof(t_command));
	pt1 = skip_spaces(ps);
	pt2 = pt1;
	while(pt2 < pe && *pt2 != ' ' && !(*pt2 >= 9 && *pt2 <= 13))
		pt2++;
	pt2 = '\0';
	cmd.program_name = ft_strdup(pt1);
	pt1 = ++pt2;
	
}

char	*get_comp(char **ps, char *pe)
{
	
	char	*cs;
	char	*ec;
	
	
	cs = *ps;	
	ec = ft_seek(*ps, pe, "<|>");
	if (*ec && ec != cs && (*ec == '<' || *ec == '>'))
	if (ec[1] == ec[0])
} 
	void	start_parse(char *buff)
	{
		char	*ps;
		char	*pe;
		
		ps = buff;
		pe = ps + ft_strlen(buff);
		ps = skip_spaces(ps);
		get_comp(&ps, pe);
	}