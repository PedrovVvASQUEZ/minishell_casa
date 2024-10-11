/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:23:59 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/11 16:25:09 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirs(t_redirs *redirs)
{
	redirs->infile = NULL;
	redirs->in_flag = false;
	redirs->outfile = NULL;
	redirs->out_flag = false;
	redirs->out_trunc = false;
	redirs->here_doc = NULL;
	redirs->hd_flag = false;
}

void	init_cmd(t_ms *ms)
{
	ms->cmdline->cmd->tok = ms->tokens;
	ms->cmdline->cmd->cmds = the_cmds(ms->tokens);
	ms->cmdline->cmd->pipefd[0] = -1;
	ms->cmdline->cmd->pipefd[1] = -1;
	ms->cmdline->cmd->pid = NULL;
	init_redirs(&ms->cmdline->cmd->redirs);
}
