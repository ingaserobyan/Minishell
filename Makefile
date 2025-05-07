NAME = minishell
FLAGS = -Wall -Wextra -Werror  # -fsanitize=address -g3
SRC =	environment/rbt/color_setter.c\
		environment/rbt/ctor.c\
		environment/env_help.c\
		environment/env_lib_functions.c\
		environment/env_lib_two.c\
		environment/env_lib_three.c\
		environment/load_env.c\
		environment/load_env_helper.c\
		environment/init.c\
		environment/inserting.c\
		environment/operators.c\
		environment/prints.c\
		environment/rbt/rbt_insert.c\
		environment/rbt/rbt_rotates.c\
		environment/delete_from_list.c\
		environment/rbt/delete_rb_node.c\
		environment/rbt/rbt_delet_sibling.c\
		environment/delete_env.c\
		builtin/ft_cd.c\
		builtin/ft_cd_cases.c\
		builtin/ft_cd_updates.c\
		builtin/ft_cd_inits.c\
		builtin/exit_status.c\
		builtin/ft_echo.c\
		builtin/ft_env.c\
		builtin/ft_pwd.c\
		builtin/ft_unset.c\
		builtin/is_builtin.c\
		builtin/ft_export.c\
		builtin/ft_export_helper.c\
		builtin/ft_exit.c\
		environment/converter_env_to_ptr.c\
		lexicalanalyzer/tokenization.c\
		lexicalanalyzer/token_value.c\
		lexicalanalyzer/init_idx.c\
		lexicalanalyzer/init_idx_two.c\
		lexicalanalyzer/true_false_check.c\
		lexicalanalyzer/true_false_check_two.c\
		lexicalanalyzer/error_message.c\
		lexicalanalyzer/del_idx_struct.c\
		lexicalanalyzer/quates_value.c\
		lexicalanalyzer/env.c\
		lexicalanalyzer/env_var_value.c\
		lexicalanalyzer/var_value_quates_cause.c\
		lexicalanalyzer/separator_checking.c\
		lexicalanalyzer/command_and_args.c\
		lexicalanalyzer/struct_init.c\
		lexicalanalyzer/find_executable.c\
		lexicalanalyzer/redirections/redirections.c\
		lexicalanalyzer/redirections/red_append.c\
		lexicalanalyzer/redirections/red_in.c\
		lexicalanalyzer/redirections/red_out.c\
		lexicalanalyzer/redirections/heredoc.c\
		lexicalanalyzer/heredoc_dollar_converter.c\
		lexicalanalyzer/logical_operator_check.c\
		helper/ft_split.c\
		helper/utils_func_2.c\
		helper/utils_func.c\
		helper/utils_list.c\
		helper/ft_itoa.c\
		helper/ft_atoi.c\
		main_helper/input_helper.c\
		main_helper/counts.c\
		main_helper/token_helper.c\
		main_helper/if_dollar.c\
		execution/execution.c\
		execution/execution_helper.c\
		execution/create_procces_pipes.c\
		execution/pipe_helper.c\
		execution/execute_red_heredoc.c\
		execution/inc_dec_rement.c\
		signals/signals.c\
		execution/path_case.c\
		main.c

CC = cc
INC =  -I./includes -Ireadline
OBJ = $(SRC:.c=.o)
HEADERS = includes/tokenization.h includes/environment_variables.h
LIBS = ../readline/libreadline.a -lncurses
all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(INC) -g3 $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c Makefile $(HEADERS)
	$(CC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
