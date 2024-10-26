/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:12 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/26 18:49:10 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code = 0;

static void	__minishell(t_data *d)
{
	char	*input;
	int		error;

	error = 0;
	while (1)
	{
		display_shell_info();
		set_signals();
		input = readline(d->prompt);
		if (input == NULL) // Gestion de CTRL+D (EOF)
		{
			ft_printf(STDERR_FILENO, "exit\n");
			break ;
		}
		else if (input[0] != '\0')
		{
			add_history(input);
			if (create_main_lst(d, input) == FAILURE)
				error = 1;
			else
				// display_main_lst(&(d->main));
			if (create_token_dblst(d) == FAILURE)
				error = 1;
			else
				// display_token_dblst(&(d->token));
			printf("\n---------------------------------- INT MAIN ------------------------------------\n");
			// display_exec_lst(&(d->exec));
			if (error != 1)
				while_cmd(d, &(d->exec));
		}
		clean_after_execution(d, input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*d;

	(void)argv;
	d = data_struct();
	if (argc != 1)
	{
		ft_printf(STDOUT_FILENO, BOLD YELLOW "No arguments allowed\n" R);
		clean_exit_shell(FAILURE);
	}
	printf("\n%s", BOLD WELCOME_BANNER R);
	create_env(d, envp);
	// get_parent_pid(d);
	// dprintf(2, "ppid  = %d\n", d->ppid);
	__minishell(d);
	return (SUCCESS);
}
