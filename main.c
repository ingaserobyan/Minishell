/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:50:57 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 22:17:17 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment_variables.h>

void	init_counts(t_shell *shell)
{
	shell->pipe_count_temp = 0;
	shell->pipe_count = 0;
	shell->word_count = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_shell		shell;
	extern int	rl_catch_signals;

	(void)argc;
	init_all_structs(&shell, argv[0]);
	shell.handler = load_env(env);
	if (shell.handler == NULL)
		free_shell(&shell, LAST_EXIT, DELETE_ENV, get_status());
	increment_shlvl(&shell);
	rl_catch_signals = 0;
	while (1)
	{
		init_counts(&shell);
		shell.executable_name = cut_after(argv[0], '/');
		if_executable_name_is_null(&shell);
		minishell_signals(INTERACTIVE_SIGN, NULL);
		shell.input = readline("minishell: ");
		if (if_input_is_null(&shell) == 1)
			break ;
		if_input(&shell);
		if (get_status() == SIGNAL_STATUS)
			set_unsigned_status(1);
		shell.error_flag = 0;
		free_shell(&shell, NO_EXIT, NO_DELETE_ENV, get_status());
	}
}
