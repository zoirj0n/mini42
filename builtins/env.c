/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:15:00 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/01 18:15:01 by zoisobir         ###   ########.fr       */
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
void	ft_env(t_shell *shell, t_exec_step *step)
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
