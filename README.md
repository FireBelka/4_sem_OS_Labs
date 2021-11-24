# laboratory on the subject of operating systems(С++)
## Lab 1
- Задача: 
Написать консольную программу Main и две утилиты (служебные программы) Creator и Reporter, которые выполняют следующие действия.
- Утилита Creator создает бинарный файл, имя которого и количество записей в котором получает через командную строку. Записи файла вводятся с консоли и имеют следующую структуру:   
struct employee   
{   
int num; // идентификационный номер сотрудника    
char name[10]; // имя сотрудника    
double hours; // количество отработанных часов    
};    
- Утилита Reporter создает текстовый файл, содержащий упорядоченный список сотрудников с начисленной заработной платой. Отчет формируется на основе бинарного файла, созданного программой Creator.
1. Утилита получает через командную строку следующие данные:  
1.1. Имя исходного бинарного файла.  
1.2. Имя файла отчета.  
1.3. Оплата за час работы.
2. Отчет содержит следующие строки:  
2.1. Заголовок: Отчет по файлу «имя исходного бинарного файла».  
2.2. Строка: Номер сотрудника, имя сотрудника, часы, зарплата.  
2.3. Список сотрудников по строкам. Каждая строка содержит информацию из
соответствующей записи бинарного файла, а последний столбец строки -
начисленную зарплату = кол-ву отработанных часов * оплату за час работы.
Программа Main выполняет следующие действия:
1. Запрашивает с консоли имя бинарного файла и количество записей в этом файле.
2. Запускает утилиту Creator, которой передает через командную строку имя
создаваемого бинарного файла и количество записей в этом файле.
3. Ждет завершения работы утилиты Creator.
4. Выводит содержимое созданного бинарного файла на консоль.
5. Запрашивает с консоли:
a. Имя файла отчета.
b. Оплату за час работы.
6. Запускает утилиту Reporter, которой передает через командную строку:
a. Имя исходного бинарного файла.
b. Имя файла отчета.
c. Оплату за час работы.
7. Ждет завершения работы утилиты Reporter.
8. Выводит отчет на консоль.
9. Завершает свою работу.
## Lab 2
- Задача. Написать программу для консольного процесса, который состоит из трех потоков: main,
min_max и average.
- Поток main должен выполнить следующие действия:
1. Создать массив целых чисел, размерность и элементы которого вводятся с консоли.
2. Создать потоки min_max и average.
3. Дождаться завершения потоков min_max и average.
4. Заменить максимальный и минимальный элементы массива на среднее значение элементов
массива. Вывести полученные результаты на консоль.
5. Завершить работу.    

- Поток min_max должен выполнить следующие действия:
1.  Найти минимальный и максимальный элементы массива и вывести их на консоль. После
каждого сравнения элементов «спать» 7 миллисекунд.
2.  Завершить свою работу.   

- Поток average должен выполнить следующие действия:
1.  Найти среднее арифметическое значение элементов массива и вывести его на консоль.
После каждой операции суммирования элементов «спать» 12 миллисекунд.
2.  Завершить свою работу

## Lab3
- Задача. Написать программу для консольного процесса, который состоит из потока main и
нескольких экземпляров потока marker.   
- Поток main должен выполнять следующие действия:
1. Захватить память под массив целых чисел, размерность которого вводится с консоли.
2. Инициализировать элементы массива нулями.
3. Запросить количество потоков marker, которые требуется запустить.
4. Запустить заданное количество экземпляров потока marker. В качестве параметра
каждому экземпляру потока marker передать его порядковый номер в запуске.
5. Дать сигнал на начало работы всех потоков marker.
6. Выполнять в цикле следующие действия:  
6.1. Ждать, пока все потоки marker не подадут сигналы о невозможности продолжения своей работы.  
6.2. Вывести содержимое массива на консоль.  
6.3. Запросить с консоли порядковый номер потока marker, которому будет подан сигнал на завершение своей работы.  
6.4. Подать потоку marker, номер которого получен в пункте 6.3, сигнал на завершение работы.  
6.5. Ждать завершение работы потока marker, которому был подан сигнал на завершение работы в пункте 6.4.  
6.6. Вывести содержимое массива на консоль.  
6.7. Подать сигнал на продолжение работы, оставшимся потокам marker.
7. Завершить свою работу после завершения работы всех потоков marker.   
- Поток marker должен выполнять следующие действия:
1. Начать работу по сигналу от потока main.
2. Инициализировать генерацию последовательности случайных чисел. Для этого
использовать функцию srand, которой передать в качестве аргумента свой
порядковый номер.
3. Работать циклически, выполняя на каждом цикле следующие действия:    
3.1. Генерировать случайное число, используя функцию rand.    
3.2. Разделить это число по модулю на размерность массива.    
3.3. Если элемент массива, индекс которого равен результату деления, равен нулю, то
выполнить следующие действия:   
3.3.1. Поспать 5 миллисекунд.    
3.3.2. Занести в элемент, индекс которого вычислен, свой порядковый номер.    
3.3.3. Поспать 5 миллисекунд.   
3.3.4. Продолжить исполнение цикла 3.   
3.4. В противном случае:    
3.4.1. Вывести на консоль следующую информацию:   
 -- свой порядковый номер;    
 -- количество помеченных элементов;    
 -- индекс элемента массива, который невозможно пометить.   
