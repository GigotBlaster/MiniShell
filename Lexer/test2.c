/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenibart <lenibart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:32:23 by lenibart          #+#    #+#             */
/*   Updated: 2023/11/09 23:15:17 by lenibart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

Token* createToken(TokenType type, const char* value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    strncpy(token->value, value, MAX_TOKEN_LENGTH);
    token->next = NULL;
    return token;
}

void freeTokens(Token* tokens) {
    while (tokens != NULL) {
        Token* temp = tokens;
        tokens = tokens->next;
        free(temp);
    }
}

Token* processWord(const char* input, int* index)
{
    int j = 0;
    while (isalnum(input[*index]) || input[*index] == '$') {
        j++;
        (*index)++;
    }

    if (j > 0) {
        char word[MAX_TOKEN_LENGTH];
        strncpy(word, input + (*index) - j, j);
        word[j] = '\0';

        TokenType type = (word[0] == '$') ? TOKEN_ENV_VARIABLE : TOKEN_WORD;

        Token* token = createToken(type, word);
        return (token);
    }

    return NULL;
}

Token* processPipe()
{
    Token* token = createToken(TOKEN_PIPE, "|");
    return(token);
}

Token* processInputRedirect()
{
    Token* token = createToken(TOKEN_INPUT_REDIRECT, "<");
    return token;
}
Token* processOutputRedirect()
{
    Token* token;

    if (input[i + 1] == '>') {
        token = createToken(TOKEN_APPEND_REDIRECT, ">>");
        i += 2;
    } else {
        token = createToken(TOKEN_OUTPUT_REDIRECT, ">");
        i++;
    }

    return (token);
}

Token* processDoubleQuotes(const char* input, int* index) {
    char doubleQuotes[MAX_TOKEN_LENGTH];
    int j = 0;

    (*index)++;  // Skip the opening double quote
    while (input[*index] != '"' && input[*index] != '\0') {
        doubleQuotes[j++] = input[(*index)++];
    }

    if (input[*index] == '"') {
        doubleQuotes[j] = '\0';
        (*index)++;  // Skip the closing double quote

        Token* token = createToken(TOKEN_DOUBLE_QUOTES, doubleQuotes);
        return token;
    }

    return NULL;  // Missing closing double quote
}

Token* processSingleQuotes(const char* input, int* index) {
    char singleQuotes[MAX_TOKEN_LENGTH];
    int j = 0;

    (*index)++;  // Skip the opening single quote
    while (input[*index] != '\'' && input[*index] != '\0') {
        singleQuotes[j++] = input[(*index)++];
    }

    if (input[*index] == '\'') {
        singleQuotes[j] = '\0';
        (*index)++;  // Skip the closing single quote

        Token* token = createToken(TOKEN_SINGLE_QUOTES, singleQuotes);
        return token;
    }

    return NULL;  // Missing closing single quote
}

Token* lexer(const char* input) {
    Token* tokens = NULL;
    Token* current = NULL;
    int i = 0;

    while (input[i] != '\0') {
        while (input[i] == ' ' || input[i] == '\t') {
            i++;
        }

        if (isalpha(input[i]) || input[i] == '$') {
            current = processWord(input, &i);
            if (tokens == NULL) {
                tokens = current;
            }
        } else if (input[i] == '|') {
            current = processPipe();
        } else if (input[i] == '<') {
            current = processInputRedirect();
        } else if (input[i] == '>') {
            current = processOutputRedirect();
        } else if (input[i] == '"') {
            current = processDoubleQuotes(input, &i);
        } else if (input[i] == '\'') {
            current = processSingleQuotes(input, &i);
        }
    }

    return tokens;
}

// Token* lexer(const char* input) {
//     Token* tokens = NULL;
//     Token* current = NULL;
//     int i = 0;

//     while (input[i] != '\0') {
//         while (input[i] == ' ' || input[i] == '\t') {
//             i++;
//         }

//         int j = 0;
//         while (input[i] != ' ' && input[i] != '\t' && input[i] != '\0') {
//             j++;
//             i++;
//         }

//         if (j > 0) {
//             char word[MAX_TOKEN_LENGTH];
//             ft_strncpy(word, input + i - j, j);
//             word[j] = '\0';

//             if (word[0] == '$') {
//                 if (current) {
//                     current->next = createToken(TOKEN_ENV_VARIABLE, word);
//                     current = current->next;
//                 } else {
//                     tokens = createToken(TOKEN_ENV_VARIABLE, word);
//                     current = tokens;
//                 }
//             } else {
//                 if (current) {
//                     current->next = createToken(TOKEN_WORD, word);
//                     current = current->next;
//                 } else {
//                     tokens = createToken(TOKEN_WORD, word);
//                     current = tokens;
//                 }
//             }
//         } else if (input[i] == '|') {
//             if (current) {
//                 current->next = createToken(TOKEN_PIPE, "|");
//                 current = current->next;
//             } else {
//                 tokens = createToken(TOKEN_PIPE, "|");
//                 current = tokens;
//             }
//             i++;
//         } else if (input[i] == '<') {
//             if (current) {
//                 current->next = createToken(TOKEN_INPUT_REDIRECT, "<");
//                 current = current->next;
//             } else {
//                 tokens = createToken(TOKEN_INPUT_REDIRECT, "<");
//                 current = tokens;
//             }
//             i++;
//         } else if (input[i] == '>') {
//             if (input[i + 1] == '>') {
//                 if (current) {
//                     current->next = createToken(TOKEN_APPEND_REDIRECT, ">>");
//                     current = current->next;
//                 } else {
//                     tokens = createToken(TOKEN_APPEND_REDIRECT, ">>");
//                     current = tokens;
//                 }
//                 i += 2;
//             } else {
//                 if (current) {
//                     current->next = createToken(TOKEN_OUTPUT_REDIRECT, ">");
//                     current = current->next;
//                 } else {
//                     tokens = createToken(TOKEN_OUTPUT_REDIRECT, ">");
//                     current = tokens;
//                 }
//                 i++;
//             }
//         } else if (input[i] == '"') {
//             char doubleQuotes[MAX_TOKEN_LENGTH];
//             j = 0;
//             i++;
//             while (input[i] != '"' && input[i] != '\0') {
//                 doubleQuotes[j++] = input[i++];
//             }
//             if (input[i] == '"') {
//                 doubleQuotes[j] = '\0';
//                 if (current) {
//                     current->next = createToken(TOKEN_DOUBLE_QUOTES, doubleQuotes);
//                     current = current->next;
//                 } else {
//                     tokens = createToken(TOKEN_DOUBLE_QUOTES, doubleQuotes);
//                     current = tokens;
//                 }
//                 i++;
//             }
//         } else if (input[i] == '\'') {
//             char singleQuotes[MAX_TOKEN_LENGTH];
//             j = 0;
//             i++;
//             while (input[i] != '\'' && input[i] != '\0') {
//                 singleQuotes[j++] = input[i++];
//             }
//             if (input[i] == '\'') {
//                 singleQuotes[j] = '\0';
//                 if (current) {
//                     current->next = createToken(TOKEN_SINGLE_QUOTES, singleQuotes);
//                     current = current->next;
//                 } else {
//                     tokens = createToken(TOKEN_SINGLE_QUOTES, singleQuotes);
//                     current = tokens;
//                 }
//                 i++;
//             }
//         }
//     }

//     return tokens;
// }

int main(int ac, char **av) {
    
    (void) ac;
    Token* tokens = lexer(av[1]);

    Token* current = tokens;
    while (current != NULL) {
        printf("Token type: %d, value: %s\n", current->type, current->value);
        current = current->next;
    }

    freeTokens(tokens);

    return 0;
}