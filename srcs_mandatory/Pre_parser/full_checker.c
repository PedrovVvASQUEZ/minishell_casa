/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:44:59 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/14 20:52:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	full_check(t_ms *ms)
{
	if (q_check(ms->prompt) == false || c_check(ms->prompt) == false
		|| shit_check_1(ms->prompt) == false)
	{
		ft_putstr_fd("/! error bitch /! \n", 2);
		return (false);
	}
	else
	{
		ms->tokens = lexer(ms->prompt);
		expander(ms);
		display_tokens(ms->tokens);
		return (true);
	}
}
