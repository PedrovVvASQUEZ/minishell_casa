/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:47:02 by codespace         #+#    #+#             */
/*   Updated: 2024/10/14 22:46:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executioner(t_ms *ms)
{
	int	x;
	t_cmdline *head;

	x = 0;
	head = ms->cmdlines;
	while (ms->cmdlines)
	{
		pipe(ms->cmdlines->cmd->pipefd);
		ms->cmdlines->cmd->pid[x] = fork();
		if (ms->cmdlines->cmd->pid[x] == -1)
			exit(1);
		if (ms->cmdlines->cmd->pid[x] == 0)
			child_process(ms);
		else
		{
			close(ms->cmdlines->cmd->pipefd[1]);
			if (x > 0)
				close(ms->cmdlines->cmd->previous_fd);
			ms->cmdlines->cmd->previous_fd = ms->cmdlines->cmd->pipefd[0];
		}
		ms->cmdlines = ms->cmdlines->next;
		x++;
	}
	return (wait_da_boy(head));
}

int	executor(t_ms *ms)
{
	int	v_return;

	ms->cmdlines = the_cmdlines(ms);
	precheck(ms->cmdlines);
	v_return = executioner(ms);
	clear_cmdlines(&ms->cmdlines);
	return (v_return);
}
