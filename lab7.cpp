#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const double MROT = 22440.0;

struct Student {
    std::string fio;
    std::string group;
    int grades[4];        
    double family_income;
    double average_grade;
};

int main() {
    std::setlocale(LC_ALL, "Russian");
    
    int nst;
    std::cout << "Введите число студентов: ";
    if (!(std::cin >> nst)) return 1;

    std::vector<Student> mstud(nst);

    for (int i = 0; i < nst; i++) {
        std::cin.ignore();
        
        std::cout << "\n--- Студент #" << i + 1 << " ---\n";
        std::cout << "Введите ФИО: ";
        std::getline(std::cin, mstud[i].fio);
        
        std::cout << "Введите номер группы: ";
        std::getline(std::cin, mstud[i].group);
        
        std::cout << "Введите месячный доход семьи: ";
        std::cin >> mstud[i].family_income;
        
        std::cout << "Введите 4 оценки через пробел: ";
        mstud[i].average_grade = 0;
        for (int j = 0; j < 4; j++) {
            std::cin >> mstud[i].grades[j];
            mstud[i].average_grade += mstud[i].grades[j] / 4.0;
        }
    }

    // Умная сортировка introsort с приоритетом по МРОТ
    std::sort(mstud.begin(), mstud.end(), [](const Student& a, const Student& b) {
        bool a_below_mrot = a.family_income < MROT;
        bool b_below_mrot = b.family_income < MROT;

        // Если у одного доход ниже МРОТ, а у другого выше/равен
        if (a_below_mrot != b_below_mrot) {
            return a_below_mrot; // Тот, у кого ниже МРОТ, идет первым
        }
        
        // Если оба ниже МРОТ или оба выше МРОТ, сортируем по среднему баллу
        return a.average_grade > b.average_grade;
    });

    std::cout << "\n\n Рейтинг студентов (Приоритет: Доход < МРОТ, затем Средний балл) \n";
    for (int i = 0; i < nst; i++) {
        std::cout << mstud[i].fio  << " | Группа: " << mstud[i].group << " | Ср. балл: " << mstud[i].average_grade << " | Доход: " << mstud[i].family_income;
        
        if (mstud[i].family_income < MROT) {
            std::cout << " [НИЖЕ МРОТ]";
        }
        std::cout << std::endl;
    }

    return 0;
}
