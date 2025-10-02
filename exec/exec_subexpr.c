
#include "minishell.h"

int	calculate_heredoc_count(t_list *substeps)
{
	int			num_heredocs;
	t_exec_step	*step;
	t_redir		*last_redir;

	num_heredocs = 0;
	while (substeps != NULL)
	{
		step = substeps->content;
		if (step->cmd != NULL && step->cmd->redirs != NULL)
		{
			last_redir = retrieve_last_input_redirect(step->cmd->redirs);
			if (last_redir != NULL)
				num_heredocs++;
		}
		substeps = substeps->next;
	}
	return (num_heredocs);
}

void	bypass_subexpression_heredocs(t_list *heredocs, int num_skipped)
{
	int	i;

	i = 0;
	if (num_skipped == 0)
		return ;
	while (heredocs != NULL && heredocs->content == NULL)
		heredocs = heredocs->next;
	if (heredocs == NULL)
		return ;
	while (i < num_skipped)
	{
		deallocate_memory(&heredocs->content);
		heredocs->content = NULL;
		heredocs = heredocs->next;
		i++;
	}
}

static int	parse_and_fork_subexpr(t_shell *shell, t_exec_step *step,
	t_list **sub_steps)
{
	t_list		*sub_tokens;
	int			pid;
	bool		success;

	sub_tokens = process_input_line(shell, step->subexpr_line, &success);
	*sub_steps = analyze_token_stream(sub_tokens, &success);
	ft_lstclear(&sub_tokens, release_token_memory);
	ft_lstadd_back(&shell->steps_to_free, ft_lstnew(*sub_steps));
	pid = fork();
	if (pid == 0)
	{
		execute_commands(shell, *sub_steps, 0, step->subexpr_line);
		ft_lstclear(&shell->tokens, release_token_memory);
		release_execution_steps(&shell->steps_to_free);
		close_descriptor(&g_dupstdin);
		release_string_array(shell->env);
		release_string_array(shell->declared_env);
		ft_lstclear(&shell->heredoc_contents, free);
		deallocate_memory(&shell->fd);
		get_next_line(-1);
		exit(shell->last_exit_code);
	}
	return (pid);
}

bool	execute_subexpression(t_shell *shell, t_exec_step *step, t_exec_flags *flags,
	t_list **steps)
{
	int			pid;
	t_list		*sub_steps;
	int			heredocs_to_skip;

	pid = parse_and_fork_subexpr(shell, step, &sub_steps);
	waitpid(pid, &flags->w_status, 0);
	heredocs_to_skip = calculate_heredoc_count(sub_steps);
	bypass_subexpression_heredocs(shell->heredoc_contents, heredocs_to_skip);
	step->exit_code = WEXITSTATUS(flags->w_status);
	shell->last_exit_code = step->exit_code;
	if (!(flags->first_flag))
		flags->first_flag = true;
	if (step->and_next || step->or_next)
		return (false);
	*steps = (*steps)->next;
	return (true);
}
