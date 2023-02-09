/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:33:57 by smessal           #+#    #+#             */
/*   Updated: 2023/02/09 15:48:11 by smessal          ###   ########.fr       */
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

void	free_com(t_cmdtab **com)
{
	t_cmdtab	*temp;
	
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
	if (data && (*data))
	{
		if ((*data) && (*data)->temp)
			free_com(&(*data)->temp);
		if ((*data) && (*data)->com)
			free((*data)->com);
		if ((*data) && (*data)->pid)
			free((*data)->pid);
		if ((*data) && data && (*data)->paths)
			free_tab((*data)->paths);
		if ((*data) && (*data) && (*data)->final_path)
			free((*data)->final_path);
		if ((*data))
			free(*data);
	}
}
