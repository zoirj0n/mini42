
#include "minishell.h"

static t_list	*wait_cmds(t_list *steps, t_exec_flags *flags)
{
	t_exec_step	*step;

	while (steps && flags->step_num_start < flags->step_num)
	{
		step = steps->content;
		if (step->cmd->arg_arr[0] && !check_directory_status(step->cmd->arg_arr[0])
			&& (access(step->cmd->arg_arr[0], X_OK) != -1
				|| check_builtin_command(step)))
		{
			waitpid(step->cmd->pid, &flags->w_status, 0);
		}
		if (step->and_next || step->or_next)
			return (steps);
		flags->step_num_start++;
		steps = steps->next;
	}
	return (steps);
}

int	retrieve_exit_status(t_list *exec_steps, t_exec_step *step, t_exec_flags *flags)
{
	if (!flags->exit && !WIFEXITED(flags->w_status)
		&& WIFSIGNALED(flags->w_status))
	{
		if (WTERMSIG(flags->w_status) == SIGINT)
			step->exit_code = 130;
		if (WTERMSIG(flags->w_status) == SIGQUIT)
		{
			printf("Quit\n");
			step->exit_code = 131;
		}
		return (step->exit_code);
	}
	if (!flags->exit)
	{
		if (!(((t_exec_step *)exec_steps->content)->pipe_next == false
				&& requires_parent_execution(exec_steps->content)))
		{
			step->exit_code = WEXITSTATUS(flags->w_status);
		}
	}
	return (step->exit_code);
}

t_list	*await_completion_and_get_status(t_shell *shell, t_exec_step *step,
	t_list *exec_steps, t_exec_flags *flags)
{
	t_list	*steps;
	int		i;

	if (step->cmd)
	{
		steps = rewind_to_step(exec_steps, flags->step_num_start);
		steps = wait_cmds(steps, flags);
		shell->last_exit_code = retrieve_exit_status(exec_steps, step, flags);
	}
	else
	{
		i = 1;
		steps = exec_steps;
		while (steps && i < flags->step_num)
		{
			steps = steps->next;
			i++;
		}
	}
	return (steps);
}
