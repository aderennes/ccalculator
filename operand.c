#include <stdlib.h>
#include "operand.h"

void append(OperandNode** root, Operand* operand){
    OperandNode* new = malloc(sizeof(OperandNode));
    new->value = operand;
    new->next = NULL;

    if (*root == NULL) {
        *root = new;
    } else {    
        OperandNode* cursor = *root;
        while (cursor->next != NULL) {
            cursor = cursor->next;
        }
        cursor->next = new;
    }
}