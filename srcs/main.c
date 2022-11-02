/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:35:51 by smessal           #+#    #+#             */
/*   Updated: 2022/11/02 22:58:37 by smessal          ###   ########.fr       */
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

    id = fork();
    paths = get_paths(envp);
    com = extract_commands(av);
    while (com)
    {
        final_path = command_exists(com, paths);
        // printf("%s\n", final_path);
        if (final_path)
            execve(final_path, com->options, envp);
        com = com->next;
    }
    // infile = open(av[1], O_RDONLY);
    // if (infile != -1)
    //     dup2(infile, STDIN_FILENO);
    // outfile = open(av[3], O_RDWR | O_CREAT);
    // dup2(outfile, STDOUT_FILENO);
    // close(infile);
    // close(outfile);
}