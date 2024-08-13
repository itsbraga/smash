/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:33 by annabrag          #+#    #+#             */
/*   Updated: 2024/08/13 15:35:42 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_node(char *content)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->idx = 0;
	new_node->to_expand = false;
	new_node->s_quoted = false;
	new_node->db_quoted = false;
	new_node->t_quoted = 0;
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

t_token	*t_last_node(t_token *t)
{
	if (!t)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}

void	add_back(t_token **t, t_token *new_node)
{
	t_token	*tmp;

	if (!(*t))
		*t = new_node;
	else
	{
		tmp = t_last_node(*t);
		tmp->next = new_node;
	}
}

void	display_tokens(t_token *t)
{
	t_token	*tmp;

	tmp = t;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->content, 1);
		tmp = tmp->next;
		if (!tmp)
			ft_putendl_fd("\n", 1);
		else
			ft_putstr_fd("->", 1);
	}
}
