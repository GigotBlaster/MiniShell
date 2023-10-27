/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenibart <lenibart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:32:23 by lenibart          #+#    #+#             */
/*   Updated: 2023/10/27 16:30:17 by lenibart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **lexer(char *prompt)
{
    
}

// Fonction pour créer un nouveau token
Token* createToken(const char* value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->value = ft_strdup(value);
    token->next = NULL;
    return token;
}

// Fonction pour ajouter un token à la liste chaînée
void addToken(Token** head, Token* newToken) {
    if (*head == NULL) {
        *head = newToken;
    } else {
        Token* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newToken;
    }
}

// Fonction pour analyser l'entrée en tokens
Token* lexer(const char* prompt) {
    Token* tokens = NULL;
    int i = 0;
    int promptLength = ft_strlen(prompt);

    while (i < promptLength) {
        // Ignorer les espaces
        while (i < promptLength && ft_isspace(prompt[i])) {
            i++;
        }

        // Identifier les mots
        int j = i;
        while (j < promptLength && !ft_isspace(prompt[j])) {
            j++;
        }

        if (i < j) {
            char* word = (char*)malloc(j - i + 1);
            strncpy(word, prompt + i, j - i);
            word[j - i] = '\0';

            Token* newToken = createToken(word);
            addToken(&tokens, newToken);
            i = j;
        }
    }

    return tokens;
}

// Fonction pour afficher les tokens
/* void printTokens(Token* tokens) {
    while (tokens != NULL) {
        printf("Token: %s\n", tokens->value);
        tokens = tokens->next;
    }
} */

// Fonction pour libérer la mémoire allouée pour les tokens
void freeTokens(Token* tokens) {
    while (tokens != NULL) {
        Token* temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
}
