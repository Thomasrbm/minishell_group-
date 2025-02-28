/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 00:56:09 by throbert          #+#    #+#             */
/*   Updated: 2025/02/28 18:26:11 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dans main.c

t_shell	*is_builtin(t_shell *s)
{
	if (!s || !s->cmd || !s->cmd[0])
		return (s);
	if (!ft_strcmp("cd", s->cmd[0]) || !ft_strcmp("pwd", s->cmd[0])
		|| !ft_strcmp("export", s->cmd[0]) || !ft_strcmp("unset", s->cmd[0])
		|| !ft_strcmp("env", s->cmd[0]) || !ft_strcmp("echo", s->cmd[0])
		|| !ft_strcmp("exit", s->cmd[0]))
		s->check = 0;
	else
		s->check = 1;
	return (s);
}

int	is_redirection(t_shell *s)
{
	int	i;

	i = 0;
	if (!s || !s->cmd || !s->cmd[0])
		return (1);
	while (s->cmd[i])
	{
		if ((!ft_strcmp(s->cmd[i], "<")) || (!ft_strcmp(s->cmd[i], ">")
				|| (!ft_strcmp(s->cmd[i], "<<")) || (!ft_strcmp(s->cmd[i], "|"))
				|| (!ft_strcmp(s->cmd[i], ">>"))))
			return (0);
		i++;
	}
	return (1);
}

void	get_shlvl(t_shell *shell)
{
	int		shlvl;
	char	*shlvl_str;

	shlvl = ft_atoi(getenv("SHLVL")) + 1;
	shlvl_str = ft_itoa(shlvl);
	edit_env_value(shell, "SHLVL", shlvl_str);
	free(shlvl_str);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	int		i;
	int		env_count;
	int		exit_code;

	(void)argv;
	if (argc != 1)
		return (1);
	setup_signals(1);
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	env_count = tab_size(env);
	shell->env = malloc(sizeof(char *) * (env_count + 1));
	if (!shell->env)
		return (free(shell), 1);
	i = -1;
	while (env[++i])
		shell->env[i] = ft_strdup(env[i]);
	shell->env[i] = NULL;
	if (getenv("SHLVL"))
		get_shlvl(shell);
	shell->cmd = NULL;
	exit_code = shell_loop(shell);
	return (exit_code);
}

// echo $"$USER"$'$USER'

// cp /bin/ls .
// ls


// minishell > unset PATH
// minishell > < Makefile cat 

// minishell > << dawdwa
// $USER
// dawdwa

// echo $"$USER"
// echo $'$USER'

// /|/

// < Makefile > ls ->ok
