
#include "minishell.h"

// This is ft_strjoin but with an additional argument
// to specify which input strings to free
char *strjoin_free(char *s1, char *s2, int f)
{
	char *joined;

	joined = ft_strjoin(s1, s2);
	if (f == 1)
		ft_free(&s1);
	if (f == 2)
		ft_free(&s2);
	if (f == 3)
	{
		ft_free(&s1);
		ft_free(&s2);
	}
	return (joined);
}

char *substr_free(char *s, unsigned int start, size_t len)
{
	char *substr;
	size_t substr_length;
	size_t i;

	if (start > ft_strlen(s))
		len = 0;
	else
	{
		substr_length = ft_strlen(&s[start]);
		if (len > substr_length)
			len = substr_length;
	}
	substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	ft_free(&s);
	return (substr);
}

char **copy_str_arr(char **arr)
{
	size_t len;
	size_t i;
	char **arr_cpy;

	len = 0;
	while (arr[len] != NULL)
		len++;
	arr_cpy = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (i < len)
	{
		arr_cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	arr_cpy[i] = NULL;
	return (arr_cpy);
}

void free_steps(t_list **step_lists)
{
	t_list *steps;
	t_list *temp;

	while ((*step_lists) != NULL)
	{
		steps = (*step_lists)->content;
		temp = (*step_lists)->next;
		ft_lstclear(&steps, free_exec_step);
		ft_free(step_lists);
		(*step_lists) = temp;
	}
	*step_lists = NULL;
}

char *get_env(const t_shell *shell, const char *name)
{
	size_t i;
	char **vars;
	char *look_for;
	size_t look_for_len;

	i = 0;
	vars = shell->env;
	if (name[0] == '?')
	{
		return (ft_itoa(shell->last_exit_code));
	}
	while (vars[i] != NULL)
	{
		look_for = ft_strjoin(name, "=");
		look_for_len = ft_strlen(look_for);
		if (ft_strncmp(vars[i], look_for, look_for_len) == 0)
		{
			ft_free(&look_for);
			return (ft_substr(vars[i], look_for_len,
							  ft_strlen(vars[i]) - look_for_len + 1));
		}
		ft_free(&look_for);
		i++;
	}
	return (NULL);
}
