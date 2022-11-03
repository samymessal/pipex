/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:18 by smessal           #+#    #+#             */
/*   Updated: 2022/11/03 14:24:50 by smessal          ###   ########.fr       */
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

t_command   *extract_commands(char **av)
{
    t_command   *com;
    int         i;
    
    i = 3;
    com = ft_lstnew_com(av[2]);
    if (!com)
        return (NULL);
    while (av && av[i])
    {
        ft_lst_addback_com(&com, ft_lstnew_com(av[i]));
        i++;
    }
    return(com);
}

char    *command_exists(t_command *com, char **paths)
{
    char    *final_path;
    int     i;

    i = 0;
    while (paths && paths[i])
    {
        if (!access(com->command, X_OK))
			return(com->command);
		final_path = ft_strjoin(paths[i], "/");
        final_path = ft_strjoin(final_path, com->command);
        if (!access(final_path, X_OK))
            return (final_path);
        i++;
    }
    return (NULL);
}
