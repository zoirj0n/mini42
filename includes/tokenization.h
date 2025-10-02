
#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <dirent.h>

# define TRUE 1
# define FALSE 0
# define CONTINUE 2

typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_shell		t_shell;
typedef struct s_wildcard	t_wildcard;

enum	e_token_type
{
	QUOTED_STRING,
	DOUBLE_QUOTED_STRING,
	NORMAL,
	INPUT_REDIR,
	OUTPUT_REDIR,
	APPEND,
	HEREDOC,
	PIPE,
	AND,
	OR,
	SUB_EXPR,
	LAST_EXIT,
	ENV_VAR,
	WILDCARD,
	DUMMY
};

struct s_token
{
	t_token_type	type;
	size_t			start;
	size_t			end;
	char			*substr;
	t_list			*sub_tokens;
	bool			expanded;
};

struct s_wildcard
{
	char	*str;
	bool	is_wildcard;
};

char		*strip_dollar_signs(const char *str);
t_list		*process_input_line(const t_shell *shell, const char *line,
				bool *success);
t_list		*process_environment_string(const char *line, bool *success);
t_list		*extract_environment_variable(const t_shell *shell, const char *line,
				size_t *idx);
void		display_token_details(t_list *tokens);
char		*join_and_free_strings(char *s1, char *s2, int f);
char		*extract_and_free_substring(char *s, unsigned int start, size_t len);
bool		check_environment_variable(const char *str);
char		*resolve_environment_variable(const t_shell *shell, char *str);
void		deallocate_memory(void *memory);
t_list		*create_operator_token(const char *line, size_t *idx,
				const t_token_type type);
t_list		*create_subexpression_token(const t_shell *shell, const char *line,
				size_t *idx);
char		*apply_wildcard_expansion(char *token);
t_wildcard	**parse_wildcard_pattern(const char *wc);
void		release_token_memory(void *mem);
void		release_string_array(char **split);
t_list		*create_single_quote_token(const t_shell *shell, const char *line,
				size_t *idx);
t_list		*create_double_quote_token(const t_shell *shell, const char *line,
				size_t *idx, const bool expand_var);
void		display_token_details(t_list *tokens);
void		display_token_list(t_list *tokens);
char		*remove_quote_characters(const char *str);
t_list		*create_normal_token(const t_shell *shell, const char *line,
				size_t *idx, bool expand_var);
void		track_quote_state(const char *str, const size_t i, bool *in_single,
				bool *in_double);
bool		compare_string_with_wildcard(const char *str, t_wildcard **wc_segs);
bool		detect_operator_character(const char *line, const size_t i);
t_list		*process_operator_token(const char *line, size_t *i);
void		*handle_token_error(const char *msg, t_list **tokens, bool *success);
bool		check_previous_heredoc(t_list *tokens);
bool		process_wildcard_token(const t_shell *shell, t_list **el,
				t_list **tokens, bool *success);
void		update_quote_state(const char ch, char *quote, bool *in_quote);
bool		detect_token_syntax_errors(const char *line, bool *success);
void		cleanup_environment_tokenization(t_list **el,
				t_list **tokens, bool *success);
bool		process_primary_tokens(const t_shell *shell, const char *line,
				size_t *i, t_list **tokens);
bool		process_secondary_tokens(const t_shell *shell, const char *line,
				size_t *i, t_list **tokens);
bool		process_text_and_wildcard(const t_shell *shell, const char *line,
				size_t *i, t_list **tokens);
bool		count_quoted_words(const char *str, size_t *num_words, size_t *i);
bool		split_quoted_wildcard(const char *wc, size_t *i, size_t *word_count,
				t_wildcard **wc_split);
char		*build_word_string(char const *str, const size_t word_start,
				const size_t word_end);
t_wildcard	*build_wildcard_segment(char *str, bool is_wildcard);

#endif
