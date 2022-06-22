#include "pipex.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*a;
	int		i;

	if (!s1 || !s2 || !s3)
		return (NULL);
	a = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +ft_strlen(s3) +1 ));
	if (!a)
		return (NULL);
	i = 0;
	while (*s1)
		a[i++] = *(char *)s1++;
	while (*s2)
		a[i++] = *(char *)s2++;
	while(*s3)
		a[i++] = *(char *)s3++;
	a[i] = 0;
	return (a);
}

int	ft_lettercount(char const *s, char c)
{
	int	count;

	count = 0;
	while (s[count] && s[count] != c)
		count++;
	return (count);
}

int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	chk;
	int	count;

	i = 0;
	count = 0;
	chk = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		chk = ft_lettercount(s + i, c);
		i += chk;
		if (chk)
			count++;
	}
	return (count);
}

char	*ft_wordadd(char const *s, int letter_n, char **rtn)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word = malloc((sizeof(char) * letter_n) + 1);
	if (!word)
	{
		while (rtn[j] != NULL)
		{
			free(rtn[j]);
			j++;
		}
		return (NULL);
	}
	while (i < letter_n && s[i])
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	int		word_n;
	int		letter_n;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word_n = ft_wordcount(s, c);
	rtn = malloc(sizeof(char *) * (word_n + 1));
	if (!rtn)
		return (NULL);
	while (j < word_n)
	{
		while (s[i] == c)
			i++;
		letter_n = ft_lettercount(s + i, c);
		rtn[j] = ft_wordadd(s + i, letter_n, rtn);
		i += letter_n;
		j++;
	}
	rtn[j] = NULL;
	return (rtn);
}
char *find_path(char *command, char **envp) // yol bulucu
{
	int i = 0;
	char **paths;
	char *path;
	
	while(strnstr(envp[i], "PATH" , 4) == 0)
		++i;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while(paths[i])
	{
		path = ft_strjoin(paths[i], "/", command);
		if (access(path, F_OK) == 0)
			return(path);
		++i;
	}
	ft_error("\x1b[1;31\x7mError");
	return(NULL);
} 