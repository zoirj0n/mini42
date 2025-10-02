
#include "minishell.h"

static int	open_last_redir(t_list *hd_contents, t_exec_step *step,
	int *heredoc_fds, t_redir **inredir)
{
	int			in_fd;

	in_fd = -1;
	*inredir = retrieve_last_input_redirect(step->cmd->redirs);
	if (*inredir != NULL)
	{
		if ((*inredir)->type == INPUT_REDIR)
			in_fd = open((*inredir)->file, O_RDONLY);
		else if ((*inredir)->type == HEREDOC)
		{
			pipe(heredoc_fds);
			while (hd_contents != NULL)
			{
				if (hd_contents->content != NULL)
					break ;
				hd_contents = hd_contents->next;
			}
			ft_putstr_fd(hd_contents->content, heredoc_fds[1]);
			deallocate_memory(&hd_contents->content);
		}
	}
	return (in_fd);
}

int	*cleanup_command_resources(int *fds, int *in_fd, int *out_fd,
	int *heredoc_fds)
{
	close_descriptor(in_fd);
	close_descriptor(out_fd);
	close_descriptor(&heredoc_fds[0]);
	close_descriptor(&heredoc_fds[1]);
	close_descriptor(&fds[1]);
	return (fds);
}

int	initialize_command_execution_context(t_shell *shell, t_redir **inredir, t_exec_step *step,
	int *heredoc_fds)
{
	int	in_fd;

	*inredir = NULL;
	heredoc_fds[0] = -1;
	heredoc_fds[1] = -1;
	in_fd = -1;
	if (step->cmd->redirs)
		in_fd = open_last_redir(shell->heredoc_contents, step,
				heredoc_fds, inredir);
	return (in_fd);
}

int	execute_builtin_in_child(t_shell *shell, t_exec_step *step, int *fds,
	int *heredoc_fds)
{
	int	exit_code;

	execute_builtin_command(step, shell, true);
	close_descriptor(&fds[1]);
	close_descriptor(&fds[0]);
	close_descriptor(&heredoc_fds[0]);
	close_descriptor(&heredoc_fds[1]);
	close_descriptor(&g_dupstdin);
	exit_code = step->exit_code;
	ft_lstclear(&shell->tokens, release_token_memory);
	release_execution_steps(&shell->steps_to_free);
	release_string_array(shell->env);
	release_string_array(shell->declared_env);
	ft_lstclear(&shell->heredoc_contents, free);
	deallocate_memory(&fds);
	return (exit_code);
}

void	setup_pipe_descriptors(const t_exec_step *step, int *fds)
{
	if (step->pipe_next)
		pipe(fds);
}
