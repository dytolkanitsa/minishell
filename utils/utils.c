/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:10:06 by lgarg             #+#    #+#             */
/*   Updated: 2021/07/16 18:15:07 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

void	get_key(t_all **all, char *key)
{
	int i;

	i = 0;
	while (if_key((*all)->parse->line1[(*all)->parse->i_1]))
		key[i++] = (*all)->parse->line1[(*all)->parse->i_1++];
	key[i] = '\0';
}

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	ft_check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
