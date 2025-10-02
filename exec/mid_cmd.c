
#include "minishell.h"

static void	dup_heredoc_fds(t_redir *inredir, int *heredoc_fds, int *fdtmp)
{
	dup2(*fdtmp, 0);
	if (inredir && inredir->type == HEREDOC)
	{
		close_descriptor(&heredoc_fds[1]);
		close_descriptor(fdtmp);
		dup2(heredoc_fds[0], 0);
	}
}

static void	dup_pipes_and_redirs(t_exec_step *step, int *fds, int in_fd,
	int out_fd)
{
	if (step->pipe_next)
	{
		close_descriptor(&fds[0]);
		dup2(fds[1], 1);
	}
	if (in_fd != -1)
		dup2(in_fd, 0);
	if (out_fd != -1)
		dup2(out_fd, 1);
}

static void	child_builtin_cleanup(int *out_fd, int *in_fd, int *fdtmp,
	int exit_code)
{
	close_descriptor(out_fd);
	close_descriptor(in_fd);
	close_descriptor(fdtmp);
	exit(exit_code);
}

static void	close_fds(const t_exec_step *step, int *fds, int *fdtmp)
{
	if (!step->pipe_next)
		close_descriptor(&fds[0]);
	close_descriptor(fdtmp);
}

int	*execute_pipeline_command(t_exec_step *step, int *fds, t_shell *shell, int out_fd)
{
	int			in_fd;
	int			fdtmp;
	int			heredoc_fds[2];
	int			exit_code;
	t_redir		*inredir;

	fdtmp = fds[0];
	in_fd = initialize_command_execution_context(shell, &inredir, step, heredoc_fds);
	setup_pipe_descriptors(step, fds);
	if (step->cmd->arg_arr[0] != NULL)
		step->cmd->pid = fork();
	if (step->cmd->arg_arr[0] != NULL && step->cmd->pid == 0)
	{
		dup_heredoc_fds(inredir, heredoc_fds, &fdtmp);
		dup_pipes_and_redirs(step, fds, in_fd, out_fd);
		if (check_builtin_command(step))
		{
			exit_code = execute_builtin_in_child(shell, step, fds, heredoc_fds);
			child_builtin_cleanup(&out_fd, &in_fd, &fdtmp, exit_code);
		}
		execve(step->cmd->arg_arr[0], step->cmd->arg_arr, shell->env);
	}
	close_fds(step, fds, &fdtmp);
	return (cleanup_command_resources(fds, &in_fd, &out_fd, heredoc_fds));
}
