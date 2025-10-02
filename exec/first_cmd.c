
#include "minishell.h"

static int	*run_parent_builtin(t_exec_step *step, t_shell *shell, int *fd)
{
	execute_builtin_command(step, shell, false);
	if (compare_strings(step->cmd->arg_arr[0], "exit") == 0)
	{
		if (step->cmd->arg_arr)
		{
			ft_lstclear(&shell->tokens, release_token_memory);
			release_execution_steps(&shell->steps_to_free);
			release_string_array(shell->env);
			release_string_array(shell->declared_env);
			ft_lstclear(&shell->heredoc_contents, free);
			close_descriptor(&g_dupstdin);
			deallocate_memory(&fd);
		}
		exit(shell->last_exit_code);
	}
	return (fd);
}

static void	dup_pipe_fds(t_redir *inredir, int *heredoc_fds, t_exec_step *step,
	int *fd)
{
	if (inredir && inredir->type == HEREDOC)
	{
		close_descriptor(&heredoc_fds[1]);
		dup2(heredoc_fds[0], 0);
	}
	if (step->pipe_next)
	{
		close_descriptor(&fd[0]);
		dup2(fd[1], 1);
	}
}

static void	dup_redir_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
		dup2(in_fd, 0);
	if (out_fd != -1)
		dup2(out_fd, 1);
}

int	*execute_initial_command(t_exec_step *step, int *fds, t_shell *shell, int out_fd)
{
	int			in_fd;
	int			heredoc_fds[2];
	int			exit_code;
	t_redir		*inredir;

	in_fd = initialize_command_execution_context(shell, &inredir, step, heredoc_fds);
	setup_pipe_descriptors(step, fds);
	if (requires_parent_execution(step) && !step->pipe_next)
		return (run_parent_builtin(step, shell, fds));
	if (step->cmd->arg_arr[0] != NULL)
		step->cmd->pid = fork();
	if (step->cmd->arg_arr[0] != NULL && step->cmd->pid == 0)
	{
		dup_pipe_fds(inredir, heredoc_fds, step, fds);
		dup_redir_fds(in_fd, out_fd);
		if (check_builtin_command(step))
		{
			exit_code = execute_builtin_in_child(shell, step, fds, heredoc_fds);
			close_descriptor(&out_fd);
			close_descriptor(&in_fd);
			exit(exit_code);
		}
		execve(step->cmd->arg_arr[0], step->cmd->arg_arr, shell->env);
	}
	return (cleanup_command_resources(fds, &in_fd, &out_fd, heredoc_fds));
}
