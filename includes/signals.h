
#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	handle_eof(const char *line, t_shell *shell);
void	handle_ctrl_c(t_shell *shell);
bool	handle_heredoc_ctrl_c(t_shell *shell, char *line);

#endif
