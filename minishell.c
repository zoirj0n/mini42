
#include "minishell.h"

extern int	g_dupstdin;

char	*read_command_line(t_shell *shell)
{
	char	*line;

	g_dupstdin = dup(0);
	signal(SIGINT, handle_interrupt_interactive);
	signal(SIGQUIT, SIG_IGN);
	line = readline("\001\033[1;31m\002minishell$ \001\033[0m\002");
	reset_after_interrupt(shell);
	shell->line = line;
	signal(SIGQUIT, handle_quit_command);
	signal(SIGINT, handle_interrupt_command);
	process_end_of_file(line, shell);
	return (line);
}

void	process_heredoc_inputs(t_shell *shell)
{
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, handle_heredoc_signal);
	shell->heredoc_contents = execute_heredoc_inputs(shell, shell->steps);
	signal(SIGINT, handle_interrupt_command);
	signal(SIGQUIT, handle_quit_command);
}

void	execute_and_cleanup_shell(t_shell *shell, char *line)
{
	if (shell->steps != NULL)
		execute_commands(shell, shell->steps, 0, shell->line);
	ft_lstclear(&shell->tokens, release_token_memory);
	ft_lstclear(&shell->heredoc_contents, free);
	release_execution_steps(&shell->steps_to_free);
	rl_on_new_line();
	deallocate_memory(&line);
	close_descriptor(&g_dupstdin);
}
