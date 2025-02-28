/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:48 by throbert          #+#    #+#             */
/*   Updated: 2025/02/28 02:18:35 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ignore first ' et copy till next '
void	process_single_quote(const char *s, char *clean, int *i, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		clean[(*j)++] = s[*i];
		(*i)++;
	}
	if (s[*i] == '\'')
		(*i)++;
}

// ignore first " et copy till next "
void	process_double_quote(const char *s, char *clean, int *i, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != '\"')
	{
		if (s[*i] == '\\' && s[*i + 1] && (s[*i + 1] == '\"' || s[*i
					+ 1] == '\\' || s[*i + 1] == '$' || s[*i + 1] == '`'))
		{
			(*i)++;
			clean[(*j)++] = s[*i];
			(*i)++;
		}
		else
		{
			clean[(*j)++] = s[*i];
			(*i)++;
		}
	}
	if (s[*i] == '\"')
		(*i)++;
}

// escape
void	process_backslash(const char *s, char *clean, int *i, int *j)
{
	(*i)++;
	if (s[*i])
	{
		clean[(*j)++] = s[*i];
		(*i)++;
	}
}

void	copy_without_quotes(const char *s, char *clean)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			process_single_quote(s, clean, &i, &j);
		else if (s[i] == '\"')
			process_double_quote(s, clean, &i, &j);
		else if (s[i] == '\\')
			process_backslash(s, clean, &i, &j);
		else
		{
			clean[j] = s[i];
			i++;
			j++;
		}
	}
	clean[j] = '\0';
}

char	*remove_quotes(char *s)
{
	char	*clean;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	if (!ft_strchr(s, '*'))
	{
		copy_without_quotes(s, clean);
		free(s);
		return (clean);
	}
	else
	{
		free(clean);
		return (s);
	}
}