3.4.2. Дать сигнал потоку main на невозможность продолжения своей работы.   
3.4.3. Ждать ответный сигнал на продолжение или завершение работы от потока
main.   
4. Если получен сигнал на завершение работы, то выполнить следующие действия:   
4.1. Заполнить нулями в массиве все элементы, которые он пометил.   
4.2. Завершить работу.    
5. Если получен сигнал на продолжение работы, то продолжить исполнение цикла из
пункта 3.
## Lab4
- Задача. Написать программу для передачи сообщений между процессами через
общий файл. Программа включает один процесс Receiver и несколько процессов
Sender. Процессы Sender посылают сообщения процессу Receiver.

- Требования к реализации процесса Receiver. Процесс Receiver должен
выполнять следующие действия:
1. Ввести с консоли имя бинарного файла и количество записей в бинарном файле,
который будет использоваться для передачи сообщений.
2. Создать бинарный файл для сообщений. Максимальная длина сообщения 20
символов.
3. Ввести с консоли количество процессов Sender.
4. Запустить заданное количество процессов Sender. Каждому процессу Sender
передать через командную строку имя файла для сообщений.
5. Ждать сигнал на готовность к работе от всех процессов Sender.
6. Выполнять циклически следующие действия по команде с консоли:  
читать сообщение из бинарного файла или завершить свою работу.  
Замечание. Процесс Receiver переходит в состояние ожидания поступления нового сообщения, если вызывается команда чтения сообщения из пустого бинарного файла.
- Требования к реализации процесса Sender. Процесс Sender должен выполнять следующие действия:
1. Открыть файл для передачи сообщений. Имя файла получить из командной строки.
2. Отправить процессу Receiver сигнал на готовность к работе.
3. Выполнять циклически следующие действия по команде с консоли: отправить процессу Receiver сообщение или прекратить свою работу.
- Текст сообщения вводится с консоли. Длина сообщения меньше 20 символов.
- Замечание. Процесс Sender переходит в состояние ожидания, если вызывается команда записи сообщения в заполненный сообщениями бинарный файл.
- Дополнительные требования: Передача сообщений через бинарный файл должна быть организована как кольцевая очередь FIFO. Т.е. процесс Receiver должен читать сообщения в соответствии с порядком их отправления процессами Sender.
## Lab5
- Задача. Написать консольную программу Main и две утилиты (служебные программы) Creator и Reporter, которые выполняют следующие действия.
- Утилита Creator создает бинарный файл, имя которого и количество записей в котором получает через командную строку. Записи файла вводятся с консоли и имеют следующую структуру:  
 struct employee  
 {  
 int num; // идентификационный номер сотрудника  
 char name[10]; // имя сотрудника  
 double hours; // количество отработанных часов  
 };  
- Утилита Reporter создает текстовый файл, содержащий упорядоченный список сотрудников с начисленной заработной платой. Отчет формируется на основе бинарного файла, созданного программой Creator.
1. Утилита получает через командную строку следующие данные:  
1.1. Имя исходного бинарного файла.  
1.2. Имя файла отчета.  
1.3. Оплата за час работы.
2. Отчет содержит следующие строки:  
2.1. Заголовок: Отчет по файлу «имя исходного бинарного файла».  
2.2. Строка: Номер сотрудника, имя сотрудника, часы, зарплата.  
2.3. Список сотрудников по строкам. Каждая строка содержит информацию из соответствующей записи бинарного файла, а последний столбец строки - начисленную зарплату = кол-ву отработанных часов * оплату за час работы.
- Программа Main выполняет следующие действия:
1. Запрашивает с консоли имя бинарного файла и количество записей в этом файле.
2. Запускает утилиту Creator, которой передает через командную строку имя
создаваемого бинарного файла и количество записей в этом файле.
3. Ждет завершения работы утилиты Creator.
4. Выводит содержимое созданного бинарного файла на консоль.
5. Запрашивает с консоли:
a. Имя файла отчета.
b. Оплату за час работы.
6. Запускает утилиту Reporter, которой передает через командную строку:  
a. Имя исходного бинарного файла.  
b. Имя файла отчета.  
c. Оплату за час работы.  
7. Ждет завершения работы утилиты Reporter.  
8. Выводит отчет на консоль.  
9. Завершает свою работу.   

