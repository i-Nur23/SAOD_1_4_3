#include <iostream>
#include <locale>
#include <string>
#include <set>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DBG_NEW new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW

using namespace std;

struct subListElem
{
    int info;
    subListElem* next;
};

struct mainListElem
{
    string infoStr;
    mainListElem* next;
    subListElem* subHead;
};

mainListElem* head;

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

string CheckedRead() // Ввод строки с проверкой на пустоту
{
    string str;
    int length; int count;
    while (true)
    {
        getline(cin, str);
        if (str == "")
        {
            cout << "Вы ввели пустую строку. Попробуйте еще раз: "; //cin.ignore(32767, '\n');
            continue;
        }
        length = str.size();
        count = 0;
        for (int i = 0; i < length; i++)
        {
            if (str[i] == ' ')
            {
                count++;
            }
        }
        if (count == length)
        {
            cout << "Вы ввели пустую строку. Попробуйте еще раз: "; str.clear(); //cin.ignore('\n');
            continue;
        }
        return str;
    }
}

void InitMainList(mainListElem*& head)
{
    head->infoStr = " ";
    head->subHead = NULL;
    head->next = NULL;
}

bool isEmpty(mainListElem* headElem)
{
    if (headElem->next == NULL)
    {
        return true;
    }
    return false;
}

bool isEmpty(subListElem* headElem)
{
    if (headElem->next == NULL)
    {
        return true;
    }
    return false;
}

void Print()
{
    mainListElem* pMainCur = head->next;
    while (pMainCur != NULL)
    {
        subListElem* pSubCur = pMainCur->subHead;
        cout << pMainCur->infoStr << ": ";
        if (isEmpty(pSubCur))
        {
            cout << "пустой\n"; pMainCur = pMainCur->next; continue;
        }
        pSubCur = pSubCur->next;
        while (pSubCur != NULL)
        {
            cout << pSubCur->info << " ";
            pSubCur = pSubCur->next;
        }
        pMainCur = pMainCur->next;
        cout << endl;
    }
}

template <typename T>
T Search(string strToSearch) // поиск в базовом списке
{
    T pCur = head->next;
    while (pCur != NULL)
    {
        if (pCur->infoStr == strToSearch)
        {
            return pCur;
        }
        pCur = pCur->next;
    }
    return NULL;
}

template <typename T>
T Search(int intToSearch) // поиск во вспомогательном списке
{
    mainListElem* pMainCur = head->next;
    while (pMainCur != NULL)
    {
        T pSubCur = (pMainCur->subHead)->next;
        while (pSubCur != NULL)
        {
            if (pSubCur->info == intToSearch)
            {
                return pSubCur;
            }
            pSubCur = pSubCur->next;
        }
        pMainCur = pMainCur->next;
    }
    return NULL;
}

subListElem* SearchInList(int intToSearch, subListElem* subHead)
{
    subListElem* pCur = subHead;
    while (pCur != NULL)
    {
        if (pCur->info == intToSearch)
        {
            return pCur;
        }
        pCur = pCur->next;
    }
    return NULL;
}

void Add(string strToAdd, mainListElem* pTemp) // добавление после в базовый список
{
    mainListElem* newItem = new mainListElem;
    subListElem* newSub = new subListElem;
    newSub->info = 0; newSub->next = NULL;
    newItem->infoStr = strToAdd; newItem->next = pTemp->next; newItem->subHead = newSub;
    pTemp->next = newItem;
}

void Add(int intToAdd, subListElem* pTemp) // добавление после в вспомогательный список
{
    subListElem* newSub = new subListElem;
    newSub->info = intToAdd; newSub->next = pTemp->next;
    pTemp->next = newSub;
}

void Add(string strToAdd, string strToBefore) // добавление перед в базовый список
{
    mainListElem* current = head->next;
    mainListElem* previous = head;
    while (current->infoStr != strToBefore)
    {
        previous = current;
        current = current->next;
    }
    mainListElem* newItem = new mainListElem;
    subListElem* newSub = new subListElem;
    newSub->info = 0; newSub->next = NULL;
    newItem->infoStr = strToAdd; newItem->next = current; newItem->subHead = newSub;
    previous->next = newItem;
}

void Add(int intToAdd, subListElem* pHead, int intToBefore) // добавление перед в вспомогательный список
{
    subListElem* newSub = new subListElem;
    subListElem* current = pHead->next;
    subListElem* previous = pHead;
    while (current->info != intToBefore)
    {
        previous = current;
        current = current->next;
    }
    newSub->info = intToAdd; newSub->next = current;
    previous->next = newSub;
}

