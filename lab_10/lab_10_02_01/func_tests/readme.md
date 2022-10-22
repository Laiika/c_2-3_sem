# Тесты для лабораторной работы №10, задача №2

## Входные данные
Строка - команда, целые числа

## Выходные данные
Целые числа

## Позитивные тесты:
- 01 - обычный полином (val);
- 02 - полином - число (val);
- 03 - переменная - 0 (val);
- 04 - обычный полином (ddx);
- 05 - обычные полиномы (sum);
- 06 - в полиноме есть четные и нечетные степени (dvd).

## Негативные тесты:
- 01 - один из коэффициентов - не число;
- 02 - неверное название команды;
- 03 - одна из степеней - не число;
- 04 - переменная - не число (val);
- 05 - ввод пустой;
- 06 - все коэффициенты - 0;
- 07 - полином - число (ddx);
- 08 - нет четных степеней (dvd);
- 09 - нет нечетных степеней (dvd);
- 10 - новая степень больше предыдущей;
- 11 - степень меньше 0;
- 12 - степень не указана.