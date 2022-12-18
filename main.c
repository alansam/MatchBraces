/*
	program to check if braces matches or not
*/

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAXSIZE 100

char stack[MAXSIZE];
int top = 0;

void empty(void);
void push(char);
char pop(void);
bool is_full(void);
bool is_empty(void);
void stack_overflow(void);
void stack_underflow(void);

int main() {
    char ch;

    while((ch = getchar()) != '\n' ) {

        switch(ch) {
            case '}':
                if (pop() == '{') {
                    break;
                } else {
                    printf("Parentheses and/or braces doesnt matches."); return 0;
                }
            case ')':
                if (pop() == '(') {
                    break;
                } else {
                    printf("Parentheses and/or braces doesnt matches."); return 0;
                }
            default: push(ch);
        }
    }

    if (top == 0) {
        printf("Parentheses and/or braces matches.");
    } else {
        printf("Parentheses and/or braces doesnt matches.");
    }

    return 0;
}
void empty(void) {
    top = 0;
}

void push(char ch) {
    if (is_full()) {
        stack_overflow();
    } else {
        stack[top++] = ch;
    }
}

char pop(void) {
    if(is_empty()) {
        stack_underflow();
    } else {
        return stack[--top];
    }
}

bool is_empty(void) {
    return top == 0;
}

bool is_full(void) {
    return top == MAXSIZE;
}

void stack_overflow(void) {
    if (top == MAXSIZE) {
        printf("Stack overflow");
		exit(EXIT_SUCCESS);
	}
}

void stack_underflow(void) {
    if (top == 0) {
        printf("Stack underflow");
		exit(EXIT_SUCCESS);
	}
}
