/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2022/11/03 16:52:43 by smessal          ###   ########.fr       */
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

    paths = get_paths(envp);
    com = extract_commands(av);
	if (pipe(fd) == -1)
	{
		write(1, "Error in pipe\n", 14);
		return (1);
	}
    // infile = open(av[1], O_RDONLY);
    // if (infile != -1)
    //     dup2(infile, STDIN_FILENO);
    // outfile = open(av[3], O_RDWR | O_CREAT);
    // dup2(outfile, STDOUT_FILENO);
    while (com)
    {
        id = fork();
		wait(NULL);
		if (id == 0)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			final_path = command_exists(com, paths);
			if (final_path)
				execve(final_path, com->options, envp);
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			com = com->next;
			close(fd[0]);
		}
    }
    // close(infile);
    // close(outfile);
}
