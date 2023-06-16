/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:38:46 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 16:20:34 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char				**env;
	int					exit_status;
	struct s_command	*cmds;
	int					saved_out;
}	t_shell;

t_shell	g_shell;

typedef struct s_command
{
	char				*full_str;
	char				*cmd_path;
	int					input_fd;
	int					output_fd;
	char				*input_filename;
	char				*output_filename;
	char				*heredoc_delimiter;
	int					heredoc_flag_exp;
	char				**args;
	struct s_command	*next;
}	t_cmd;

/* Main */
char	**ft_check_args(int ac, char *av[], char *envp[]);

/* Creating node of the list with splite pipes */
char	**ft_split_pipes(char *s, char c);
void	ft_write_nodes(char *s, char **split, char c);
int		ft_count_nodes(char *s);
int		ft_find_closed_quote(char *s, int i);
int		ft_find_pipe(char *s, int i, int *count);

/* Arguments - check syntax errors */
int		ft_pipe_syntax(char *str);
int		ft_redirec_syntax(char *str);
int		ft_redirec2_syntax(char *str);
int		ft_syntax_check(char *str);
int		ft_count_redirections(char *str, int i);

/* Signals */
void	ft_signals_received(int where);
void	ft_restore_prompt(int sig);
void	ft_ctrl_c(int sig);
void	ft_backslash(int sig);
void	ft_sig_exit(int sig);
void	ft_nothing(int sig);
void	ft_received_ctrl_d(t_cmd **cmd);

/* Functions for the list t_cmd */
t_cmd	*ft_lstcmd_new_pipe(char *str);
void	ft_lstcmd_add_back(t_cmd **lst, t_cmd *new);
int		ft_lstcmd_size(t_cmd *lst);
void	ft_lstcmd_delete(t_cmd **lst);
void	ft_lstcmd_print(t_cmd *lst);

/* Parse */
t_cmd	*ft_parse_line(char *line);
int		ft_count_strs(char **str);
int		ft_fill_node(t_cmd *cmd);
char	**ft_get_args_m(char **str, t_cmd *cmd);
void	ft_update_args(char **str, t_cmd *cmd, int count);

/* Tokens */
int		ft_count_tokens(char *str, char *delimit);
int		ft_next_token_len(char *str, char *delimit, int start);
char	**ft_tokenize(char *str, char *delimit);
int		ft_is_delimiter(char ch, char *delimit);

/* Open Fds for redirections */
int		ft_update_fd(char **str, int i, t_cmd *cmd);
int		ft_check_open_fds(int fd);
int		ft_do_heredoc(t_cmd *cmd, char **envp, char **str, int i);
int		ft_do_redirections(t_cmd *cmd, char **str, int i);

/* Dollar Expansion */
char	*ft_join_to_str(char *str, char ch);
char	*ft_dollar_expansion_x(char *full_str, char **envp);
char	*ft_get_dollar_variable(char *str, int i);
char	*ft_get_dollar_val(char *full_str, int *i, char *new_str, char **envp);

char	*ft_expand(char *str, char **envp);
int		ft_var_len(char *str, int i);
char	*ft_varname(char *str, int i);
char	*ft_dollar_exp_dq(char *var_value, char **envp);

/* Getting path of the input commands */
void	ft_fill_path_cmds(t_cmd **cmd);
char	*ft_get_path(t_cmd **cmd);
char	*ft_check_cmd_paths_table(t_cmd **cmd);
char	*ft_check_cmd_path(t_cmd **cmd);
char	*ft_strjoin_path(char *s1, char *s2);

/* Get Env */
char	**ft_copy_env(char **envp);
char	*ft_getenv(char *variable);
char	*ft_get_var_name(char *str);
int		ft_is_var_env(char *arg);
int		ft_is_var_env_loop(int i, char *var_name, char *arg, int size);

/* Execution */
int		ft_execute_line(t_cmd *cmd);
int		ft_check_redirection_input(t_cmd *cmd);
int		ft_check_redirection_output(t_cmd *cmd);
int		*ft_open_pipes(int nbr_pipes, int fds[]);
int		ft_close_pipes(int pipesfds[], int nbr_pipes);

