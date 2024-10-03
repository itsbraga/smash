/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:44:31 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/03 22:08:23 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	__redir_in_and_out(t_token_dblst *t)
{
	t_redir_lst	*new_redir;

	if (t->next != NULL)
	{
		if (t->type == REDIR_IN && t->next->type == INFILE)
		{
			new_redir = redir_lst_new_node(REDIR_IN);
			secure_malloc(new_redir);
			new_redir->infile = token_cleanup(t->next->content);;
			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "infile:\t\t [" R "%s" BOLD PINK "]\n" R, new_redir->infile);
		}
		else if (t->type == REDIR_OUT_TRUNC && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_TRUNC);
			secure_malloc(new_redir);
			new_redir->outfile = token_cleanup(t->next->content);
			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "outfile:\t [" R "%s" BOLD PINK "]\n" R, new_redir->outfile);
		}
		else if (t->type == REDIR_OUT_APPEND && t->next->type == OUTFILE)
		{
			new_redir = redir_lst_new_node(REDIR_OUT_APPEND);
			secure_malloc(new_redir);
			new_redir->outfile = token_cleanup(t->next->content);
			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "outfile:\t [" R "%s" BOLD PINK "]\n" R, new_redir->outfile);
		}
	}
}

int	create_redir_lst(t_data *d)
{
	t_redir_lst	*new_redir;

	if (d->token == NULL || d->token->content == NULL)
		return (FAILURE);
	lstclear_redir(&(d->exec->redir));
	while (d->token != NULL)
	{
		__redir_in_and_out(d->token);
		if (d->token->type == HERE_DOC && d->token->next != NULL
			&& d->token->next->type == LIMITER)
		{
			new_redir = redir_lst_new_node(HERE_DOC);
			secure_malloc(new_redir);
			new_redir->limiter = token_cleanup(d->token->next->content);
			printf(BOLD PINK "new_redir:\t [" R "%d" BOLD PINK "]\n" R, new_redir->type);
			printf(BOLD PINK "limiter:\t [" R "%s" BOLD PINK "]\n" R, new_redir->limiter);
		}
		else
		{
			d->token = d->token->next;
			continue ;
		}
		redir_lst_add_back(&(d->exec->redir), new_redir);
		d->token = d->token->next->next; // eviter de traiter deux fois redir + file/lim
	}
	return (SUCCESS);
}
