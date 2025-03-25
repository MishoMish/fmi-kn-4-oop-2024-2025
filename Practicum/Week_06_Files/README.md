
### IV.Работа с файлове

1. Видове файлове според типа данни
   - Текстови
   - Двоични

Текстови файлове
: Файлове, в които съдържанието е предназначено за четене от хора. Данните във файла са различни от паметта.

Двоични файлове
: Файлове, които съдържанието е почти точно копие на паметта

2. Видове операции по файлове
   - четене
   - писане
   - четене и писане

Поток
: абстракция с която описваме връзката между програмата и даден файл или устройство

3. Видове потоци
   - потоци за вход (istream)
   - потоци за изход (ostream)

За работа с файлове използваме билбиотеката `<fstream>` или съответните `ifstream` и `ofstream`

![](https://i.sstatic.net/NZ8ST.gif)
<br>
<br>

***Преди работа с какъвто и да е файл той трябва първо да бъде отворен от програмата.***
<br>
***Задължително след отваряне на файл в някакъв момент той трябва да бъде затворен***
<br>

`open` - метод за отваряне на файл
`close` - метод за затваряне на файл
`ifstream` - клас за четене от файл
`оfstream` - клас за писане във файл


1. Флагове
   - `good` 
     : Потокът е в добро състояние. Последната операция е била успешна.
   - `bad` - 
     : Несъвместим с `good`. Възникнала е грешка при последната операция. Например хардуерен проблем
   - `fail` - 
     : Несъвместим с `good`. Пример за този флаг е грешен формат на данните
   - `eof` 
     : Флаг за край на файла. Вдига се при опит за прочитане **след** последния символ. Заедно с него се вдига и `fail`, тъй като данните са невалидни.
   - `clear()`
     : Метод за изчистване на флаговете за грешка. Оставя само флага `good`

*При получаване на флаг за грешка операциите по потока ще бъдат неуспешни и без ефект*

*Добра практика е да се използва `good` флага за условие в цикъл вместо `eof`*

- Методи на `ifstream`
  - \>> - четене на следващото парче данни
  - get - четене на един или повече символи
  - getline - четене на реда

- Методи на `оfstream`
  - \<< - записване на стойността от променливата в потока
  - put - записване на символ в потока


#### Текстови файлове

Пример за четене от текстови файл

```cpp 
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream file("myFile.txt"); // Трябва да съществува такъв файл!!!
	if (!file.is_open())
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}
	int a, b;

	file >> a >> b;

	file.close();
}
```

<br>
<br>

Пример за писане в текстови файлове
```cpp
#include <iostream>
#include <fstream>

int main()
{
	std::ofstream file("myFile.txt");

	if (!file.is_open())
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}
	int a = 3;
	int b = 10;

	file << a << " " << b << " " << a + b << std::endl;

	file.close();
}
```

Четенето и писането се случва чрез съответно get и put указатели

Позициониране на get и put указателите
 - tellg() - Връща позицията на текущия символ в потока за четене
 - tellp() - Връща позицията на текущия символ в потока за писане
 - seekg(streamoff offset,ios_base::seekdir way) - Премества get-указателят на потока за четене с offset символа спрямо way.
 - seekg(streampos idx) - Премества get-указателят на потока за четене на позиция idx.
 - seekp(streamoff offset, ios_base::seekdir way) - Премества put-указателят на потока за писане с offset символа спрямо way.
 - seekp(streampos idx) - Премества put-указателят на потока за писане на позиция idx.
  
 <br>

- idx: цяло поожително число
- offset: целочислена стойност. Отместването от way. 
- way: Може да заема следите стойности:
    - std::ios::beg - началото на файла.
    - std::ios::cur - текущата позиция във файла.
    - std::ios::end - края на файла.


#### Режими на работа
```cpp
ifstream str("file.txt", <режим на работа>);
```

Режимът на работа е комбинация от флагове
|Флаг|Ефект|
|-|-|
|ios::app|Отваря за вмъкване без да изтрива съдържанието на файла. Вмъква се винаги в края на файла.|
|ios::ate|Отваря за вмъкване без да изтрива съдържанието на файла. Вмъква се винаги в края на файла. За разлика от ios::app тук можем да променяме старото съдържание|
|ios::binary|Превключва режима от текстов в двоичен.|
|ios::in|Отваря файл за четене.|
|ios::out|Отваряне на файл за вмъкване. Допуска се вмъкване на произволни места във файла. Ако файлът съществува, съдържанието се изтрива.|
|ios::trunc|Ако файлът съществува, съдържанието се изтрива.|

Пример
```cpp
ofstream file("file.txt", ios::out | ios::app);
```

#### Двоични файлове

За двоичните файлове използваме следните методи:

- read(char* memoryBlock, size_t size) 
- write(const char* memoryBlock, size_t size)

*Важното тук е, че се използват указатели от тип char\* , т.е. нужно е да се преобразуват адресите на променливите до тип char\**

#### Сериализаци и Десериализация


#### Записване на проста структура в двоичен файл

Структура
```cpp
    struct Test{

        bool b;
        int x;

    };
```
<br>
<br>
Записване на структурата Test в двоичен файл

```cpp 
    Test t = { true, 45 };
    std::ofstream file("testObj.bat", std::ios::binary | std::ios::trunc);

    if(!file.is_open()) return -1;

    file.write(reinterpret_cast<const char*>(&t), sizeof(t));

    file.close();
```
<br>
<br>

Четене на структурата Test от двоичен файл
```cpp
    Test t;
    std::ifstream file("testObj.bat", std::ios::binary);
    
    if(!file.is_open()) return -1;

    file.read(reinterpret_cast<char*>(&t), sizeof(t));

    std::cout << t.b << " " << t.x << '\n';

    file.close();
```

<br>
<br>

#### Записване на масив структура от структури с масиви двоичен файл

Структура
```cpp
struct Student{
	char name[24];
	int age;
	int fn;
};
```
<br>
<br>

Записване на структурa Student в двоичен файл

```cpp
void WriteStudent(const Student &student, std::ifstream &file){
    size_t nameSize = strlen(students[i].name);
    file.write(reinterpret_cast<char const *>(&nameSize), sizeof(size_t));
    file.write(students[i].name, nameSize);
    file.write(reinterpret_cast<char const *>(&students[i].age), sizeof(int));
    file.write(reinterpret_cast<char const *>(&students[i].fn), sizeof(int));
}

```
<br>
<br>

Записване на масив от структури Student в двоичен файл

```cpp
void SaveToFile(Student const *students, size_t const count, std::ofstream &file){

	file.write(reinterpret_cast<char const *>(&count), sizeof(size_t));

	for(size_t i = 0; i < count; ++i){
        WriteStudent(students[i],file);
	}

}
```
<br>
<br>

Четене на структурa Student от двоичен файл
```cpp
void ReadStudent(Student &student, std::ifstream &f){
    size_t nameLen;
    f.read(reinterpret_cast<char *>(&nameLen), sizeof(size_t)); // First we read the size of the name!
    f.read(student.name, nameLen);
    student.name[nameLen] = '\0';
    f.read(reinterpret_cast<char *>(&student.fn), sizeof(int));
    f.read(reinterpret_cast<char *>(&student.age), sizeof(int));
    f.read(reinterpret_cast<char *>(&student.fn), sizeof(double));

}

```
<br>
<br>

Четене на масив от структури Student от двоичен файл

```cpp

    Student *ReadFromFile(size_t &studentsCount, std::ifstream &f){

	size_t numberOfStudents;
	f.seekg(0, std::ios::beg);
	f.read(reinterpret_cast<char *>(&numberOfStudents), sizeof(size_t));

	Student *ptr = new(std::nothrow) Student[studentsCount];
	if(!ptr) return nullptr;

	for(size_t i = 0; i < numberOfStudents; ++i) ReadStudent(ptr[i], f);

	return ptr;

}
```


Задачи за текстови файлове:
1. Напишете функция, която приема име на съществуващ файл, принтира съдържанието на файла и отпечатва броя на редовете в него.

2. Напишете функция, която приема имената на два текстови файла, в които са записани цели числа в сортиран вид. Числата са разделени с интервал. Запишете в нов файл числата от двата дайла в сортиран вид. Числата отново да са разделени с интервал.

3. Напишете програма, която прочита съдържанието на файл, в който има текст след това върху този текст прилага Цезарово кодиране с изместване 3 символа и премахва интервалите. За да можем да разкодираме съобщението запишете число преди всяка дума, което указва колко символа има до следващия интервал. След това се опитайте да декодирате съобщението.

Пример:

**original.txt**
``` 
This is an extraordinary example
```

**encoded.txt**
```
4Wklv2lv2dq13hawudruglqdu|7hadpsoh
```

**decoded.txt**
```
This is an extraordinary example
```

4. Напишете методи `void serialize(ostream& out)` и `void deserialize(istream& in)` на вашата имплементация на вектор и стринг за сериализация и десериализаци, използвайки двоични файлове. Искаме имплементацията на serialize да няма странични ефекти по съответния обект, а имплементацията на deserialize да изчиства информацията съхранена в обекта и да възстановява състоянието записано във файла в същия обект. Ако сте работили правилно трябва след сериализация и десериализация да се получили същият обект.