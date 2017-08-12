#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Декларация массива валидных флагов
const char * const allowedFlags[] = { "--size", "--sort", "--antg" };

//Вычисление размера массива валидных флагов
const unsigned int const allowedFlagsLength = sizeof allowedFlags / sizeof allowedFlags[0];

//Функция сравнения валидных и не валидных флагов
void validateFlags(const char * const flags[], const int const length)
{
  bool flagExists; //Переменная состояния флага
  int incorrectFlagIndex = -1; //В эту переменную будет сохранен индекс массива некорректного флага

  //Первый цикл проходит по массиву флагов которые мы передаем из командной строки
  for (int i = 1; i < length; i++)
    {
      flagExists = false; // Обнуляем состояние флага при каждой итерации цикла

      //Второй вложенный цикл проходит по массиву задекларированных флагов
      for (int j = 0; j < allowedFlagsLength; j++)
        {
          //Сравниваем флаги введенные из командной строки и задекларированные в массиве
          if (strcmp(flags[i], allowedFlags[j]) == 0)
            {
              flagExists = true;
              incorrectFlagIndex = -1;
            }
          else { incorrectFlagIndex = i; }
        }

      //Если флаг не валидный, сказать об этом и выйти из программы
      if (!flagExists && incorrectFlagIndex > -1)
        {
          printf("[-] Error: %s incorrect flag was given!\n", flags[incorrectFlagIndex]);
          exit(EXIT_FAILURE);
        }
    }
}

int main(const int const argc, const char * const argv[])
{
  if (argc > 1) validateFlags(argv, argc);

  printf("[+] Congratulations!\n");

  return EXIT_SUCCESS;
}