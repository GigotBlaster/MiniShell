/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:36:10 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 10:22:56 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_(t_env entry)
{
	ft_putstr("declare -x ");
	ft_putstr(entry.var);
	if (entry.value)
	{
		ft_putstr("=\"");
		ft_putstr(entry.value);
		ft_putstr("\"");
	}
	ft_putstr("\n");
}

static void	print_unquote(t_env entry)
{
	ft_putstr(entry.var);
	ft_putstr("=");
	ft_putstr(entry.value);
	ft_putstr("\n");
}

void		print_envl(t_list *envl, int declare)
{
	t_env	*entry;

	while (envl)
	{
		entry = (t_env *)envl->content;
		if (authorized_char(entry->var))
		{
			if (declare && entry->exported >= 1
				&& ft_strcmp(entry->var, "_") != 0)
				print_quote(*entry);
			else if (!declare && entry->exported >= 2)
				print_unquote(*entry);
		}
		envl = envl->next;
	}
}

int			ft_env(t_info *cmd, t_list **envl)
{
	int		pid;

	add_env("_", ft_strdup("env"), envl, 1);
	pid = fork();
	if (pid == 0)
	{
		if (nb_args(cmd->argv + cmd->offset) > 1)
		{
			print_error("env", NULL, 0,\
			"should be used without option and argument");
			exit(MISUSE);
		}
		change_stdin_stdout(cmd);
		print_envl(*envl, 0);
		exit(SUCCESS);
	}
	return (SUCCESS);
}








//ENV

static int	add_new_var(char *var, char *value, t_list **envl, int exported)
{
	t_list	*new;
	t_env	*cont;

	new = malloc(sizeof(t_list));
	if (!new)
		return (ERROR);
	cont = malloc(sizeof(t_env));
	if (!cont)
	{
		free(new);
		return (ERROR);
	}
	cont->var = var;
	cont->value = value;
	cont->exported = 0;
	if (!value && exported == 2)
		cont->exported = 1;
	else if (value && exported == 2)
		cont->exported = 2;
	new->content = cont;
	new->next = NULL;
	ft_lstadd_back(envl, new);
	return (SUCCESS);
}


int			add_env(char *var, char *value, t_list **envl, int exported)
{
	t_list	*env;

	env = *envl;
	while (env)
	{
		if (ft_strcmp(((t_env *)env->content)->var, var) == 0)
		{
			if (value)
			{
				if (((t_env *)env->content)->value)
					free(((t_env *)env->content)->value);
				((t_env *)env->content)->value = value;
			}
			if (exported > ((t_env *)env->content)->exported)
				((t_env *)env->content)->exported = exported;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (add_new_var(ft_strdup(var), value, envl, exported));
}

int			export_all(char **vars, t_list **envl, int exported)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (vars[i])
	{
		err += export_one(vars[i], envl, exported);
		i++;
	}
	if (err)
		return (ERROR);
	return (SUCCESS);
}

static int	export_one(char *var, t_list **envl, int exported)
{
	char	*value;
	char	*tmp;

	tmp = ft_strchr(var, '=');
	if (tmp)
	{
		value = ft_strdup(tmp + 1);
		tmp[0] = '\0';
	}
	else
		value = NULL;
	if (authorized_char(var))
		return (add_env(var, value, envl, exported));
	invalid_identifier(var, "export", exported);
	if (value)
		free(value);
	return (ERROR);
}