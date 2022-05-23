# Лабораторная работа 1. Атомарные снимки, блокировки

# Задание

В данной работе вы должны выбрать подтему по своему желанию. 
После выбора выберите свой вариант по своему номеру в списке группы 
(по формуле `k mod N + 1`, где `k` ваш номер, `N` – общее число вариантов)

## Атомарные снимки

1. Реализовать алгоритм атомарного снимка 
(языки: `C++/C` желательно, `Java` допускается, но хуже)
2. Разработать простой тест
3. Оценить эффективность, построить графы, проанализировать, сформулировать выводы.
4. Написать отчет с результатами экспериментов и выводами.

#### Задание на "4" (максимальная оценка 4)

Атомарный снимок без ожиданий из лекций

#### Tasks for "5" (maximum mark is 5)

Практический атомарный снимок, описанный в литературе 
(посмотреть на scholar.google.com)

## Блокировки

1. Реализовать алгоритм блокировки потоков 
(языки: `C++/C` желательно, `Java` допускается, но хуже)
2. Разработать простой тест
3. Оценить эффективность, построить графы, проанализировать, сформулировать выводы.
4. Написать отчет с результатами экспериментов и выводами.

### Варианты заданий

#### Задание на "4" (максимальная оценка “4”) – варианты выбираются по номеру студента:

1. TS, TTS, Backoff-lock
2. CLH-lock
3. MCS-lock

#### Задание на "5" (максимальная оценка 5) – здесь варианты выбираются по желанию:

1. Flat-combining (сравнить с CLH, MCS)
2. Remote Core Locking или другая блокировка на основе делегирования
3. Lock cohorting
4. Persistent lock (если у вас есть энергонезависимая память)
5. Ваш вариант: любая интересный алгоритм блокировки (согласовать с преподавателем)

# Реализация

...