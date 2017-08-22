#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AC_RED     "\x1b[31;1m"
#define AC_GREEN   "\x1b[32;45;1m"
#define AC_YELLOW  "\x1b[33;1m"
#define AC_BLUE    "\x1b[34;1m"
#define AC_MAGENTA "\x1b[35;1m"
#define AC_CYAN    "\x1b[36;1m"
#define AC_RESET   "\x1b[0m"

//Декларация массива валидных флагов
const char * const allowedFlags[] = { "--size", "--sort", "--antg" };

//Вычисление размера массива валидных флагов
const unsigned int const allowedFlagsLength = sizeof allowedFlags / sizeof allowedFlags[0];

//Функция сравнения валидных и не валидных флагов
void validateFlags(const char * const flags[], const int const length)
{
  int incorrectFlagIndex = -1; //В эту переменную будет сохранен индекс массива некорректного флага

  //Первый цикл проходит по массиву флагов которые мы передаем из командной строки
  for (int i = 1; i < length; i++)
    {
      //Второй вложенный цикл проходит по массиву задекларированных флагов
      for (int j = 0; j < allowedFlagsLength; j++)
        {
          //Сравниваем флаги введенные из командной строки и задекларированные в массиве
          if (strcmp(flags[i], allowedFlags[j]) == 0)
            {
              incorrectFlagIndex = -1;
              break;
            }
          else { incorrectFlagIndex = i; }
        }

      //Если флаг не валидный, сказать об этом и выйти из программы
      if (incorrectFlagIndex > -1)
        {
          printf(AC_RED "[-] Error: %s incorrect flag was given!%s\n" , flags[incorrectFlagIndex], AC_RESET);
          exit(EXIT_FAILURE);
        }
    }
}

int main(const int const argc, const char * const argv[])
{
  if (argc > 1) validateFlags(argv, argc);

  printf(AC_GREEN "[+] Congratulations!%s\n", AC_RESET);

  return EXIT_SUCCESS;
}