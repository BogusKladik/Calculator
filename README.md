# Calculator

Все операции: 
1) Для листов или очередей: алгебра(+, -, *, /, ^, ! - дефолтные; \ - деление нацело, # - остаток от деления), векторы(+, - - дефолтные; с - скалярное произведение)
2) Для стека(обратной польской нотации): алгебра(+, -, *, /, ^, ! - дефолтные)

Пример заполнения строки для листов или очередей:

1) Сначало пишем какой калькулятор использовать (a - для алгебрый, v - для векторов)
2) Если вектора, то пишем размер векторов, иначе ничего сюда не пишем
3) Пишем первое число, либо через пробел первый вектор
4) Пишем операцию
5) Если знак операции ! ничего не пишем, иначе второе число или второй вектор
6) Пишем знак продолжения вычислений (y - продолжить, n - закончить)

Пример заполнения строки для стека(обратной польской нотации):

1) Пишется сложное выражение, не важно через пробелы или нет
2) В конце строки пишется или 'y' или 'n' для того, чтобы продолжить ывчисление из этого файла или окончить
