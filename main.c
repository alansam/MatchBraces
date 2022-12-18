/*
 * program to check if delimiters {([])} match or not
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXSIZE 4096

// char stack[MAXSIZE];
static
char * stack = NULL;
static
int top = 0;

void empty(void);
void push(char);
char pop(void);
bool is_full(void);
bool is_empty(void);
void stack_overflow(void);
void stack_underflow(void);
void clean_death(int RC);

char const * const msg_success = "Delimiters match.";
char const * const msg_failure = "Delimiters don't match.";

//  MARK: main()
int main(int argc, char const * argv[]) {
  int RC = EXIT_SUCCESS;
  char ch;

  stack = malloc(MAXSIZE);
  if (stack == NULL) {
    puts("Unable to allocate memory for stack.");
    clean_death(EXIT_FAILURE);
  }

  while ((ch = getchar()) != EOF ) {
    //  embed delimiters inside comments so this
    //  source can be used to test the program
    switch(ch) {
    case /* { */ '}':
      if (pop() != '{' /* } */) {
        puts(msg_failure);
        puts("GRONK! B");
        clean_death(EXIT_FAILURE);
      }
      break;

    case /* ( */ ')':
      if (pop() != '(' /* ) */) {
        puts(msg_failure);
        puts("GRONK! P");
        clean_death(EXIT_FAILURE);
      }
      break;

    case /* [ */ ']':
      if (pop() != '[' /* ] */) {
        puts(msg_failure);
        puts("GRONK! S");
        clean_death(EXIT_FAILURE);
      }
      break;

    case '{': /* } */
    case '(': /* ) */
    case '[': /* ] */
      push(ch);
      break;

    default:
      break;
    }
  }

  if (top == 0) {
    puts(msg_success);
    RC = EXIT_SUCCESS;
  }
  else {
    puts(msg_failure);
    RC = EXIT_FAILURE;
  }

  if (stack != NULL) {
    free(stack);
    stack = NULL;
  }

  return RC;
}

//  MARK: empty()
void empty(void) {
  top = 0;
}

//  MARK: push()
void push(char ch) {
  if (is_full()) {
    stack_overflow();
  }
  else {
    stack[top++] = ch;
  }
}

//  MARK: pop()
char pop(void) {
  if(is_empty()) {
    stack_underflow();
    return '\0';
  }
  else {
    return stack[--top];
  }
}

//  MARK: is_empty()
bool is_empty(void) {
  return top == 0;
}

//  MARK:  is_full()
bool is_full(void) {
  return top == MAXSIZE;
}

//  MARK: stack_overflow()
void stack_overflow(void) {
  if (top == MAXSIZE) {
    puts("Stack overflow");
    clean_death(EXIT_FAILURE);
	}
}

//  MARK: stack_underflow()
void stack_underflow(void) {
  if (top == 0) {
    puts("Stack underflow");
    clean_death(EXIT_FAILURE);
	}
}

//  MARK: clean_death()
void clean_death(int RC) {
  if (stack != NULL) {
    free(stack);
    stack = NULL;
  }
  exit(RC);
}
