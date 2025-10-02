# ---------- Pretty ----------
COLOR=\033[0;36m
NC=\033[0m
AI = \n\n​​​​​\n\
\t\t\t\t\t\t\t\\t\t\t\033[36m  𝚉𝙾𝙸𝚁𝙹𝙾𝙽 𝚂𝙾𝙱𝙸𝚁𝙾𝚅 & 𝙸𝚂𝙻𝙾𝙼𝙹𝙾𝙽 𝚅𝙰𝙻𝙸𝙴𝚅\033[0m \n\n​​​​​\n\
\033[31m\t\t\t\t\t\t\t\t███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░\n\t\t\t\t\t\t\t\t████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░\n\t\t\t\t\t\t\t\t██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░\n\t\t\t\t\t\t\t\t██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░\n\t\t\t\t\t\t\t\t██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗\n\t\t\t\t\t\t\t\t╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝\n\n\n

# ---------- Project ----------
NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g

# ---------- Readline fixed path ----------
RLFLAGS = -lreadline -lhistory
RLDIR   = -L/opt/vagrant/embedded/lib
RLINC   = -I/opt/vagrant/embedded/include/readline

CFLAGS += $(RLINC) -Iincludes -Ift_printf -Ilibft
LDFLAGS += $(RLDIR)
LIBS = $(RLFLAGS)

LIBFT       := libft/libft.a
FT_PRINTF   := ft_printf/libftprintf.a

# ---------- Sources ----------
TOKENIZATION_SRCS = tokenize_line.c expansion.c \
					tokenize_subexpr.c wildcard.c split_wildcard.c \
					split_wildcard2.c free_funcs.c tokenize_quotes.c \
					contains_env_var.c wildcard_algorithm.c eat_quotes.c \
					tokenize_normal.c tokenize_env_var.c eat_dollars.c \
					tokenize_operator.c tokenize_line_utils.c tokenize_env_var_str.c
TOKENIZATION_SRCS := $(addprefix tokenization/, $(TOKENIZATION_SRCS))

PARSING_SRCS = parsing.c parsing_utils.c check_subexprs.c error_checking.c parse_step.c
PARSING_SRCS := $(addprefix parsing/, $(PARSING_SRCS))

BUILTINS_SRCS = echo.c pwd.c builtins.c env.c exit.c export.c export_utils.c \
				cd.c cd_utils.c unset.c unset_utils.c
BUILTINS_SRCS := $(addprefix builtins/, $(BUILTINS_SRCS))

EXEC_SRCS = exec_and_or.c exec_utils.c here_doc.c first_cmd.c mid_cmd.c cmd_utils.c exec_cmds.c wait_exit.c \
			exec_redir.c validate_redir.c validation_message.c handle_validation.c check_validation.c exec.c \
			exec_subexpr.c
EXEC_SRCS := $(addprefix exec/, $(EXEC_SRCS))

SIGNAL_SRCS = signal_handlers.c signals.c
SIGNAL_SRCS := $(addprefix signals/, $(SIGNAL_SRCS))

SRCS = $(TOKENIZATION_SRCS) $(PARSING_SRCS) $(BUILTINS_SRCS) $(EXEC_SRCS) $(SIGNAL_SRCS) \
	   utils.c main.c minishell.c
OBJS = $(SRCS:%.c=%.o)

# ---------- Rules ----------
.PHONY: all bonus clean fclean re norm giga

all: $(NAME)

giga:
	@echo "$(COLOR)$(AI)$(NC)"

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) $(FT_PRINTF) $(LIBS) -o $@
	@echo "$(COLOR)$(AI)$(NC)"

# Pattern rule for .c -> .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

$(FT_PRINTF):
	$(MAKE) -C ft_printf

bonus: all

norm:
	norminette | grep Error || true

clean:
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C ft_printf fclean
	rm -f $(NAME)

re: fclean all
