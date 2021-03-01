// У завданні потрібно сформувати вихідний рядок із вхідного,
// шляхом заміни послідовностей %s, %n, %с вхідного рядка значенням
// із вказівника value (одного тогож самого для всіх форматів),
// який потрібно трактувати відповідно до формату.
// Забороняється використовувати будь-які функції стандартної бібліотеки.
// Також будь ласка не змінюйте нічого у файлі окрім тіла функції sprintf_m().
// Формат типу може зустрічатися декілька разів, наприклад "The ASCII code of
// '%c' is %n", aле підставляти потрібно одне і те саме значення value. Функці
// очікує коректні вхідні данні не треба робити ніяких перевірок або
// реалізовувати escape послідовності.

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *sprintf_m(const char *format, const void *value) {

static char buff[256] = {0};
const char *ptr = &buff[0];
const char *v = (const char *)value;
int i = 0, j = 0, k = 0;
uint8_t n = 0;
char c = '\0';
int wher[100] = {0};
int cnt = 0;

	for (i = 0; format[i] != '\0'; i++);
  	int fmt_len = i;

	for (i = 0; i < fmt_len - 1; i++) {
		if (format[i] == '%') {
		wher[cnt] = i;
      		// printf("%d\n",wher[cnt]);
		if (format[i + 1] == 's') {

        	k = 0;
        	if (cnt >= 1)
          	k = wher[cnt - 1] + j;
        	printf("k = %d\n", k);
        	while (k < (wher[cnt] + j)) {
          	buff[k] = format[k - j];
          	// printf("form = %c\n",format[k]);
          	k++;
        	}
        	for (j = 0; v[j] != '\0'; j++) {
          	*(buff + wher[cnt] + j) = v[j];
        	}
        	cnt++;

        	continue;
      		} else if (format[i + 1] == 'n') {

        	k = 0;
        	if (cnt >= 1)
		k = wher[cnt - 1] + j;
        	//printf("k = %d\n", k);
		while (k < (wher[cnt] + j)) {
          	buff[k] = format[k - j];
          	// printf("form = %c\n",format[k]);
          	k++;
        	}
		n = *(const uint8_t *)value;
		int hund = n / 100;
		int dec = (n - hund * 100) / 10;
		int val = (n - hund * 100 - dec * 10);
		*(buff + wher[cnt] + j) = (hund + 48);
		*(buff + wher[cnt] + 1 + j) = (dec + 48);
		*(buff + wher[cnt] + 2 + j) = (val + 48);
		cnt++;
		continue;

      		} else if (format[i + 1] == 'c') {
        	k = 0;
        	if (cnt >= 1)
         	k = wher[cnt - 1];
        	// printf("k = %d\n",k);
        	while (k < wher[cnt]) {
          	buff[k] = format[k];
          	// printf("form = %c\n",format[k]);
          	k++;
        	}
        	c = *(const char *)value;
        	*(buff + wher[cnt]) = c;
        	cnt++;
        	continue;
      		}
    	}
  }

  return ptr;
}

// Function usage examples:
int main(int argc, char *argv[]) {

  const char *formatS = "Hello %s %s!";
  const char *world = "World";

  const char *formatN = "Value: %n %n";
  const uint8_t a = 142;

  const char *formatC = "Char: %c %c";
  const char c = 'P';

  const char *result;
  result = sprintf_m(formatC, (const void *)&c);
  printf("%s\n", result); // should print: Char: P

  result = sprintf_m(formatN, (const void *)&a);
  printf("%s \n", result); // should print: Value: 42

  result = sprintf_m(formatS, (const void *)world);
  printf("%s\n", result); // should print: Hello World!

  return 0;
}
