
#include "minishell.h"

static	bool	subexpr_parse_error(t_list *tokens, t_list *steps)
{
	if (tokens != NULL)
		ft_lstclear(&tokens, free_token);
	if (steps != NULL)
		ft_lstclear(&steps, free_exec_step);
	return (false);
}

bool	check_subexprs(t_shell *shell, t_list *shell_steps)
{
	t_exec_step	*step;
	t_list		*steps;
	t_list		*tokens;
	bool		success;

	while (shell_steps != NULL)
	{
		step = shell_steps->content;
		if (step->subexpr_line != NULL)
		{
			tokens = tokenize_line(shell, step->subexpr_line, &success);
			if (success == false)
				return (subexpr_parse_error(tokens, NULL));
			steps = parse_tokens(tokens, &success);
			ft_lstclear(&tokens, free_token);
			if (!steps || !success || check_subexprs(shell, steps) == false)
				return (subexpr_parse_error(NULL, steps));
			step = steps->content;
			if (step->subexpr_line != NULL && steps->next == NULL)
				return (subexpr_parse_error(NULL, steps));
			ft_lstclear(&steps, free_exec_step);
		}
		shell_steps = shell_steps->next;
	}
	return (true);
}
