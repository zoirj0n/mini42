
#ifndef EXEC_H
# define EXEC_H

# include "parsing.h"

# define CONT 1
# define BREAK -1
# define PASS 0

struct	s_exec_flags
{
	bool	first_flag;
	bool	exit;
	bool	valid_redirs;
	int		w_status;
	int		action;
	int		step_num_start;
	int		step_num;
};

typedef struct s_exec_flags	t_exec_flags;

bool		execute_subexpression(t_shell *shell, t_exec_step *step, t_exec_flags *flags,
				t_list **steps);
void		configure_command_path(t_shell *shell, t_exec_step *step);
t_list		*rewind_to_step(t_list *exec_steps, int step_number_start);
void		initialize_command_execution(t_shell *shell, int *out_fd, t_exec_flags *flags,
				int step_number);
t_list		*navigate_to_step(t_exec_flags *flags, t_list *exec_steps,
				t_exec_step **step);

/* ----- EXECUTE THE COMMANDS ----- */
void		execute_commands(t_shell *shell, t_list *exec_steps, int step_number,
				char *current_line);

/* ----- FUNCTION CALLS TO RUN THE COMMANDS ----- */
int			*execute_initial_command(t_exec_step *step, int *fd, t_shell *shell, int out_fd);
int			*execute_pipeline_command(t_exec_step *step, int *fds, t_shell *shell, int out_fd);

/* ----- CMD UTILS -- CLOSE PIPES -- CHILD BUILTINS ----- */
int			initialize_command_execution_context(t_shell *shell, t_redir **inredir, t_exec_step *step,
				int *heredoc_fds);
int			*cleanup_command_resources(int *fds, int *in_fd, int *out_fd,
				int *heredoc_fds);
int			execute_builtin_in_child(t_shell *shell, t_exec_step *step, int *fds,
				int *heredoc_fds);
void		setup_pipe_descriptors(const t_exec_step *step, int *fds);

/* ----- RUN HEREDOCS ----- */
// void		execute_heredoc_inputs(t_shell *shell, t_exec_step *step);
t_list		*execute_heredoc_inputs(t_shell *shell, t_list *steps);
int			calculate_heredoc_count(t_list *substeps);
void		bypass_subexpression_heredocs(t_list *heredocs, int num_skipped);

/* ----- IMPLEMENT && || AND REPARSE AGAIN DURING EXECUTION ----- */
void		process_logical_operators(t_shell *shell, t_exec_step *step, int step_number,
				t_list **steps);

/* ----- FUNTIONS TO HANDLE WAITING FOR COMMANDS RAN AND EXIT ----- */
int			retrieve_exit_status(t_list *exec_steps, t_exec_step *step,
				t_exec_flags *flags);
t_list		*await_completion_and_get_status(t_shell *shell, t_exec_step *step,
				t_list *exec_steps, t_exec_flags *flags);

/* ----- HANDLE INVALIDATIONS AND CALL CHECK FUNCTIONS ----- */
void		validate_command_execution(t_shell *shell, t_list **steps, t_exec_step *step,
				t_exec_flags *flags);

/* ----- FUNCITONS TO PRINT THE ERR MESSAGE FOR INVALID COMMANDS/FILES ----- */
void		report_command_not_found(t_shell *shell, t_exec_step *step, bool *exit_flag);
void		report_command_is_directory(t_shell *shell, t_exec_step *step, bool *exit_flag);
void		report_file_not_found(t_shell *shell, t_exec_step *step, bool *exit_flag);
void		report_permission_denied(t_shell *shell, t_exec_step *step,
				bool *exit_flag);

/* ----- FUNCTIONS TO CHECK FOR COMMAND AND FILE VALIDATIONS ----- */
bool		verify_path_validity(t_exec_step *step);
bool		verify_command_validity(t_exec_step *step, bool valid_redirs);
bool		detect_missing_command(t_exec_step *step, bool valid_redirs);
bool		detect_missing_file(t_exec_step *step, bool valid_redirs);
bool		detect_permission_issue(t_exec_step *step, bool valid_redirs);

/* ----- FUNCTION TO HANDLE REDIRECTIONS -----*/
t_redir		*retrieve_last_input_redirect(t_list *in_redir);
bool		configure_redirections(t_shell *shell, t_exec_step *step,
				bool *exit_flag, int *out_fd);

/* ----- SOME UTILS ----*/
int			check_directory_status(const char *path);
void		close_descriptor(int *fd);
char		*resolve_command_path(char *bin, char **env);

/* ----- FUNCITON TO CHECK VALIDATION OF REDIRECTION -----*/
int			verify_redirection_access(t_redir *redir_file, t_list **redir);
bool		validate_redirection_files(t_exec_step *step);
bool		confirm_redirection_file_exists(t_redir *redir_file, int *out_fd);

#endif
