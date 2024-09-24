/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/23 19:49:01 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		free(path_bin);
		//free_child_tab ?
		return;//à changer
	}
}

void	go_exec(t_exec_lst *node, char **env)
{
	char **tab_path;
	
	tab_path = NULL;
	if (node->absolute_path == true)
		check_bin_path(node);
	else
	{
		tab_path = search_path(tab_path, env);
		if (tab_path == NULL)
		{
			err_msg(NULL, "$PATH don't exist, please specify absolute path", 0);
			return;
		}
		else
			node->bin_path = search_bin(node->cmd[0], tab_path);
	}
	if (node->bin_path != NULL)
		exec(node->bin_path, node->cmd, env);
	else
	{
		err_msg2();
		return;//à changer
	}
}