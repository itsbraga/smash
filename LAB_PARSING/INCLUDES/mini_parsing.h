/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:02:51 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/26 15:39:04 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIEXEC_H
# define MINIEXEC_H

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include "../LIBFT/INCLUDES/libft.h"
# include "../LIBFT/INCLUDES/ft_printf.h"
# include "../LIBFT/INCLUDES/get_next_line_bonus.h"

typedef struct s_token
{
	int             idx;
	bool			to_expand;
    char			*content;
	struct s_token	*next;
}					t_token;

typedef struct s_exec
{
    char *input;
	char **envp;
}   t_exec;

void    init_e(t_exec *e);
t_token	*new_node(char *content);
t_token	*last_node(t_token *t);
void	add_back(t_token **t, t_token *new_node);
void	display_tokens(t_token *t);
size_t	get_tlist_size(t_token **t);
char	*handle_quotes_and_expand(char *input, char **envp);
char	*handle_expand(char *str, char **envp);
char 	*search_var(char *to_find, char **envp);
char	*take_var(char *str, char *var);
bool	switch_bool(bool closed);

#endif