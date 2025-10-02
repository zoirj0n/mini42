/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:18:59 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/02 19:19:00 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Iterate through the copy of env variables array,
 * and print them out when env is called.
 *
 * @param shell
 * @param step
 */
void	show_environment_variables(t_shell *shell, t_exec_step *step)
{
	size_t	i;

	i = 0;
	if (step->cmd->arg_arr[1] != NULL)
	{
		step->exit_code = 1;
		shell->last_exit_code = step->exit_code;
		return ;
	}
	while (shell->env[i] != NULL)
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	step->exit_code = 0;
	shell->last_exit_code = step->exit_code;
}
