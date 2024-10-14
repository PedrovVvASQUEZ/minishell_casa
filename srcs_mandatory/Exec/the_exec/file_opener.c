/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:28:01 by codespace         #+#    #+#             */
/*   Updated: 2024/10/14 20:47:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_file_opener(t_cmdline *cmdline)
{
	while (cmdline->cmd->redirs)
	{
		if (cmdline->cmd->redirs->in_flag == true)
		{
			if (cmdline->cmd->fd_in != -1)
				close(cmdline->cmd->fd_in);
			if (access(cmdline->cmd->redirs->infile, F_OK) != 0)
			{
				perror(cmdline->cmd->redirs->infile);
				exit(EXIT_FAILURE);
			}
			cmdline->cmd->fd_in = open(cmdline->cmd->redirs->infile, O_RDONLY);
			if (cmdline->cmd->fd_in < 0)
			{
				perror(cmdline->cmd->redirs->infile);
				exit(EXIT_FAILURE);
			}
			dup2(cmdline->cmd->fd_in, STDIN_FILENO);
			close(cmdline->cmd->fd_in);
		}
		cmdline->cmd->redirs = cmdline->cmd->redirs->next;
	}
}

void	outfile_opener_trunc(t_cmdline *cmdline)
{
	while (cmdline->cmd->redirs)
	{
		if (cmdline->cmd->redirs->out_flag == true)
		{
			if (cmdline->cmd->fd_out != -1)
				close(cmdline->cmd->fd_out);
			cmdline->cmd->fd_out = open(cmdline->cmd->redirs->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmdline->cmd->fd_out < 0)
			{
				perror(cmdline->cmd->redirs->outfile);
				exit(EXIT_FAILURE);
			}
			dup2(cmdline->cmd->fd_out, STDOUT_FILENO);
			close(cmdline->cmd->fd_out);
		}
		cmdline->cmd->redirs = cmdline->cmd->redirs->next;
	}
}

void	outfile_opener_app(t_cmdline *cmdline)
{
	while (cmdline->cmd->redirs)
	{
		if (cmdline->cmd->redirs->out_app == true)
		{
			if (cmdline->cmd->fd_out != -1)
				close(cmdline->cmd->fd_out);
			cmdline->cmd->fd_out = open(cmdline->cmd->redirs->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmdline->cmd->fd_out < 0)
			{
				perror(cmdline->cmd->redirs->outfile);
				exit(EXIT_FAILURE);
			}
			dup2(cmdline->cmd->fd_out, STDOUT_FILENO);
			close(cmdline->cmd->fd_out);
		}
		cmdline->cmd->redirs = cmdline->cmd->redirs->next;
	}
}

void	ft_open_files(t_cmdline *cmdline)
{
	in_file_opener(cmdline);
	outfile_opener_trunc(cmdline);
	outfile_opener_app(cmdline);
}