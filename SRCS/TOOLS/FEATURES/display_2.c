/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:56:55 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/31 11:24:18 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	display_exec_lst(t_exec_lst **e)
{
	t_exec_lst	*curr;

	curr = *e;
	ft_printf(1, R BOLD Y LIM " t_exec_lst " LIM "\n" R);
	while (curr != NULL)
	{
		ft_printf(1, "--- NODE ---\n");
		ft_printf(1, Y "heredoc_nb:\t [" R "%d" Y "]\n" R, curr->heredoc_nb);
		ft_printf(1, Y "is_given_path:\t [" R);
		ft_printf(1, "%d" Y "]\n" R, curr->is_given_path);
		ft_printf(1, Y "bin_path:\t [" R "%s" Y "]\n" R, curr->bin_path);
		if (curr->cmd != NULL)
			print_cmd(curr->cmd);
		else
			ft_printf(1, Y "cmd:\t\t [" R "(null)" Y "]\n" R);
		if (curr->redir != NULL)
			display_redir_lst(&(curr->redir));
		else
			ft_printf(1, BOLD Y "t_redir_lst:\t [" R "(null)" BOLD Y "]\n" R);
		curr = curr->next;
	}
	if (curr == NULL)
		ft_putendl_fd("", 1);
}

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		dprintf(2, Y "cmd[i]:\t\t [" R "%s" Y "]\t @bloc " R, cmd[i]);
		dprintf(2, "%p\n", cmd[i]);
		i++;
	}
}

void	print_tab2(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		dprintf(2, "tab existe\n");
	else
		dprintf(2, "tab n'existe pas\n");
	if (tab[i])
	{
		while (tab[i])
		{
			dprintf(2, "tab[%d] = %s\n", i, tab[i]);
			i++;
		}
	}
	else
		dprintf(2, "tab existe mais est vide\n");
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		dprintf(2, BOLD GREEN "tab[i]: " R "%s" GREEN " ; " R, tab[i]);
		dprintf(2, BOLD GREEN "located at: " R "%p\n", tab[i]);
		i++;
	}
	if (tab[i] == NULL)
	{
		dprintf(2, BOLD GREEN "tab[i]: " R "%s" GREEN " ; " R, tab[i]);
		dprintf(2, BOLD GREEN "located at: " R "%p\n", tab[i]);
	}
}

void	display_shell_info(void)
{
	ft_printf(STDOUT_FILENO, "\rPID : %d\n", getpid());
	if (isatty(STDIN_FILENO) == 1)
		printf("STDIN connected to terminal :)\n");
	else
		printf("STDIN isn't connected to terminal /!\\\n");
}
