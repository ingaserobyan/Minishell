/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:04:05 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 20:04:06 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <stdbool.h>

# define NO_EXECUTE 101
# define EXECUTE 202
# define NO_CMD 303
# define YES_CMD 404

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_QUOTES,
	TOKEN_SPACE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*var_value;
	char			*key;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct command_args
{
	char				*command;
	char				**args;
	char				*red_in;
	char				*red_out;
	char				*red_append;
	char				*heredoc;
	int					type_heredoc;
	int					type_command;
	int					fd_out;
	int					fd_in;
	int					exist_cmd;
	int					error_flag;
	struct command_args	*next;
	struct command_args	*prev;
}t_command;

typedef struct s_count
{
	int	count_env;
	int	count_pipe;
	int	count_r_in;
	int	count_r_out;
	int	i;
}	t_count;

typedef struct s_init
{
	int		len_pipe;
	int		len_redir;
	int		j;
	int		tmp;
	char	*str;
}	t_init;

typedef struct s_env_init
{
	int		i;
	int		j;
	int		len;
	char	*tmp_str;
	char	*join;
	char	*temp;
}t_env_init;

typedef struct s_quates
{
	int	i;
	int	j;
	int	tmp;
	int	len;
	int	count;
	int	count_quate;
	int	count_double_quate;
	int	flag;
	int	flag_open;
	int	flag_close;
	int	error_flag;
}	t_quates;

typedef struct s_command_args
{
	int			i;
	int			count;
	t_command	*tmp_word;
	t_token		*tmp_token;
	t_token		*start_token;
	t_command	*new_node;
}	t_command_args;

typedef struct s_find_executable
{
	char	**token;
	char	*full_path;
	char	*tmp_full_path;
	char	*path_env;
	char	*path_copy;
	int		i;
	int		len;
}	t_find_executable;

typedef struct s_env_heredoc
{
	int		i;
	int		flag;
	int		j;
	int		len;
	char	*join;
	char	*tmp_str;
	char	*var_value;
	char	*temp;
}	t_env_heredoc;

#endif
