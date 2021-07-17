/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarg <lgarg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:44:47 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/17 19:02:19 by lgarg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_all	*all;
	pid_t	pid;
	t_parse	*par;
	char	*line;
	char	**split;
	t_env	*envi;
	int		len_split;
	t_parse *head;
	int fd_copy[2];

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	all = malloc(sizeof(t_all));
	par = new_node();
	all->parse = par;
	head = all->parse;
	signal_init();
	init_env(&envi, env);
	all->error = 0;
	while (42)
	{
		all->count_fd = 0;
		all->count_pipe = 0;
		all->fd_iter = 0;
		all->tm_fd0 = 0;
		all->tm_fd1 = 1;
		all->parse->count_r = 0;
		all->absol = 0;
		
		line = readline("minishell> ");
		if (line == NULL)
			ctrl_d_hook();
		if (line && line[0] == '\0')
		{
			free(line);
			continue ;
		}
		split = NULL;
		add_history(line);
		rl_redisplay();
		parse_redir_pipe(all, line);
		quot(all, envi);
		all->parse = head;
		work_with_fd(line, all);
		all->pid = malloc(sizeof(pid_t) * (all->count_pipe + 1));
		// print_struct(all);
		if (all->count_pipe != 0)
		{
			len_split = ft_splitlen(all->parse->split);
			fd_copy[0] = dup(0);
			fd_copy[1] = dup(1);
			pipex(len_split, all->parse->split, env, all, envi);
			dup2(fd_copy[0], 0);
			dup2(fd_copy[1], 1);
		}
		else
		{
			if (ft_strcmp(all->parse->split2[0], "pwd") == 0)
				cmd_pwd(envi, all);
			else if (ft_strcmp(all->parse->split2[0], "echo") == 0)
				cmd_echo(ft_splitlen(all->parse->split2), all->parse->split2, envi, all);
			else if (ft_strcmp(all->parse->split2[0], "cd") == 0)
				cmd_cd(envi, all->parse->split[1]);
			else if (ft_strcmp(all->parse->split2[0], "env") == 0)
				cmd_env(envi, all);
			else if (ft_strcmp(all->parse->split2[0], "export") == 0)
				cmd_export(envi, all->parse->split2, ft_splitlen(all->parse->split), all);
			else if (ft_strcmp(all->parse->split2[0], "unset") == 0)
				cmd_unset(envi, all->parse->split[1]);
			else if (ft_strcmp(all->parse->split2[0], "exit") == 0)
				cmd_exit(envi);
			else if (ft_strcmp(all->parse->split2[0], "<<") == 0)
			{
				if (!all->parse->split[1])
				{
					printf("minishell> syntax error near unexpected token `newline'\n");
					all->parse = par;
					free(line);
					line = NULL;
					continue ;
				}
				while (42)
				{
					line = readline("> ");
					if (line == NULL)
						break ;
					if (ft_strcmp(line, all->parse->split[1]) == 0)
						break ;
					rl_on_new_line();
				}
			}
			else if (ft_strcmp(all->parse->split[0], "$?") == 0)
			{
				printf("minishell> %d: command not found\n", g_exit_status);
			}
			else
			{
				other_cmd(all->parse->split, envi, all);
			}
		}
		all->parse = par;
		free(line);
		line = NULL;
	}
	return (g_exit_status);
}
	