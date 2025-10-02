
#include "minishell.h"

t_list	*process_operator_token(const char *line, size_t *i)
{
	t_list			*el;
	t_token_type	operator_type;

	if (line[*i] == '>' && line[*i + 1] != '>')
		operator_type = OUTPUT_REDIR;
	else if (line[*i] == '<' && line[*i + 1] != '<')
		operator_type = INPUT_REDIR;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		operator_type = HEREDOC;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		operator_type = APPEND;
	else if (line[*i] == '|' && line[*i + 1] != '|')
		operator_type = PIPE;
	else if (line[*i] == '&' && line[*i + 1] == '&')
		operator_type = AND;
	else
		operator_type = OR;
	el = create_operator_token(line, i, operator_type);
	return (el);
}

void	*handle_token_error(const char *msg, t_list **tokens, bool *success)
{
	*success = false;
	ft_lstclear(tokens, release_token_memory);
	if (msg != NULL)
		ft_stderr(msg);
	return (NULL);
}

bool	check_previous_heredoc(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
		return (false);
	token = ft_lstlast(tokens)->content;
	return (token->type == HEREDOC);
}

bool	process_wildcard_token(const t_shell *shell, t_list **el,
	t_list **tokens, bool *success)
{
	t_token	*token;
	t_list	*wildcard_tokens;

	token = (*el)->content;
	token->substr = apply_wildcard_expansion(token->substr);
	token->expanded = true;
	if (ft_strchr(token->substr, '*') == NULL)
	{
		wildcard_tokens = process_input_line(shell, token->substr, success);
		if (*success == false || wildcard_tokens == NULL)
		{
			ft_lstclear(el, release_token_memory);
			ft_lstclear(tokens, release_token_memory);
			ft_lstclear(&wildcard_tokens, release_token_memory);
			return (*success);
		}
		token = wildcard_tokens->content;
		token->expanded = true;
		ft_lstclear(el, release_token_memory);
		ft_lstadd_back(tokens, wildcard_tokens);
	}
	else
		ft_lstadd_back(tokens, *el);
	return (*success);
}

bool	detect_token_syntax_errors(const char *line, bool *success)
{
	size_t	i;
	char	quote;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	quote = '\0';
	while (line[i] != '\0')
	{
		update_quote_state(line[i], &quote, &in_quotes);
		if (!in_quotes && (line[i] == '\\' || line[i] == ';' || line[i] == '`'
				|| (line[i] == '&' && line[i + 1] != '&')
				|| (line[i] == '(' && line[i + 1] == ')')))
		{
			ft_stderr("Parse Error: Invalid input\n");
			*success = false;
			return (false);
		}
		if (!in_quotes && (line[i] == '&' && line[i + 1] != '\0'))
			i++;
		i++;
	}
	return (true);
}
