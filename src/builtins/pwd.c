/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncontin <ncontin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:28:54 by ncontin           #+#    #+#             */
/*   Updated: 2025/04/12 11:10:54 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
custom pwd function,
it uses the getcwd function to get the current working directory
char	*getcwd(char *__buf, size_t __size)
if buf is NULL, an array is allocated with `malloc'; the array is SIZE
bytes long, unless SIZE == 0, in which case it is as big as necessary.
*/
void	ft_pwd(long long int *exit_code)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer)
	{
		*exit_code = 0;
		printf("%s\n", buffer);
		free(buffer);
	}
	else
	{
		*exit_code = 1;
		perror("pwd");
	}
}
