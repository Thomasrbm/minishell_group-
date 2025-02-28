/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:16:40 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 18:16:40 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// close a single
int	process_single_quote_closed(char *s, int i, int *in_single)
{
	if (s[i] == '\'')
	{
		*in_single = 0;
	}
	(i)++;
	return (i);
}

// close a double + if non pair nb of backslash quote is escaped so not closed
// we get back before curr char and bount backslash till its backslash
int	process_double_quote_closed(char *s, int i,
		int *in_double, int *backslashes)
{
	int	j;

	*backslashes = 0;
	j = i - 1;
	while (j >= 0 && s[j] == '\\')
	{
		(*backslashes)++;
		j--;
	}
	if (s[i] == '"' && (*backslashes % 2 == 0))
	{
		*in_double = 0;
	}
	(i)++;
	return (i);
}

// backslash escpae char + set in quote to 1 if met
int	process_normal(char *s, int *i, int *in_single, int *in_double)
{
	if (s[*i] == '\'')
	{
		*in_single = 1;
		(*i)++;
	}
	else if (s[*i] == '"')
	{
		*in_double = 1;
		(*i)++;
	}
	else if (s[*i] == '\\')
	{
		if (s[*i + 1] != '\0')
			*i += 2;
		else
			(*i)++;
	}
	else
	{
		(*i)++;
	}
	return (*i);
}

int	all_quotes_closed(char *s)
{
	int	i;
	int	in_single;
	int	in_double;
	int	backslashes;

	i = 0;
	in_single = 0;
	in_double = 0;
	backslashes = 0;
	while (s[i])
	{
		if (in_single)
			i = process_single_quote_closed(s, i, &in_single);
		else if (in_double)
			i = process_double_quote_closed(s, i, &in_double, &backslashes);
		else
			i = process_normal(s, &i, &in_single, &in_double);
	}
	return (!(in_single || in_double));
}
