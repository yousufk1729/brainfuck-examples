#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compile_brainfuck(const char* bf_code, FILE* output) {
  fprintf(output, "#include <stdio.h>\n");
  fprintf(output, "#include <stdlib.h>\n");
  fprintf(output, "#include <string.h>\n\n");
  fprintf(output, "int main() {\n");
  fprintf(output, "  char memory[30000];\n");
  fprintf(output, "  char* p = memory;\n");
  fprintf(output, "  memset(memory, 0, 30000);\n");
  for (int i = 0; bf_code[i] != '\0'; i++) {
    switch (bf_code[i]) {
      case '>':
        fprintf(output, "  ++p;\n");
        break;
      case '<':
        fprintf(output, "  --p;\n");
        break;
      case '+':
        fprintf(output, "  ++*p;\n");
        break;
      case '-':
        fprintf(output, "  --*p;\n");
        break;
      case '.':
        fprintf(output, "  putchar(*p);\n");
        break;
      case ',':
        fprintf(output, "  *p = getchar();\n");
        break;
      case '[':
        fprintf(output, "  while (*p) {\n");
        break;
      case ']':
        fprintf(output, "  }\n");
        break;
      default:
        break;
    }
  }
  fprintf(output, "return 0;\n");
  fprintf(output, "}\n");
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Usage: %s <input.bf> <output.c>\n", argv[0]);
    return 1;
  }

  FILE* input = fopen(argv[1], "r");
  if (!input) {
    return 1;
  }

  fseek(input, 0, SEEK_END);
  long length = ftell(input);
  fseek(input, 0, SEEK_SET);
  char* bf_code =
      malloc(length + 1);  // almost forgot about null-terminated strings
  fread(bf_code, 1, length, input);
  bf_code[length] = '\0';
  fclose(input);

  FILE* output = fopen(argv[2], "w");
  if (!output) {
    free(bf_code);
    return 1;
  }

  compile_brainfuck(bf_code, output);
  fclose(output);
  free(bf_code);

  return 0;
}