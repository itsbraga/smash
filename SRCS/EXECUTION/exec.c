/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:16:04 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/20 17:09:42 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *path_bin, char **cmd_and_args, char **env)
{
	dprintf(2, "PID : %d | before execve (exec)\n", getpid());
	if (execve(path_bin, cmd_and_args, env) == -1)
	{
		dprintf(2, "PID : %d | execve failed /!\\(exec)\n", getpid());
		free(path_bin);
		path_bin = NULL;
		exit(FAILURE); // à changer
	}
}

void	go_exec(t_exec_lst *node, char **env)
{
	if (handle_bin_path(node, env) == 0)
		exec(node->bin_path, node->cmd, env);
	else
		exit(FAILURE); // à changer
}
