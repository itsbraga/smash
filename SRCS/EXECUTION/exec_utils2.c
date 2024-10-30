/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:27:06 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/30 20:28:11 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "exec.h"

bool	check_if_is_dir(char *bin_path)
{
	struct stat	s_bin_path;

	if (stat(bin_path, &s_bin_path) == 0)
	{
		if (S_ISDIR(s_bin_path.st_mode) != 0)
			return (true);
	}
	return (false);
}

char	**search_path(char **tab_path, char **env)
{
	char	*all_path;
	int		i;

	dprintf(2, "PID[%d] | %s\n", getpid(), __func__);
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