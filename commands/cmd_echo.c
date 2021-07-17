/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:11:23 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/17 15:52:29 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	check_redir(char *str)
// {
// 	if (ft_strch)
// }

char	*cmd_echo(int argc, char **argv, t_env *envi, t_all *all)
{
	t_env	*head;
	int		i;
	int		n;
	int		key_len;
	int		cmd_not_found;
	int		z;

	i = 0;
	head = envi;
	key_len = 0;
	z = 0;
	while (z < all->parse->count_r)
	{
		all->fd_iter++;
		z++;
	}
	dup_fd(all);
	if (argc == 1)
		printf("\n");
	else
	{
		if (ft_strcmp(argv[1], "-n") == 0)
		{
			i = 2;
			while (argv[i] && !ft_strchr("<>", argv[i][0]))
			{
				envi = head;
					printf("%s", argv[i]);
					if (argv[i + 1] != 0)
						printf(" ");
				i++;
			}
		}
		else
		{
			i = 1;
			while (argv[i] && !ft_strchr("<>", argv[i][0]))
			{
				envi = head;
					printf("%s\n", argv[i]);
				i++;
			}
		}
	}
	close_fd(all);
	g_exit_status = 0;
	return (0);
}
