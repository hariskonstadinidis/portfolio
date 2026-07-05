/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:15:03 by hariskon          #+#    #+#             */
/*   Updated: 2025/11/19 18:35:06 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <string.h> 
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

enum	e_in_out
{
	IN,
	OUT,
	APPEND,
};

typedef struct s_data
{
	char	***cmds;
	char	**paths;
	char	**argv;
	char	**envp;
	int		argc;
	int		pipefd[2];
	int		input_fd;
	int		cmds_count;
	char	**first_cmd;
	pid_t	*pids;
}	t_data;

int		main(int argc, char **argv, char **envp);
int		read_heredoc(t_data *data);
t_data	*setup(int argc, char **argv, char **envp);
t_data	*init_data(int argc, char **argv, char **envp);
int		build_empty_cmd(char ***cmds);
char	*ft_strjoin_path(char const *s1, char const *s2);
void	free_data(t_data *data);
void	close_pipefd(int pipefd[2]);
int		argc_check(char **argv, int argc);
int		pid_wait_and_free(t_data *data);
void	child_exec_error(t_data *data, int i);
#endif
