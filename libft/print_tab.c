/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:07:23 by throbert          #+#    #+#             */
/*   Updated: 2025/02/27 23:29:16 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	printab(char *fmt, char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] && i < 5)
	{
		printf("[%d] : ", i);
		printf(fmt, tab[i]);
		printf("\n");
		i++;
	}
}
