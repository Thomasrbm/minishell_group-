/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:57:14 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/05 10:32:12 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// reproduce pwd function
int	ft_pwd(t_shell *shell)
{
	int		exit_code;
	char	*pwd;

	pwd = get_env(shell, "PWD");
	if (!pwd)
	{
		pwd = ft_calloc(5000, sizeof(char));
		getcwd(pwd, 5000);
	}
	if (!pwd)
	{
		exit_code = 1;
		ft_putstr_fd("Error in pwd.\n", STDERR_FILENO);
		return (1);
	}
	ft_printf("%s\n", pwd);
	exit_code = 0;
	if (pwd)
		free(pwd);
	return (exit_code);
}
