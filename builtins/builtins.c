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

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

bool is_builtin(t_exec_step *step)
{
	if (ft_strcmp(step->cmd->arg_arr[0], "echo") == 0 || ft_strcmp(step->cmd->arg_arr[0], "cd") == 0 || ft_strcmp(step->cmd->arg_arr[0], "pwd") == 0 || ft_strcmp(step->cmd->arg_arr[0], "env") == 0 || ft_strcmp(step->cmd->arg_arr[0], "export") == 0 || ft_strcmp(step->cmd->arg_arr[0], "exit") == 0 || ft_strcmp(step->cmd->arg_arr[0], "unset") == 0)
		return (true);
	return (false);
}

bool parent_builtin(t_exec_step *step)
{
	if (step->cmd == NULL || step->cmd->arg_arr[0] == NULL)
		return (false);
	if (ft_strcmp(step->cmd->arg_arr[0], "unset") == 0 || ft_strcmp(step->cmd->arg_arr[0], "cd") == 0 || (ft_strcmp(step->cmd->arg_arr[0], "export") == 0 && step->cmd->arg_arr[1] != NULL) || ft_strcmp(step->cmd->arg_arr[0], "exit") == 0)
		return (true);
	return (false);
}

bool run_builtin(t_exec_step *step, t_shell *shell, bool child)
{
	if (ft_strcmp(step->cmd->arg_arr[0], "echo") == 0)
		ft_echo(step, shell);
	if (ft_strcmp(step->cmd->arg_arr[0], "cd") == 0)
		ft_cd(step, shell->env, shell);
	if (ft_strcmp(step->cmd->arg_arr[0], "pwd") == 0)
		ft_pwd(step, shell);
	if (ft_strcmp(step->cmd->arg_arr[0], "env") == 0)
		ft_env(shell, step);
	if (ft_strcmp(step->cmd->arg_arr[0], "export") == 0)
		ft_export(shell, step);
	if (ft_strcmp(step->cmd->arg_arr[0], "exit") == 0)
		ft_exit(step, shell, child);
	if (ft_strcmp(step->cmd->arg_arr[0], "unset") == 0)
		ft_unset(shell, step);
	if (ft_strcmp(step->cmd->arg_arr[0], "echo") == 0 || ft_strcmp(step->cmd->arg_arr[0], "cd") == 0 || ft_strcmp(step->cmd->arg_arr[0], "pwd") == 0 || ft_strcmp(step->cmd->arg_arr[0], "env") == 0 || ft_strcmp(step->cmd->arg_arr[0], "export") == 0 || ft_strcmp(step->cmd->arg_arr[0], "exit") == 0 || ft_strcmp(step->cmd->arg_arr[0], "unset") == 0)
		return (true);
	return (false);
}
