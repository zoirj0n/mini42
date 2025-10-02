
#include "minishell.h"

static bool	run_cmds(t_shell *shell, t_exec_step *step, t_exec_flags *flags,
	int out_fd)
{
	if (!flags->first_flag && flags->valid_redirs)
	{
		shell->fd = execute_initial_command(step, shell->fd, shell, out_fd);
		flags->first_flag = true;
	}
	else if (flags->valid_redirs)
		shell->fd = execute_pipeline_command(step, shell->fd, shell, out_fd);
	if (step->and_next || step->or_next)
		return (false);
	return (true);
}

static t_exec_step	*run_subexpr(t_shell *shell, t_exec_step *step,
	t_exec_flags *flags, t_list **steps)
{
	if (execute_subexpression(shell, step, flags, steps) == false)
	{
		flags->action = BREAK;
		return (step);
	}
	flags->action = CONT;
	return (step);
}

static t_exec_step	*run_exec_cmds(t_shell *shell, t_list **steps, int *out_fd,
	t_exec_flags *flags)
{
	t_exec_step	*step;

	flags->action = PASS;
	step = (*steps)->content;
	if (step->subexpr_line != NULL)
		return (run_subexpr(shell, step, flags, steps));
	flags->exit = false;
	flags->valid_redirs = configure_redirections(shell, step, &flags->exit, out_fd);
	configure_command_path(shell, step);
	validate_command_execution(shell, steps, step, flags);
	if (flags->action == BREAK)
		return (step);
	else if (flags->action == CONT)
	{
		close_descriptor(out_fd);
		return (step);
	}
	if (run_cmds(shell, step, flags, *out_fd) == false)
		flags->action = BREAK;
	return (step);
}

void	execute_commands(t_shell *shell, t_list *exec_steps, int step_number,
	char *current_line)
{
	t_exec_step		*step;
	t_list			*steps;
	t_exec_flags	flags;
	int				out_fd;

	initialize_command_execution(shell, &out_fd, &flags, step_number);
	steps = navigate_to_step(&flags, exec_steps, &step);
	if (steps == NULL)
		return ;
	while (steps)
	{
		flags.step_num++;
		step = run_exec_cmds(shell, &steps, &out_fd, &flags);
		if (flags.action == CONT)
			continue ;
		if (flags.action == BREAK)
			break ;
		steps = steps->next;
	}
	close_descriptor(&shell->fd[0]);
	close_descriptor(&out_fd);
	steps = await_completion_and_get_status(shell, step, exec_steps, &flags);
	shell->current_line = current_line;
	process_logical_operators(shell, step, flags.step_num, &steps);
}
