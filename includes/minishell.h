
#ifndef MINISHELL_H
#define MINISHELL_H

#include "tokenization.h"
#include "parsing.h"
#include "builtins.h"
#include "exec.h"
#include "ft_printf.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
void rl_replace_line(const char *text,int clear_undo);
extern int g_dupstdin;

typedef struct s_shell t_shell;
struct s_shell
{
	t_list *steps;
	t_list *tokens;
	t_list *steps_to_free;
	char *current_line;
	char **env;
	char **declared_env;
	int last_exit_code;
	char *line;
	int *fd;
	t_list *heredoc_contents;
};

bool validate_subexpressions(t_shell *shell, t_list *shell_steps);
void close_descriptor(int *fd);
char **duplicate_string_array(char **arr);
void release_execution_steps(t_list **step_lists);
void handle_interrupt_interactive(int sig);
void handle_interrupt_command(int sig);
void handle_quit_command(int sig);
void handle_heredoc_signal(int sig);
char *retrieve_environment_variable(const t_shell *shell, const char *name);
bool reprocess_environment_token(
	t_token *token, t_list **el, t_list **tokens);
char *read_command_line(t_shell *shell);
void process_heredoc_inputs(t_shell *shell);
void execute_and_cleanup_shell(t_shell *shell, char *line);

#endif
