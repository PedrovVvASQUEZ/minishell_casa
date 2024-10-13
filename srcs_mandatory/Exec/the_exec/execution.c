/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:43:36 by codespace         #+#    #+#             */
/*   Updated: 2024/10/13 10:49:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	executor(t_ms *ms)
// {
// 	if (ms->cmdline && !ms->cmdline->next && !ms->cmdline->prev)
// 		ms->v_return = ft_exec(ms->cmdline);
// 	else
// 		ms->v_return = ft_pipe_exec(ms->cmdline);
// 	return (ms->v_return);
// }