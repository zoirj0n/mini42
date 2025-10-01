
#include "minishell.h"

void	free_redir(void *redir_ptr)
{
	t_redir	*redir;

	redir = redir_ptr;
	ft_free(&redir->file);
	ft_free(&redir->limiter);
	ft_free(&redir);
}

void	free_exec_step(void *exec_step_ptr)
{
	t_exec_step	*exec_step;
	size_t		i;

	exec_step = exec_step_ptr;
	if (exec_step->cmd != NULL)
	{
		ft_lstclear(&exec_step->cmd->redirs, free_redir);
		ft_lstclear(&exec_step->cmd->args, free);
		i = 0;
		while (exec_step->cmd->arg_arr && exec_step->cmd->arg_arr[i] != NULL)
		{
			ft_free(&exec_step->cmd->arg_arr[i]);
			i++;
		}
		ft_free(&exec_step->cmd->arg_arr);
		ft_free(&exec_step->cmd);
	}
	ft_free(&exec_step->subexpr_line);
	ft_free(&exec_step);
}

void	list_to_str_arr(void *step_ptr)
{
	t_list		*arg_list;
	size_t		i;
	size_t		list_size;
	t_exec_step	*step;

	step = step_ptr;
	if (step->cmd == NULL)
		return ;
	arg_list = step->cmd->args;
	list_size = ft_lstsize(arg_list);
	step->cmd->arg_arr = ft_calloc(list_size + 1, sizeof(char *));
	if (step->cmd->arg_arr == NULL)
	{
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < list_size)
	{
		step->cmd->arg_arr[i] = ft_strdup(arg_list->content);
		arg_list = arg_list->next;
		i++;
	}
	ft_lstclear(&step->cmd->args, free);
	step->cmd->arg_arr[i] = NULL;
}

bool	is_terminator(const t_token *token)
{
	if (token->type == PIPE
		|| token->type == AND
		|| token->type == OR)
		return (true);
	return (false);
}

bool	is_redirection(const t_token *token)
{
	if (token->type == INPUT_REDIR || token->type == OUTPUT_REDIR
		|| token->type == APPEND || token->type == HEREDOC)
		return (true);
	return (false);
}
