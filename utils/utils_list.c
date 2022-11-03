/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:25:53 by smessal           #+#    #+#             */
/*   Updated: 2022/11/03 13:23:05 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_command	*ft_lstnew_com(char *arg)
{
	t_command	*new;

	new = malloc(sizeof(t_command) * 1);
	if (!new)
		return (NULL);
	fill_list(new, arg);
	return (new);
}

void    ft_lst_addback_com(t_command **com, t_command *new)
{
    t_command   *copy;

    copy = *com;
    while(copy->next)
        copy = copy->next;
    copy->next = new;
}

void    fill_list(t_command *com, char *arg)
{
    char    **split;
    int     i;
    
    split = ft_split(arg, ' ');
    if (!split)
        return ;
    com->command = split[0];
    com->options = ft_calloc(sizeof(char *), ft_count_tab(split) + 1);
    if (!com->options)
        return ;
    i = 0;
    while(i < (ft_count_tab(split)))
    {
        com->options[i] = split[i];
        i++;
    }
    com->options[i] = NULL;
    com->next = NULL;
}

int	len_list(t_command *com)
{
	int			len;
	t_command	*copy;

	len = 0;
	copy = com;
	while (copy)
	{
		copy = copy->next;
		len++;
	}
	return (len);
}
