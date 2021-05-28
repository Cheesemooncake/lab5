
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "windows.h"

using namespace std;

struct Cup {

    string color;
    int price;
    int volume;
    double weight;
    void Out();
    
};


struct DLList
{
    struct Node
    {
        Cup data;     //information
        Node* next;   //next node position
        Node* prev;   //previous node position
    };

    Node* F = NULL;     //first node
    Node* L = NULL;     //last node
    Node* C = NULL;     //current node
    int Count;        //node count

    void Out();
    void Info();
    void Clear();
    //void Sort();
 

    bool MoveNext();
    bool MovePrev();
    bool MoveFirst();
    bool MoveLast();
  

    bool Init(Cup);
    bool AddNext(Cup);
    bool AddPrev(Cup);
    bool AddFirst(Cup);
    bool AddLast(Cup);

    bool Del(Cup&);
    bool DelNext(Cup&);
    bool DelPrev(Cup&);
    bool DelFirst(Cup&);
    bool DelLast(Cup&);
};

bool DLList::MoveNext()
{
    if (!F) {
        return false;
    }
    if (!C) {
        C = F; return true; 
    }
    if (!C->next) {
        return false;
    }
    C = C->next;
    return true;
}

bool DLList::MovePrev()
{
    if (!F)       return false;
    if (!C) { C = F; return true; }
    if (!C->prev) return false;
    C = C->prev;
    return true;
}
bool DLList::MoveFirst()
{
    if (!F) {
        return false;
    }
        C = F;
    return true;
}

bool DLList::MoveLast()
{
    if (!L) {
        return false;
    }
        C = L;
    return true;
}

bool DLList::Init(Cup data)
{
    if (!F)
    {
        F = new Node;
        L = F;
        C = F;
        F->prev = NULL;
        F->next = NULL;
        F->data = data;
        Count = 1;
        return true;
    }
    else
        return false;
}

bool DLList::AddNext(Cup data)
{
    if (!F) return Init(data);

    Node* temp = C->next;
    C->next = new Node;
    C->next->next = temp;
    C->next->prev = C;

    if (!temp)
        L = C->next;
    else
        temp->prev = C->next;

    C = C->next;
    C->data = data;
    Count++;
    return true;

}

bool DLList::AddPrev(Cup data)
{
    if (!F) {
        return Init(data);
    }
    Node* temp = C->prev;
    C->prev = new Node;
    C->prev->next = C;
    C->prev->prev = temp;

    if (!temp) {
        F = C->prev;
    }
    else
    {
        temp->next = C->prev;
    }

    C = C->prev;
    C->data = data;
    Count++;
    return true;
}

bool DLList::AddFirst(Cup data)
{
    if (MoveFirst()) {
        return AddPrev(data);
    }
    else {
        return false;
    }
}

bool DLList::AddLast(Cup data)
{
    if (MoveLast()) {
        return AddNext(data);
    }
    else {
        return false;
    }
}

void DLList::Out()
{
    if (!F) {
        cout << "Список пуст" << endl;
        return;
    }

    Node* temp = F;
    cout << "Список: " << endl;
    do
    {
        temp->data.Out();
        temp = temp->next;
    } while (temp);
    cout << endl;
}

void DLList::Info()
{

    if (Count) {
        cout << "Кол-во объектов: "
            << Count << endl;
    }
    else
    {
        cout << "Список пуст" << endl;
    }
    if (C) {

        if (MoveFirst())
        {
        
            cout << "Текущий элемент = ";
            C->data.Out();
        }
     }
}

bool DLList::DelFirst(Cup& data)
{
    if (!F){
    
        return false;
    }

    if (C != F) {
        MoveFirst();
    }

    Node* temp = C->next;
    data = C->data;

    if (temp) {

        temp->prev = NULL;
    }

    delete C;

    C = temp;
    F = temp;
    Count--;

    if (!temp){

     L = NULL; return false; 

    }
    return true;
}

bool DLList::DelLast(Cup& data)
{
    if (!F) {
        return false;
    }

    if (C != L) {
        MoveLast();
    }

    Node* temp = C->prev;
    data = C->data;

    if (temp) {
        temp->next = NULL; 
    }
    delete C;

    C = temp;
    L = temp;
    Count--;

    if (!temp) { 
        F = NULL; return false;
    }
    return true;
}

