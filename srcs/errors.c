/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:32:11 by smessal           #+#    #+#             */
/*   Updated: 2022/12/03 19:05:45 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int     search_commands(t_data  *data)
{
    t_command   *temp;
    int         i;

    temp = (*data->com);
    i = 0;
    while (temp)
    {
        if (!command_exists((*data->com), data->paths))
            return (0);
        temp = temp->next;
        i++;
    }
    if (i < data->ac - 3)
        return (0);
    else
        return (1);
}

void    print_error(t_data **data, int code)
{
    char    *error;

    error = NULL;
    if (code == -1)
    {
        ft_putstr_fd("Could not find environment\n", 2);
        if ((*data))
            free_data(data);
        exit(1);
    }
    else
    {
        error = strerror(code);
        ft_putstr_fd(error, 2);
        ft_putstr_fd("\n", 2);
        if ((*data))
            free_data(data);
        exit(code);
    }
}

void    check_data(t_data *data)
{
    if (data->infile < 0)
        print_error(&data, 2);
    else if (!data->paths)
        print_error(&data, -1);
    else if (!search_commands(data))
        print_error(&data, 127);
}
