#include <string.h>
#include <iostream>
#include <fstream>

#define FILENAME "C:\Users\danil\source\repos\kyrsovaya_rabota_3Semak\kyrsovaya_rabota_3Semak"

using namespace std;


class Students() { // warrior in past
private:
    char name[32];
    char surname[32];
    int groupNumber;
    int visitDates[100];
    int visitDatesIndex = 0;
    int AmountOfStudentsInGroup = 5;

public:

    Student() {}

    Student(char name[], char surname[], int groupNumber) {
        this->name = name;
        this->surname = surname;
        this->groupNumber = groupNumber;
    }

    void addDate(int date) {
        visitDates[visitDatesIndex] = date;
        visitDatesIndex++;
    }


    bool visited(int date) {
        for (int i = 0; i < visitDatesIndex; i++) {
            if (visitDates[i] == date)
            {
                return true;
            }
        }
        return false;
    }


}



class Visits { // Squad in past
private:
    Students* students;
    int size = 10;
    int index = 0;

public:
    Visits() {
        students = new Student[this->size];
    }

    int WriteToFile();
    int ReadFromFile();
    bool Add(Student student);
    bool Add(Student petrov, int pos);

    bool AddVisitToStudent(char surname, int date);// должна найти в списке студентов данного с данной фамилией и вызвать функцию addDate для него или вернуть что такого студента нет
    bool AddVisitToStudents(char surnames[], int date);// внутри в цикле будет вызываться функиця AddVisitToStudent для каждой фамилии

    void sortingBySurname();
    void sortingByAmountOfVisits(); //сортировка по visitDatesIndex в классе студента

    void printStudentsByDate(int date); //бежишь по списку студентов и смотришь есть ли дата в массиве с датами (функция visited)

    Students Pop(int pos);
    bool Delete(int pos);
    void Show();
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

    bool AddVisitToStudent(char surname, int date) {
        if individualMath.Visit(char surname, int date) == ("Danil", "Karpenko", 141206) {
            student.addDate("Danil", "Karpenko", 141218);
        };
        else { cout << "такого студента нет " << endl; }
    }

    bool AddVisitToStudents(char surnames[], int date) {
        for (int i = 0; i < AmountOfStudentsInGroup; i++) {
            if ((groupMath.Visit(char surname, int date) == ("Danil", "Karpenko", 141218)) && (groupMath.Visit(char surname, int date) == ("Nikolay", "Velikii", 141218))) {
                student.AddVisitToStudent("Danil", "Karpenko", 141218);
                student.AddVisitToStudent("Nikolay", "Velikii", 141218);
            }
        }
    }
    void printStudentsByDate(int date) {
        if visitDates[visitDatesIndex] == date { cout << visitDates[visitDatesIndex] << " "; }
    }
    bool Add(Students student) {    // добавление элемента в конец структуры
        if (this->index >= this->size) {
            this->size *= 2;
            Students* tmp = new Students[this->size];
            for (int i = 0; i < this->index; ++i) {
                tmp[i] = new Students(students[i]);
            }
            delete[] students;
            students = tmp;
        }
        students[index] = new Students(student);
        index++;
        return true;
    }

    void sorting() {
        Students temp; // временная штука для хранения массива
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (students[j].visitDatesIndex > students[j + 1].visitDatesIndex) {
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

    // test_write();
    // //    test_read();
    Visits individualMath = new Visits();
    Visits groupMath = new Visits();

    individualMath.Add(new Student("Danil", "Karpenko", 141206));
    groupMath.Add(new Student("Danil", "Karpenko", 141206));
   
    individualMath.Add(new Student("Vasya", "Krasnov", 141206));
    individualMath.Add(new Student("Petya", "Mesnikan", 141206));

    individualMath.Add(new Student("Nikolay", "Velikii", 141218));
    groupMath.Add(new Student("Nikolay", "Velikii", 141218));


    return 0;
}