/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 12:13:52 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/13 18:40:52 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	принудительно ставит кавычки, если встречает $ в зависимости от кавычек берет значение env
	или просто печатает строку
*/
void	do_simple_quotes(t_all **all, t_env *envi)
{
	(*all)->parse->line2[(*all)->parse->i_2] = '\'';
	(*all)->parse->i_2++;
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && (*all)->parse->line1[(*all)->parse->i_1] != '\'')
	{
		if ((*all)->parse->line1[(*all)->parse->i_1] == '\"')
		{
			(*all)->parse->flag = 1;
			do_two_quotes(all, envi);
			continue ;
		}
		(*all)->parse->line2[(*all)->parse->i_2++] = (*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->line2[(*all)->parse->i_2] = '\'';
	(*all)->parse->i_2++;
}

void	do_two_quotes(t_all **all, t_env *envi)
{
	(*all)->parse->line2[(*all)->parse->i_2] = '\"';
	(*all)->parse->i_2++;
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && (*all)->parse->line1[(*all)->parse->i_1] != '\"')
	{
		if ((*all)->parse->line1[(*all)->parse->i_1] == '\'')
		{
			do_simple_quotes(all, envi);
			continue ;
		}
		if ((*all)->parse->line1[(*all)->parse->i_1] == '$' && (*all)->parse->flag != 1)
		{
			do_dollar(all, envi);
			continue ;
		}
		(*all)->parse->line2[(*all)->parse->i_2++] = (*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->line2[(*all)->parse->i_2] = '\"';
	(*all)->parse->i_2++;
}

void	for_quotes(t_all *all, t_env *envi)
{
	if (all->parse->line1[all->parse->i_1] == '\'')
		do_simple_quotes(&all, envi);
	if (all->parse->line1[all->parse->i_1] == '\"')
		do_two_quotes(&all, envi);
	if (all->parse->line1[all->parse->i_1] == '$')
		do_dollar(&all, envi);
}

void	quotes(t_all *all, t_env *envi)
{
	int	i;

	i = 0;
	while (all->parse->split[i])
	{
		all->parse->flag = 0;
		all->parse->i_1 = 0;
		all->parse->i_2 = 0;
		all->parse->line1 = all->parse->split[i];
		all->parse->line2 = (char *)ft_calloc(1000, sizeof(char));
		while (all->parse->line1[all->parse->i_1])
		{
			if (all->parse->line1[all->parse->i_1] == '\'' || all->parse->line1[all->parse->i_1] == '\"' \
									|| all->parse->line1[all->parse->i_1] == '$')
				for_quotes(all, envi);
			else
				all->parse->line2[all->parse->i_2++] = all->parse->line1[all->parse->i_1++];
		}
		all->parse->line2[all->parse->i_2] = '\0';
		all->parse->split2[i] = all->parse->line2;
		free(all->parse->line1);
		i++;
	}
	all->parse->split2[i] = NULL;
	free(all->parse->split2);
}
	// int n = 0;
	// while (all->parse->split2[n])
	// {
	// 	printf("%s\n", all->parse->split2[n]);
	// 	n++;
	// }

void	quot(t_all *all, t_env *envi)
{
	while (all->parse)
	{
		all->parse->split2 = malloc(sizeof(char *) * (ft_splitlen(all->parse->split) + 1));
		quotes(all, envi);
		all->parse = all->parse->next;
	}
}
