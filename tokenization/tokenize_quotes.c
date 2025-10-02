
#include "minishell.h"

static void	*parse_error(const char *msg, t_token *tkn)
{
	release_token_memory(tkn);
	if (msg != NULL)
		ft_stderr(msg);
	return (NULL);
}


static t_list	*create_token_el(const t_shell *shell, t_token *tkn,
	const char *line, const bool expand_var)
{
	t_list	*el;

	if (tkn->end <= tkn->start)
		tkn->substr = ft_strdup("");
	else
		tkn->substr = ft_substr(line, tkn->start, tkn->end - tkn->start + 1);
	if (tkn->substr == NULL)
		return (parse_error(NULL, tkn));
	while (expand_var == true && check_environment_variable(tkn->substr))
		tkn->substr = resolve_environment_variable(shell, tkn->substr);
	if (ft_strchr(tkn->substr, '*') == NULL)
		tkn->substr = remove_quote_characters(tkn->substr);
	if (tkn->substr == NULL)
		return (parse_error("Parse error: Invalid Input\n", tkn));
	if (ft_strchr(tkn->substr, '*') != NULL)
		tkn->substr = apply_wildcard_expansion(tkn->substr);
	el = ft_lstnew(tkn);
	return (el);
}

t_list	*create_single_quote_token(const t_shell *shell, const char *line,
	size_t *idx)
{
	size_t  i;
	t_token *tkn;
	t_list  *el;

	i = *idx + 1;
	tkn = ft_calloc(1, sizeof(t_token));
	if (tkn == NULL)
		return (NULL);
	tkn->start = i - 1;
	tkn->type = QUOTED_STRING;
	while (line[i] != '\0' && line[i] != '\'')
		i++;
	if (line[i] == '\0')
		return (parse_error("Parse Error: Unterminated string\n", tkn));
	tkn->end = i;
	i++; // move past closing quote
	el = create_token_el(shell, tkn, line, false);
	if (el == NULL)
		return (NULL);
	*idx = i - 1;
	return (el);
}

t_list	*create_double_quote_token(const t_shell *shell, const char *line,
	size_t *idx, const bool expand_var)
{
	size_t  i;
	t_token *tkn;
	t_list  *el;

	i = *idx + 1;
	tkn = ft_calloc(1, sizeof(t_token));
	if (tkn == NULL)
		return (NULL);
	tkn->start = i - 1;
	tkn->type = DOUBLE_QUOTED_STRING;
	while (line[i] != '\0' && line[i] != '"')
		i++;
	if (line[i] == '\0')
		return (parse_error("Parse Error: Unterminated string\n", tkn));
	tkn->end = i;
	i++; // move past closing quote
	el = create_token_el(shell, tkn, line, expand_var);
	if (el == NULL)
		return (NULL);
	*idx = i - 1;
	return (el);
}