void Delete(string strToDel)
{
    mainListElem* pTemp = head->next;
    mainListElem* pPrev = head;
    while (pTemp->infoStr != strToDel)
    {
        pPrev = pTemp;
        pTemp = pTemp->next;
    }
    subListElem* pSub = pTemp->subHead; subListElem* pSubTemp;
    while (pSub != NULL)
    {
        pSubTemp = pSub;
        pSub = pSub->next;
        delete pSubTemp;
    }
    pPrev->next = pTemp->next;
    delete pTemp;
}

void Delete(int intToDel, subListElem* subHead)
{
    subListElem* pTemp = subHead->next;
    subListElem* pPrev = subHead;
    while (pTemp->info != intToDel)
    {
        pPrev = pTemp;
        pTemp = pTemp->next;
    }
    pPrev->next = pTemp->next;
    delete pTemp;
}

void DeleteAll()
{
    mainListElem* pMainCur = head->next; mainListElem* pMainTemp;
    subListElem* pSubCur; subListElem* pSubTemp;
    while (pMainCur != NULL)
    {
        pSubCur = pMainCur->subHead;
        while (pSubCur != NULL)
        {
            pSubTemp = pSubCur;
            pSubCur = pSubCur->next;
            delete pSubTemp;
        }
        pMainTemp = pMainCur;
        pMainCur = pMainCur->next;
        delete pMainTemp;
    }
    delete head;
}

