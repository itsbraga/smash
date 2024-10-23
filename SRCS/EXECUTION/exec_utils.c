/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:24:08 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 21:03:12 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**search_path(char **tab_path, char **env)
{
	char	*all_path;
	int		i;

	all_path = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) != 0)
			i++;
		else
		{
			all_path = env[i];
			break ;
		}
	}
	if (all_path != NULL)
	{
		tab_path = yama(ADD_TAB, ft_split(all_path, ':'), 0);
		secure_malloc(tab_path, true);
	}
	return (tab_path);
}

char	*search_bin(char *cmd, char **tab_path)
{
	char	*path_to_try;
	char	*tmp;
	int		i;

	i = 0;
	while (tab_path[i] != NULL)
	{
		tmp = ft_strjoin(tab_path[i], "/");
		secure_malloc(tmp, true);
		(void)yama(ADD, tmp, 0);
		path_to_try = ft_strjoin(tmp, cmd);
		secure_malloc(path_to_try, true);
		(void)yama(ADD, path_to_try, 0);
		(void)yama(REMOVE, tmp, 0);
		if (access(path_to_try, F_OK) == -1)
		{
			(void)yama(REMOVE, path_to_try, 0);
			i++;
		}
		else
			return ((void)yama(REMOVE, tab_path, 0), path_to_try);
	}
	return ((void)yama(REMOVE, tab_path, 0), NULL);
}

static bool	__check_if_is_dir(char *bin_path)
{
	struct stat	s_bin_path;

	if (stat(bin_path, &s_bin_path) != 0)
	{
		err_msg("stat", strerror(errno), 0);
		exit(FAILURE);
	}
	if (S_ISDIR(s_bin_path.st_mode) != 0)
	{
		err_msg(bin_path, ERR_IS_DIR, 0);
		return (true);
	}
	else
		return (false);
}

int	check_bin_path(t_exec_lst *node, bool absolute_path)
{
	dprintf(2, "check_bin_path | bin_path = %s\n", node->bin_path);
	if (__check_if_is_dir(node->bin_path) == true)
		exit(CMD_CANNOT_EXEC);
	if (access(node->bin_path, F_OK) == -1)
	{
		dprintf(2, "access = -1\n");
		if (absolute_path == true)
			err_msg_cmd(node->bin_path, NULL, ERR_BAD_FILE, CMD_NOT_FOUND);
		else
			err_msg_cmd(node->cmd[0], NULL, ERR_CMD, CMD_NOT_FOUND);
		free_and_set_null(node->bin_path);
		return (FAILURE);
	}
	else if (access(node->bin_path, X_OK) == -1)
	{
		err_msg_cmd(node->bin_path, NULL, ERR_BAD_PERM, CMD_CANNOT_EXEC);
		free_and_set_null(node->bin_path);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	handle_bin_path(t_exec_lst *node, char **env)
{
	int		error;
	char	**tab_path;

	error = 0;
	tab_path = NULL;
	if (node->absolute_path == true)
		error = check_bin_path(node, node->absolute_path);
	else
	{
		tab_path = search_path(tab_path, env);
		if (tab_path == NULL)
		{
			err_msg(NULL, ERR_NO_ENV, 0);
			error = 1;
		}
		else
			node->bin_path = search_bin(node->cmd[0], tab_path);
		dprintf(2, "handle_bin_path | bin path = %s\n", node->bin_path);
		// si binpath == NULL error = 1
		if (node->bin_path != NULL)
			error = check_bin_path(node, node->absolute_path);
	}
	return (error);
}
