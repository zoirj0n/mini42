
#include "minishell.h"

extern int	g_dupstdin;

/**
 * @brief Function reads from standard input and returns the content.
 * But the here doc fails when the limiter is the first line.
 *
 * @param limiter
 * @return char*
 */
static char	*read_from_stdin(const t_shell *shell, char *limiter)
{
	char	*buff;
	char	*line;

	buff = ft_calloc(1, sizeof(char));
	if (buff == NULL)
		return (NULL);
	limiter = join_and_free_strings(limiter, "\n", 0);
	while (1)
	{
		if (g_dupstdin != -1)
			ft_putstr_fd("> ", 1);
		line = get_next_line(g_dupstdin);
		if (line == NULL)
			break ;
		if (compare_strings(line, limiter) == 0)
			break ;
		while (check_environment_variable(line) == true)
			line = resolve_environment_variable(shell, line);
		buff = join_and_free_strings(buff, line, 3);
	}
	deallocate_memory(&limiter);
	deallocate_memory(&line);
	get_next_line(-1);
	return (buff);
}

static void	run_heredoc(const t_shell *shell, t_exec_step *step,
	t_list **heredocs)
{
	t_list	*redirs;
	t_redir	*redir;
	char	*contents;

	contents = NULL;
	if (step->cmd->redirs != NULL)
	{
		redirs = step->cmd->redirs;
		while (redirs != NULL)
		{
			redir = redirs->content;
			if (redir->type == HEREDOC)
			{
				deallocate_memory(&contents);
				contents = read_from_stdin(shell, redir->limiter);
			}
			redirs = redirs->next;
		}
		if (contents != NULL)
		{
			ft_lstadd_back(heredocs, ft_lstnew(ft_strdup(contents)));
			deallocate_memory(&contents);
		}
	}
}

/**
 * @brief Runs the herdoc, reads the herdoc content
 * from standard input and displays it.
 *
 * @param shell
 * @param step
 */
t_list	*execute_heredoc_inputs(t_shell *shell, t_list *steps)
{
	t_list		*heredocs;
	t_exec_step	*step;
	t_list		*tokens;
	t_list		*substeps;
	bool		success;

	heredocs = NULL;
	while (steps != NULL)
	{
		step = steps->content;
		if (step->subexpr_line != NULL)
		{
			tokens = process_input_line(shell, step->subexpr_line, &success);
			substeps = analyze_token_stream(tokens, &success);
			ft_lstclear(&tokens, release_token_memory);
			ft_lstadd_back(&heredocs, execute_heredoc_inputs(shell, substeps));
			ft_lstclear(&substeps, release_execution_step);
			steps = steps->next;
			continue ;
		}
		run_heredoc(shell, step, &heredocs);
		steps = steps->next;
	}
	return (heredocs);
}
