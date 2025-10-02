/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:15:08 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/01 18:15:09 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	display_export_error(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
}

char	**resize_string_array(char **old, size_t new_size)
{
	size_t	i;
	char	**new_arr;

	new_arr = ft_calloc(new_size + 1, sizeof(char *));
	if (new_arr == NULL)
		exit(1);
	i = 0;
	while (old[i] != NULL)
	{
		new_arr[i] = old[i];
		i++;
	}
	deallocate_memory(&old);
	return (new_arr);
}

bool	set_variable_value(t_shell *shell, char *to_look,
			char *key, char *key_val)
{
	int	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], to_look, ft_strlen(to_look)) == 0)
		{
			deallocate_memory(&to_look);
			deallocate_memory(&shell->env[i]);
			deallocate_memory(&key);
			shell->env[i] = key_val;
			return (false);
		}
		i++;
	}
	return (true);
}

void	display_export_variables(char **val, char **key)
{
	if (*val[0] == '\0')
	{
		deallocate_memory(val);
		printf("declare -x %s\n", *key);
	}
	else
	{
		*val = join_and_free_strings("=\"", *val, 2);
		*val = join_and_free_strings(*val, "\"", 1);
		*key = join_and_free_strings(*key, *val, 3);
		printf("declare -x %s\n", *key);
	}
}

void	process_export_arguments(char **args, t_shell *shell, bool *error)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		if (validate_export_argument(args[i]) == false)
		{
			*error = true;
			display_export_error(args[i]);
		}
		else if (ft_strchr(args[i], '=') != NULL)
			modify_environment_variable(shell, args[i]);
		else
		{
			delete_declared_variable(shell, args[i]);
			modify_declared_variable(shell, args[i]);
		}
		i++;
	}
}
