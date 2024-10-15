/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:43:36 by codespace         #+#    #+#             */
/*   Updated: 2024/10/15 19:37:59 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirector(t_ms *ms)
{
	if (ms->cmdlines && ms->cmdlines->prev)
	{
		dup2(ms->cmdlines->cmd->previous_fd, STDIN_FILENO);
		close(ms->cmdlines->cmd->previous_fd);
	}
	if (ms->cmdlines && ms->cmdlines->next)
		dup2(ms->pipefd[1], STDOUT_FILENO);
	close(ms->pipefd[0]);
	close(ms->pipefd[1]);
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
	t_cmdline	*current;
	int			x;

	x = 0;
	current = cmdline;
	while (current)
	{
		x += 1;
		current = current->next;
	}
	return (x);
}

int	wait_da_boy(t_ms *ms)
{
	int	x;
	int	status;
	int	*exit_status;

	exit_status = malloc(sizeof(int) * cmdlines_counter(ms->cmdlines));
	if (!exit_status)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (-1);
	}
	x = 0;
	while (x < cmdlines_counter(ms->cmdlines))
	{
		if (ft_strncmp(ms->cmdlines->cmd->cmds[0], "sleep", 5) == 0)
			wait(&status);
		else
			waitpid(ms->pid[x], &status, 0);
		exit_status[x] = status >> 8;
		x++;
	}
	status = exit_status[cmdlines_counter(ms->cmdlines) - 1];
	free(exit_status);
	return (status);
}
