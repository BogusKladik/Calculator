#if !defined(stackh)
#define stackh

typedef struct numbers
{ // Очередь для чисел
	double num;
	struct numbers *next;
} numbers;

typedef struct operations
{ // Очередь для операций
	char operation;
	struct operations *next;
} operations;

typedef struct links_for_stacks
{ // Структура всех ссылок
	numbers *head_n;
	operations *head_o;
} links_for_stacks;

double pop_n(links_for_stacks *link);// Удалить из стека чисел

char pop_o(links_for_stacks *link);// Удалить из стека операций

void delete_n(links_for_stacks *link);// Удалить весь стек номеров

void delete_o(links_for_stacks *link);// Удалить весь стек операций

void push_back_n(double data, links_for_stacks *link);// Добавить в конец стека с номерами

void push_back_o(char data, links_for_stacks *link);// Добавить в конец стека с операциями

#endif // stackh
