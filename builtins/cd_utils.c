/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:18:36 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/02 19:18:37 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief move from the current directory to the home/root directory.
 *
 * @param shell
 * @param step
 * @param env
 * @param home
 */
void	navigate_to_home(t_shell *shell, t_exec_step *step, char **env,
		char *home)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		oldpwd = retrieve_environment_variable(shell, "PWD");
		deallocate_memory(&home);
		return ;
	}
	if (!chdir(home) && ft_strlen(oldpwd))
	{
		refresh_current_working_directory(env, shell);
		refresh_old_working_directory(shell, env, oldpwd);
		step->exit_code = 0;
	}
	deallocate_memory(&oldpwd);
	deallocate_memory(&home);
}

/**
 * @brief Iterates through the env variables,
 * and returns the length of them.
 *
 * @param env
 * @return size_t
 */
size_t	calculate_environment_length(char **env)
{
	size_t	len;

	len = 0;
	while (env[len] != NULL)
		len++;
	return (len);
}
