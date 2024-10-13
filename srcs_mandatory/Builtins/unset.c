/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:27:28 by acarpent          #+#    #+#             */
/*   Updated: 2024/10/13 11:02:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_node(t_env *env, t_env *delete)
{
	delete = env;
	if (delete)
	{
		if (env->prev)
			env->prev->next = env->next;
		if (env->next)
			env->next->prev = env->prev;
		free(env->name);
		free(env->value);
		free(env);
	}
}

void	ft_unset(t_ms *ms)
{
	t_token	*current;
	t_env	*delete;

	delete = NULL;
	current = ms->tokens;
	if (current->next)
	{
		current = current->next;
		while (ms->env)
		{
			if (ft_strcmp(ms->env->name, ms->tokens->value) == 0)
			{
				del_node(ms->env, delete);
				if (ms->envi)
					ft_free_tab(ms->envi);
				ms->envi = the_env(ms->env);
				if (!ms->envi)
					ms->envi = NULL;
				break ;
			}
			ms->env = ms->env->next;
		}
	}
}
