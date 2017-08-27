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

#define APP_VERSION "0.1.0"

/* Прототипы функций */
void versionCommand(void);
void helpCommand(void);

//Декларация массива валидных флагов
const char * const allowedFlags[] = { "--version", "--help" };

//Mapping - карта функций, массив указателей на функции
void(*commandsStore[])(void) = { versionCommand, helpCommand };

//Вычисление размера массива валидных флагов
const unsigned int const allowedFlagsLength = sizeof allowedFlags / sizeof allowedFlags[0];

//Функция сравнения валидных и не валидных флагов
void validateFlags(const char * const flags[], const int const length)
{
  int incorrectFlagIndex = -1; //В эту переменную будет сохранен индекс массива некорректного флага
  int i, j;
  //Первый цикл проходит по массиву флагов которые мы передаем из командной строки
  for (i = 1; i < length; i++)
    {
      //Второй вложенный цикл проходит по массиву задекларированных флагов
      for (j = 0; j < allowedFlagsLength; j++)
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

// Функция запуска команд после валидации
void invokeCommands(const char * const commands[], unsigned int count)
{
  int i, j;
  // сравниваем массивы флагов прошедших валидачию и массив комманд для запуска
  for(i = 1; i < count; i++)
    {
      for(j = 0; j < allowedFlagsLength; j++)
        {
          if(strcmp (commands[i], allowedFlags[j]) == 0)
            {
              commandsStore[j](); // передаем массив функций
            }
        }
    }
}

/* Функция обработки флага version */
void versionCommand(void)
{
  printf("Programm version: %s", APP_VERSION);
}

/* Функция обработки флага version */
void helpCommand(void)
{
  printf("Help command invoke!");
}

int main(const int const argc, const char * const argv[])
{
  if (argc > 1) validateFlags(argv, argc);
  else printf(AC_GREEN "[+] Congratulations!%s\n", AC_RESET);

  invokeCommands(argv, argc);

  printf("\n");

  return EXIT_SUCCESS;
}