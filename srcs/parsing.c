/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:18 by smessal           #+#    #+#             */
/*   Updated: 2022/11/24 18:28:03 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char    **get_paths(char **envp)
{
    char **paths;
    char *env_path;
    int i;

    i = 0;
    while (envp && envp[i])
    {
        if (!ft_strncmp(envp[i], "PATH", 4))
            env_path = envp[i];
        i++;
    }
    i = 0;
    while (i < 5)
    {
        env_path++;
        i++;
    }
    paths = ft_split(env_path, ':');
    if (!paths)
        return (NULL);
    return (paths);
}

// Tester avec double pointeur liste chainee

t_command   *extract_commands(char **av)
{
    t_command   *com;
    int         i;
	int			index;
    
    i = 3;
	index = 0;
    com = ft_lstnew_com(av[2], index);
	index++;
    if (!com)
        return (NULL);
    while (av && av[i])
    {
        ft_lst_addback_com(&com, ft_lstnew_com(av[i], index));
        i++;
		index++;
		if (!av[i + 1])
			break;
    }
    return(com);
}

char    *command_exists(t_command *com, char **paths)
{
    char    *final_path;
    int     i;

    i = 0;
	if (!access(com->command, X_OK))
		return(com->command);
    while (paths && paths[i])
    {
		final_path = ft_strjoin(paths[i], "/");
        final_path = ft_strjoin(final_path, com->command);
        if (!access(final_path, X_OK))
            return (final_path);
        i++;
    }
	if (final_path)
		free(final_path);
    return (NULL);
}
