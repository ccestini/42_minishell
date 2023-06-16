/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:25:57 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 16:02:43 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_pipe_syntax(char *str);
int	ft_redirec_syntax(char *str);
int	ft_redirec2_syntax(char *str);
int	ft_syntax_check(char *str);
int	ft_count_redirections(char *str, int i);

int	ft_pipe_syntax(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_find_closed_quote(str, i);
		if (str[i] == '|')
		{
			if ((word == 0) || (str[i + 1] == '\0'))
				return (-1);
			word = 0;
		}
		else if ((ft_isspace(str[i]) == 0))
			word = 1;
		i++;
	}
	return (0);
}

int	ft_redirec_syntax(char *str)
{
	int	i;
	int	redirection;

	i = -1;
	redirection = 0;
	while (str[++i])
	{
		if (redirection && (str[i] == '>' || str[i] == '|' || str[i] == '<'))
			return (0);
		if (str[i] == '>')
		{
			redirection = ft_count_redirections(str, i);
			if (redirection > 2)
				return (0);
			i = i + redirection - 1;
		}
		else if (ft_isspace(str[i]) == 0 && str[i] != '<' && str[i] != '|')
			redirection = 0;
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_find_closed_quote(str, i);
	}
	if (redirection)
		return (0);
	return (1);
}

int	ft_redirec2_syntax(char *str)
{
	int	i;
	int	redirection;

	i = -1;
	redirection = 0;
	while (str[++i])
	{
		if (redirection && (str[i] == '>' || str[i] == '|' || str[i] == '<'))
			return (0);
		if (str[i] == '<')
		{
			redirection = ft_count_redirections(str, i);
			if (redirection > 2)
				return (0);
			i = i + redirection - 1;
		}
		else if (ft_isspace(str[i]) == 0 && str[i] != '>' && str[i] != '|')
			redirection = 0;
		if (str[i] == '\'' || str[i] == '\"')
			i = ft_find_closed_quote(str, i);
	}
	if (redirection)
		return (0);
	return (1);
}

int	ft_syntax_check(char *str)
{
	if (ft_check_open_q(str) == -2)
	{
		ft_putstr_fd("my@shell: open quotes not supported\n", STDERR_FILENO);
		g_shell.exit_status = 258;
		return (-1);
	}
	if (ft_pipe_syntax(str) == -1)
	{
		ft_putstr_fd("syntax error\n", 2);
		g_shell.exit_status = 258;
		return (-1);
	}
	if (ft_redirec_syntax(str) == 0)
	{
		ft_putstr_fd("syntax error\n", 2);
		g_shell.exit_status = 258;
		return (-1);
	}
	if (ft_redirec2_syntax(str) == 0)
	{
		ft_putstr_fd("syntax error\n", 2);
		g_shell.exit_status = 258;
		return (-1);
	}
	return (0);
}

int	ft_count_redirections(char *str, int i)
{
	int		count;
	char	ch;

	count = 0;
	ch = str[i];
	while (str[i])
	{
		if (str[i] != ch)
			return (count);
		count++;
		i++;
	}
	return (count);
}
