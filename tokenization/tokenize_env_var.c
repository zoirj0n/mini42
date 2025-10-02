
#include "minishell.h"

bool	reprocess_environment_token(t_token *token, t_list **el, t_list **tokens)
{
	char	*substr_copy;
	bool	success;

	substr_copy = ft_strdup(token->substr);
	ft_lstclear(el, release_token_memory);
	*el = process_environment_string(substr_copy, &success);
	deallocate_memory(&substr_copy);
	ft_lstadd_back(tokens, *el);
	return (success);
}

void	update_quote_state(const char ch, char *quote, bool *in_quote)
{
	if (ch == '\'' || ch == '\"')
	{
		if (*quote == '\0')
		{
			*quote = ch;
			*in_quote = !(*in_quote);
		}
		else if (*quote == ch)
		{
			*in_quote = !(*in_quote);
			*quote = '\0';
		}
	}
}

static char	*get_env_string(const char *line, size_t *idx)
{
	char	*str;
	size_t	i;
	bool	in_quote;
	char	quote;

	i = *idx;
	in_quote = false;
	quote = '\0';
	while (line[i] != '\0')
	{
		update_quote_state(line[i], &quote, &in_quote);
		if ((line[i] == ' ' || ft_strchr("<>|(&)", line[i])) && !in_quote)
			break ;
		i++;
	}
	if (in_quote == true)
	{
		*idx = i;
		return (NULL);
	}
	str = ft_substr(line, *idx, i - *idx);
	*idx = i - 1;
	return (str);
}

t_list	*extract_environment_variable(const t_shell *shell, const char *line,
	size_t *idx)
{
	t_token	*tkn;

	tkn = ft_calloc(1, sizeof(t_token));
	if (tkn == NULL)
		return (NULL);
	tkn->type = ENV_VAR;
	tkn->substr = get_env_string(line, idx);
	if (tkn->substr == NULL)
	{
		deallocate_memory(&tkn);
		return (NULL);
	}
	if (ft_strncmp(tkn->substr, "$\"\"", ft_strlen(tkn->substr)) == 0
		&& ft_strlen(tkn->substr) == 3)
	{
		tkn->type = NORMAL;
		return (ft_lstnew(tkn));
	}
	if (check_environment_variable(tkn->substr))
		tkn->substr = resolve_environment_variable(shell, tkn->substr);
	tkn->type = NORMAL;
	return (ft_lstnew(tkn));
}
