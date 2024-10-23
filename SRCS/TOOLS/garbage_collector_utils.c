/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:54:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 14:30:10 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	*new_gc_node(void *ptr, bool is_tab)
{
	t_gc_lst	*node;

	node = malloc(sizeof(t_gc_lst));
	if (node == NULL)
		return (err_msg(NULL, ERR_MALLOC, 0), NULL);
	node->ptr = ptr;
	node->is_tab = is_tab;
	node->next = NULL;
	return (node);
}

static t_gc_lst	*__last_gc_lst_node(t_gc_lst *yama)
{
	if (yama == NULL)
		return (NULL);
	while (yama->next != NULL)
		yama = yama->next;
	return (yama);
}

void	add_gc_node(t_gc_lst **yama, t_gc_lst *node)
{
	t_gc_lst	*tmp;

	if (*yama == NULL)
		*yama = node;
	else
	{
		tmp = __last_gc_lst_node(*yama);
		tmp->next = node;
	}
}

// static	int	remove_gc_node2(t_gc_lst **yama, void *ptr)
// {
// 	t_gc_lst	*node;
// 	t_gc_lst	*prev;
	
// 	prev = *yama;
// 	while (prev->next != NULL && prev->next->ptr != ptr)
// 		prev = prev->next;
// 	node = prev->next;
// 	prev->next = (prev->next)->next;
// 	free(node->ptr);
// 	node->ptr = NULL;
// 	free(node);
// }

int	remove_gc_node(t_gc_lst **yama, void *ptr)
{
	t_gc_lst	*node;
	t_gc_lst	*prev;

	if (yama == NULL || *yama == NULL)
		return (FAILURE);
	if ((*yama)->ptr == ptr)
	{
		node = *yama;
		*yama = (*yama)->next;
		free_and_set_null(node->ptr);
		free_and_set_null(node);
		return (SUCCESS);
	}
	prev = *yama;
	while (prev->next != NULL && prev->next->ptr != ptr)
	{
		// dprintf(2, "prev->content = %s\n", (char *)prev->ptr);
		prev = prev->next;
	}
	node = prev->next;
	// dprintf(2, "ligne 69 : node = %p\n", node);
	prev->next = (prev->next)->next;
	free_and_set_null(node->ptr);
	free_and_set_null(node);
	return (SUCCESS);
}
