
#include "minishell.h"

void	cmd_not_found(t_shell *shell, t_exec_step *step, bool *exit_flag)
{
	ft_stderr("minishell: %s: command not found\n", step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 127;
	shell->last_exit_code = step->exit_code;
}

void	cmd_is_dir(t_shell *shell, t_exec_step *step, bool *exit_flag)
{
	ft_stderr("minishell: %s: is a directory\n", step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 126;
	shell->last_exit_code = step->exit_code;
}

void	file_not_found(t_shell *shell, t_exec_step *step, bool *exit_flag)
{
	ft_stderr("minishell: %s: No such file or directory\n",
		step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 127;
	shell->last_exit_code = step->exit_code;
}

void	permission_denied(t_shell *shell, t_exec_step *step, bool *exit_flag)
{
	ft_stderr("minishell: %s: Permission denied\n", step->cmd->arg_arr[0]);
	*exit_flag = true;
	step->exit_code = 126;
	shell->last_exit_code = step->exit_code;
}
