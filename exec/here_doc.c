
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
	limiter = strjoin_free(limiter, "\n", 0);
	while (1)
	{
		if (g_dupstdin != -1)
			ft_putstr_fd("> ", 1);
		line = get_next_line(g_dupstdin);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limiter) == 0)
			break ;
		while (contains_env_var(line) == true)
			line = expand_env_var(shell, line);
		buff = strjoin_free(buff, line, 3);
	}
	ft_free(&limiter);
	ft_free(&line);
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
				ft_free(&contents);
				contents = read_from_stdin(shell, redir->limiter);
			}
			redirs = redirs->next;
		}
		if (contents != NULL)
		{
			ft_lstadd_back(heredocs, ft_lstnew(ft_strdup(contents)));
			ft_free(&contents);
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
t_list	*run_here_docs(t_shell *shell, t_list *steps)
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
			tokens = tokenize_line(shell, step->subexpr_line, &success);
			substeps = parse_tokens(tokens, &success);
			ft_lstclear(&tokens, free_token);
			ft_lstadd_back(&heredocs, run_here_docs(shell, substeps));
			ft_lstclear(&substeps, free_exec_step);
			steps = steps->next;
			continue ;
		}
		run_heredoc(shell, step, &heredocs);
		steps = steps->next;
	}
	return (heredocs);
}
