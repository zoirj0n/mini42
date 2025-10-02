
#include "minishell.h"

static char	*create_env_var_str(const t_shell *shell, char *str,
	const size_t start, const size_t end)
{
	char	*before;
	char	*env_var;
	char	*expansion;
	char	*after;

	before = ft_substr(str, 0, start - 1);
	env_var = ft_substr(str, start, end - start + 1);
	expansion = retrieve_environment_variable(shell, env_var);
	deallocate_memory(&env_var);
	after = ft_substr(str, end + 1, ft_strlen(str));
	deallocate_memory(&str);
	if (expansion == NULL)
		str = join_and_free_strings(before, "", 1);
	else
		str = join_and_free_strings(before, expansion, 3);
	str = join_and_free_strings(str, after, 3);
	return (str);
}

void	track_quote_state(const char *str, const size_t i, bool *in_single,
	bool *in_double)
{
	if (str[i] == '\'' && *in_double == false)
		*in_single = !(*in_single);
	if (str[i] == '\"' && *in_single == false)
		*in_double = !(*in_double);
}

static bool	skip_to_end(const char *str, size_t *i, size_t *start, size_t *end)
{
	*i += 1;
	*start = *i;
	while (str[*i] != '\0' && (ft_isalnum(str[*i]) || str[*i] == '_'))
		*i += 1;
	*end = *i - 1;
	if (start < end)
		return (false);
	return (true);
}

char	*resolve_environment_variable(const t_shell *shell, char *str)
{
	size_t	i;
	size_t	start;
	size_t	end;
	bool	in_s_quotes;
	bool	in_d_quotes;

	i = 0;
	in_s_quotes = false;
	in_d_quotes = false;
	while (str[i] != '\0')
	{
		track_quote_state(str, i, &in_s_quotes, &in_d_quotes);
		if (str[i] == '$' && str[i + 1] != '?' && in_s_quotes == false)
		{
			if (ft_isdigit(str[i + 1]))
				return (create_env_var_str(shell, str, i + 1, i + 1));
			if (skip_to_end(str, &i, &start, &end) == false)
				break ;
		}
		else if (str[i] == '$' && str[i + 1] == '?' && in_s_quotes == false)
			return (create_env_var_str(shell, str, i + 1, i + 1));
		else
			i++;
	}
	return (create_env_var_str(shell, str, start, end));
}
