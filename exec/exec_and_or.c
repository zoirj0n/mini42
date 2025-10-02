
#include "minishell.h"

static int	handle_and_next(t_shell *shell, t_list **steps, t_exec_step *step,
	int step_number)
{
	if (shell->last_exit_code != 0)
	{
		while (*steps != NULL && step->and_next)
		{
			step = (*steps)->content;
			*steps = (*steps)->next;
			step_number++;
		}
		if (step->or_next)
			step_number--;
		while (*steps && !step->and_next && !step->or_next)
		{
			step = (*steps)->content;
			*steps = (*steps)->next;
			step_number++;
		}
		if (*steps == NULL)
			return (-1);
	}
	return (step_number);
}

static int	handle_or_next(t_shell *shell, t_list **steps, t_exec_step *step,
	int step_number)
{
	if (shell->last_exit_code == 0)
	{
		while (*steps != NULL && step->or_next)
		{
			step = (*steps)->content;
			*steps = (*steps)->next;
			step_number++;
		}
		if (step->and_next)
		{
			step_number--;
		}
		while (*steps && !step->and_next && !step->or_next)
		{
			step = (*steps)->content;
			*steps = (*steps)->next;
			step_number++;
		}
		if (*steps == NULL)
			return (-1);
	}
	return (step_number);
}

static void	reparse(t_shell *shell, char *current_line, int step_number)
{
	t_list		*tokens;
	t_list		*new_steps;
	bool		success;

	ft_lstclear(&shell->tokens, release_token_memory);
	tokens = process_input_line(shell, current_line, &success);
	new_steps = analyze_token_stream(tokens, &success);
	ft_lstadd_back(&shell->steps_to_free, ft_lstnew(new_steps));
	shell->tokens = tokens;
	shell->steps = new_steps;
	execute_commands(shell, new_steps, step_number, current_line);
}

void	process_logical_operators(t_shell *shell, t_exec_step *step, int step_number,
	t_list **steps)
{
	if (step && step->and_next)
		step_number = handle_and_next(shell, steps, step, step_number);
	else if (step && step->or_next)
		step_number = handle_or_next(shell, steps, step, step_number);
	if (step && *steps != NULL && (step->and_next || step->or_next))
		reparse(shell, shell->current_line, step_number);
}
