/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:22:22 by pgrellie          #+#    #+#             */
/*   Updated: 2024/10/13 19:16:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/***********************/
/*  LIBRARIES IMPORTS  */
/***********************/

# include "../Libraries/pedro_lib/pedro_lib.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

/************************/
/*       DEFINES        */
/************************/

# define PROMPT_LINE "\1\033[1;91m\2MYSHELL=> \1\033[0m\2"

/************************/
/*       SIGNALS        */
/************************/

# define CTRL_C 130
# define CTRL_D 0
# define CTRL_BS 131

/************************/
/*    GLOBAL VARIABLE   */
/************************/

extern int	*g_var;

/************************/
/*      STRUCTURES      */
/************************/

typedef struct s_var
{
	int		x;
	int		y;
}				t_var;

typedef struct s_exp
{
	size_t	x;
	bool	in_single_quote;
	bool	in_double_quote;
}				t_exp;

typedef enum s_token_type
{
	CMD,
	ARG,
	WORD,
	PIPE,
	INFILE,
	OUTFILE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND,
	LIMITER,
}				t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				equal_sign;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

typedef struct s_redirs
{
	char			*infile;
	bool			in_flag;
	char			*outfile;
	bool			out_flag;
	bool			out_app;
	char			*limiter;
	bool			hd_flag;
	struct s_redirs	*next;
	struct s_redirs	*prev;
}				t_redirs;

typedef struct s_cmd
{
	t_token		*tok;
	char		**cmds;
	pid_t		pipefd[2];
	int			*pid;
	t_redirs	*redirs;
}				t_cmd;

typedef struct s_cmdline
{
	t_cmd		*cmd;
	struct s_cmdline	*next;
	struct s_cmdline	*prev;
}				t_cmdline;

typedef struct s_ms
{
	char		*prompt;
	char		**envi;
	t_env		*env;
	t_token		*tokens;
	t_cmdline	*cmdlines;
	int			v_return;
	int			t_count;
}				t_ms;

/************************/
/*	    PROTOTYPES	    */
/************************/

//MINISHELL

//----------The program----------//

t_ms			*init_ms(void);
t_ms			*init_program(char **env);
char			*prompt(t_ms *ms);
void			the_program(t_ms *ms);

//----------Visualisers----------//

void			display_tokens(t_token *tokens);
void			display_envi(t_env *env);
void			display_env(char **envi);
void			display_redirs(t_redirs *redirs);
void			display_cmdlines(t_cmdline *cmdline);

//-----------Signals-------------//

void			ft_signals(void);
void			ft_sigint_handler(int sig);
void			ft_sigint_setup(void);
void			ft_sigquit_handler(int sig);
void			ft_sigquit_setup(void);
void			sigint_here_doc(int sig);

//-----Pre_parser functions------//

bool			q_check(char *s);
bool			is_quoted(char *s, int index);
bool			c_check(char *s);
bool			shit_check_1(char *s);
bool			full_check(t_ms *ms);

//---------Env funtions----------//

t_env			*find_lastv(t_env *env);
int				find_equal_sign(char *s);
void			add_env(t_env **tok, char *value);
t_env			*init_env(char **env);
void			delete_env(t_env **head, t_env *node_to_del);
void			free_env(t_env **head);

//--------Lexer functions--------//

bool			is_separator(char c, char next_c);
bool			is_quote(char c);
bool			is_space(char c);
int				token_counter(t_token *tok);
t_token			*find_last(t_token *tok);
t_token			*init_token(char *value);
void			add_token(t_token **tok, char *value);
t_token_type	da_tok(char *s, t_token *previous);
t_token			*lexer(char *input);
void			delete_token(t_token **head, t_token *node_to_del);
void			free_tokens(t_token **head);

//-------Expander functions------//

void			init_var(t_var *v);	
char			*malloc_calculator(t_token *tok, t_env *env, int v_return);
char			*tracker(char *s, int *x);
void			transformer(t_token *tok, char *fs);
void			double_dollar(char *fs, int *x, int *y);
void			dollar_bruh(char *fs, int *x, int *y, int v_return);
bool			expandable(const char *str, size_t pos);
t_env			*find_node(char *s, t_env *env);
void			expand_variable(t_token *tok, t_env *env, t_var *v, char *fs);
char			*process_token_value(t_token *tok,
					t_env *env, int v_return, char *fs);
void			dr_kron(t_token *tok, t_env *env, int v_return);
void			finishing(t_token *tok);
void			remove_quotes(char *str);
void			expander(t_ms *ms);

//------------Builtins-----------//

void			builtins(t_ms *ms, t_token *tok);
void			ft_cd(t_token *tok);
void			changedir(char *path);
void			ft_echo(t_token *tok);
void			print_env(t_token *tok, t_env *env);
void			ft_exit(t_token *tok);
int				is_num(const char *str);
void			ft_export(t_ms *ms);
void			print_export(t_env *env);
t_env			*find_env(t_env *env, const char *find);
void			no_args(t_env *env);
void			swap_list(t_env *a, t_env *b);
void			dont_exist(t_ms *ms, t_env *new_node, char *name, char *value);
void			alr_exist(t_env *exist, char *value);
char			*get_cwd(void);
void			ft_pwd(void);
void			ft_unset(t_ms *ms);
void			del_node(t_env *env, t_env *node_to_delete);

//------------Here doc-----------//

void			sigint_here_doc(int sig);
void			close_pipe(int fd1, int fd2);
void			arg_not_found(char *s);
void			handle_here_doc(t_token *tok);
bool			line_error(int l, char *line, char *limiter);
void			papa_proces(pid_t pid, int pipefd[2]);
void			read_until_limit(char *limiteur, int pipefd);
void			start_pipe(char *limiteur);

//-----Executioner functions-----//

// void			exec_cleaner(t_ms *ms);
// char			**find_infile(t_token *tok);
// char			**find_outfile(t_token *tok);
// char			**the_env(t_env *env);
// char			**the_cmds(t_token *tok);
// char			*cmd_path(char **envi, char *cmd);
// char			*get_the_path(char **pathsss, char *cmd);
// void			file_opener(t_ms *ms, int i_o);
// int				exit_brr(int code);
// void			child_process(t_ms *ms, int x);
// void			cmd_exec(t_ms *ms, char *cmd);
// void			init_pipe(t_ms *ms);
// void			redirector(t_ms *ms, int x);
// // int				wait_da_boy(t_pipe *p);
// void			handle_exec_error(void);
// int				executioner(t_ms *ms);
// int				executor(t_ms *ms);

//-------------Exec--------------//

char			**the_env(t_env *env);
void			init_rs(t_redirs *redirs, t_token *tok);
void			clear_redirs_list(t_redirs **redirs);
void			add_redirs_node(t_redirs **redirs, t_token *tok);
t_redirs		*the_redirs(t_token *tok);

char			 **the_cmds(t_token *tok);
void			init_cmd(t_cmdline *cmdline);
void			add_cmdline_node(t_cmdline **cmdline, t_token *tok);
t_cmdline		*the_cmdlines(t_ms *ms);

int				executor(t_ms *ms);

#endif