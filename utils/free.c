/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:33:57 by smessal           #+#    #+#             */
/*   Updated: 2022/11/22 16:43:37 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_com(t_command *com)
{
	t_command	*temp;
	
	while (com)
	{
		temp = com;
		free(com->command);
		free_tab(com->options);
		com = com->next;
		free(temp);
	}
	free(com);
}

void	free_data(t_data data)
{
	free_com(data.com);
}


