
#include "minishell.h"

void	tokenize_env_cleanup(t_list **el,
	t_list **tokens, bool *success)
{
	t_token	*token;

	token = (*el)->content;
	if (token->substr == NULL)
		ft_lstclear(el, free_token);
	else if (ft_strncmp(token->substr, "$\"\"", 3) == 0)
	{
		ft_free(&token->substr);
		token->substr = ft_strdup("");
		ft_lstadd_back(tokens, *el);
	}
	else if (ft_strlen(token->substr) != 0
		&& ft_strchr(token->substr, '$') != NULL)
		ft_lstadd_back(tokens, *el);
	else if (ft_strlen(token->substr) != 0)
	{
		*success = retokenize_env_var(token, el, tokens);
	}
	else
	{
		token->type = DUMMY;
		ft_lstadd_back(tokens, *el);
	}
}

bool	first_token_group(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
	bool	success;

	success = true;
	if (line[*i] == '\'')
		el = tokenize_single_quote(shell, line, i);
	else if (line[*i] == '\"')
		el = tokenize_double_quote(shell, line, i,
				!last_token_was_heredoc(*tokens));
	else if (is_operator(line, *i) == true)
		el = tokenize_operator_token(line, i);
	else
		el = tokenize_subexpr(shell, line, i);
	if (el == NULL)
	{
		token_error(NULL, tokens, &success);
		return (false);
	}
	ft_lstadd_back(tokens, el);
	return (true);
}

bool	second_token_group(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
	bool	success;

	success = true;
	if (line[*i] == '$' && last_token_was_heredoc(*tokens) == false)
	{
		el = tokenize_env_variable(shell, line, i);
		if (el == NULL)
		{
			token_error("Parse Error\n", tokens, &success);
			return (false);
		}
		tokenize_env_cleanup(&el, tokens, &success);
		if (success == false)
		{
			token_error(NULL, tokens, &success);
			return (false);
		}
	}
	else if (line[*i] == ')')
	{
		token_error("Parse Error\n", tokens, &success);
		return (false);
	}
	return (true);
}

bool	tokenize_normal_and_wildcard(const t_shell *shell, const char *line,
	size_t *i, t_list **tokens)
{
	t_list	*el;
	bool	success;
	t_token	*token;

	success = true;
	el = tokenize_normal(shell, line, i, !last_token_was_heredoc(*tokens));
	if (el == NULL)
	{
		token_error(NULL, tokens, &success);
		return (false);
	}
	token = el->content;
	if (ft_strchr(token->substr, '*') != NULL)
	{
		if (tokenize_wildcard(shell, &el, tokens, &success) == false)
			return (false);
	}
	else
		ft_lstadd_back(tokens, el);
	return (true);
}

t_list	*tokenize_line(const t_shell *shell, const char *line, bool *success)
{
	size_t	i;
	t_list	*tokens;

	*success = true;
	if (check_for_token_errors(line, success) == false)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"' || is_operator(line, i) == true
			|| line[i] == '(')
			*success = first_token_group(shell, line, &i, &tokens);
		else if ((line[i] == '$' && last_token_was_heredoc(tokens) == false)
			|| line[i] == ')')
			*success = second_token_group(shell, line, &i, &tokens);
		else if (line[i] != ' ')
			*success = tokenize_normal_and_wildcard(shell, line, &i, &tokens);
		if (*success == false)
			return (NULL);
		if (line[i] != '\0')
			i++;
	}
	return (tokens);
}
