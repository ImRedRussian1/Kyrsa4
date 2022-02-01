#include <string.h>
#include <iostream>
#include <fstream>

#define FILENAME "C:\Users\danil\source\repos\kyrsovaya_rabota_3Semak\kyrsovaya_rabota_3Semak"

using namespace std;

class Students {
public:
    char name[20];
    int hp;
    int mana;
    int VisitIndividual; // посещение индивидуальных занятий
    int VisitCollective; // посещения коллективных занятий
    int GroupNumber; // номер группы
    int AmountOfVisits;
    int* ArrayOfVisits = new int[AmountOfVisits]; // массив дат посещения занятий
    Students() {
    }


    Students(Students* el) {
        // copy constructor
        strcpy_s(this->name, el->name);
        this->hp = el->hp;
        this->mana = el->mana;
    }

    void Print() {
        cout << "\tName: " << name << endl;
        cout << "\tHp: " << hp << endl;
        cout << "\tMana: " << mana << endl;
    }
};


class Squad {
public:
    Students* students;
    int size = 10;
    int index = 0;

    Squad() {
        students = new Students[this->size];
    }

    int WriteToFile() {
        ofstream wf(FILENAME, ios::out | ios::binary);
        if (!wf) {
            cout << "Cannot open file!" << endl;
            return 1;
        }
        wf.write((char*)&this->size, sizeof(int));
        wf.write((char*)&this->index, sizeof(int));

        for (int i = 0; i < this->index; i++)
            wf.write((char*)&students[i], sizeof(Students));
        wf.close();
        if (!wf.good()) {
            cout << "Error occurred at writing time!" << endl;
            return 1;
        }
        return 0;
    }

    int ReadFromFile() {
        ifstream rf(FILENAME, ios::in | ios::binary);
        if (!rf) {
            cout << "Cannot open file!" << endl;
            return 1;
        }
        int tmp_size = this->size;
        rf.read((char*)&this->size, sizeof(int));
        if (this->size > tmp_size) {
            students = new Students[this->size];
        }
        rf.read((char*)&this->index, sizeof(int));

        for (int i = 0; i < this->index; i++) {
            rf.read((char*)&students[i], sizeof(Students));
        }
        rf.close();
        if (!rf.good()) {
            cout << "Error occurred at reading time!" << endl;
            return 1;
        }
        return 0;
    }

    bool Add(Students warrior) {    // добавление элемента в конец структуры
        if (this->index >= this->size) {
            this->size *= 2;
            Students* tmp = new Students[this->size];
            for (int i = 0; i < this->index; ++i) {
                tmp[i] = new Students(students[i]);
            }
            delete[] students;
            students = tmp;
        }
        students[index] = new Students(warrior);
        index++;
        return true;
    }

    void sorting() {
        Students temp; // временная штука для хранения массива
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (students[j].AmountOfVisits > students[j + 1].AmountOfVisits) {
                    // меняем элементы местами
                    temp = students;
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        cout << "." << endl;
    }

    bool Add(Students petrov, int pos) {   // включение с сохранением порядка
        if (this->index >= this->size) {
            this->size += 1;
        }
        this->index += 1;
        Students* tmp = new Students[this->size];
        int indexToCopy = 0;
        for (int i = 0; i < this->index; ++i) {
            if (i == pos) {
                tmp[i] = new Students(petrov);
            }
            else {
                tmp[i] = new Students(students[indexToCopy]);
                indexToCopy++;
            }
        }
        delete[] this->students;
        this->students = tmp;
        return true;
    }

    Students Pop(int pos) {    //извлечение по логическому номеру
        Students res = new Students(this->students[pos]);
        this->Delete(pos);
        return res;
    }

    bool Delete(int pos) {
        /*
         *  удаление из любой позиции
         */
        Students* tmp = new Students[this->size];
        int indexToPaste = 0;
        for (int i = 0; i < this->index; ++i) {
            if (i != pos) {
                tmp[indexToPaste] = new Students(this->students[i]);
                indexToPaste++;
            }
        }
        this->index -= 1;
        delete[] this->students;
        this->students = tmp;
        return true;
    }

    void Show() {    // вывод структуры
        for (int i = 0; i < this->index; ++i) {
            cout << "студенты посещавшие занятия: " << i << endl;
            students[i].Print();
        }
        cout << "------------------" << endl;
    }

};

void test_write() {
    remove(FILENAME);

    Squad* squad = new Squad();
    Students warrior;
    for (int i = 0; i < 100; ++i) {
        warrior = new Students();
        warrior.hp = 5;
        warrior.mana = 7;
        strcpy_s(warrior.name, "Ignat");
        squad->Add(warrior);
    }
    squad->Show();
    squad->WriteToFile();
}

void test_read() {
    Squad* squad = new Squad();
    squad->ReadFromFile();
    squad->Show();
}

int main() {

    test_write();
    //    test_read();


    return 0;
}
