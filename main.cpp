#include <iostream>
#include <fstream>
#include <string>

struct Student {
    std::string fullName;
    std::string group;
    double averageGrade;
};

void addStudentToFile(const Student& student) {
    std::ofstream outFile("students.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << student.fullName << "," << student.group << "," << student.averageGrade << std::endl;
        outFile.close();
        std::cout << "Студент успешно добавлен." << std::endl;
    } else {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
    }
}

void searchStudentByName(const std::string& name) {
    std::ifstream inFile("students.txt");
    if (inFile.is_open()) {
        std::string line;
        bool found = false;
        while (std::getline(inFile, line)) {
            size_t pos = line.find(',');
            std::string fullName = line.substr(0, pos);
            if (fullName == name) {
                std::cout << "Найден студент: " << line << std::endl;
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) {
            std::cout << "Студент с таким именем не найден." << std::endl;
        }
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

void sortStudentsByGrade() {
    std::ifstream inFile("students.txt");
    if (inFile.is_open()) {
        // Чтение данных и сортировка (пузырьковая сортировка)
        std::string lines[100]; // Предполагаем, что не более 100 студентов
        int count = 0;
        std::string line;
        while (std::getline(inFile, line)) {
            lines[count] = line;
            count++;
        }
        inFile.close();
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                size_t pos1 = lines[j].find_last_of(',');
                size_t pos2 = lines[j + 1].find_last_of(',');
                double grade1 = std::stod(lines[j].substr(pos1 + 1));
                double grade2 = std::stod(lines[j + 1].substr(pos2 + 1));
                if (grade1 < grade2) {
                    std::swap(lines[j], lines[j + 1]);
                }
            }
        }
        // Запись отсортированных данных обратно в файл
        std::ofstream outFile("students.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < count; i++) {
                outFile << lines[i] << std::endl;
            }
            outFile.close();
            std::cout << "Студенты отсортированы по среднему баллу." << std::endl;
        } else {
            std::cerr << "Не удалось открыть файл для записи." << std::endl;
        }
    } else {
        std::cerr << "Не удалось открыть файл для чтения." << std::endl;
    }
}

int main() {
    int choice;
    std::string name;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить студента" << std::endl;
        std::cout << "2. Поиск студента по ФИО" << std::endl;
        std::cout << "3. Сортировать студентов по среднему баллу" << std::endl;
        std::cout << "0. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::string fullName, group;
                double averageGrade;
                std::cout << "Введите ФИО студента: ";
                std::getline(std::cin, fullName);
                if (fullName.empty()) {
                    std::cout << "Ввод прерван." << std::endl;
                    break;
                }
                std::cout << "Введите группу студента: ";
                std::getline(std::cin, group);
                std::cout << "Введите средний балл студента: ";
                std::cin >> averageGrade;
                Student newStudent = {fullName, group, averageGrade};
                addStudentToFile(newStudent);
                break;
            }
            case 2: {
                std::cin.ignore();
                std::cout << "Введите ФИО студента для поиска: ";
                std::getline(std::cin, name);
                searchStudentByName(name);
                break;
            }
            case 3: {
                sortStudentsByGrade();
                break;
            }
            case 0: {
                std::cout << "Программа завершена." << std::endl;
                break;
            }
            default: {
                std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
