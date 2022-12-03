/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:49:06 by smessal           #+#    #+#             */
/*   Updated: 2022/12/02 19:18:22 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void    first_child(t_data *data, t_command *com, char **envp)
// {
//     data->final_path = command_exists(com, data->paths);
//     if (data->final_path)
//     {
//         if (data->infile == -1)
//         {
//             free_data(&data);
//             return ;
//         }
//         dup2(data->fd[1], STDOUT_FILENO);
//         dup2(data->infile, 0);
//         close(data->fd[0]);
//         close(data->fd[1]);
//         execve(data->final_path, com->options, envp);
//     }
// }

// void    second_child(t_data *data, t_command *com, char **envp)
// {
//     if (data->final_path)
//         free(data->final_path);
//     com = com->next;
//     data->final_path = command_exists(com, data->paths);
//     if (data->final_path)
//     {
//         if (data->outfile == -1)
//         {
//             free_data(&data);
//             return ;
//         }
//         dup2(data->fd[0], STDIN_FILENO);
//         dup2(data->outfile, 1);
//         close(data->fd[0]);
//         close(data->fd[1]);
//         execve(data->final_path, com->options, envp);
//     }
// }

// void    exec_all(t_data *data, char **envp)
// {
//     int	i;

// 	i = 0;
// 	if (pipe(data->fd) == -1)
// 		return ;
// 	while (i < data->ac - 3)
// 	{
// 		data->pid[i] = fork();
// 		if (data->pid[i] < 0)
// 			return ;
// 		else if (data->pid[i] == 0 && i == 0)
// 			first_child(data, (*data->com), envp);
// 		else if (data->pid[i] == 0 && i == 1)
// 			second_child(data, (*data->com), envp);
// 		i++;
// 	}
// 	close(data->fd[0]);
// 	close(data->fd[1]);
// 	wait_for_all(data, (*data->com));
// }

int	conditions_child(t_data	*data, int fd[2], char **envp)
{
	if ((*data->com)->index == data->ac - 4)
		dup2(data->outfile, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	if ((*data->com)->index != 0)
		dup2(data->old_fd, STDIN_FILENO);
	data->final_path = command_exists((*data->com), data->paths);
	if (data->final_path)
    {
		close(fd[0]);
        close(fd[1]);
        execve(data->final_path, (*data->com)->options, envp);
    }
    else
		return (free_data(&data), 0);
	return (free_data(&data), 1);
}

void	conditions_parent(t_data *data, int fd[2])
{
	data->old_fd = fd[0];
	if ((*data->com))
		(*data->com) = (*data->com)->next;
}


void    exec_all_test(t_data *data, char **envp)
{
	int			i;
    
    i = 0;
    if (pipe(data->fd) == -1)
    {
        write(1, "Error in pipe\n", 14);
        return ;
    }
    while (i < data->ac - 3)
    {
        data->pid[i] = fork();
		if (data->pid[i] == 0)
		{	
			if(!conditions_child(data, data->fd, envp))
				return ;
		}
		else
		{
			conditions_parent(data, data->fd);
		}
		i++;
	}
    wait_for_all(data, data->temp);
    // wait(NULL);
}
