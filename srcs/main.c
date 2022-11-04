/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2022/11/04 19:13:38 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int ac, char **av, char **envp)
{
    int         id;
    char        **paths;
    t_command   *com;
    char        *final_path;
    int         infile;
    int         outfile;
	int			fd[2];
	int			old_fd;

    paths = get_paths(envp);
    com = extract_commands(av);
    infile = open(av[1], O_RDONLY);
	if (infile != -1)
		dup2(infile, STDIN_FILENO);
    outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
    // dup2(outfile, STDOUT_FILENO);
    while (com)
    {
		if (pipe(fd) == -1)
		{
			write(1, "Error in pipe\n", 14);
			return (1);
		}
        id = fork();
		if (id == 0)
		{
			if (com->index == ac - 4)
				dup2(outfile, STDOUT_FILENO);
			else
				dup2(fd[1], STDOUT_FILENO);
			if (com->index != 0)
				dup2(old_fd, STDIN_FILENO);
			final_path = command_exists(com, paths);
			if (final_path)
				execve(final_path, com->options, envp);
			else
				return (0);
		}
		else
		{
			old_fd = fd[0];
			close(fd[1]);
			com = com->next;
		}
    }
	wait(NULL);
    // close(infile);
    // close(outfile);
}
