/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:37:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/20 14:54:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*__generate_prompt(t_prompt *pr)
{	
	pr->username = getenv("USER");
	if (pr->username == NULL)
		pr->username = "unknown";
	pr->header = ft_strjoin(rainbow_prompt(PROMPT_BAR), "[");
	secure_malloc(pr->header);
	pr->colored_user = ft_strjoin(BLUE, pr->username);
	secure_malloc(pr->colored_user);
	pr->part1 = ft_strjoin(pr->header, pr->colored_user);
	secure_malloc(pr->part1);
	(free(pr->header), free(pr->colored_user));
	pr->colored_42 = ft_strjoin(GREEN, "42");
	secure_malloc(pr->colored_42);
	pr->tmp = ft_strjoin(R "@", pr->colored_42);
	secure_malloc(pr->tmp);
	free(pr->colored_42);
	pr->part2 = ft_strjoin(pr->tmp, R "] $> ");
	secure_malloc(pr->part2);
	free(pr->tmp);
	pr->prompt = ft_strjoin(pr->part1, pr->part2);
	secure_malloc(pr->prompt);
	(void)yama(ADD, pr->prompt, 0);
	(free(pr->part1), free(pr->part2));
	return (pr->prompt);
}

// singleton version
t_data	*data_struct(void)
{
	static t_data	*instance = NULL;
	t_prompt		pr;

	if (instance == NULL)
	{
		instance = yama(CREATE, NULL, sizeof(t_data));
		secure_malloc(instance);
		instance->prompt = __generate_prompt(&pr);
		if (instance->prompt == NULL)
			clean_exit_shell(FAILURE);
		instance->main = NULL;
		instance->token = NULL;
		instance->exec = NULL;
		instance->info = NULL;
		instance->env = NULL;
		instance->exp_env = NULL;
		instance->last_exit_status = 0;
	}
	return (instance);
}
