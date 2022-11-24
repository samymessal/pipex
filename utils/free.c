/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:33:57 by smessal           #+#    #+#             */
/*   Updated: 2022/11/24 18:07:12 by smessal          ###   ########.fr       */
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

void	free_data(t_data *data)
{
	if (data && data->com)
		free_com(data->com);
	if (data && data->paths)
		free_tab(data->paths);
	if (data && data->final_path)
		free(data->final_path);
	if (data)
		free(data);
}