bool DLList::Del(Cup& data)
{
    if (!F) {
        return false;
    }
    if (!C) {
        return false;
    }
    if (C == F) {
        return DelFirst(data); 
    }
    if (C == L) {
        return DelLast(data);
    }
    Node* temp = C->next;
    data = C->data;

    C->prev->next = C->next;
    C->next->prev = C->prev;

    delete C;
    C = temp;
    Count--;
    return true;
}

bool DLList::DelNext(Cup& data){

    if (!F) {
        return false;
    }
    if (!C) {
        return false;
    }

    if (MoveNext()) { 
        return Del(data); 
    }
    return false;
}

bool DLList::DelPrev(Cup& data){

    if (!F) {
        return false;
    }
    if (!C) {
        return false;
    }
    if (MovePrev()) {
        return Del(data);
    }
    return false;
}

void DLList::Clear(){

    if (!MoveFirst())
    {
        cout << "Список пуст" << endl;
        return;
    }
    Cup k;
    while (Del(k));
}


void Cup::Out(){

    cout << "Цвет чашки: " << color << "\t\t" << "Цена: " << price << "\t" << "Объем: " << volume << "\t" << "Вес: " << weight << endl;
}

bool GetFile(DLList&, Cup&);
bool WriteFile(DLList&, Cup&);
void GetCup(Cup&);




int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");


    Cup Info;
    DLList DLList;
    GetFile(DLList, Info);
    DLList.Out();
    Cup w;
    Cup p;

    int num, key = 0, key1 = 0, key2 = 0;

    do
    {
        cout << "1. Добавить элемент" << endl
            << "2. Удалить элемент" << endl
            << "3. Упорядочить элементы по весу" << endl
            << "4. Упорядочить элементы по цене" << endl
            << "5. Очистить список" << endl
            << "6. Перезаписать файл" << endl
            << "0. Выйти" << endl;

        cout << endl << "Выберите действие: ";
        cin >> key;
        cout << endl;
        switch (key) {
        
        case 1:

            cout << "1. Добавить элемент в начало" << endl
                << "2. Добавить элемент в конец" << endl
                << "3. Добавить элемент на k-ую позицию" << endl
                << "0. Назад" << endl;

            cout << endl << "Выберите действие: ";
            cin >> key1;
            cout << endl;
            switch (key1)
            {
            case 1:

                GetCup(Info);
                DLList.AddFirst(Info);
                DLList.Out();
                break;

            case 2:

                GetCup(Info);
                DLList.AddLast(Info);
                DLList.Out();
                break;

            case 3:

                cout << "Введите позицию: ";
                cin >> num;
                GetCup(Info);
                if (num == 1) {
               
                    DLList.AddFirst(Info);
                    DLList.Out();
                    break;
                }

                else if (num == DLList.Count + 1) {
                
                    DLList.AddLast(Info);
                    DLList.Out();
                    break;
                }

                DLList.MoveFirst();

                for (int i = 1; i < num - 1; i++) {
                
                    DLList.MoveNext();
                }

                DLList.AddNext(Info);
                DLList.Out();
                break;

            default:

                if (key1 != 0)
                {
                    cout << "Такого действия нет" << endl << endl;
                }
                break;
            }
            break;

        case 2:
            cout << "1. Удалить первый элемент" << endl
                << "2. Удалить второй элемент" << endl
                << "3. Удалить элемент с k-ой позиции" << endl
                << "0. Назад" << endl;
            cout << endl << "Выберите действие: ";
            cin >> key2;
            cout << endl;

            switch (key2){
            
            case 1:

                DLList.DelFirst(Info);
                DLList.Out();
                break;

            case 2:

                DLList.DelLast(Info);
                DLList.Out();
                break;

            case 3:

                cout << "Введите позицию: ";
                cin >> num;
                if (num == 1) {
                
                    DLList.DelFirst(Info);
                    DLList.Out();
                    break;
                }
                else if (num == DLList.Count) {
                
                    DLList.DelLast(Info);
                    DLList.Out();
                    break;
                }
                DLList.MoveFirst();

                for (int i = 1; i < num; i++) {
                
                    DLList.MoveNext();
                }

                DLList.Del(Info);
                DLList.Out();
                break;

            default:
                if (key2 != 0)
                {
                    cout << "Такого действия нет" << endl << endl;
                }
                break;
            }
            break;


        case 3:
            for (int i = 0; i < DLList.Count - 1; i++)
            {
                DLList.MoveLast();
                for (int j = (DLList.Count - 1); j > 0; j--)
                {
                    if ((DLList.C->prev->data.weight) > (DLList.C->data.weight))
                    {
                        w = DLList.C->data;
                        DLList.C->data = DLList.C->prev->data;
                        DLList.C->prev->data = w;
                    }
                    DLList.MovePrev();
                }


            }
            DLList.Info();
            DLList.Out();
            break;


        case 4:
            for (int i = 0; i < DLList.Count - 1; i++)
            {
                DLList.MoveLast();
                for (int j = (DLList.Count - 1); j > 0; j--)
                {
                    if ((DLList.C->prev->data.price) > (DLList.C->data.price))
                    {
                        p = DLList.C->data;
                        DLList.C->data = DLList.C->prev->data;
                        DLList.C->prev->data = p;
                    }
                    DLList.MovePrev();
                }


            }
            DLList.Info();
            DLList.Out();
            break;


        case 5:

            DLList.Clear();
            DLList.Out();
            break;

        case 6:

            WriteFile(DLList, Info);
            break;

        default:
            if (key != 0) {
            
                cout << "Нет такого действия" << endl << endl;
            }
            DLList.Clear();
            DLList.Out();
            break;
        }
    } while (key != 0);
}










