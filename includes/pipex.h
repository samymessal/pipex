/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:54:16 by smessal           #+#    #+#             */
/*   Updated: 2022/11/03 13:23:20 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <features.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../utils/libft/libft.h"

typedef struct s_command
{
    char                *command;
    char                **options;
    struct s_command    *next;
}               t_command;
/*----------PARSING-----------*/
char        **get_paths(char **envp);
t_command   *extract_commands(char **av);
char        *command_exists(t_command *com, char **paths);
/*----------UTILS-------------*/
int         ft_count_tab(char **tab);
t_command	*ft_lstnew_com(char *arg);
void        ft_lst_addback_com(t_command **com, t_command *new);
void        fill_list(t_command *com, char *arg);
int			len_list(t_command *com);

#endif