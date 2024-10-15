/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:28:01 by codespace         #+#    #+#             */
/*   Updated: 2024/10/15 20:03:51 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_file_opener(t_cmdline *cmdline)
{
	t_redirs	*current;

	current = cmdline->cmd->redirs;
	while (current)
	{
		if (current->in_flag == true)
		{
			if (cmdline->cmd->fd_in != -1)
				close(cmdline->cmd->fd_in);
			if (access(current->infile, F_OK) != 0)
			{
				perror(current->infile);
				exit(1);
			}
			cmdline->cmd->fd_in = open(current->infile, O_RDONLY);
			if (cmdline->cmd->fd_in < 0)
			{
				perror(current->infile);
				exit(1);
			}
			dup2(cmdline->cmd->fd_in, STDIN_FILENO);
			close(cmdline->cmd->fd_in);
		}
		current = current->next;
	}
}

void	outfile_opener_trunc(t_cmdline *cmdline)
{
	t_redirs	*current;

	current = cmdline->cmd->redirs;
	while (current)
	{
		if (current->out_flag == true)
		{
			if (cmdline->cmd->fd_out != -1)
				close(cmdline->cmd->fd_out);
			cmdline->cmd->fd_out = open(current->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmdline->cmd->fd_out < 0)
			{
				perror(current->outfile);
				exit(1);
			}
			dup2(cmdline->cmd->fd_out, STDOUT_FILENO);
			close(cmdline->cmd->fd_out);
		}
		current = current->next;
	}
}

void	outfile_opener_app(t_cmdline *cmdline)
{
	t_redirs	*current;

	current = cmdline->cmd->redirs;
	while (current)
	{
		if (current->out_app == true)
		{
			if (cmdline->cmd->fd_out != -1)
				close(cmdline->cmd->fd_out);
			cmdline->cmd->fd_out = open(current->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmdline->cmd->fd_out < 0)
			{
				perror(current->outfile);
				exit(1);
			}
			dup2(cmdline->cmd->fd_out, STDOUT_FILENO);
			close(cmdline->cmd->fd_out);
		}
		current = current->next;
	}
}

void	ft_open_files(t_cmdline *cmdline)
{
	in_file_opener(cmdline);
	outfile_opener_trunc(cmdline);
	outfile_opener_app(cmdline);
}
