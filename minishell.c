
#include "minishell.h"

extern int	g_dupstdin;

char	*minishell_readline(t_shell *shell)
{
	char	*line;

	g_dupstdin = dup(0);
	signal(SIGINT, sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
	line = readline("\001\033[1;31m\002minishell$ \001\033[0m\002");
	handle_ctrl_c(shell);
	shell->line = line;
	signal(SIGQUIT, sigquit_command);
	signal(SIGINT, sigint_command);
	handle_eof(line, shell);
	return (line);
}

void	minishell_run_heredocs(t_shell *shell)
{
	signal(SIGINT, hd_sig_handler);
	signal(SIGQUIT, hd_sig_handler);
	shell->heredoc_contents = run_here_docs(shell, shell->steps);
	signal(SIGINT, sigint_command);
	signal(SIGQUIT, sigquit_command);
}

void	minishell_exec_and_cleanup(t_shell *shell, char *line)
{
	if (shell->steps != NULL)
		exec_cmds(shell, shell->steps, 0, shell->line);
	ft_lstclear(&shell->tokens, free_token);
	ft_lstclear(&shell->heredoc_contents, free);
	free_steps(&shell->steps_to_free);
	rl_on_new_line();
	ft_free(&line);
	ft_close(&g_dupstdin);
}
