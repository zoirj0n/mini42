
#include "minishell.h"

static int	open_last_redir(t_list *hd_contents, t_exec_step *step,
	int *heredoc_fds, t_redir **inredir)
{
	int			in_fd;

	in_fd = -1;
	*inredir = last_inredir(step->cmd->redirs);
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
			ft_free(&hd_contents->content);
		}
	}
	return (in_fd);
}

int	*cmd_cleanup(int *fds, int *in_fd, int *out_fd,
	int *heredoc_fds)
{
	ft_close(in_fd);
	ft_close(out_fd);
	ft_close(&heredoc_fds[0]);
	ft_close(&heredoc_fds[1]);
	ft_close(&fds[1]);
	return (fds);
}

int	cmd_init(t_shell *shell, t_redir **inredir, t_exec_step *step,
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

int	run_child_builtin(t_shell *shell, t_exec_step *step, int *fds,
	int *heredoc_fds)
{
	int	exit_code;

	run_builtin(step, shell, true);
	ft_close(&fds[1]);
	ft_close(&fds[0]);
	ft_close(&heredoc_fds[0]);
	ft_close(&heredoc_fds[1]);
	ft_close(&g_dupstdin);
	exit_code = step->exit_code;
	ft_lstclear(&shell->tokens, free_token);
	free_steps(&shell->steps_to_free);
	free_split_array(shell->env);
	free_split_array(shell->declared_env);
	ft_lstclear(&shell->heredoc_contents, free);
	ft_free(&fds);
	return (exit_code);
}

void	pipe_fds(const t_exec_step *step, int *fds)
{
	if (step->pipe_next)
		pipe(fds);
}
