/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:15:17 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/01 18:15:18 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	unset_error(char *arg)
{
	ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
}

static bool	check_unset_arg(const char *arg)
{
	size_t	i;

	if (ft_strchr(arg, '=') != NULL || ft_isdigit(arg[0]))
		return (false);
	i = 0;
	while (arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

void	delete_variable(t_shell *shell, const char *var)
{
	size_t	i;
	bool	found;
	char	*to_look;
	char	**env_copy;

	i = -1;
	found = false;
	to_look = ft_strjoin(var, "=");
	while (shell->env[++i] != NULL)
		if (ft_strncmp(shell->env[i], to_look, ft_strlen(to_look)) == 0)
			found = true;
	if (found == false)
	{
		deallocate_memory(&to_look);
		return ;
	}
	env_copy = ft_calloc(calculate_environment_length(shell->env), sizeof(char *));
	erase_environment_entry(shell, env_copy, to_look);
	deallocate_memory(&shell->env);
	deallocate_memory(&to_look);
	shell->env = env_copy;
}

void	delete_declared_variable(t_shell *shell, const char *var)
{
	size_t	i;
	bool	found;
	char	*to_look;
	char	**env_copy;

	i = -1;
	found = false;
	if (shell->declared_env == NULL)
		return ;
	to_look = ft_strdup(var);
	while (shell->declared_env[++i] != NULL)
		if (ft_strncmp(shell->declared_env[i], to_look,
				ft_strlen(to_look)) == 0)
			found = true;
	if (found == false)
	{
		deallocate_memory(&to_look);
		return ;
	}
	env_copy = ft_calloc(calculate_environment_length(shell->declared_env), sizeof(char *));
	erase_declared_entry(shell, env_copy, to_look);
	deallocate_memory(&shell->declared_env);
	deallocate_memory(&to_look);
	shell->declared_env = env_copy;
}

void	remove_environment_variable(t_shell *shell, t_exec_step *step)
{
	size_t	i;
	char	**args;
	bool	error;

	error = false;
	args = step->cmd->arg_arr;
	i = 0;
	while (args[++i] != NULL)
	{
		if (check_unset_arg(args[i]) == false)
		{
			unset_error(args[i]);
			error = true;
		}
		else
		{
			delete_declared_variable(shell, args[i]);
			delete_variable(shell, args[i]);
		}
	}
	if (error)
		step->exit_code = 1;
	else
		step->exit_code = 0;
	shell->last_exit_code = step->exit_code;
}
