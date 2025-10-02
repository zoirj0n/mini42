
#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	process_end_of_file(const char *line, t_shell *shell);
void	reset_after_interrupt(t_shell *shell);
bool	process_heredoc_interrupt(t_shell *shell, char *line);

#endif
