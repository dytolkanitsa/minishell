/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:38:36 by lgarg             #+#    #+#             */
/*   Updated: 2021/07/14 12:40:04 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_dollar(t_all **all, t_env *envi)
{
	int		key_len;
	char	*temp;
	int		len;

	(*all)->parse->i_2++;
	(*all)->parse->i_1++;
	key_len = ft_strlen((*all)->parse->line1 + (*all)->parse->i_1);
	while (envi)
	{
		if (ft_strncmp(((*all)->parse->line1 + (*all)->parse->i_1), envi->value, key_len) == 0)
		{
			temp = ft_strdup(envi->value + key_len + 1);
			(*all)->parse->line2 = ft_strjoin((*all)->parse->line2, temp);
			free (temp);
		}
		(*all)->parse->i_2 += ft_strlen(envi->value + key_len + 1);
		envi = envi->next;
	}
	(*all)->parse->i_2++;
}