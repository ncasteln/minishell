/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/21 09:46:22 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "stdbool.h"
# include <signal.h>
# include <termcap.h> // ???
# include <termios.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

# include "libft.h"
# include "ft_printf.h"
# include "lexer.h"
# include "env.h"
# include "parser.h"

/*
	@param n_ps: number of the process that has to be forked from parent ps
*/
typedef struct s_data
{
	char	*prompt;
	t_list	*env;
	char	*input;
	t_list	*tokens;
	t_node	*tree;
	int		n_ps;
	int		*pid;
	int		e_code;
}	t_data;

/*
	Custom error values are in the range between 106 (max errno value) and
	126 (min reserved exit code), excluded.
*/
enum e_custom_errors
{
	CE_INVARG = 107,
	CE_INVALIDIDENTIFIER = 108,
	CE_TOOMANYARGS = 109,
	CE_SYNTAX_ERROR = 110,
	CE_SYNTAX_TREE = 111,
	CE_EXPANSION = 112,
	CE_HERE_DOC = 113,
	CE_OVERFLOW = 114,
	CE_NUM_REQUIRED = 115,
	CE_CMDNOTFOUND = 127
};

// --------------------------------------------------------------------- PARSER
void	parser(t_data *data);

// -------------------------------------------------------------------- SIGNALS
void	init_sig_handling(void);
// void	setup_child_signals(void);

// ------------------------------------------------------------------ EXPANSION
void	expansion(t_data *data);
int		check_expansion(t_cmd *cmd, t_list *env, int e_code);
char	*expand(char *s, t_list *env, int e_code);
char	*build_str(char *old_str, t_list *var_lst);
void	del_to_expand(void *content);
void	print_expansion(t_list *var_lst);
int		get_n_dollars(char *s);
int		get_var_name_len(char *s);

// ------------------------------------------------------------------- HERE_DOC
void	here_doc(t_node *tree, t_data *data);

// ------------------------------------------------------------------- EXECUTOR
int		executor(t_data *data);
int		parent(t_data *data);
void	child(t_node *node, char **env, int *fd_pipe, int *prev_pipe);
int		resolve_args(char **cmd_name, char **env);
int		resolve_redir(t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
int		run_builtin(t_data *data);

// ------------------------------------------------------------------- BUILTINS
int		print_env(t_list *env);
int		cd(t_data *data);
int		pwd(void);
int		exit_custom(t_data *data);
int		unset(t_data *data);
int		get_exported(t_list *env);
int		export(t_data *data);
int		echo(t_data *data);

// ---------------------------------------------------------------------- UTILS
void	error(char *s1, char *s2, int err_id);
int		ft_strcmp(const char *s1, const char *s2);
void	free_data(t_data *data);
int		get_substr_len(char *s, char c);
int		is_valid_for_history(t_data *data);
int		is_empty_input(char *s);
char	*trim_one_quote(char *s);

#endif
