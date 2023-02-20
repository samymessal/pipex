/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2023/02/20 13:24:09 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_data	*init_data(int ac, char **av, char **envp)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data) * 1);
	if (!data)
		return (NULL);
	data->ac = ac;
	data->p_count = ac - 3;
	data->pid = malloc(sizeof(int) * data->p_count);
	if (!data->pid)
		return (NULL);
	data->fd = malloc(sizeof(int *) * data->p_count - 1);
	if (!data->fd)
		return (NULL);
	while (i < data->p_count - 1)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (!data->fd[i])
			return (NULL);
		i++;
	}
	data->env = envp;
	data->paths = get_paths(envp);
	data->com = extract_commands(av, data);
	data->temp = data->com;
	data->final_path = NULL;
    data->infile.fd = open(av[1], O_RDONLY);
	data->infile.file = ft_strdup(av[1]);
	data->outfile.fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
	data->outfile.file = ft_strdup(av[ac - 1]);
	data->old_fd = 0;
	return (data);
}

void	wait_for_all(t_data *data, t_cmdtab *com)
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
		waitpid(0, &wpid, 0);
		// check_status(WEXITSTATUS(data->wpid), pip[i].options[0], file);
		i++;
	}
}

void	printer(t_data *data)
{
	if (data->com && data->com->command)	
		printf("Command: %s\n", data->com->command);
	else
		printf("No command\n");
	for (int i = 0; data->com->options[i]; i++)
		printf("Options_%d: %s\n", i, data->com->options[i]);
}

int main(int ac, char **av, char **envp)
{
    int         id;
	int			check;
    t_data		*data;
	// int			fd[2];
	// int			i;
	
	// i = 0;
	if (ac < 5)
	{
		ft_putstr_fd("Incorrect number of arguments\n", 2);
		return (1);
	}
    data = init_data(ac, av, envp);
	// check_data(data);
	// exec_all_test(data, envp);
	// printer(data);
	exec(data->com, data);
	// close(data->fd[0]);
	// close(data->fd[1]);
	// close(data->old_fd);
	// wait_for_all(data, (*data->com));
	// if (data)
	// 	free_data(&data);
	return (0);
}
