/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyanar <tyanar@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:18:15 by tyanar            #+#    #+#             */
/*   Updated: 2022/06/22 19:23:04 by tyanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>

char	**ft_split(char const *s, char c);
char	*find_path(char *command, char **envp);
char	*ft_strjoin(char const *s1, char const *s2, char const *s3);
int		ft_strlen(const char *str);
void	ft_error(char *str);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
#endif