void CallMenu(mainListElem*& head)
{
    bool work = true;
    int choice;
    while (work)
    {
        cout << "Выбор действия:\n1 - Полный проход по структуре\n2 - Поиск элемента в базовом списке\n3 - Поиск элемента в подсписках\n";
        cout << "4 - Добавление элмента в базовый список после заданного\n5 - Добавление элмента в базовый список перед заданным\n6 - Добавление элемента после в один из подсписков\n";
        cout << "7 - Добавление элемента перед в один из подсписков\n8 - Удаление элемента базового списка\n";
        cout << "9 - Удаление элемента из одного из подсписков\n10 - Завершение работы\n";
        cout << "Действие: "; choice = CheckedInput(1, 10);
        mainListElem* pTemp; 
        subListElem* pSub;
        string strToDel, strToBefore;
        int intToDel, intToBefore;
        switch (choice)
        {
        
        case 1:
            if (isEmpty(head))
            {
                cout << "Базовый список пуст.";
            }
            else
            {
                Print();
            }
            cout << "\n\n";
            break;
        
        case 2:
            if (isEmpty(head))
            {
                cout << "Базовый список пуст.\n\n";
                break;
            }
            cout << "Введите имя искомого списка: ";
            if (Search <mainListElem*> (CheckedRead()) == NULL)
            {
                cout << "Заданный элемент не найден.";
            }
            else
            {
                cout << "Задданный элемент найден. ";
            }
            cout << "\n\n";
            break;
        
        case 3:
            if (isEmpty(head))
            {
                cout << "Базовый список пуст.\n\n";
                break;
            }
            cout << "Введите искомый элемент: ";
            if (Search <subListElem*> (CheckedInput()) == NULL)
            {
                cout << "Заданный элемент не найден.";
            }
            else
            {
                cout << "Задданный элемент найден. ";
            }
            cout << "\n\n";
            break;
        
        case 4:
            if (isEmpty(head)) // если базовый список пуст
            {
                cout << "Введите имя списка, который хотели бы добавить в базовый: ";
                Add(CheckedRead(), head);
                cout << "\n\n";
                break;
            }
            
            cout <<"Введите элемент, после которого хотите добавить новый: "; // ввод элемента списка 
            pTemp = Search <mainListElem*> (CheckedRead());
            if (pTemp == NULL)
            {
                cout << "Такого элемента в базовом списке не существует.\n\n"; break;
            }
            
            cout << "Введите имя списка, который хотели бы добавить в базовый: "; // ввод нового элемнта
            Add(CheckedRead(), pTemp);
            cout << "\n\n";
            break;
        
        case 5:
            if (isEmpty(head)) // если базовый список пуст
            {
                cout << "Введите имя списка, который хотели бы добавить в базовый: ";
                Add(CheckedRead(), head);
                cout << "\n\n";
                break;
            }

            cout << "Введите элемент, перед которым хотите добавить новый: "; // ввод элемента списка 
            
            strToBefore = CheckedRead();
            pTemp = Search <mainListElem*>(strToBefore);
            if (pTemp == NULL)
            {
                cout << "Такого элемента в базовом списке не существует.\n\n"; break;
            }

            cout << "Введите имя списка, который хотели бы добавить в базовый: "; // ввод нового элемнта
            Add(CheckedRead(), strToBefore);
            cout << "\n\n";
            break;
        
        case 6:
            if (isEmpty(head)) // Если базовый список пуст
            {
                cout << "Базовый список пуст.";
                cout << "\n\n";
                break;
            }
            
            cout << "Введите имя списка, в который хотели бы добавить новый элемент: ";
            pTemp = Search <mainListElem*>(CheckedRead());
            if (pTemp == NULL) // проверка наличия элемента в базовом списке.
            {
                cout << "Такого элемента в базовом списке не существует.\n\n"; break;
            }
            
            if (isEmpty(pTemp->subHead)) // проверка пустоты элемента базового списка
            {
                cout << "Введите число, которое хотели бы добавить в список: ";
                Add(CheckedInput(), pTemp->subHead);
                cout << "\n\n";
                break;
            }

            cout << "Введите элемент, после которого хотели бы добавить новый: "; // проверка наличия элемента в списке
            pSub = SearchInList(CheckedInput(),pTemp->subHead);
            if (pSub == NULL)
            {
                cout << "Такого элемента в списке не существует.\n\n"; break;
            }

            cout << "Введите элемент, который хотели бы добавить: "; // добавление 
            Add(CheckedInput(),pSub);

            cout << "\n\n";
            break;
        
        case 7:
            if (isEmpty(head)) // Если базовый список пуст
            {
                cout << "Базовый список пуст.";
                cout << "\n\n";
                break;
            }

            cout << "Введите имя списка, в который хотели бы добавить новый элемент: ";
            pTemp = Search <mainListElem*>(CheckedRead());
            if (pTemp == NULL) // проверка наличия элемента в базовом списке.
            {
                cout << "Такого элемента в базовом списке не существует.\n\n"; break;
            }

            if (isEmpty(pTemp->subHead)) // проверка пустоты элемента базового списка
            {
                cout << "Введите число, которое хотели бы добавить в список: ";
                Add(CheckedInput(), pTemp->subHead);
                cout << "\n\n";
                break;
            }

            cout << "Введите элемент, перед которым хотели бы добавить новый: "; // проверка наличия элемента в списке
            intToBefore = CheckedInput();
            pSub = SearchInList(intToBefore, pTemp->subHead);
            if (pSub == NULL)
            {
                cout << "Такого элемента в списке не существует.\n\n"; break;
            }

            cout << "Введите элемент, который хотели бы добавить: "; // добавление 
            Add(CheckedInput(), pTemp->subHead, intToBefore);
            cout << "\n\n";
            break;
        
        case 8:
            if (isEmpty(head))
            {
                cout << "Базовый список пуст.";
                cout << "\n\n";
                break;
            }

            cout << "Введите, имя списка, который хотели бы удалить: ";
            strToDel = CheckedRead();
            if (Search <mainListElem*>(strToDel) == NULL)
            {
                cout << "Заданного элемента не существует."; break;
            }

            Delete(strToDel);

            cout << "\n\n";
            break;
        
        case 9:
            if (isEmpty(head))
            {
                cout << "Базовый список пуст.";
                cout << "\n\n";
                break;
            }

            cout << "Введите, имя списка, в котором хотели бы удалить элемент: ";
            strToDel = CheckedRead(); pTemp = Search <mainListElem*>(strToDel);
            if (pTemp == NULL)
            {
                cout << "Заданного элемента не существует.\n\n"; break;
            }

            if (isEmpty(pTemp->subHead))
            {
                cout << "Данный список пустой.";
                cout << "\n\n";
                break;
            }

            cout << "Введите элемент, который хотели бы удалить: "; intToDel = CheckedInput();
            if (Search <subListElem*>(intToDel) == NULL)
            {
                cout << "Заданного элемента не существует.\n\n"; break;
            }

            Delete(intToDel, pTemp->subHead);

            cout << "\n\n";
            break;
        
        case 10:
            work = false;
            DeleteAll();
            cout << "\n\n";
            break;
        
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    head = new mainListElem;
    InitMainList(head);
    CallMenu(head);
    _CrtDumpMemoryLeaks();
}