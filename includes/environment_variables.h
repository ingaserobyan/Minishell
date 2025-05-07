/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:33:16 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 21:48:33 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_VARIABLES_H
# define ENVIRONMENT_VARIABLES_H

# include <stddef.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <tokenization.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <environment_variables.h>
# include <sys/wait.h>
# include <dirent.h>

# define CR	13

# ifndef SPACE
#  define SPACE 32
# endif

# ifndef TAB
#  define TAB 9
# endif

# define MALLOC_ERROR 11
# define INTERACTIVE_SIGN 2
# define NON_INTERACTIVE_SIGN 3
# define HEREDOC_SIGN 4
# define LAST_EXIT 666
# define NO_EXIT   999
# define DELETE_ENV 444
# define NO_DELETE_ENV 555
# define SIGNAL_STATUS 57
# define COMMAND_NOT_FOUND 127
# define SYNTAX_ERROR 258 //2 er poxel em 258
# define PERMISSION_DENIED 1

typedef struct s_handler	t_handler;

typedef struct env_dta
{
	char			*key;
	char			*value;
	struct env_dta	*next;
}	t_env_data;

typedef struct shell
{
	t_handler	*handler;
	t_token		*token;
	t_command	*word;
	char		*executable_name;
	char		*input;
	int			shlvl;
	char		*pwd;
	char		*oldpwd;
	int			error_flag;
	int			heredoc_count;
	int			pipe_count_temp;
	int			pipe_count;
	int			word_count;
	int			cmd_counter;
	int			*pipe_fds;
	int			seperator_error;
	int			pipe_index;
}	t_shell;

//lexical analyzer functiones
void				input_tokenization(t_shell *shell);
void				token_value(int *i, t_shell *shell, t_token **node,
						int *error_flag);
void				get_spr_value(int *i, t_token **node, t_shell *shell,
						int *error_flag);
void				checking_value(char *str, int *error_flag);
void				get_var_value_quates_cause(t_shell *shell, t_token **node);
void				get_env_value(int *i, t_token **node, t_shell *shell,
						int *error_flag);
void				get_env_var_value(char *value, t_shell *shell,
						t_token **node);
int					checking_quates_counts(t_quates idx, t_token **node,
						t_shell *shell);
void				get_quotes_value(t_shell *shell, int *i, t_quates *idx,
						t_token **node);
int					if_its_control_operator(t_shell *shell);

//char *get_quotes_value(char *input, int *i, int len)

//utils functiones
char				**ft_split(char const *s, char c);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlcpy(char *dest, const char *source, size_t dstsize);
int					ft_var_strcmp(const char *s1, const char *s2);
void				printf_tokens(t_shell *shell);
char				*ft_strdup(const char *s1);
char				*ft_itoa(int n);
int					ft_atoi(const char *str);

//true_false check
int					is_white_space(char c);
int					is_not_white_space(char c);
int					is_not_quotes_and_colon(char c);
int					is_quotes(char c);
int					is_not_separator(char c);
int					is_redir(char *str, t_shell *shell);
int					if_type_is(t_token *tmp_token);
int					if_type_is_not(t_token *tmp_token);
int					if_srct_init_is(t_token **tmp_token);
int					if_cmd_srct_init_is(t_token **tmp_token,
						t_command **tmp_word);

//utils list
void				del_node(t_token **head, t_token *tmp);
t_token				*new_node(int *i, t_shell *shell, int *error_flag);
int					create_list(t_shell *shell, int i, t_token **prev_prev,
						t_token **tmp);
void				free_shell_exit(t_shell *shell);
void				space_checking( t_token **node, t_shell *shell);
void				start_checking(int i, t_shell *shell);

// inits
void				init_all_structs(t_shell *shell, char *argv);
void				clear_idx(t_command_args *idx);
t_count				init_count(void);
t_init				init_idx(void);
t_env_init			env_init_idx(void);
t_quates			quates_idx(void);
t_command_args		command_args_idx(t_shell *shell);
t_find_executable	find_executable_idx(void);
t_env_heredoc		init_env_heredoc(void);

// error_message and free functiones
void				error_message(char *str, char *str2, char *str3);
void				free_t_token(t_shell *shell);
void				free_shell(t_shell *shell, int exit_flag,
						int env_flag, int exit_status);
void				del_env_init_idx(t_env_init *idx, int flag);
void				del_command_args(t_command *cmd);

//command and args func
int					commands_and_args(t_shell *shell);
int					if_struct_init(t_command **tmp_word, t_token **tmp_token,
						int *i, t_shell *shell);
int					struct_init(t_command **tmp_word, t_token **tmp_token,
						int *i, t_shell *shell);
int					redirection_init(t_command **tmp_word, t_token **tmp_token,
						t_shell *shell);
int					redirection_out(t_command **tmp_word, t_token **tmp_token,
						t_shell *shell);
