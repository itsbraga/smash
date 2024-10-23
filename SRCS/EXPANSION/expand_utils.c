/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:56:57 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/23 14:54:03 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing-lexing.h"

size_t	len_to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

static char	*__take_var_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (str[i] != '=')
		i++;
	value = ft_strdup((str + i + 1));
	secure_malloc(value, true);
	(void)yama(ADD, value, 0);
	return (value);
}

char	*clean_translated_variable(char *str, char *var)
{
	char	*new_str;
	int		i;

	new_str = yama(CREATE, NULL, (sizeof(char) * (ft_strlen(str) - 2)));
	secure_malloc(new_str, true);
	i = 0;
	while (str != (var - 1))
		new_str[i++] = *str++;
	str += 2;
	while (*str != *var)
		new_str[i++] = *str++;
	str += 1;
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	free_and_set_null(str);
	return (new_str);
}

char	*take_var(char *str, char *var)
{
	char	*to_find;
	int		i;
	int		j;

	i = 0;
	while ((str + i) != var)
		i++;
	j = i;
	while (str[j] && ((str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= 'a' && str[j] <= 'z')
			|| (str[j] >= '0' && str[j] <= '9')
			|| str[j] == '_'))
		j++;
	to_find = ft_strldup(&(str[i]), (j - i));
	secure_malloc(to_find, true);
	(void)yama(ADD, to_find, 0);
	return (to_find);
}

char	*search_var(char *to_find, t_env_lst *env)
{
	char		*to_cmp;
	t_env_lst	*current;

	to_cmp = NULL;
	current = env;
	while (current != NULL)
	{
		to_cmp = ft_strldup(current->content, len_to_equal(current->content));
		secure_malloc(to_cmp, true);
		(void)yama(ADD, to_cmp, 0);
		if (ft_strcmp(to_find, to_cmp) == 0)
		{
			(void)yama(REMOVE, to_cmp, 0);
			return (__take_var_value(current->content));
		}
		else
		{
			(void)yama(REMOVE, to_cmp, 0);
			to_cmp = NULL;
			current = current->next;
		}
	}
	return (NULL);
}
