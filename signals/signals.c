
#include "minishell.h"

void	process_end_of_file(const char *line, t_shell *shell)
{
	if (line == NULL)
	{
		printf("exit\n");
		release_string_array(shell->env);
		release_string_array(shell->declared_env);
		close_descriptor(&g_dupstdin);
		deallocate_memory(&shell->fd);
		clear_history();
		get_next_line(-1);
		exit(shell->last_exit_code);
	}
}

void	reset_after_interrupt(t_shell *shell)
{
	if (g_dupstdin == -1)
	{
		g_dupstdin = dup(0);
		shell->last_exit_code = 1;
	}
}

bool	process_heredoc_interrupt(t_shell *shell, char *line)
{
	if (g_dupstdin == -1)
	{
		shell->last_exit_code = 1;
		ft_lstclear(&shell->tokens, release_token_memory);
		release_execution_steps(&shell->steps_to_free);
		ft_lstclear(&shell->heredoc_contents, free);
		rl_on_new_line();
		deallocate_memory(&line);
		close_descriptor(&g_dupstdin);
		return (false);
	}
	return (true);
}
