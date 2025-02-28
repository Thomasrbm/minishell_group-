/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:39:54 by throbert          #+#    #+#             */
/*   Updated: 2025/02/28 14:49:27 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	error_message_print(char **cmd)
{
	if (cmd[0][0] == '/' || !ft_strncmp(cmd[0], "./", 2) || (ft_strchr(cmd[0],
				'/') && ft_strncmp(cmd[0], "./", 2)))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
}

void	error_message(char **cmd)
{
	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return ;
	if (!ft_strcmp(cmd[0], "."))
	{
		ft_putstr_fd("minishell:  .: filename argument required\n",
			STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		return ;
	}
	if (cmd[0][0] == '`')
		return ;
	if (ft_isspace(cmd[0][0]))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return ;
	}
	error_message_print(cmd);
}