int		ft_execute_cmds(t_cmd *cmd, int nbr_pipes, int fds[]);
int		ft_do_builtin_parent(t_cmd *cmd);
int		ft_dup_for_pipes(t_cmd *cmd, int fds[], int j);
int		ft_exe_child_afterdup(t_cmd *cmd, int nbr_pipes, int fds[], int pid[]);

int		ft_check_fork_error(int pid);
void	ft_write_pipe_error(void);
int		ft_wait(int pid[], int nbr_pipes);
void	ft_close_wait_free(int pid[], int nbr_pipes, int fds[]);
void	ft_close_std_fds_child(void);

/* Heredoc */
int		ft_get_heredoc_fd(t_cmd **cmd, char **envp);
char	*ft_get_heredoc_loop(t_cmd **cmd, char **envp, char *line, int fd);
int		ft_check_delimiter(t_cmd **cmd);

char	*ft_trim_heredoc_delimiter(t_cmd **cmd);
int		ft_find_quotes_heredoc(char *s, int i);
void	ft_exit_heredoc(t_cmd **cmd);
void	ft_received_ctrl_d_heredoc(void);
void	ft_handle_ctrl_c_heredoc(int signbr);
void	ft_handle_sigquit_hd(int signbr);

/* BuiltIns Child*/
int		ft_check_is_builtin_child(t_cmd **cmd, int fds[], int pid[]);
int		ft_builtin_pwd(t_cmd **cmd, int fds[], int pid[]);
int		ft_builtin_env(t_cmd **cmd, int fds[], int pid[]);

int		ft_builtin_echo(t_cmd **cmd, int fds[], int pid[]);
int		ft_check_args_echo(char **str, int i);
int		ft_check_echo_option(char **args);

/* BuiltIns Parent */
int		ft_check_is_builtin_parent(t_cmd *cmd);
int		ft_builtin_parent_exe(t_cmd *cmd, int fds[], int pid[]);
int		ft_builtin_exit(char **args, t_cmd **cmd, int fds[], int pid[]);

int		ft_builtin_cd(t_cmd *cmd);
int		ft_cd_go(char **args);
int		ft_cd_only(char **args);
int		ft_update_pwd(char *pwd);

int		ft_builtin_export(t_cmd *cmd);
char	**ft_insert_var_env(char *str, char **envp);
int		ft_valid_var_export(char *str);
char	**ft_sort_export_2darray(char **str);
void	ft_export_print(void);

int		ft_builtin_unset(t_cmd *cmd);
char	**ft_delete_var_env(char **envp, int i);
int		ft_check_env_unset(char *arg);

int		ft_check_redirections_parent(t_cmd *cmd);

/* BuiltIns Utils */
void	ft_clean_child_builtin(t_cmd **cmd, int nbr_pipes, int fds[]);
void	ft_clean_child(t_cmd *cmd, int nbr_pipes, int fds[], int pid[]);
void	ft_clean_child_after_exe(t_cmd *cmd, int nbr_pipes, int fds[], \
								int pid[]);

/* Free functions */
void	ft_free_cmds(t_cmd **cmd);
void	ft_free_cmds_and_line(t_cmd **cmd, char *line);
void	ft_free_2d_array(char **array2d);

/* Utils */
int		ft_isspace(char ch);
int		ft_get_wordlen(char *str, int i, char *delimit);
char	*ft_get_next_word(char *str, int i, char *delimit);
char	*ft_strjoin_m(char *s1, char *s2);
int		ft_print_2darray(char **str);

/* Utils2 */
int		ft_is_quote(char ch);
char	*ft_str_in_sq(char *full_str, int *i, char *new_str);
char	*ft_str_in_dq(char *full_str, int *i, char *new_str, char **envp);
char	*ft_check_for_quotes(char *str);
int		ft_is_valid_nbrs(char *nbrs);

/* Utils3 */
int		ft_2d_array_len(char **str);
int		ft_atoi_exit(char *str);
int		ft_check_open_q(char *str);
int		ft_is_directory(char *path);

#endif
