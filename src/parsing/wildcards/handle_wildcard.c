/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 07:42:28 by throbert          #+#    #+#             */
/*   Updated: 2025/02/27 23:19:17 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	contain_wildcard(char *current_token)
{
	if (ft_strchr(current_token, '*'))
		return (1);
	return (0);
}

char	*remove_quotes_wild(char *s)
{
	char	*clean;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	clean = malloc(len + 1);
	if (!clean)
		return (NULL);
	copy_without_quotes(s, clean);
	return (clean);
}

/* --- Fonctions pour expand_token --- */

/* --- Fonction de remplissage de la nouvelle commande --- */

char	**fill_new_cmd(char **new_cmd, char **expansion)
{
	char	**new;
	int		len_a;
	int		len_b;
	int		i;
	int		j;

	len_a = ft_tablen(new_cmd);
	len_b = ft_tablen(expansion);
	new = malloc(sizeof(char *) * (len_a + len_b + 1));
	j = 0;
	i = 0;
	while (i < len_a)
	{
		new[j++] = ft_strdup(new_cmd[i]);
		i++;
	}
	i = 0;
	while (i < len_b)
	{
		new[j++] = ft_strdup(expansion[i]);
		i++;
	}
	new[j] = NULL;
	return (new);
}

/* --- Découpage de expand_wildcard --- */

static char	**process_token(char *token, char **current_cmd)
{
	char	**expansion;
	char	**tmp;

	if (contain_wildcard(token))
		expansion = expand_token(token);
	else
	{
		expansion = malloc(sizeof(char *) * 2);
		if (!expansion)
			return (current_cmd);
		expansion[0] = ft_strdup(token);
		expansion[1] = NULL;
	}
	tmp = fill_new_cmd(current_cmd, expansion);
	free_tab(current_cmd);
	free_tab(expansion);
	return (tmp);
}

char	**expand_wildcard(char **token_cmd, t_shell *shell)
{
	char	**new_cmd;
	int		i;

	new_cmd = malloc(sizeof(char *) * 1);
	new_cmd[0] = NULL;
	detect_ambiguous_redirects(token_cmd, shell);
	i = 0;
	while (token_cmd[i])
	{
		new_cmd = process_token(token_cmd[i], new_cmd);
		i++;
	}
	free_tab(token_cmd);
	return (new_cmd);
}
