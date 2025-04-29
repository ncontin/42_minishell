/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:40:15 by aroullea          #+#    #+#             */
/*   Updated: 2025/04/29 18:22:18 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_history_file(void)
{
	int		fd;
	size_t	len;
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	fd = open(HISTORY_FILE, O_RDONLY);
	if (fd == -1)
		return ;
	while (i < 100)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		len = ft_strlen(str);
		if (str[len - 1] == '\n')
			str[len - 1] = '\0';
		if (str[0] != '\0')
			add_history(str);
		free(str);
		str = NULL;
		i++;
	}
	close(fd);
}
