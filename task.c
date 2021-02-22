// У завданні потрібно сформувати вихідний рядок із вхідного,
// шляхом заміни послідовностей %s, %n, %с вхідного рядка значенням
// із вказівника value (одного тогож самого для всіх форматів),
// який потрібно трактувати відповідно до формату.
// Забороняється використовувати будь-які функції стандартної бібліотеки.
// Також будь ласка не змінюйте нічого у файлі окрім тіла функції sprintf_m().
// Формат типу може зустрічатися декілька разів, наприклад "The ASCII code of
// '%c' is %n", aле підставляти потрібно одне і те саме значення value. Функція
// очікує коректні вхідні данні не треба робити ніяких перевірок або
// реалізовувати escape послідовності.

#include <stdint.h>
#include <stdio.h>

// const char format[] - contains the format string
// void *value - is a value to insert instead of %s, %n or %c placeholder
// the function should return the result in C-string format.
// format string samples: "Hello %s!", "Value :%n", "Character :%c"
//
// %s - C-string is passed in void *value
// %n - 1 byte unsigned number (uint8_t) is passed in void *value
// %c - a character is passed in void *value

enum flag_type {
  char_t = 1,
  uint_t = 2,
  str_t = 3,
};

int strlen(const char *s) {
  int i;
  for (i = 0; s[i] != '\0'; i++);
  
  return i;
}

int rempart(char *format) {
  uint8_t var = 0;
  char *remove;
  int flag = 0;

  for (; *format != '\0'; *format++) {
  
    printf("%c  ", *format);
    
    if (*format == '%') {
    
      printf("Yes\n");
      var = 1;
      continue;
    }
    
    if (var == 1) {
    
      switch (*format) {
      
      case 's':
        printf("string\n");
        var = 0;
        flag = str_t;
        break;
        
      case 'n':
        printf("uint8\n");
        var = 0;
        flag = uint_t;
        break;
        
      case 'c':
        printf("char\n");
        var = 0;
        flag = char_t;
        break;
        
      default:
        printf("No\n");
      }
    }
  }
  return flag;
}

int where_to_chan(char *str, char *substr) {
  uint8_t flag = 0;
  int start = 0;
  int i = 0, j = 0;

  while (*str != '\0') {
    if (*(str + i) == *(substr + j)) {
    
      if (!flag)
        start = i;
      
      j++;

      if (*(substr + j) == '\0')
        break;

      flag = 1;

    } else {

      flag = start = j = 0;
    }

    i++;
  }

  return start;
}

/*const char * */ void sprintf_m(const char *format, const void *value) {
  const char *repl_string = *(char *)value;
  char *remstr;
  int flag = rempart(*repl_string);
  char *buffer;

  switch (flag) {
  case 1:
    *remstr = "%c";
    break;
  case 2:
    *remstr = "%n";
    break;
  case 3:
    *remstr = "%s";
    break;
  default:
    printf("error\n");
  }

  int d = where_to_chan(*remstr, *repl_string);
  int i, j;

  for (i = 0; i < d; i++)
    *(buffer + i) = *(format + i);

  for (j = 0; j < 2; j++) {
    *(buffer + i) = *(remstr + j);
    i++;
  }

  for (j = d + strlen(repl_string); j < strlen(format); j++) {

    *(buffer + i) = *(format + j);
    
    i++;
  }

  *(buffer + i) = '\0';

  return *buffer;
}

// Function usage examples:
int main(int argc, char *argv[]) {

  const char *formatS = "Hello %s!";
  const char *world = "World";

  const char *formatN = "Value: %n";
  const uint8_t a = 42;

  const char *formatC = "Char: %c";
  const char c = 'P';

  const char *result;
  result = sprintf_m(formatC, (const void *)&c);
  printf("%s\n", result); // should print: Char: P

  result = sprintf_m(formatN, (const void *)&a);
  printf("%s\n", result); // should print: Value: 42

  result = sprintf_m(formatS, (const void *)world);
  printf("%s\n", result); // should print: Hello World!

  return 0;
}
