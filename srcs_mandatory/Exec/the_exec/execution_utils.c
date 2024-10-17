/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:43:36 by codespace         #+#    #+#             */
/*   Updated: 2024/10/17 18:59:48 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirector(t_ms *ms)
{
	if (ms->cmdlines && ms->cmdlines->prev)
	{
		dup2(ms->previous_fd, STDIN_FILENO);
		close(ms->previous_fd);
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
	t_wdb	w;

	if (ms->c_count <= 0)
		return (0);
	w.exit_status = ft_calloc(ms->c_count, sizeof(int));
	if (!w.exit_status)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (-1);
	}
	w.current = ms->cmdlines;
	w.x = 0;
	while (w.x < ms->c_count && w.current)
	{
		if (ft_strncmp(ms->cmdlines->cmd->cmds[0], "sleep", 5) == 0)
			wait(&w.status);
		else
			waitpid(ms->pid[w.x], &w.status, 0);
		w.exit_status[w.x] = WEXITSTATUS(w.status);
		w.current = w.current->next;
		w.x++;
	}
	w.status = w.exit_status[ms->c_count - 1];
	free(w.exit_status);
	return (w.status);
}