int					redirection_append(t_command **tmp_word,
						t_token **tmp_token, t_shell *shell);
int					redirection_in(t_command **tmp_word, t_token **tmp_token,
						t_shell *shell);
int					heredoc_init(t_command **tmp_word, t_token **tmp_token,
						t_shell *shell);
char				*find_executable(char *command, t_handler *handler,
						t_shell *shell);
void				count_heredoc(t_shell *shell);

//execution
void				execute_command(t_shell *shell);
int					redirection_init(t_command **tmp_word, t_token **tmp_token,
						t_shell *shell);
void				execute_out(t_command *cmd);
void				execute_in(t_command *cmd);
int					execute_heredoc(t_command *cmd, t_shell *shell);
int					path_case(t_shell *shell, t_command *cmd, char **full_path);
void				feragamo(t_command *cmd);
void				create_process_pipes(t_shell *shell, char *full_path,
						t_command *cmd, bool exec_flag);
void				do_child_dups(int *pipe_fd, int prev_fd_out,
						t_command *cmd);
int					do_parent_dups(int *pipe_fd, int prev_fd_out,
						t_command *cmd);
void				execute_child_proccess(t_shell *shell, char *full_path,
						t_command *cmd, bool exec_flag);
void				if_pid_is_zero(t_shell *shell, char *full_path,
						t_command *cmd, bool exec_flag);

void				hdoc_dollar_cvrtr(char **input, t_shell *shell);
//void test_b(t_shell *shell, char *input, char *join, int j, int len);

//main helper
void				if_input_is_not_backslash_zero(t_shell *shell);
void				if_input_is_backslash_zero(t_shell *shell);
void				if_executable_name_is_null(t_shell *shell);
void				if_input(t_shell *shell);
int					if_input_is_null(t_shell *shell);
void				if_pipe_count(t_shell *shell);
void				word_count(t_shell *shell);
int					pipe_count(t_shell *shell);

int					if_its_not_dollar(t_shell *shell);
void				add_dollar(t_shell *shell);
void				from_val_value_to_val(t_shell *shell);
void				if_its_heredoc(t_shell *shell);
void				checking_all_tokens(t_shell *shell);
int					if_its_control_operator(t_shell *shell);

int					if_its_not_dollar(t_shell *shell);
void				add_dollar(t_shell *shell);

// ##########################INGA#########################

# ifndef SEPARATOR
#  define SEPARATOR '='
# endif

# ifndef RED
#  define RED 1
# endif

# ifndef BLACK
#  define BLACK 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef CONTINUE_WHILE
#  define CONTINUE_WHILE 88
# endif

typedef struct s_node
{
	char			*key;
	char			*value;
	char			*temp_value;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
	int				color;
	struct s_node	*next;
	struct s_node	*prev;
}t_node;

typedef struct s_tree
{
	t_node	*root;
	t_node	*nill;
	int		nodes_count;
	int		height;
}t_tree;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	int		nodes_count;
}t_list;

struct	s_handler
{
	t_tree	*tree;
	t_list	*list;
	char	**env;
	int		i;
	int		nodes_count;
	char	*lst_cmd;
	char	*tmp;
	char	*exit_status;
};

typedef struct s_cut_helper
{
	int		i;
	int		j;
	int		k;
	char	*new_str;
}t_cut_helper;

typedef struct s_cd
{
	struct stat	path_info;
	char		*new_path;
	char		*old_path;
	char		*tmp_str;
}t_cd;

typedef struct s_export_data
{
	int		i;
	char	*key;
	t_node	*node;
}t_export_data;

//init.c
void				init_node(t_node *node);
void				init_tree(t_tree *tree);
void				init_list(t_list *list);
void				init_handler(t_handler *handler);

//constructors.c
t_node				*make_node(void);
t_tree				*make_tree(void);
t_list				*make_list(void);
t_handler			*make_handler(void);

//env_helper.c
void				error_msg_env(char *s1, char *s2, char *s3, char *s4);
char				*cut_until(char *line, char c);
char				*cut_after(char *line, char c);
char				*cut_replace(char *stack, char *needle, char *replace);

//rbt_insert.c
void				tree_insert_helper(t_node *new_node, t_tree *tree);
//rbt_rotates.c
void				left_rotate(t_tree *tree, t_node *n_x);
void				right_rotate(t_tree *tree, t_node *n_y);

//color_setter.c
void				set_color_black(t_node *node);
void				set_color_red(t_node *node);

//operators.c
int					nodes_are_same(t_node *node_1, t_node *node_2);
void				put_nills(t_node *node, t_tree *tree);
char				*ft_strnstr_env(char *haystack, char *needle, size_t len);

// prints.c
void				print_node_tree(t_node *node, int print);
void				print_list(t_list *list);
void				print_tree_inorder(t_tree *tree, t_node *node);
void				print_node_list(t_node *node, int print);

