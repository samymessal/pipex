/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2022/11/22 17:13:54 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_data	init_data(int ac, char **av, char **envp)
{
	t_data	data;

	data.ac = ac;
	data.paths = get_paths(envp);
	data.com = extract_commands(av);
    data.infile = open(av[1], O_RDONLY);
	if (data.infile != -1)
		dup2(data.infile, STDIN_FILENO);
	data.outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC | 0664);
	data.old_fd = 0;
	return (data);
}

int	conditions_child(t_data	data, int fd[2], char **envp)
{
	if (data.com->index == data.ac - 4)
		dup2(data.outfile, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	if (data.com->index != 0)
		dup2(data.old_fd, STDIN_FILENO);
	data.final_path = command_exists(data.com, data.paths);
	if (data.final_path)
		execve(data.final_path, data.com->options, envp);
	else
		return (0);
	return (1);
}

void	conditions_parent(t_data data, int fd[2])
{
	data.old_fd = fd[0];
	close(fd[1]);
	data.com = data.com->next;
}

int main(int ac, char **av, char **envp)
{
    int         id;
    t_data		data;
	int			fd[2];

    data = init_data(ac, av, envp);
    while (data.com)
    {
		if (pipe(fd) == -1)
		{ pipe (pipe.c:29)

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
			// conditions_parent(data, fd);
			data.old_fd = fd[0];
			close(fd[1]);
			data.com = data.com->next;
		}
	}
	wait(NULL);
	return (0);
}
