/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:51:18 by smessal           #+#    #+#             */
/*   Updated: 2023/02/20 12:41:15 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char    **get_paths(char **envp)
{
    int        i;
    char    *path_var;
    char    **env_path;

    i = 0;
    env_path = NULL;
    while (envp[i])
    {
        path_var = ft_strnstr(envp[i], "PATH=", 6);
        if (path_var)
        {
            env_path = ft_split(path_var, ':');
            break ;
        }
        i++;
    }
    i = -1;
    while (env_path && env_path[++i])
        env_path[i] = ft_strjoin(env_path[i], "/");
    return (env_path);
}

t_cmdtab   *extract_commands(char **av, t_data *data)
{
    t_cmdtab   *com;
    int         i;
	int			index;
    
    i = 3;
	index = 0;
	com = malloc(sizeof(t_cmdtab *) * 1);
	if (!com)
		return (NULL);
    com = ft_lstnew_com(av[2], index);
	index++;
    if (!com)
        return (NULL);
    while (av && av[i])
    {
		// printf("av: %s\n", av[i]);
		ft_lst_addback_com(&com, ft_lstnew_com(av[i], index));
        i++;
		index++;
		if (!av[i + 1])
			break;
    }
    return(com);
}

char    *command_exists(t_cmdtab *com, char **paths)
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
