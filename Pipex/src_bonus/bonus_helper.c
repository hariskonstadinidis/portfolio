/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:02:28 by hariskon          #+#    #+#             */
/*   Updated: 2025/11/19 18:34:57 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/// @brief Reads here_doc input from stdin into an internal pipe.
/// @details Repeatedly reads lines from stdin until the delimiter string
///          is encountered. All intermediate lines are written to the pipe,
///          whose read end becomes the new input_fd for the pipeline.
///          On failure, prints an error and leaves data unchanged.
/// @param data Pointer to the main program state (uses argv[2] as delimiter).
/// @return 1 on success, or 0 if pipe creation or input reading fails.
int	read_heredoc(t_data *data)
{
	int		pipefd[2];
	char	*s;
	char	*delimiter;

	delimiter = data->argv[2];
	if (!delimiter)
		return (write(2, "Invalid delimiter", 17), 0);
	if (pipe(pipefd) < 0)
		return (perror("Pipe failed"), 0);
	s = get_next_line(0);
	if (!s)
		return (close_pipefd(pipefd), write(2, "GNL Fail", 8), 0);
	while (ft_strncmp(s, delimiter, ft_strlen(delimiter)))
	{
		write(pipefd[1], s, ft_strlen(s));
		free(s);
		s = get_next_line(0);
		if (!s)
			return (close_pipefd(pipefd), free(s), write(2, "GNL Fail", 8), 0);
	}
	free (s);
	get_next_line(-1);
	close(pipefd[1]);
	data->input_fd = pipefd[0];
	return (1);
}

int	argc_check(char **argv, int argc)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		if (argc <= 5)
			return (write(2, "Wrong input, put more arguments\n", 32), 0);
	}
	else
		if (argc <= 4)
			return (write(2, "Wrong input, put more arguments\n", 32), 0);
	return (1);
}
