/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:47 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/11 18:09:17 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_counter(t_token *tok)
{
	t_token	*current;
	int		x;

	x = 0;
	current = tok;
	while (current && current->type != PIPE)
	{
		if (tok->type == CMD || tok->type == ARG || tok->type == WORD)
			x += 1;
		current = current->next;
	}
	return (x);
}

char	**the_cmds(t_token *tok)
{
	t_token	*current;
	char	**cmds;
	int		y;

	y = 0;
	current = tok;
	cmds = ft_calloc(cmd_counter(tok) + 1, sizeof(char *));
	if (!cmds)
		return (NULL);
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == ARG
			|| current->type == WORD)
			cmds[y] = ft_strdup(tok->value);
		tok = tok->next;
	}
	cmds[y] == NULL;
	return (cmds);
}

t_cmdline	*parsing(t_ms *ms)
{
	t_cmdline	*cmdline;
	t_token *current;

	cmdline = NULL;
	current = ms->tokens;
	while (current)
	{
		add_cmdline_node(&cmdline, current);
		while (current && current->type != PIPE)
			current = current->next;
		if (current)
			current = current->next;
		if (!current)
			break ;
	}
	return (cmdline);
}

int	executor(t_ms *ms)
{
	if (ms->cmdline && !ms->cmdline->next && !ms->cmdline->prev)
		ms->v_return = ft_exec(ms->cmdline);
	else
		ms->v_return = ft_pipe_exec(ms->cmdline);
	return (ms->v_return);
}
