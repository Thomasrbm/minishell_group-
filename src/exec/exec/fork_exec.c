/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:34:46 by throbert          #+#    #+#             */
/*   Updated: 2025/02/27 20:01:42 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fork_and_exec(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork", 2);
		return (127);
	}
	if (pid == 0)
	{
		setup_signals(0);
		status = exec(shell->cmd, shell);
		exit(status);
	}
	return (wait_ignore(pid));
}
