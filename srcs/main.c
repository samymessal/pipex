/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2022/12/03 19:19:12 by smessal          ###   ########.fr       */
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
	data->pid = malloc(sizeof(int) * (ac - 3));
	if (!data->pid)
		return (NULL);
	data->paths = get_paths(envp);
	data->com = extract_commands(av);
	data->temp = (*data->com);
	data->final_path = NULL;
    data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
	data->old_fd = 0;
	return (data);
}

void	wait_for_all(t_data *data, t_command *com)
{
	int		i;
	char	*file;
	int		wpid;

	i = 0;
	while (i < data->ac - 3)
	{
		// if (i == 0)
		// 	file = data->infile;
		// else if (i == 1)
		// 	file = data->outfile;
		waitpid(data->pid[i], &wpid, 0);
		// check_status(WEXITSTATUS(data->wpid), pip[i].options[0], file);
		i++;
	}
}

int main(int ac, char **av, char **envp)
{
    int         id;
	int			check;
    t_data		*data;
	// int			fd[2];
	// int			i;
	
	// i = 0;
	if (ac != 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n", 2);
		return (1);
	}
    data = init_data(ac, av, envp);
	check_data(data);
	exec_all_test(data, envp);
	// close(data->fd[0]);
	// close(data->fd[1]);
	// close(data->old_fd);
	// wait_for_all(data, (*data->com));
	if (data)
		free_data(&data);
	return (0);
}
