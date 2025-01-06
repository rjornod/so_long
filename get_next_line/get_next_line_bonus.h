/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:03:32 by rojornod          #+#    #+#             */
/*   Updated: 2024/12/16 11:56:54 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

size_t	get_length(const char *str);
char	*combine_strings(char *p_line, char *buf);
char	*ft_strchr(char *str, int ch);
char	*get_next_line(int fd);
char	*extract_line(char *buffer);
char	*read_and_join(int fd, char *buffer, char *line);
void	manage_buffer(char *buffer);
char	*ft_strdup(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *c );

#endif