/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:25:53 by smessal           #+#    #+#             */
/*   Updated: 2023/02/20 12:33:19 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmdtab	*ft_lstnew_com(char *arg, int index)
{
	t_cmdtab	*new;

	new = malloc(sizeof(t_cmdtab) * 1);
	if (!new)
		return (NULL);
	fill_list(new, arg, index);
	return (new);
}

void    ft_lst_addback_com(t_cmdtab **com, t_cmdtab *new)
{
    t_cmdtab   *copy;

    copy = *com;
    while(copy && copy->next)
        copy = copy->next;
    copy->next = new;
}

void    fill_list(t_cmdtab *com, char *arg, int index)
{
    char    **split;
    int     i;
    
    split = ft_split(arg, ' ');
    if (!split)
        return ;
    com->command = NULL;
    com->options = ft_calloc(sizeof(char *), ft_count_tab(split) + 1);
    if (!com->options)
        return ;
    i = 0;
    while(i < (ft_count_tab(split)))
    {
        com->options[i] = ft_strdup(split[i]);
        i++;
    }
    com->options[i] = NULL;
	com->index = index;
	// com->pid = 0;
	// com->wpid = 0;
    com->next = NULL;
	free_tab(split);
}

int	len_list(t_cmdtab *com)
{
	int			len;
	t_cmdtab	*copy;

	len = 0;
	copy = com;
	while (copy)
	{
		copy = copy->next;
		len++;
	}
	return (len);
}
