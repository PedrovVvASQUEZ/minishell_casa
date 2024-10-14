/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_programm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:51:23 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/14 21:29:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(t_ms *ms)
{
	char	*input;

	input = readline(PROMPT_LINE);
	if (input == NULL)
		return (NULL);
	if (input[0] == '\0' || !ft_strcmp(input, ":")
		|| !ft_strcmp(input, "!") || !ft_strcmp(input, "#"))
	{
		if (!ft_strcmp(input, ":") || !ft_strcmp(input, "#"))
			ms->v_return = 0;
		if (!ft_strcmp(input, "!"))
			ms->v_return = 1;
		free(input);
		return (ft_strdup(""));
	}
	add_history(input);
	return (input);
}

t_ms	*init_ms(void)
{
	t_ms	*ms;

	ms = malloc(sizeof(t_ms));
	if (ms == NULL)
	{
		ft_putstr_fd("Error: couldn't allocate memory\n", 2);
		exit(1);
	}
	ms->prompt = NULL;
	ms->envi = NULL;
	ms->env = NULL;
	ms->tokens = NULL;
	ms->cmdlines = NULL;
	ms->v_return = 0;
	ms->t_count = 0;
	return (ms);
}

t_ms	*init_program(char **env)
{
	t_ms	*ms;
	// int		sig_val;

	// sig_val = SIGINT;
	// ft_sigint_setup();
	// ft_sigquit_setup();
	ms = init_ms();
	ms->env = init_env(env);
	if (ms->env == NULL)
	{
		ft_putstr_fd("Error: couldn't allocate memory\n", 2);
		exit(1);
	}
	ms->envi = the_env(ms->env);
	if (ms->envi == NULL)
	{
		ft_putstr_fd("Error: couldn't allocate memory\n", 2);
		exit(1);
	}
	return (ms);
}

void	the_program(t_ms *ms)
{
	while (true)
	{
		ms->prompt = prompt(ms);
		if (ft_strcmp(ms->prompt, "exit") == 0)
			break ;
		if (!full_check(ms))
			continue ;
		// handle_here_doc(ms->tokens);
		ms->v_return = executor(ms);
		free_tokens(&ms->tokens);
		free(ms->prompt);
	}
	free_env(&ms->env);
	free(ms->prompt);
}
