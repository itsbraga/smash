/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:53:27 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/21 02:08:47 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	secure_malloc(void *to_secure, bool cleanup)
{
	if (to_secure == NULL)
	{
		err_msg("malloc", ERR_MALLOC, 0);
		if (cleanup == true)
			clean_exit_shell(FAILURE);
	}
}

void	clean_exit_shell(int err_status)
{
	yama(CLEAN_ALL, NULL, 0);
	rl_clear_history();
	printf("%s\n", BOLD BLUE BYE_MSG R);
	exit(err_status);
}
