
#include "minishell.h"

void	cleanup_environment_tokenization(t_list **el,
	t_list **tokens, bool *success)
{
	t_token	*token;

	token = (*el)->content;
	if (token->substr == NULL)
		ft_lstclear(el, release_token_memory);
	else if (ft_strncmp(token->substr, "$\"\"", 3) == 0)
	{
		deallocate_memory(&token->substr);
		token->substr = ft_strdup("");
		ft_lstadd_back(tokens, *el);
	}
	else if (ft_strlen(token->substr) != 0
		&& ft_strchr(token->substr, '$') != NULL)
		ft_lstadd_back(tokens, *el);
	else if (ft_strlen(token->substr) != 0)
	{
		*success = reprocess_environment_token(token, el, tokens);
	}
	else
	{
		token->type = DUMMY;
		ft_lstadd_back(tokens, *el);
	}
}

bool	process_primary_tokens(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
	bool	success;

	success = true;
	if (line[*i] == '\'')
		el = create_single_quote_token(shell, line, i);
	else if (line[*i] == '\"')
		el = create_double_quote_token(shell, line, i,
				!check_previous_heredoc(*tokens));
	else if (detect_operator_character(line, *i) == true)
		el = process_operator_token(line, i);
	else
		el = create_subexpression_token(shell, line, i);
	if (el == NULL)
	{
		handle_token_error(NULL, tokens, &success);
		return (false);
	}
	ft_lstadd_back(tokens, el);
	return (true);
}

bool	process_secondary_tokens(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
	bool	success;

	success = true;
	if (line[*i] == '$' && check_previous_heredoc(*tokens) == false)
	{
		el = extract_environment_variable(shell, line, i);
		if (el == NULL)
		{
			handle_token_error("Parse Error\n", tokens, &success);
			return (false);
		}
		cleanup_environment_tokenization(&el, tokens, &success);
		if (success == false)
		{
			handle_token_error(NULL, tokens, &success);
			return (false);
		}
	}
	else if (line[*i] == ')')
	{
		handle_token_error("Parse Error\n", tokens, &success);
		return (false);
	}
	return (true);
}

bool	process_text_and_wildcard(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
	bool	success;
	t_token	*token;

	success = true;
	el = create_normal_token(shell, line, i, !check_previous_heredoc(*tokens));
	if (el == NULL)
	{
		handle_token_error(NULL, tokens, &success);
		return (false);
	}
	token = el->content;
	if (ft_strchr(token->substr, '*') != NULL)
	{
		if (process_wildcard_token(shell, &el, tokens, &success) == false)
			return (false);
	}
	else
		ft_lstadd_back(tokens, el);
	return (true);
}

t_list	*process_input_line(const t_shell *shell, const char *line, bool *success)
{
	size_t	i;
	t_list	*tokens;

	*success = true;
	if (detect_token_syntax_errors(line, success) == false)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"' || detect_operator_character(line, i) == true
			|| line[i] == '(')
			*success = process_primary_tokens(shell, line, &i, &tokens);
		else if ((line[i] == '$' && check_previous_heredoc(tokens) == false)
			|| line[i] == ')')
			*success = process_secondary_tokens(shell, line, &i, &tokens);
		else if (line[i] != ' ')
			*success = process_text_and_wildcard(shell, line, &i, &tokens);
		if (*success == false)
			return (NULL);
		if (line[i] != '\0')
			i++;
	}
	return (tokens);
}
