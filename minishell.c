/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/12 18:25:33 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_splitlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t number, size_t size)
{
	unsigned char	*str;

	str = (unsigned char *)malloc(number * size);
	if (str == NULL)
		return (NULL);
	if (str != NULL && (number * size) != 0)
		ft_bzero(str, number * size);
	return (str);
}

void	do_two_quotes(t_all **all);

void	do_simple_quotes(t_all **all)
{
	// printf("!!!!!!!");
	(*all)->parse->line2[(*all)->parse->i_2] = '\'';
	(*all)->parse->i_2++;
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && (*all)->parse->line1[(*all)->parse->i_1] != '\'')
	{
		if ((*all)->parse->line1[(*all)->parse->i_1] == '\"')
		{
			do_two_quotes(all);
			continue ;
		}
		(*all)->parse->line2[(*all)->parse->i_2++] = (*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->line2[(*all)->parse->i_2] = '\'';
	(*all)->parse->i_2++;
}

void	do_two_quotes(t_all **all)
{
	(*all)->parse->line2[(*all)->parse->i_2] = '\"';
	(*all)->parse->i_2++;
	(*all)->parse->i_1++;
	while ((*all)->parse->line1[(*all)->parse->i_1] && (*all)->parse->line1[(*all)->parse->i_1] != '\"')
	{
		if ((*all)->parse->line1[(*all)->parse->i_1] == '\'')
		{
			do_simple_quotes(all);
			continue ;
		}
		(*all)->parse->line2[(*all)->parse->i_2++] = (*all)->parse->line1[(*all)->parse->i_1++];
	}
	(*all)->parse->line2[(*all)->parse->i_2] = '\"';
	(*all)->parse->i_2++;
}

void	quotes(t_all *all)
{
	int	i;

	i = 0;
	// all->parse->split2 = malloc(sizeof(char *) * (ft_splitlen(all->parse->split) + 1));
	while (all->parse->split[i])
	{
		all->parse->i_1 = 0;
		all->parse->i_2 = 0;
		all->parse->line1 = all->parse->split[i];
		all->parse->line2 = (char *)ft_calloc(1000, sizeof(char));
		while (all->parse->line1[all->parse->i_1])
		{
			if (all->parse->line1[all->parse->i_1] == '\'' || all->parse->line1[all->parse->i_1] == '\"')
			{
				if (all->parse->line1[all->parse->i_1] == '\'')
					do_simple_quotes(&all);
				else if (all->parse->line1[all->parse->i_1] == '\"')
					do_two_quotes(&all);
			}
			else
				all->parse->line2[all->parse->i_2++] = all->parse->line1[all->parse->i_1++];
				printf("%s\n", all->parse->line2);
		}
		all->parse->line2[all->parse->i_2] = '\0';
		all->parse->split2[i] = all->parse->line2;
		free(all->parse->line1);
		i++;
	}
	all->parse->split2[i] = NULL;
	free(all->parse->split2);
	// free(all->parse->line1);
	// int n = 0;
	// while (all->parse->split2[n])
	// {
	// 	printf("%s\n", all->parse->split2[n]);
	// 	n++;
	// }
}

void	quot(t_all *all)
{
	all->parse->split2 = malloc(sizeof(char *) * (ft_splitlen(all->parse->split) + 1));
	while (all->parse)
	{
		quotes(all);
		all->parse = all->parse->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	pid_t	pid;
	t_parse	*par;
	char	*line;
	char	**split;
	t_env	*envi;
	int		len_split;

	(void)argc;
	(void)argv;
	all = malloc(sizeof(t_all));
	par = new_node();
	all->parse = par;
	init_env(&envi, env);
	signal_init();
	while (42)
	{
		all->count_fd = 0;
		all->count_pipe = 0;
		all->fd_iter = -1;
		all->tm_fd0 = 0;
		all->tm_fd1 = 1;
		all->parse->count_r = 0;
		line = readline("minishell> ");
		if (line == NULL)
			ctrl_d_hook();
		if (line && line[0] == '\0') // чтобы можно было вечно нажимать ентер
		{
			free(line);
			continue ;
		}
		split = NULL;
		add_history(line);
		rl_redisplay();
		parse_redir_pipe(all, line);
		quot(all);
		work_with_fd(line, all);
		// print_struct(all);
		while (all->parse)
		{
			if (all->count_pipe != 0)
			{
				// split = ft_split(line, '|');
				
				len_split = ft_splitlen(all->parse->split);
				pipex(len_split, all->parse->split, env, all);
				break ;
			}
			// PIPEX
			
			// split = ft_split(line, '|');
			// len_split = ft_splitlen(split);
			// if (par->pipe != 0)
			// {
			// 	// pipex(par->pipe, split, env);
			// 	pipex(len_split, split, env);
			// 	break ;
			// }
			// PIPEX
			
			// while (split[i])
			// {
			// 	printf("%s\n", split[i]);
			// 	i++;
			// }
			else
			// {
			// 	split = ft_split(line, ' ');
			// 	len_split = ft_splitlen(split);
			// while (all->parse)
			{
				if (ft_strcmp(all->parse->split[0], "pwd") == 0)
					cmd_pwd(envi, all);
				else if (ft_strcmp(all->parse->split[0], "echo") == 0)
					cmd_echo(ft_splitlen(all->parse->split), all->parse->split, envi, all);
				else if (ft_strcmp(all->parse->split[0], "cd") == 0)
					cmd_cd(envi, all->parse->split[1]);
				else if (ft_strcmp(all->parse->split[0], "env") == 0)
					cmd_env(envi, all);
				else if (ft_strcmp(all->parse->split[0], "export") == 0)
					cmd_export(envi, split, ft_splitlen(all->parse->split), all);
				else if (ft_strcmp(all->parse->split[0], "unset") == 0)
					cmd_unset(envi, all->parse->split[1]);
				else if (ft_strcmp(all->parse->split[0], "exit") == 0)
					cmd_exit(envi);
				else
				{
					other_cmd(all->parse->split, envi, env, all);
					wait(0);
				}
			}
			all->parse = all->parse->next;
		}
		all->parse = par;
		// free(all->parse); // доработать фри
		// all->parse = NULL;
	}
}
