
#include "minishell.h"

static bool	handle_invalid_path(t_shell *shell, t_exec_step *step,
	t_exec_flags *flags)
{
	ft_stderr("minishell: %s: command not found\n",
		step->cmd->arg_arr[0]);
	flags->exit = true;
	step->exit_code = 127;
	shell->last_exit_code = step->exit_code;
	close_descriptor(&shell->fd[0]);
	shell->fd[0] = open("/dev/null", O_RDONLY);
	if (!flags->first_flag)
		flags->first_flag = true;
	if (step->and_next || step->or_next)
		return (false);
	return (true);
}

static bool	handle_invalid_cmd(t_shell *shell, t_exec_step *step,
	t_exec_flags *flags)
{
	if (detect_missing_command(step, flags->valid_redirs))
		report_command_not_found(shell, step, &flags->exit);
	else if (check_directory_status(step->cmd->arg_arr[0]) && flags->valid_redirs)
		report_command_is_directory(shell, step, &flags->exit);
	else if (detect_missing_file(step, flags->valid_redirs))
		report_file_not_found(shell, step, &flags->exit);
	else if (detect_permission_issue(step, flags->valid_redirs))
		report_permission_denied(shell, step, &flags->exit);
	close_descriptor(&shell->fd[0]);
	shell->fd[0] = open("/dev/null", O_RDONLY);
	if (step->and_next || step->or_next)
		return (false);
	return (true);
}

void	validate_command_execution(t_shell *shell, t_list **steps, t_exec_step *step,
	t_exec_flags *flags)
{
	if (verify_path_validity(step) == true)
	{
		if (!handle_invalid_path(shell, step, flags))
		{
			flags->action = BREAK;
			return ;
		}
		*steps = (*steps)->next;
		flags->action = CONT;
		return ;
	}
	if (verify_command_validity(step, flags->valid_redirs) == true)
	{
		if (!flags->first_flag)
			flags->first_flag = true;
		if (!handle_invalid_cmd(shell, step, flags))
		{
			flags->action = BREAK;
			return ;
		}
		*steps = (*steps)->next;
		flags->action = CONT;
		return ;
	}
	flags->action = PASS;
}
