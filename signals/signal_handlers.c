
#include "minishell.h"

void	handle_interrupt_interactive(int sig)
{
	int	ret;

	ret = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGINT && ret == -1)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		close_descriptor(&g_dupstdin);
	}
}

void	handle_interrupt_command(int sig)
{
	int	ret;

	ret = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGINT)
	{
		if (ret == -1)
		{
			write(2, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	handle_quit_command(int sig)
{
	if (sig == SIGQUIT)
	{
	}
}

void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		close_descriptor(&g_dupstdin);
		get_next_line(-1);
		rl_on_new_line();
		printf("\n");
	}
}
