/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:29:06 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* Minishell utils */
t_minishell		*get_minishell(t_minishell *minishell);

/* ENV List */
t_env			*new_env_content(char *var);
t_list			*init_env_lst(char **envp);
t_list			*copy_env_lst(t_list *original);
void			del_env_content(void *env_var);
void			delone_env_lst(t_list *to_del, t_list **env);

/* ENV List getters and setters */
char			*get_env_lst_name(t_list *env_lst);
char			*get_env_lst_value(t_list *env_lst);
t_list			*get_env_lst(char *name, t_list *env);
char			*get_env_value(char *name);
void			set_env_value(char *name, char *value);

/* Array utils */
int				get_array_len(char **split);

/* Merge Sort Linked Lists */
void			merge_sort(t_list **list);

/* Free Memory utils */
void			free_minishell(t_minishell *minishell);
void			free_split(char **split);
void			free_table(t_cmd_table *cmd_table, int nb_cmds);
void			free_tokens(t_token *tokens, int nb_tokens);
void			free_redirs(t_redir *redirs, int nb_redirs);

/* Error and/or Exit utils */
t_error			error_and_exit(t_error code);
int				error_and_return(t_error code, int exit_code);
void			error_message(t_error code);
int				open_or_exit(char *file_path, mode_t mode);
void			*calloc_or_exit(size_t size, int count);

#endif
