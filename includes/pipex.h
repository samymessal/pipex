/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smessal <smessal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:54:16 by smessal           #+#    #+#             */
/*   Updated: 2023/02/09 16:33:31 by smessal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <features.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../utils/libft/libft.h"

/*----------Structures---------*/
typedef struct s_command
{
    char                *command;
    char                **options;
	int					index;
	// int					pid;
	// int					wpid;
    struct s_command    *next;
}               t_cmdtab;

typedef struct s_file
{
	char    *file;
	int		fd;
}       t_file;

typedef struct s_data
{
	t_cmdtab	**com;
	t_cmdtab	*temp;
	int			ac;
	int			p_count;
	t_file		infile;
	t_file		outfile;
	int			old_fd;
	int			**fd;
	int			*pid;
	char		**paths;
	char		*final_path;
	char		**env;
}				t_data;

/*----------PARSING-----------*/
char        **get_paths(char **envp);
t_cmdtab   **extract_commands(char **av);
char        *command_exists(t_cmdtab *com, char **paths);
/*----------UTILS-------------*/
int         ft_count_tab(char **tab);
t_cmdtab	*ft_lstnew_com(char *arg, int index);
void        ft_lst_addback_com(t_cmdtab **com, t_cmdtab *new);
void        fill_list(t_cmdtab *com, char *arg, int index);
int			len_list(t_cmdtab *com);
/*----------EXEC---------------*/
void    first_child(t_data *data, t_cmdtab *com, char **envp);
void    second_child(t_data *data, t_cmdtab *com, char **envp);
void    exec_all(t_data *data, char **envp);
void	wait_for_all(t_data *data, t_cmdtab *com);
void    exec_all_test(t_data *data, char **envp);
/*----------FREE---------------*/
void	free_tab(char **tab);
void	free_com(t_cmdtab **com);
void	free_data(t_data **data);
void	free_tab_int(int **tab);
/*----------ERRORS-------------*/
void    print_error(t_data **data, int code);
void    check_data(t_data *data);
int     search_commands(t_data  *data);

#endif