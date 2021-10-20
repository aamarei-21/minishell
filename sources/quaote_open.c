/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaote_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamarei <aamarei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 07:19:20 by whector           #+#    #+#             */
/*   Updated: 2021/06/30 11:04:33 by aamarei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_endl_ignor(char *str, t_data *data)
{
	int		len;

	len = ft_strlen(str);
	return (backslash_is_active(str, len)
		|| quaote_is_open(str, len) != 0 || str[len - 1] == '|'
		|| ft_strncmp(&str[len - 2], "&&", 2) == 0
		|| brackets_is_open(str, len) > 0 || ft_stdin_active(str, data));
}

char	*get_line_slash(char *line, char *tmp, int *error)
{
	line = rl_gets_without_hist(QUAOTE_PROMT, error);
	if (NULL == line)
		return (NULL);
	line = ft_g_strjoin(tmp, -1, 0, line);
	add_history(line);
	return (line);
}

char	*get_line_quaote(char *line, char *tmp, int *error, int len)
{
	line = rl_gets_without_hist(QUAOTE_PROMT, error);
	if (NULL == line)
		return (NULL);
	else if (quaote_is_open(tmp, len) != 0)
		line = ft_g_strjoin(tmp, 0, 1, line);
	else
		line = ft_g_strjoin(tmp, 0, 0, line);
	add_history(line);
	return (line);
}

void	read_next_line(t_data *data, char *tmp, int *error)
{
	int		len;

	len = ft_strlen(data->line);
	if (backslash_is_active(tmp, len))
		data->line = get_line_slash(data->line, tmp, error);
	else if (ft_stdin_active(tmp, data))
		*error = read_tmp_stdin(data, tmp, *error);
	else
		data->line = get_line_quaote(data->line, tmp, error, len);
}

int	quaote_open_mode(t_data *data)
{
	int		error;
	char	*tmp;

	error = 0;
	if (check_unexpected_token(data->line) != 0)
		return (258);
	while (error == 0 && is_endl_ignor(data->line, data))
	{
		tmp = data->line;
		read_next_line(data, tmp, &error);
		if (NULL == data->line && error != 1)
			error = unexpected_eof(tmp);
	}
	if (error == 258)
		ft_perr("syntax error", 258, NULL, "unexpected end of file");
	return (error);
}
