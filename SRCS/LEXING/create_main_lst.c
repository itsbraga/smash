/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_main_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:02:17 by annabrag          #+#    #+#             */
/*   Updated: 2024/10/23 14:44:43 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing-lexing.h"

static void	__init_exec_info(t_data *d)
{
	d->info = yama(CREATE, NULL, sizeof(t_exec_info));
	secure_malloc(d->info, true);
	ft_bzero(d->info, sizeof(t_exec_info));
	d->info->fd[0] = -1;
	d->info->fd[1] = -1;
}

static char	**__get_all_segments(char *input)
{
	t_parser	p;
	size_t		input_len;

	if (input == NULL || input[0] == '\0')
		return (NULL);
	ft_bzero(&p, sizeof(t_parser));
	p.user_input = input;
	input_len = ft_strlen(p.user_input);
	p.segment = yama(CREATE_TAB, NULL, (sizeof(char *) * (input_len + 1)));
	secure_malloc(p.segment, true);
	while (p.user_input[p.i] != '\0')
		parse_input(&p);
	p.segment[p.seg_count] = NULL;
	return (p.segment);
}

int	create_main_lst(t_data *d, char *input)
{
	t_main_lst	*new_node;
	char		**segments;
	int			i;

	if (unclosed_quotes(input) == true)
		return (err_msg(NULL, YELLOW "warning: unclosed quotes" R, 0), FAILURE);
	__init_exec_info(d);
	segments = __get_all_segments(input);
	if (segments == NULL)
		return ((void)yama(REMOVE, segments, 0), SUCCESS);
	i = 0;
	while (segments[i] != NULL)
	{
		new_node = main_lst_new_node(segments[i]);
		secure_malloc(new_node, true);
		main_lst_add_back(&(d->main), new_node);
		i++;
		d->info->cmd_count = i;
		d->info->pipe_count = d->info->cmd_count - 1;
	}
	(void)yama(REMOVE, segments, 0);
	del_unwanted_whitespaces(d->main);
	return (SUCCESS);
}
