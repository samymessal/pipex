/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:33:57 by smessal           #+#    #+#             */
/*   Updated: 2022/11/25 18:11:02 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	free_com(t_command **com)
{
	t_command	*temp;
	
	while (com && *com)
	{
		temp = *com;
		if ((*com)->command)
			free((*com)->command);
		if ((*com)->options)
			free_tab((*com)->options);
		(*com) = (*com)->next;
		if (temp)
			free(temp);
	}
}

void	free_data(t_data **data)
{
	if (data)
	{
		if ((*data)->temp)
			free_com(&(*data)->temp);
		if ((*data)->com)
			free((*data)->com);
		if (data && (*data)->paths)
			free_tab((*data)->paths);
		if ((*data) && (*data)->final_path)
			free((*data)->final_path);
		if ((*data))
			free(*data);
	}
}
