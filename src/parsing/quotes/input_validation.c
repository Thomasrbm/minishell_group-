/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:11 by throbert          #+#    #+#             */
/*   Updated: 2025/03/04 08:05:26 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_quotes_token(t_shell *shell, char *str)
{
	if (!all_quotes_closed(str))
	{
		ft_putstr_fd("Unclosed quotes\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	if (is_only_quotes(str))
	{
		ft_putstr_fd("Command '' not found\n", 2);
		shell->exit_code = 127;
		return (1);
	}
	if (check_error_token(str))
	{
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

int	validate_only_backslash_tick(t_shell *shell, char *str)
{
	if (is_only_backslashes_or_backtick(str))
	{
		if (ft_strlen(str) % 2 != 0)
		{
			if (str[0] == '\\')
				err_backslash();
			else if (str[0] == '`')
				err_backtick();
			shell->exit_code = 2;
			return (1);
		}
	}
	return (0);
}

// if any of ft in the "if" is == 1 we print error
//	+ return "" to not be = to null
// not int ft bc return parse cmd (char *)
char	*validate_input(char *in, t_shell *shell)
{
	char	*cmd_processed;
	char	**cmd_tokens;

	if (validate_quotes_token(shell, in))
		return (ft_strdup(""));
	if (validate_only_backslash_tick(shell, in))
		return (ft_strdup(""));
	if (!validate_only_backslash_tick(shell, in)
		&& ft_strlen(in) > 0
		&& (in[ft_strlen(in) - 1] == '\\' || in[ft_strlen(in) - 1] == '`'))
	{
		cmd_processed = parse_cmd(in);
		cmd_tokens = ft_split_token(cmd_processed, shell);
		error_message(cmd_tokens);
		free(cmd_processed);
		free_tab(cmd_tokens);
		shell->exit_code = 127;
		return (ft_strdup(""));
	}
	return (parse_cmd(in));
}

//  " \\\  "   "```"
