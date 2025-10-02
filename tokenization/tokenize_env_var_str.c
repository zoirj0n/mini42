
#include "minishell.h"

static	t_list	*tokenize_inside_envvar(const char *line,
	size_t *idx)
{
	size_t	i;
	t_token	*tkn;
	t_list	*el;

	i = *idx;
	tkn = ft_calloc(1, sizeof(t_token));
	if (tkn == NULL)
		return (NULL);
	tkn->start = i;
	tkn->type = NORMAL;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	tkn->end = i - 1;
	tkn->substr = ft_substr(line, tkn->start, tkn->end - tkn->start + 1);
	el = ft_lstnew(tkn);
	*idx = tkn->end;
	return (el);
}

t_list	*process_environment_string(const char *line,
	bool *success)
{
	size_t	i;
	t_list	*tokens;

	*success = true;
	tokens = NULL;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			ft_lstadd_back(&tokens, tokenize_inside_envvar(line, &i));
		if (line[i] != '\0')
			i++;
	}
	return (tokens);
}
