/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:49:06 by smessal           #+#    #+#             */
/*   Updated: 2023/02/20 13:22:44 by smessal          ###   ########.fr       */
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

// int	conditions_child(t_data	*data, int fd[2], char **envp)
// {
// 	if (data->infile < 0)
// 		return (0);
// 	if ((*data->com)->index == data->ac - 4)
// 		dup2(data->outfile, STDOUT_FILENO);
// 	else
// 		dup2(fd[1], STDOUT_FILENO);
// 	if ((*data->com)->index != 0)
// 		dup2(data->old_fd, STDIN_FILENO);
// 	data->final_path = command_exists((*data->com), data->paths);
// 	if (data->final_path)
//     {
// 		close(fd[0]);
//         close(fd[1]);
//         execve(data->final_path, (*data->com)->options, envp);
//     }
//     else
// 		return (free_data(&data), 0);
// 	return (free_data(&data), 1);
// }

// void	conditions_parent(t_data *data, int fd[2])
// {
// 	data->old_fd = fd[0];
// 	if ((*data->com))
// 		(*data->com) = (*data->com)->next;
// }


// void    exec_all_test(t_data *data, char **envp)
// {
// 	int			i;
    
//     i = 0;
// 	if (pipe(data->fd) == -1)
// 	{
// 		write(1, "Error in pipe\n", 14);
// 		return ;
// 	}
//     while (i < data->ac - 3)
//     {
//         data->pid[i] = fork();
// 		if (data->pid[i] == 0)
// 		{	
// 			if(!conditions_child(data, data->fd, envp))
// 				return ;
// 			free_data(&data);
// 		}
// 		else if (data->pid[i] < 0)
// 			return ;
// 		else
// 			conditions_parent(data, data->fd);
// 		i++;
// 	}
// 	close(data->fd[0]);
// 	close(data->fd[1]);
//     wait_for_all(data, (*data->com));
// }

int	check_access(t_data *data, t_cmdtab *tab)
{
	get_abs_path(data->env, tab->options);
	if (!data->env || !tab->command)
	{
		if (access(tab->options[0], X_OK) == 0)
		{
			tab->command = tab->options[0];
			data->is_abs = 1;
		}
	}
	if (access(tab->options[0], F_OK) == 0
		&& access(tab->options[0], X_OK) == -1)
		exit(126);
	if (!tab->command && tab->options[0]) /*Source problemes pipes consecutifs*/
		exit(127);
	return (0);
}

void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_count - 1)
	{
		if (pipe(data->fd[i]) == -1)
			return ;
		i++;
	}
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_count - 1)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

void	make_dup(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	redir(t_data *data, t_cmdtab *tab, int index)
{
	// if (index == 0)
	// 	make_dup(data->infile.fd, 1);
	// if (index == data->p_count - 1)
    //     make_dup(0, data->outfile.fd);
	if (index == 0 && data->p_count > 1)
		make_dup(data->infile.fd, data->fd[index][1]);
	else if (index > 0 && index < data->p_count - 1)
		make_dup(data->fd[index - 1][0], data->fd[index][1]);
	else if (index != 0 && index == data->p_count - 1)
		make_dup(data->fd[index - 1][0], data->outfile.fd);
}

char    *get_abs_path(char **paths, char **opt)
{
    int     i;
    char    *abs;

    i = 0;
    abs = NULL;
    while (paths && paths[i] && opt[0])
    {
     	abs = ft_strjoin(ft_strdup(paths[i]), opt[0]);
		if (access(abs, F_OK | X_OK) == 0)
			break ;
		free(abs);
		abs = NULL;
		i++;
    }
    return (abs);
}

void	exec(t_cmdtab *tab, t_data *data)
{
	int	i;
    t_cmdtab *tmp;

	i = 0;
    tmp = tab;
	init_pipes(data);
	while (tab && i < data->p_count)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			return ;
		tab->command = get_abs_path(get_paths(data->env), tab->options);
		redir(data, tab, i);
		if (data->pid[i] == 0)
		{
			check_access(data, tab);
			close_pipes(data);
			execve(tab->command, tab->options, NULL);
		}
		tab = tab->next;
		i++;
	}
	close_pipes(data);
	wait_for_all(data, tmp);
}
