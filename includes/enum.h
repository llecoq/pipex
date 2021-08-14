/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:24:00 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/14 20:24:33 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum	e_process
{
	CHILD_PROCESS,
	PARENT_PROCESS,
};

enum	e_token
{
	IS_CMD,
	IS_FILE,
	PIPE,
	APPEND,
	HEREDOC,
	STOP_VALUE,
	INPUT_REDIR,
	OUTPUT_REDIR,
};

enum	e_redir
{
	FROM_FILE,
	FROM_STDIN,
	FROM_HEREDOC,
};

enum	e_parse
{
	BONUS,
	MANDATORY,
};

enum	e_file
{
	IS_VALID,
	IS_NOT_VALID,
	EXISTENT,
	NONEXISTENT = -1,
};

enum	e_error
{
	FAILED = -1,
	CMD_NOT_FOUND = 127,
};
