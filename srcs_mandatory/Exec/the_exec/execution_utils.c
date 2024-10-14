/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:43:36 by codespace         #+#    #+#             */
/*   Updated: 2024/10/14 21:36:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirector(t_cmdline *cmdline)
{
	if (cmdline && cmdline->prev)
	{
		dup2(cmdline->cmd->previous_fd, STDIN_FILENO);
		close(cmdline->cmd->previous_fd);
	}
	if (cmdline && cmdline->next)
		dup2(cmdline->cmd->pipefd[1], STDOUT_FILENO);
	close(cmdline->cmd->pipefd[0]);
	close(cmdline->cmd->pipefd[1]);
}

void	handle_exec_error(void)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("Error: No such file or directory\n", 2);
		exit(127);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("Error: Permission denied\n", 2);
		exit(126);
	}
	else
		exit(1);
}
int	cmdlines_counter(t_cmdline *cmdline)
{
	int	x;

	x = 0;
	while (cmdline)
	{
		x += 1;
		cmdline = cmdline->next;
	}
	return (x);
}

int	wait_da_boy(t_cmdline *cmdline)
{
	int	x;
	int	status;
	int	*exit_status;

	exit_status = malloc(cmdlines_counter(cmdline) * sizeof(int));
	if (!exit_status)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (-1);
	}
	x = 0;
	while (x < cmdlines_counter(cmdline))
	{
		if (ft_strncmp(cmdline->cmd->cmds[0], "sleep", 5) == 0)
			wait(&status);
		else
			waitpid(cmdline->cmd->pid[x], &status, 0);
		exit_status[x] = status >> 8;
		x++;
	}
	status = exit_status[cmdlines_counter(cmdline) - 1];
	free(exit_status);
	return (status);
}
