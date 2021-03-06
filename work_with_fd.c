/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjammie <mjammie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 11:21:49 by mjammie           #+#    #+#             */
/*   Updated: 2021/07/16 18:35:45 by mjammie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_file_name(t_all *all)
{
	t_parse	*head;
	char	*fname;

	head = all->parse;
	if (head->files_name[all->f] != NULL)
	{
		fname = head->files_name[all->f];
		all->f++;
	}
	else
	{
		if (head->next != NULL)
		{
			while (head->files_name[all->f] == NULL)
			{
				all->f = 0;
				head = head->next;
			}
			fname = head->files_name[all->f];
			all->f++;
		}
	}
	return (fname);
}

void	work_with_fd(char *line, t_all *all)
{
	int		i;
	int		n;
	int		z;
	int		mfd[2];
	int		fd;
	t_parse	*head;
	char	*fname;

	i = 0;
	n = 0;
	z = 0;
	fd = 0;
	all->f = 0;
	head = all->parse;
	while (line[i])
	{
		fname = NULL;
		// if (line[i] == '|')
		// {
		// 	while (z < 2)
		// 	{
		// 		pipe(all->pfd[z]);
		// 		z++;
		// 		// pipe(mfd);
		// 		// all->pfd[n][0] = mfd[0]; //all->pfd[n + 1][0] = mfd[0];
		// 		// all->pfd[n][1] = mfd[1];
		// 		// printf("%d %d\n", all->pfd[n][0], all->pfd[n][1]);
		// 		// n++;
		// 		// z++;
		// 	}
		// }
		if (line[i] == '>')
		{
			fname = get_file_name(all);
			if (line[i + 1] == '>')
			{
				fd = open(fname, O_CREAT | O_RDWR | O_APPEND, 0777);
				all->pfd[n][1] = fd;
				i++;
				n++;
			}
			else
			{
				fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0777);
				all->pfd[n][1] = fd;
				n++;
			}
		}
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				i = i + 2;
				continue ;
			}
			fname = get_file_name(all);
			fd = open(fname, O_CREAT | O_RDWR, 0777);
			all->pfd[n][0] = fd;
			n++;
		}
		i++;
	}
}

void	dup_fd(t_all *all)
{
	all->tm_fd1 = dup(1);
	all->tm_fd0 = dup(0);
	// printf("<%d %d>\n", all->pfd[all->fd_iter][0], all->pfd[all->fd_iter][1]);
	dup2(all->pfd[all->fd_iter][1], 1);
	dup2(all->pfd[all->fd_iter][0], 0);
}

void	close_fd(t_all *all)
{
	if (all->pfd[all->fd_iter][0] != 0)
	{
		close(all->pfd[all->fd_iter][0]);
	}
	if (all->pfd[all->fd_iter][1] != 1)
	{
		close(all->pfd[all->fd_iter][1]);
	}
	dup2(all->tm_fd1, 1);
	dup2(all->tm_fd0, 0);
}
