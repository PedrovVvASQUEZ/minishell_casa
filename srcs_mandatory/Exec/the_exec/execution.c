/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:47:02 by codespace         #+#    #+#             */
/*   Updated: 2024/10/16 17:28:13 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executioner(t_ms *ms)
{
	int			x;
	t_cmdline	*head;

	x = 0;
	head = ms->cmdlines;
	while (ms->cmdlines)
	{
		pipe(ms->pipefd);
		ms->pid[x] = fork();
		if (ms->pid[x] == -1)
			exit(1);
		if (ms->pid[x] == 0)
			child_process(ms);
		else
		{
			close(ms->pipefd[1]);
			if (x > 0)
				close(ms->cmdlines->cmd->previous_fd);
			ms->cmdlines->cmd->previous_fd = ms->pipefd[0];
		}
		ms->cmdlines = ms->cmdlines->next;
		x++;
	}
	ms->cmdlines = head;
	return (wait_da_boy(ms));
}

int	executor(t_ms *ms)
{
	int	v_return;

	the_cmdlines(ms);
	display_cmdlines(ms->cmdlines);
	ms->c_count = cmdlines_counter(ms->cmdlines);
	ms->pid = malloc(sizeof(int) * ms->c_count);
	if (!ms->pid)
	{
		ft_putstr_fd("Error : malloc failed", 2);
		return (1);
	}
	v_return = executioner(ms);
	clear_cmdlines(&ms->cmdlines);
	free(ms->pid);
	close(ms->pipefd[0]);
	close(ms->pipefd[1]);
	return (v_return);
}
