/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2022/11/01 20:34:57 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int ac, char **av, char **envp)
{
    int         id;
    char        **paths;
    t_command   *com;
    int         infile;
    int         outfile;

    id = fork();
    paths = get_paths(envp);
    com = extract_commands(av);
    infile = open(av[1], O_RDONLY);
    if (infile != -1)
        dup2(infile, STDIN_FILENO);
    outfile = open(av[3], O_RDWR | O_CREAT);
    dup2(outfile, STDOUT_FILENO);
    execve("/usr/bin/ls", com->options, envp);
    close(infile);
    close(outfile);
}