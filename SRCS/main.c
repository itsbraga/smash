/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/26 16:48:55 by annabrag         ###   ########.fr       */
=======
/*   Updated: 2024/06/25 20:00:40 by pmateo           ###   ########.fr       */
>>>>>>> 7dc4c4513f0a6a3f0cdef5edb3836223041dd263
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_global	g;

	if (argc > 1)
		exit(EXIT_FAILURE);
	(void)argv;
	init_global(&g);
	g.env = create_env(envp);
	// g.export_env = create_export_env(envp);
	while (1)
	{
		g.input = readline(BOLD PINK "[elgato@42]" RESET " $> ");
		if (*g.input)
			add_history(g.input);
		// free(g.input);
	}
	return (0);
}
