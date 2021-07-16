/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 12:13:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/16 14:19:24 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_simple_quotes(t_all **all, t_env *envi)
{
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && (*all)->parse->line1[(*all)->parse->i_1] != '\'')
	{
		(*all)->parse->line2[(*all)->parse->i_2++] = (*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->i_1++;
}

void	do_two_quotes(t_all **all, t_env *envi)
{
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && (*all)->parse->line1[(*all)->parse->i_1] != '\"')
	{
		if ((*all)->parse->line1[(*all)->parse->i_1] == '$' && (*all)->parse->line1[(*all)->parse->i_1 + 1] )
			do_dollar(all, envi);
		else
			(*all)->parse->line2[(*all)->parse->i_2++] = (*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->i_1++;
}

void	quotes(t_all *all, t_env *envi)
{
	int	i;

	i = 0;
	while (all->parse->split[i])
	{
		all->parse->i_1 = 0;
		all->parse->i_2 = 0;
		all->parse->line1 = all->parse->split[i];
		all->parse->line2 = (char *)ft_calloc(1000, sizeof(char));
		while (all->parse->line1[all->parse->i_1])
		{
			if (all->parse->line1[all->parse->i_1] == '\'' || all->parse->line1[all->parse->i_1] == '\"' \
									|| all->parse->line1[all->parse->i_1] == '$')
			{
				if (all->parse->line1[all->parse->i_1] == '\'')
					do_simple_quotes(&all, envi);
				else if (all->parse->line1[all->parse->i_1] == '\"')
					do_two_quotes(&all, envi);
				else if (all->parse->line1[all->parse->i_1] == '$' && !ft_check(all->parse->line1[all->parse->i_1 + 1], "\'\""))
					do_dollar(&all, envi);
				else if (all->parse->line1[all->parse->i_1] == '$' && ft_check(all->parse->line1[all->parse->i_1 + 1], "\'\""))
					 all->parse->i_1++;
			}
			else
			{
				all->parse->line2[all->parse->i_2++] = all->parse->line1[all->parse->i_1++];
			}
		}
		all->parse->line2[all->parse->i_2] = '\0';
		all->parse->split2[i] = all->parse->line2;
		free(all->parse->line1);
		i++;
	}
	all->parse->split2[i] = NULL;
	int n = 0;
	while (all->parse->split2[n])
	{
		printf("%s\n", all->parse->split2[n]);
		n++;
	}
}

void	quot(t_all *all, t_env *envi)
{
	while (all->parse)
	{
		all->parse->split2 = malloc(sizeof(char *) * (ft_splitlen(all->parse->split) + 1));
		quotes(all, envi);
		all->parse = all->parse->next;
	}
}
