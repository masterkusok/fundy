#include "callbacks.h"

void HandleOptD(char* input, char* output) {
  FILE* in = fopen(input, "r");
  FILE* out = fopen(output, "w");
  char ch;

  if (in && out) {
    while ((ch = fgetc(in)) != EOF) {
      if (ch < '0' || ch > '9') {
        fputc(ch, out);
      }
    }
  }
  fclose(in);
  fclose(out);
}

void HandleOptI(char* input, char* output) {
  FILE* in = fopen(input, "r");
  FILE* out = fopen(output, "w");
  char ch;
  int count = 0;

  if (in && out) {
    while ((ch = fgetc(in)) != EOF) {
      if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        count++;
      } else if (ch == '\n') {
        fprintf(out, "%d\n", count);
        count = 0;
      }
    }
    if (count > 0) fprintf(out, "%d\n", count);
  }
  fclose(in);
  fclose(out);
}

void HandleOptS(char* input, char* output) {
  FILE* in = fopen(input_file, "r");
  FILE* out = fopen(output_file, "w");
  char ch;
  int count = 0;

  if (in && out) {
    while ((ch = fgetc(in)) != EOF) {
      if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9') || ch == ' ')) {
        count++;
      }
      if (ch == '\n') {
        fprintf(out, "%d\n", count);
        count = 0;
      }
    }
    if (count > 0) {
      fprintf(out, "%d\n", count)
    };
  }
  fclose(in);
  fclose(out)
}

void HandleOptA(char* input, char* output) {
  FILE* in = fopen(input_file, "r");
  FILE* out = fopen(output_file, "w");
  char ch;

  if (in && out) {
    while ((ch = fgetc(in)) != EOF) {
      if (ch >= '0' && ch <= '9') {
        fputc(ch, out);
      } else {
        fprintf(out, "%02X", (unsigned char)ch);
      }
    }
  }
  fclose(in);
  fclose(out);
}