bool GetFile(DLList& DLList, Cup& Info) {

    ifstream F("Cup.txt");
    if (!F) {
    
        cout << "Файл не найден" << endl;
        return false;
    }
    while (F >> Info.color >> Info.price >> Info.volume >> Info.weight) {
    
        DLList.AddNext(Info);
    }

    F.close();
    return true;
}

bool WriteFile(DLList& DLList, Cup& Info) {

    ofstream F("Cup.txt");
    if (!F)
    {
        cout << "Файл не найден" << endl;
        return false;
    }

    DLList.MoveFirst();
    do {
     
        F << DLList.C->data.color<< " " << DLList.C->data.price << " " << DLList.C->data.volume << " " << DLList.C->data.weight << endl;
    }
    while (DLList.MoveNext());
    DLList.MoveFirst();
    F.close();
    return true;
}

void GetCup(Cup& Info)
{
    cout << "Цвет чашки: ";
    cin >> Info.color;
    cout << endl;
    cout << "Цена чашки: ";
    cin >> Info.price;
    cout << endl;
    cout << "Объем чашки: ";
    cin >> Info.volume;
    cout << endl;
    cout << "Вес чашки: ";
    cin >> Info.weight;
    cout << endl;
}

/*
void Sort(DLList& DLList, Cup& Info) {

    if (F != NULL) {
        cout << "\nВыберите поле, по какому сортировать:\n";
        cout << "\n1. Цвет\n";
        cout << "\n2. Вес\n";
        cout << "\nВведите цифру -> ";
        int choice; 
        cin >> choice;

        switch (choice) {

        case 1: {

            C = F;
            DLList* temp = F;

            for (int i = 0; i < Count; i++) {
                for (int j = 0; j < Count; j++) {
                    if (C == temp) continue;
                    if (strcmp(temp->data.color.c_str(), C->data.color.c_str()) > 0) {
                        swap(temp->data, C->data);
                    }
                    if (temp->next != NULL) temp = temp->next;

                }
                temp = F;
                C = C->next;

            }


            C = F;
            break;
        }

        case 2: {
            C = F;
            DLList* temp = F;

            for (int i = 0; i < Count; i++) {
                for (int j = 0; j < Count; j++) {
                    if (C == temp) continue;
                    if (temp->data.weight > C->data.weight) {
                        swap(temp->data, C->data);
                    }
                    if (temp->next != NULL) temp = temp->next;

                }
                temp = F;
                C = C->next;

            }

            C = F;
            break;
        }

        default: {
            cout << "\nОшибка, выбран неправильный пункт!\n";
            break;
        }
        }
    }
    else {
        cout << "\nСписок пустой!\n";
    }


}


*/