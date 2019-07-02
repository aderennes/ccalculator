#ifndef OPERAND_H
#define OPERAND_H

enum OperandType_t { 
    OPERAND_INT,
    OPERAND_PLUS
};
typedef enum OperandType_t OperandType;

struct Operand_t {
    OperandType type;
    char* value;
};
typedef struct Operand_t Operand;

struct OperandNode_t {
    Operand* value;
    struct OperandNode_t* next;
};
typedef struct OperandNode_t OperandNode;

void append(OperandNode** root, Operand* operand);

#endif