/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:58:33 by annabrag          #+#    #+#             */
/*   Updated: 2024/09/02 19:21:48 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_node(char *content)
{
	t_token	*new_node;
	
	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

t_token	*last_node(t_token *t)
{
	if (t == NULL)
		return (NULL);
	while (t->next != NULL)
		t = t->next;
	return (t);
}

void	add_back(t_token **t, t_token *new_node)
{
	t_token	*tmp;

	if ((*t) == NULL)
		*t = new_node;
	else
	{
		tmp = last_node(*t);
		tmp->next = new_node;
	}
}

size_t	get_tlist_size(t_token **t)
{
	size_t	size;
	t_token *node;

	size = 0;
	node = *t;
	while (node != NULL)
	{
		size++;
		node = node->next;
	}
	return (size);
}