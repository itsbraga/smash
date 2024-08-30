/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:15:10 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/30 20:39:14 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_builtins.h"

t_env	*env_new_var(char *content)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (new_var == NULL)
		return (NULL);
	new_var->content = ft_strdup(content);
	new_var->next = NULL;
	return (new_var);
}

void	del_env_var(t_env **env, char *var_to_rm)
{
	t_env	*prev;
	t_env	*current;
	int		len_var_to_rm;

	if (env == NULL || (*env) == NULL || var_to_rm == NULL)
		return ;
	prev = NULL;
	current = *env;
	len_var_to_rm = ft_strlen(var_to_rm);
    while (current != NULL)
    {
        if ((ft_strncmp(current->content, var_to_rm, len_var_to_rm) == 0)
				&& (current->content[len_var_to_rm] == '='))
        {
            if (prev == NULL)
                *env = current->next; // Si le node à supprimer est le premier de la liste
            else
                prev->next = current->next; // Si le node à supprimer est au milieu ou à la fin
            free(current->content);
            free(current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}
