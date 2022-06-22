#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

char	**ft_split(char const *s, char c);
char *find_path(char *command, char **envp);
char	*ft_strjoin(char const *s1, char const *s2, char const *s3);
int		ft_strlen(const char *str);
void	ft_error(char *str);

#endif
