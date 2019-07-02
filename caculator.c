#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "operand.h"


enum EvalResult_t {
    EVAL_SUCCESS,
    EVAL_SYNTAX_ERROR
};
typedef enum EvalResult_t EvalResult;

struct Result_t {
    EvalResult status;
    uint32_t result;
};
typedef struct Result_t Result;

char* read_prompt() {
    static char* buffer;
    static size_t length;
    ssize_t input = getline(&buffer, &length, stdin);
    return buffer;
}

Result* eval_expr(char* operation) {
    uint32_t i;
    OperandNode* operandList = NULL;
    char digits[1024];
    memset(digits, 0, 1024);

    for (i = 0; i < strlen(operation) - 1; i++) {
        if (isdigit(operation[i])) {
            memset(digits, 0, 1024);
            int j = 0;
            while (isdigit(operation[i])) {
                strncpy(&digits[j], &operation[i], 1);
                i++;
                j++;
            }

            Operand* operand = malloc(sizeof(Operand));
            operand->value = strdup(digits);
            operand->type = OPERAND_INT;
            append(&operandList, operand);

            i--;
        } else {
            if (operation[i] == '+') {
                Operand* operand = malloc(sizeof(Operand));
                operand->value = strdup("+");
                operand->type = OPERAND_PLUS;
                append(&operandList, operand);
            }
            else {
                continue;
            }
        }
    }

    Result* result = malloc(sizeof(Result));
    result->status = EVAL_SUCCESS;
    result->result = 0;

    OperandNode* cursor = operandList;
    if (*cursor->value->value == '+') {
        result->status = EVAL_SYNTAX_ERROR;
        return result;    
    }

    while (cursor != NULL && cursor->next != NULL) {
        
        if (*cursor->value->value == '+' && *cursor->next->value->value == '+') {
            result->status = EVAL_SYNTAX_ERROR;
            return result;
        } else if (*cursor->value->value != '+' && *cursor->next->value->value != '+'){
            result->status = EVAL_SYNTAX_ERROR;
            return result;
        } else {
            result->result += strtol(cursor->value->value, NULL, 10);
        }
        cursor = cursor->next;
    }

    if (*cursor->value->value == '+') {
        result->status = EVAL_SYNTAX_ERROR;
        return result;
    } else {
        result->result += strtol(cursor->value->value, NULL, 10);
    }

    return result;
}


int main(int argc, char** argv) {
    while (true) {
        printf("> ");

        char* operation = read_prompt();
        Result* result = eval_expr(operation);

        if (result->status == EVAL_SUCCESS) {
            printf("%u\n", result->result);
        } else {
            printf("Syntax error\n");
        }

        free(result);
    }
}