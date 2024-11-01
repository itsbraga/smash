/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rainbow_txt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annabrag <annabrag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:29:12 by art3mis           #+#    #+#             */
/*   Updated: 2024/10/23 19:07:45 by annabrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*rainbow_prompt(const char *str)
{
	const char	*colors[7] = {RED, YELLOW, GREEN, CYAN, BLUE, PURPLE, PINK};
	char		*colored_str;
	int			i;
	size_t		len;

	len = (ft_strlen(str) * (10 + 4) + ft_strlen(R) + 5);
	colored_str = yama(CREATE, NULL, len);
	secure_malloc(colored_str, true);
	colored_str[0] = '\0';
	i = 0;
	while (str[i] != '\0')
	{
		ft_strcat(colored_str, "\001");
		ft_strcat(colored_str, (char *)colors[i % 7]);
		ft_strcat(colored_str, "\002");
		ft_strcat(colored_str, (char []){str[i], '\0'});
		i++;
	}
	return (colored_str);
}
