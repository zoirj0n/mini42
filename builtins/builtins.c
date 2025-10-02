/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:14:52 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/01 18:14:53 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int compare_strings(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

bool check_builtin_command(t_exec_step *step)
{
	if (compare_strings(step->cmd->arg_arr[0], "echo") == 0 || compare_strings(step->cmd->arg_arr[0], "cd") == 0 || compare_strings(step->cmd->arg_arr[0], "pwd") == 0 || compare_strings(step->cmd->arg_arr[0], "env") == 0 || compare_strings(step->cmd->arg_arr[0], "export") == 0 || compare_strings(step->cmd->arg_arr[0], "exit") == 0 || compare_strings(step->cmd->arg_arr[0], "unset") == 0)
		return (true);
	return (false);
}

bool requires_parent_execution(t_exec_step *step)
{
	if (step->cmd == NULL || step->cmd->arg_arr[0] == NULL)
		return (false);
	if (compare_strings(step->cmd->arg_arr[0], "unset") == 0 || compare_strings(step->cmd->arg_arr[0], "cd") == 0 || (compare_strings(step->cmd->arg_arr[0], "export") == 0 && step->cmd->arg_arr[1] != NULL) || compare_strings(step->cmd->arg_arr[0], "exit") == 0)
		return (true);
	return (false);
}

bool execute_builtin_command(t_exec_step *step, t_shell *shell, bool child)
{
	if (compare_strings(step->cmd->arg_arr[0], "echo") == 0)
		display_echo_output(step, shell);
	if (compare_strings(step->cmd->arg_arr[0], "cd") == 0)
		change_directory(step, shell->env, shell);
	if (compare_strings(step->cmd->arg_arr[0], "pwd") == 0)
		print_working_directory(step, shell);
	if (compare_strings(step->cmd->arg_arr[0], "env") == 0)
		show_environment_variables(shell, step);
	if (compare_strings(step->cmd->arg_arr[0], "export") == 0)
		export_environment_variable(shell, step);
	if (compare_strings(step->cmd->arg_arr[0], "exit") == 0)
		terminate_shell(step, shell, child);
	if (compare_strings(step->cmd->arg_arr[0], "unset") == 0)
		remove_environment_variable(shell, step);
	if (compare_strings(step->cmd->arg_arr[0], "echo") == 0 || compare_strings(step->cmd->arg_arr[0], "cd") == 0 || compare_strings(step->cmd->arg_arr[0], "pwd") == 0 || compare_strings(step->cmd->arg_arr[0], "env") == 0 || compare_strings(step->cmd->arg_arr[0], "export") == 0 || compare_strings(step->cmd->arg_arr[0], "exit") == 0 || compare_strings(step->cmd->arg_arr[0], "unset") == 0)
		return (true);
	return (false);
}