// inserting.c
void				insert_to_list(t_node	*new_node, t_list *list);
void				insert_to_tree(t_node *new_node, t_tree *tree);
t_node				*new_node_k_v(char *key, char *value);

// load_env_helper.c
t_node				*new_nodes_from_env(char *line);
int					key_vs_node(char *key, t_node *node);
t_node				*search_node(t_tree *tree, char *key);
char				*handle_underscore(t_handler *handler);
char				*handle_qst_mark(t_handler *handler, t_shell *shell);

// load_env.c
char				*get_env(t_handler *handler, char *key, t_shell *shell);
t_handler			*load_env(char **env);

// in delete_rb_node.c
void				delete_from_tree(t_tree *tree, t_node *node);

// ft_export.c
int					ft_export(char **args, t_handler *handler,
						char *exec_name, t_shell *shell);
int					is_alpha_env(unsigned int c);
int					is_digit(unsigned int c);

//ft_env.c
int					ft_env(char **args, t_handler *handler, t_shell *shell);
int					ft_echo(char **args);
int					ft_cd(char **args, t_handler *handler, char *exec_name,
						t_shell *shell);
int					ft_pwd(char **args, t_shell *shell);

// env_lib_functions.c
char				*ft_strdup_env(char *s1);
int					ft_strcmp_env(const char *s1, const char *s2);
char				*ft_strlcat_env(char *line, int len);
int					ft_strlen_env(char *line);
int					ft_strcmp_ultra(char *s1, char *s2);
int					ft_strncmp_env(char *s1, char *s2, int len);

// env_lib_two.c
int					is_alpha_env(unsigned int c);
int					is_underscore(unsigned int c);
int					is_digit(unsigned int c);
int					is_space(unsigned int c);

//
int					is_space(unsigned int c);
void				delete_from_list(t_node *node, t_list *list);

//is_builtin

int					is_builtin(t_command *tmp_word);
int					builtin(t_shell *shell, t_command *tmp_word);
void				converter_env_to_ptr(t_handler *handler, t_shell *shell);

//inc_dec_rement.c
int					ft_exit(t_shell *shell);
void				update_lst_cmd(t_shell *shell);
void				increment_shlvl(t_shell *shell);

//ft_cd.c
char				*ft_strjoin_ultra(char *s1, char *s2, char *s3);

//ft_cd_cases.c
char				*tilda_case(char *args, t_handler *handler, t_shell *shell);
int					home_case(char **args, t_shell *shell, t_cd *cd_vars,
						char *exec_name);
int					oldpwd_case(char **args, t_shell *shell,
						t_cd *cd_vars, char *exec_name);
int					path_is_valid(char **args, t_cd *cd_vars, char *exec_name);
int					oldpwd_already_exist(t_handler *handler,
						char *old_path, t_node *old_pwd);

//ft_cd_updates.c
int					update_old_pwd(t_handler *handler, char *old_path);
int					update_pwd(t_handler *handler, char *new_path);
int					do_env_updates(t_handler *handler, t_shell *shell,
						t_cd *cd_vars);

//ft_cd_inits.c
int					init_cut_helper(t_cut_helper *cut_helper,
						char *stack, char *needle, char *replace);
void				init_cd_vars(t_cd *cd_vars);

//ft_export.c
int					is_valid_identifier(char *key);

//ft_export_helper.c
void				init_export_data(t_export_data *f_data);
void				handle_malloc_error(t_shell *shell);

//ft_unset.c
int					ft_unset(char **args, t_handler *handler,
						char *exec_name, int i);

//signals.c
void				minishell_signals(int type, t_command *cmd);

//exit_status.c
void				set_unsigned_status(int status);
int					get_status(void);
char				*convert_exit_status(t_handler *handler, t_shell *shell);

//delete_env.c
void				clear_tree(t_tree *tree, t_node *node);
void				delete_tree(t_tree *tree);
void				delete_list_and_nodes(t_list *list);
void				clear_handler(t_handler *handler);
void				delete_handler(t_shell *shell);
char				*free_chr_ptr(char *chr_ptr);
t_handler			*delete_handler_ptr(t_handler **handler);
t_node				*free_node(t_node *node);
char				**free_double_chr_ptr(char **chr_ptr_ptr);

//rbt_delete_sibling.c
void				del_sibiling_is_red(t_tree *tree, t_node *node,
						t_node	**sibling);
t_node				*del_s_black_n_red(t_tree *tree, t_node *node,
						t_node	**sibling);
t_node				*del_left_of_sibling(t_tree *tree, t_node *node,
						t_node	**sibling);
void				del_r_sibling_is_red(t_tree *tree, t_node *node,
						t_node	**sibling);
t_node				*del_right_of_sibling(t_tree *tree, t_node *node,
						t_node	**sibling);
void				execution(t_shell *shell);

int					proccess_exit_code(int temp_status);
void				sig_heredoc(int signal);

#endif
