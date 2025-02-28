/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:09 by throbert          #+#    #+#             */
/*   Updated: 2025/02/27 23:28:15 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*parse_tilde(char *in, int *i, char *w, t_shell *shell)
{
	char	*tmp;
	char	*home;

	if (!in[*i + 1] || in[*i + 1] == '/' || ft_isspace(in[*i + 1]))
	{
		home = get_env_value("HOME", *shell);
		if (!home)
		{
			home = getenv("HOME");
			w = append_char(w, '~');
		}
		else
		{
			tmp = ft_strdup(home);
			w = append_str(w, tmp);
			free(tmp);
			free(home);
		}
	}
	else
		w = append_char(w, '~');
	(*i)++;
	return (w);
}

// just copie litteraly in betwin quote
void	handle_singlequote(char *in, int *i, char **w)
{
	*w = append_char(*w, '\'');
	(*i)++;
	while (in[*i] && in[*i] != '\'')
	{
		*w = append_char(*w, in[*i]);
		(*i)++;
	}
	if (in[*i] == '\'')
	{
		*w = append_char(*w, '\'');
		(*i)++;
	}
}

int	count_backslash(char *s, int pos)
{
	int	cnt;

	cnt = 0;
	pos--;
	while (pos >= 0 && s[pos] == '\\')
	{
		cnt++;
		pos--;
	}
	return (cnt);
}

// keep char in 1rst if
void	handle_backslash(char *in, int *i, char **w)
{
	if (in[*i + 1] == '$' || in[*i + 1] == '"' || in[*i + 1] == '\\' || in[*i
			+ 1] == '\n')
	{
		(*i)++;
		if (in[*i])
		{
			*w = append_char(*w, in[*i]);
			(*i)++;
		}
	}
	else if (in[*i + 1] == '`')
		(*i)++;
	else
	{
		*w = append_char(*w, '\\');
		(*i)++;
	}
}

char	*ft_parse_word(char *in, int *pos, t_shell *shell)
{
	char	*w;
	int		i;

	w = ft_strdup("");
	i = *pos;
	while (in[i] && !ft_isspace(in[i]))
	{
		if (in[i] == '\\')
			handle_backslash(in, &i, &w);
		else if (in[i] == '\'')
			handle_singlequote(in, &i, &w);
		else if (in[i] == '"')
			handle_doublequote(in, &i, &w, shell);
		else if (in[i] == '~' && !ft_strlen(w))
			w = parse_tilde(in, &i, w, shell);
		else if (in[i] == '$')
			handle_dollar(in, &i, &w, shell);
		else
		{
			w = append_char(w, in[i]);
			i++;
		}
	}
	*pos = i;
	return (w);
}
