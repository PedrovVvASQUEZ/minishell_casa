/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_in_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:38:24 by codespace         #+#    #+#             */
/*   Updated: 2024/10/14 20:46:31 by codespace        ###   ########.fr       */
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
		free(cmd);
		handle_exec_error();
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
	free(ms->cmdlines->cmd->pid);
	redirector(ms->cmdlines);
	ft_open_files(ms->cmdlines);
	cmd_exec(ms, ms->cmdlines->cmd->cmds[0]);
	exit(127);
}
