/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:47:50 by throbert          #+#    #+#             */
/*   Updated: 2025/02/27 19:14:34 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// just pinrt $ + space
void	handle_dollar_space(int *i, char **w)
{
	*w = append_char(*w, '$');
	(*i)++;
}

// print exit code
void	handle_dollar_question(int *i, char **w, t_shell *shell)
{
	char	*tmp;

	tmp = ft_itoa(shell->exit_code);
	*w = append_str(*w, tmp);
	free(tmp);
	(*i) += 2;
}

// print env value
void	handle_dollar_var(char *in, int *i, char **w, t_shell *shell)
{
	int		start;
	char	*tmp;
	char	*var;

	start = *i + 1;
	while (in[*i + 1] && (ft_isalnum(in[*i + 1]) || in[*i + 1] == '_'))
		(*i)++;
	tmp = ft_substr(in, start, (*i - start) + 1);
	if (!tmp || !*tmp)
	{
		free(tmp);
		*w = append_char(*w, '$');
		(*i)++;
		return ;
	}
	var = get_env_value(tmp, *shell);
	free(tmp);
	if (!var)
	{
		(*i)++;
		return ;
	}
	*w = append_str(*w, var);
	free(var);
	(*i)++;
}

void	handle_dollar(char *in, int *i, char **w, t_shell *shell)
{
	if (!in[*i + 1] || ft_isspace(in[*i + 1]))
		handle_dollar_space(i, w);
	else if (in[*i + 1] == '?')
		handle_dollar_question(i, w, shell);
	else
		handle_dollar_var(in, i, w, shell);
}

// expand if find $
void	handle_doublequote(char *in, int *i, char **w, t_shell *shell)
{
	*w = append_char(*w, '"');
	(*i)++;
	while (in[*i] != '\0')
	{
		if (in[*i] == '"' && count_backslash(in, *i) % 2 == 0)
		{
			*w = append_char(*w, '"');
			(*i)++;
			break ;
		}
		if (in[*i] == '$')
			handle_dollar(in, i, w, shell);
		else
		{
			*w = append_char(*w, in[*i]);
			(*i)++;
		}
	}
}
