/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:18 by smessal           #+#    #+#             */
/*   Updated: 2022/12/03 19:54:26 by smessal          ###   ########.fr       */
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
    if (env_path)
	{
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
	return (NULL);
}

t_command   **extract_commands(char **av)
{
    t_command   **com;
    int         i;
	int			index;
    
    i = 3;
	index = 0;
	com = malloc(sizeof(t_command *) * 1);
	if (!com)
		return (NULL);
    *com = ft_lstnew_com(av[2], index);
	index++;
    if (!(*com))
        return (NULL);
    while (av && av[i])
    {
        ft_lst_addback_com(com, ft_lstnew_com(av[i], index));
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
	int		work;

    i = 0;
	final_path = NULL;
	work = access(com->command, X_OK);
	if (!work)
		return(com->command);
    while (paths && paths[i] && com->command)
    {
		final_path = ft_strjoin(paths[i], "/");
        final_path = ft_strjoin(final_path, com->command);
        work = access(final_path, X_OK);
		if (!work)
            return (final_path);
		else if (final_path)
			free(final_path);
        i++;
    }
    return (NULL);
}
