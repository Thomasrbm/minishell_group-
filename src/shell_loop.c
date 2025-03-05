/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:50:53 by throbert          #+#    #+#             */
/*   Updated: 2025/03/05 12:23:36 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_cmd(t_shell *shell, char **toks)
{
	int		i;
	char	*tmp;

	i = 0;
	shell->cmd = malloc(sizeof(char *) * (tab_size(toks) + 1));
	while (toks[i])
	{
		tmp = remove_quotes(toks[i]);
		shell->cmd[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	if (toks)
		free(toks);
	shell->cmd[i] = NULL;
}

static void	execute_tokens(t_shell *shell, char **toks)
{
	build_cmd(shell, toks);
	shell->cmd = expand_wildcard(shell->cmd, shell);
	if (shell->cmd[0] && shell->cmd[0][0] != '\0')
	{
		if (is_redirection(shell) == 0)
			shell->exit_code = redirect(shell);
		else if (is_builtin(shell)->check == 0)
			shell->exit_code = exec_builtin(shell->cmd, shell);
		else if (check_single_cmd(shell, shell->cmd)
			&& !ft_tabchr(shell->cmd, '*'))
		{
			error_message(shell->cmd);
			shell->exit_code = 127;
		}
		else
			shell->exit_code = fork_and_exec(shell);
	}
	else
	{
		error_message(shell->cmd);
		if (shell->exit_code == 0)
			shell->exit_code = 127;
	}
}

int	handle_cycle(t_shell *shell)
{
	char	**toks;

	toks = process_input_line(shell);
	if (!toks)
		return (-1);
	execute_tokens(shell, toks);
	return (0);
}

int	shell_loop(t_shell *shell)
{
	int	cycle_status;

	shell->exit_code = 0;
	shell->indexes = 0;
	while (1)
	{
		shell->pipe_count = 0;
		shell->check = 0;
		shell->save_in = 0;
		shell->size = 0;
		shell->save_out = 0;
		shell->in_count = 0;
		shell->out_count = 0;
		cycle_status = handle_cycle(shell);
		if (cycle_status == -1)
			break ;
		free_tab(shell->cmd);
	}
	clear_history();
	free(shell->indexes);
	free_tab(shell->env);
	cycle_status = shell->exit_code;
	free(shell);
	return (cycle_status);
}
