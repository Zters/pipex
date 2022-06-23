/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyanar <tyanar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:18:09 by tyanar            #+#    #+#             */
/*   Updated: 2022/06/22 20:50:32 by tyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void	ft_error(char *str)
{
	perror(str);
	exit(1);
}

int	ft_parent(char **argv, char **envp, int *pipefd)
{
	char	*com_path;
	char	**command;
	int		out;

	out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out == -1 || close(pipefd[1]) == -1 || dup2(pipefd[0],
			STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		ft_error("\x1b[1;31\x7mError");
	command = ft_split(argv[3], ' ');
	com_path = find_path(command[0], envp);
	if (execve(com_path, command, envp) == -1)
		ft_error("\x1b[1;31\x7mError");
	return (0);
}

int	ft_child(char **argv, char **envp, int *pipefd)
{
	char	*com_path;
	char	**command;
	int		in;

	in = open(argv[1], O_RDONLY, 0777);
	if (in == -1 || close(pipefd[0]) == -1 || dup2(pipefd[1],
			STDOUT_FILENO) == -1 || dup2(in, STDIN_FILENO) == -1)
		ft_error("\x1b[1;31\x7mError");
	command = ft_split(argv[2], ' ');
	com_path = find_path(command[0], envp);
	if (execve(com_path, command, envp) == -1)
		ft_error("\x1b[1;31\x7mError");
	return (0);
}

int	main(int argc, char **argv, char **envp)
	{
	int		pid;
	int		pipefd[2];

	if (argc == 5)
	{
		if (pipe(pipefd) == -1)
			ft_error("\x1b[1;31\x7mError");
		pid = fork();
		if (pid == -1)
			ft_error("\x1b[1;31\x7mError");
		if (pid == 0)
			if (!ft_child(argv, envp, pipefd))
				ft_error("\x1b[1;31\x7mError");
		waitpid(pid, NULL, 0);
		if (ft_parent(argv, envp, pipefd))
			ft_error("\x1b[1;31\x7mError");
		return (0);
	}
	ft_error("\x1b[1;31\x7mError");
}
