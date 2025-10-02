
#include "minishell.h"

void	release_redirection(void *redir_ptr)
{
	t_redir	*redir;

	redir = redir_ptr;
	deallocate_memory(&redir->file);
	deallocate_memory(&redir->limiter);
	deallocate_memory(&redir);
}

void	release_execution_step(void *exec_step_ptr)
{
	t_exec_step	*exec_step;
	size_t		i;

	exec_step = exec_step_ptr;
	if (exec_step->cmd != NULL)
	{
		ft_lstclear(&exec_step->cmd->redirs, release_redirection);
		ft_lstclear(&exec_step->cmd->args, free);
		i = 0;
		while (exec_step->cmd->arg_arr && exec_step->cmd->arg_arr[i] != NULL)
		{
			deallocate_memory(&exec_step->cmd->arg_arr[i]);
			i++;
		}
		deallocate_memory(&exec_step->cmd->arg_arr);
		deallocate_memory(&exec_step->cmd);
	}
	deallocate_memory(&exec_step->subexpr_line);
	deallocate_memory(&exec_step);
}

void	convert_list_to_array(void *step_ptr)
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

bool	check_token_terminator(const t_token *token)
{
	if (token->type == PIPE
		|| token->type == AND
		|| token->type == OR)
		return (true);
	return (false);
}

bool	check_token_redirection(const t_token *token)
{
	if (token->type == INPUT_REDIR || token->type == OUTPUT_REDIR
		|| token->type == APPEND || token->type == HEREDOC)
		return (true);
	return (false);
}
