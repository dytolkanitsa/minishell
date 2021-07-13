/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:10:06 by lgarg             #+#    #+#             */
/*   Updated: 2021/07/13 18:10:18 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_key_ok(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' || !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}