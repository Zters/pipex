#include "pipex.h"

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

	out = open(argv[4], O_WRONLY | O_CREAT);
	if (out == -1 || close(pipefd[1]) == -1 || dup2(pipefd[0],
			STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		ft_error("\x1b[1;31\x7mError");
	command = ft_split(argv[3], ' ');
	com_path = find_path(command[0],envp);
	if (execve(com_path, command, envp) == -1)
		ft_error("\x1b[1;31\x7mError");
	return (0);
}

int	ft_child(char **argv, char **envp, int *pipefd)
{
	char	*com_path;
	char	**command;
	int		in;

	in = open(argv[1], O_RDONLY);
	if (in == -1 || close(pipefd[0]) == -1 || dup2(pipefd[1],
			STDOUT_FILENO) == -1 || dup2(in, STDIN_FILENO) == -1)
		ft_error("\x1b[1;31\x7mError");
	command = ft_split(argv[2], ' ');
	com_path = find_path(command[0],envp);
	if (execve(com_path, command, envp) == -1)
		ft_error("\x1b[1;31\x7mError");
	return (0);
}

int	main(int argc, char **argv, char **envp)
	{
	int		pid;
	int		pipefd[2];// 0 İNPUT 1 OUTPUT  BUNLARI KOYABİLMEK İCİN 2 VERDİK  

	if (argc == 5) // arg kontrol
	{
		if (pipe(pipefd) == 1)
			ft_error("\x1b[1;31\x7mError"); // processlerin iletisim kurmasi icin fdleri ayarliyo
		pid = fork(); // prcessin bir kopyasini olusturuyor
		if (pid == -1) // process kontrol
			ft_error("\x1b[1;31\x7mError");
		if (pid == 0) // child isen
			if (!ft_child(argv, envp, pipefd)) // argumanlar env ve fdler ile child in yapicaga isleme gidiyo
				ft_error("\x1b[1;31\x7mError");
		waitpid(pid, NULL, 0); // pid bekliyor childin görevini bitirmesini bekliyor 
		if (ft_parent(argv, envp, pipefd)) // argumanlar env ve fdler ile parent processin yapacagi isleme gidiyor
			ft_error("\x1b[1;31\x7mError");
		return (0);
	}
	ft_error("\x1b[1;31\x7mError"); //https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797  x1b esc tusu 1 alinlastiriyo 31 kirmizi yapiyo x7 terminal alarmi
}
