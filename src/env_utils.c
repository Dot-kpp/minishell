/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgeslin <fgeslin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:39:49 by fgeslin           #+#    #+#             */
/*   Updated: 2023/04/18 12:32:28 by fgeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ms_builtins.h"

static void	ms_setenv(char *name, char *value, t_mshell *mshell)
{
	char	var[PATH_MAX];

	ft_strlcpy(var, name, PATH_MAX);
	ft_strlcat(var, "=", PATH_MAX);
	ft_strlcat(var, value, PATH_MAX);
	update_envp(var, mshell);
}

char	*ms_getenv(char const *var, char const **env)
{
	char	*eq;
	int		i;

	i = 0;
	eq = ft_strjoin(var, "=");
	while (env[i])
	{
		if (!ft_strncmp(eq, env[i], ft_strlen(eq)))
			return (free(eq), (char *)(env[i] + ft_strlen(eq)));
		i++;
	}
	return (free(eq), NULL);
}

//init envl
void	init_env(char const *env[], t_mshell *mshell)
{
	char	*temp;
	char	cwd[PATH_MAX];

	mshell->exit_status = 0;
	mshell->env = dup_matrix(env);
	getcwd(cwd, PATH_MAX);
	if (!ms_getenv("PWD", (const char **)mshell->env))
		ms_setenv("PWD", cwd, mshell);
	if (!ms_getenv("PATH", (const char **)mshell->env))
		ms_setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin",
			mshell);
	temp = ms_getenv("SHLVL", (const char **)mshell->env);
	if (!temp || ft_atoi(temp) < 1)
		ms_setenv("SHLVL", "1", mshell);
	else
	{
		temp = ft_itoa(ft_atoi(temp) + 1);
		ms_setenv("SHLVL", temp, mshell);
		free(temp);
	}
}

int	update_envp(const char *str, t_mshell *mshell)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '=')
		i++;
	j = 0;
	while (mshell->env[j])
	{
		if (!ft_strncmp(str, mshell->env[j], i + 1))
		{
			free(mshell->env[j]);
			mshell->env[j] = ft_strdup(str);
			return (0);
		}
		j++;
	}
	mshell->env = expand_matrix((const char **)mshell->env, str);
	if (!mshell->env)
		return (perror("update_envp"), 1);
	return (0);
}

int	is_valid_envp(const char *str, int n)
{
	int	i;

	i = -1;
	while (str[++i] && i < n)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}
