
#include "minishell.h"

bool verify_path_validity(t_exec_step *step)
{
	return (step->cmd->arg_arr[0] && access(step->cmd->arg_arr[0], X_OK) != -1 && !ft_strchr(step->cmd->arg_arr[0], '/'));
}

bool verify_command_validity(t_exec_step *step, bool valid_redirs)
{
	return (step->cmd->arg_arr[0] && ((access(step->cmd->arg_arr[0], X_OK) == -1 && !check_builtin_command(step)) || check_directory_status(step->cmd->arg_arr[0]) || !valid_redirs));
}

bool detect_missing_command(t_exec_step *step, bool valid_redirs)
{
	bool check;

	check = (access(step->cmd->arg_arr[0], F_OK) == -1 && !check_builtin_command(step));
	if ((check || check_directory_status(step->cmd->arg_arr[0])) && valid_redirs && !ft_strchr(step->cmd->arg_arr[0], '/'))
		return (true);
	if (access(step->cmd->arg_arr[0], F_OK) != -1 && access(step->cmd->arg_arr[0], X_OK) == -1 && !ft_strchr(step->cmd->arg_arr[0], '/') && valid_redirs)
		return (true);
	return (false);
}

bool detect_missing_file(t_exec_step *step, bool valid_redirs)
{
	return ((access(step->cmd->arg_arr[0], F_OK) == -1 && !check_builtin_command(step)) && valid_redirs && ft_strchr(step->cmd->arg_arr[0], '/'));
}

bool detect_permission_issue(t_exec_step *step, bool valid_redirs)
{
	return ((access(step->cmd->arg_arr[0], X_OK) == -1 && !check_builtin_command(step)) && valid_redirs);
}
