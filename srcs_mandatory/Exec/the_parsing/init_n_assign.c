/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_assign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:55:10 by codespace         #+#    #+#             */
/*   Updated: 2024/10/15 15:28:46 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_out_append(t_redirs *redirs, t_token *tok)
{
	if (tok->type == REDIR_OUT || tok->type == APPEND)
	{
		if (tok->next)
		{
			redirs->outfile = ft_strdup(tok->next->value);
			if (!redirs->outfile)
				return ;
			if (tok->type == REDIR_OUT)
				redirs->out_flag = true;
			else if (tok->type == APPEND)
				redirs->out_app = true;
		}
		else
		{
			redirs->outfile = NULL;
			if (tok->type == REDIR_OUT)
				redirs->out_flag = true;
			else if (tok->type == APPEND)
				redirs->out_app = true;
		}
	}
}

void	assign_limiter(t_redirs *redirs, t_token *tok)
{
	if (tok->next)
	{
		redirs->limiter = ft_strdup(tok->next->value);
		if (!redirs->limiter)
			return ;
		redirs->hd_flag = true;
	}
	else
	{
		redirs->limiter = NULL;
		redirs->hd_flag = true;
	}
}

void	assign_redir_in(t_redirs *redirs, t_token *tok)
{
	if (tok->next)
	{
		redirs->infile = ft_strdup(tok->next->value);
		if (!redirs->infile)
			return ;
		redirs->in_flag = true;
	}
	else
	{
		redirs->infile = NULL;
		redirs->in_flag = true;
	}
}

void	assign_r_type(t_redirs *redirs, t_token *tok)
{
	if (tok->type == REDIR_IN)
	{
		assign_redir_in(redirs, tok);
	}
	else if (tok->type == HERE_DOC)
	{
		assign_limiter(redirs, tok);
	}
	else if (tok->type == REDIR_OUT || tok->type == APPEND)
	{
		assign_out_append(redirs, tok);
	}
}

void	init_rs(t_redirs *redirs, t_token *tok)
{
	redirs->infile = NULL;
	redirs->in_flag = false;
	redirs->outfile = NULL;
	redirs->out_flag = false;
	redirs->out_app = false;
	redirs->limiter = NULL;
	redirs->hd_flag = false;
	redirs->next = NULL;
	redirs->prev = NULL;
	assign_r_type(redirs, tok);
}
