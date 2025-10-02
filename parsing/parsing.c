
#include "minishell.h"

static bool	parse_subexpr(t_token *token, t_list **steps,
	t_list *tokens, bool *success)
{
	t_exec_step	*step;

	step = ft_calloc(1, sizeof(t_exec_step));
	if (step == NULL)
	{
		*success = false;
		return (false);
	}
	step->subexpr_line = ft_strdup(token->substr);
	ft_lstadd_back(steps, ft_lstnew(step));
	if (validate_subexpression_token(tokens, &token, step, success) == false)
		return (false);
	return (true);
}

t_list	*analyze_token_stream(t_list *tokens, bool *success)
{
	t_token		*token;
	t_list		*steps;

	steps = NULL;
	*success = detect_parsing_errors(tokens);
	if (*success == false)
		return (steps);
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == SUB_EXPR)
			parse_subexpr(token, &steps, tokens, success);
		else if (check_token_terminator(token) == false)
			steps = process_parsing_step(&tokens, &token, &steps, success);
		if (*success == false)
			return (steps);
		tokens = tokens->next;
	}
	ft_lstiter(steps, convert_list_to_array);
	*success = true;
	return (steps);
}
