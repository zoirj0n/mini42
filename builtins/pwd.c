/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:15:12 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/01 18:15:13 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/**
 * @brief Gets the path from env to current directory
 * and displays it.
 *
 * @param step
 * @param shell
 */
void print_working_directory(t_exec_step *step, t_shell *shell)
{
	char *dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		dir = retrieve_environment_variable(shell, "PWD");
	if (!dir)
		return;
	printf("%s\n", dir);
	deallocate_memory(&dir);
	step->exit_code = 0;
	shell->last_exit_code = step->exit_code;
}
