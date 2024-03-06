/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:45:05 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 15:46:49 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Duplicates a string by allocating memory for a new string.
 *
 * This function duplicates the null-terminated string 's' by allocating
 * memory for a new string and copying the characters from 's' to the newly
 * allocated memory.
 *
 * @param s A pointer to the null-terminated string to be duplicated.
 * @return A pointer to the newly allocated string, which is a duplicate of
 *         's'. Returns NULL in case of memory allocation failure.
 */
char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s && *s)
		ptr[i++] = *s++;
	ptr[i] = '\0';
	return (ptr);
}

/**
 * @brief Merges two strings into one. The two strings are freed.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return The merged string.
 */
char	*ft_strmerge(char *s1, char *s2)
{
	char	*merged;

	merged = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (merged);
}
