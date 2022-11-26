/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2022/11/26 18:49:24 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_data	*init_data(int ac, char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->ac = ac;
	data->paths = get_paths(envp);
	data->com = extract_commands(av);
	data->temp = (*data->com);
    data->infile = open(av[1], O_RDONLY);
	if (data->infile != -1)
		dup2(data->infile, STDIN_FILENO);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
	data->old_fd = 0;
	data->final_path = NULL;
	return (data);
}

int	conditions_child(t_data	*data, int fd[2], char **envp)
{
	close(fd[0]);
	if ((*data->com)->index == data->ac - 4)
		dup2(data->outfile, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	if ((*data->com)->index != 0)
		dup2(data->old_fd, STDIN_FILENO);
	data->final_path = command_exists((*data->com), data->paths);
	// (*data->com)->pid = getpid();
	// printf("Final path: %s\n", data->final_path);
	if (data->final_path)
	{
		// printf("Executing: %s\n", (*data->com)->command);
		execve(data->final_path, (*data->com)->options, envp);
	}
	else
		return (free_data(&data), 0);
	return (free_data(&data), 1);
}

void	conditions_parent(t_data *data, int fd[2])
{
	data->old_fd = fd[0];
	close(fd[1]);
	if ((*data->com))
		(*data->com) = (*data->com)->next;
}

// void	wait_all(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->ac - 3)
// 	{
// 		waitpid((*data->com)->pid, &(*data->com)->wpid, 0);
// 		i++;
// 	}
// }

int main(int ac, char **av, char **envp)
{
    int         id;
    t_data		*data;
	int			fd[2];
	int			i;
	
	i = 0;
	if (ac != 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n", 2);
		return (0);
	}
    data = init_data(ac, av, envp);
    while (i < ac - 3)
    {
		if (pipe(fd) == -1)
		{
			write(1, "Error in pipe\n", 14);
			return (1);
		}
        id = fork();
		if (id == 0)
		{	
			if(!conditions_child(data, fd, envp))
				return (1);
		}
		else
		{
			// wait_all(data);
			conditions_parent(data, fd);
		}
		i++;
	}
	wait(NULL);
	free_data(&data);
	return (0);
}
