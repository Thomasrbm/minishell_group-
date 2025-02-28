/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:05 by throbert          #+#    #+#             */
/*   Updated: 2025/02/28 01:40:53 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_and_trim(t_shell *shell)
{
	char	*in;
	char	*trim;

	in = get_readline(shell);
	if (g_signal == SIGINT)
		get_sigint(shell);
	if (!in)
	{
		ft_putstr_fd("exit\n", 2);
		return (NULL);
	}
	trim = ft_strtrim(in, " \n\t");
	free(in);
	if (!trim)
		return (NULL);
	if (!*trim)
		trim[0] = '\0';
	return (trim);
}

char	**process_input_line(t_shell *shell)
{
	char	*original_trim;
	char	*parsed_trim;
	char	**toks;

	original_trim = read_and_trim(shell);
	if (!original_trim)
		return (NULL);
	parsed_trim = validate_input(original_trim, shell);
	if (!parsed_trim)
		return (NULL);
	free(original_trim);
	toks = ft_split_token(parsed_trim, shell);
	free(parsed_trim);
	return (toks);
}
