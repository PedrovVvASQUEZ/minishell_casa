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

int	env_counter(t_env *env)
{
	t_env	*current;
	int		x;

	x = 0;
	current = env;
	while (current)
	{
		x += 1;
		current = current->next;
	}
	return (x);
}

char	**the_env(t_env *env)
{
	char	**envi;
	int		y;

	y = 0;
	envi = ft_calloc(env_counter(env) + 1, sizeof(char *));
	if (!envi)
		return (NULL);
	while (env)
	{
		if (env->equal_sign == 1)
			envi[y] = ft_strjoin_equal(env->name, env->value);
		else
			envi[y] = ft_strdup(env->name);
		y++;
		env = env->next;
	}
	envi[y] = NULL;
	return (envi);
}

void	init_cmd(t_cmdline *cmdline)
{
	cmdline->cmd->tok = NULL;
	cmdline->cmd->cmds = NULL;
	cmdline->cmd->fd_in = -1;
	cmdline->cmd->fd_out = -1;
	cmdline->cmd->previous_fd = -1;
	cmdline->cmd->redirs = NULL;
}
