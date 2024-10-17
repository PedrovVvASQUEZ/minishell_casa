/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_in_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgrellie <pgrellie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:24 by codespace         #+#    #+#             */
/*   Updated: 2024/10/17 16:51:25 by pgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_for_exec(char **envi, char *cmd)
{
	int		x;
	char	*path;
	char	*tmp;

	x = 0;
	while (envi[x])
	{
		path = ft_strjoin(envi[x], "/");
		tmp = path;
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_tab(envi);
			return (path);
		}
		free(path);
		x++;
	}
	ft_free_tab(envi);
	return (NULL);
}

char	*cmd_path(char **envi, char *cmd)
{
	int		x;
	char	*path;
	char	**pathsss;

	x = 0;
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (envi[x])
	{
		if (ft_strncmp(envi[x], "PATH=", 5) == 0)
		{
			path = ft_strdup(envi[x] + 5);
			pathsss = ft_split(path, ':');
			free(path);
			path = env_for_exec(pathsss, cmd);
			if (path)
				return (path);
		}
		x++;
	}
	return (NULL);
}

void	cmd_exec(t_ms *ms, char *cmd)
{
	cmd = cmd_path(ms->envi, ms->cmdlines->cmd->cmds[0]);
	if (cmd)
	{
		execve(cmd, ms->cmdlines->cmd->cmds, ms->envi);
		ft_free_tab(ms->cmdlines->cmd->cmds);
		ft_putstr_fd("3\n", 2);
		free(cmd);
		ft_putstr_fd("4\n", 2);
		handle_exec_error();
		ft_putstr_fd("5\n", 2);
	}
	else
	{
		ft_putstr_fd("Error : command not found\n", 2);
		ft_free_tab(ms->cmdlines->cmd->cmds);
		exit(127);
	}
}

void	child_process(t_ms *ms)
{
	redirector(ms);
	ft_open_files(ms->cmdlines);
	cmd_exec(ms, ms->cmdlines->cmd->cmds[0]);
	exit(127);
}
