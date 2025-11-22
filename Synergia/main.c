#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Student* create_student_interactive() {
    char name[MAX_NAME_LENGTH];
    int age;
    double average_grade;
    char student_id[20];
    
    printf("\n=== СОЗДАНИЕ НОВОГО СТУДЕНТА ===\n");
    
    // Ввод имени
    printf("Введите имя студента: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        return NULL;
    }
    // Удаляем символ новой строки
    name[strcspn(name, "\n")] = '\0';
    
    // Ввод возраста (студент от 18 до 115 лет)
    printf("Введите возраст студента (18-115 лет): ");
    while (scanf("%d", &age) != 1 || age < 18 || age > 115) {
        printf("Ошибка! Студент должен быть в возрасте от 18 до 115 лет: ");
        clear_input_buffer();
    }
    clear_input_buffer();
    
    // Ввод среднего балла
    printf("Введите средний балл (0-10): ");
    while (scanf("%lf", &average_grade) != 1 || average_grade < 0 || average_grade > 10) {
        printf("Ошибка! Введите корректный средний балл (0-10): ");
        clear_input_buffer();
    }
    clear_input_buffer();
    
    // Ввод ID студента
    printf("Введите ID студента: ");
    if (fgets(student_id, sizeof(student_id), stdin) == NULL) {
        return NULL;
    }
    student_id[strcspn(student_id, "\n")] = '\0';
    
    // Создание студента
    Student* student = student_create(name, age, average_grade);
    if (student != NULL) {
        student_set_student_id(student, student_id);
        printf("Студент успешно создан!\n");
    }
    
    return student;
}

void add_courses_interactive(Student* student) {
    char course_name[MAX_COURSE_NAME_LENGTH];
    char choice;
    
    printf("\n=== ДОБАВЛЕНИЕ КУРСОВ ДЛЯ СТУДЕНТА %s ===\n", student_get_name(student));
    
    do {
        printf("Введите название курса: ");
        if (fgets(course_name, sizeof(course_name), stdin) == NULL) {
            break;
        }
        course_name[strcspn(course_name, "\n")] = '\0';
        
        if (strlen(course_name) > 0) {
            student_add_course(student, course_name);
        }
        
        if (student->course_count >= MAX_COURSES) {
            printf("Достигнуто максимальное количество курсов (%d)\n", MAX_COURSES);
            break;
        }
        
        printf("Добавить еще один курс? (y/n): ");
        choice = getchar();
        clear_input_buffer();
        
    } while (choice == 'y' || choice == 'Y');
}

void demonstrate_student_operations() {
    int student_count;
    
    printf("=== СИСТЕМА УПРАВЛЕНИЯ СТУДЕНТАМИ ===\n\n");
    
    // Ввод количества студентов
    printf("Сколько студентов вы хотите создать? ");
    while (scanf("%d", &student_count) != 1 || student_count <= 0) {
        printf("Ошибка! Введите положительное число: ");
        clear_input_buffer();
    }
    clear_input_buffer();
    
    // Создание массива указателей на студентов
    Student** students = (Student**)malloc(student_count * sizeof(Student*));
    if (students == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }
    
    // Создание студентов с вводом данных
    for (int i = 0; i < student_count; i++) {
        printf("\n--- Студент %d из %d ---\n", i + 1, student_count);
        students[i] = create_student_interactive();
        
        if (students[i] != NULL) {
            add_courses_interactive(students[i]);
        } else {
            printf("Ошибка при создании студента!\n");
        }
    }
    
    // Вывод информации о всех студентах
    printf("\n=== ИНФОРМАЦИЯ О ВСЕХ СТУДЕНТАХ ===\n");
    for (int i = 0; i < student_count; i++) {
        if (students[i] != NULL) {
            student_display_info(students[i]);
        }
    }
    
    // Демонстрация дополнительных методов
    printf("\n=== ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ ===\n");
    for (int i = 0; i < student_count; i++) {
        if (students[i] != NULL) {
            const char* excellent_status = student_is_excellent_student(students[i]) ?
                                          "отличник" : "не отличник";
            printf("%s - %s, %s\n",
                   student_get_name(students[i]),
                   excellent_status,
                   student_get_study_year(students[i]));
        }
    }
    
    // Поиск отличников
    printf("\n=== СТУДЕНТЫ-ОТЛИЧНИКИ ===\n");
    int excellent_count = 0;
    for (int i = 0; i < student_count; i++) {
        if (students[i] != NULL && student_is_excellent_student(students[i])) {
            printf("%s - средний балл: %.2f\n",
                   student_get_name(students[i]),
                   student_get_average_grade(students[i]));
            excellent_count++;
        }
    }
    
    if (excellent_count == 0) {
        printf("Отличников нет\n");
    }
    
    // Демонстрация изменения данных
    printf("\n=== ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА ===\n");
    if (student_count > 0 && students[0] != NULL) {
        printf("Текущий средний балл студента %s: %.2f\n",
               student_get_name(students[0]),
               student_get_average_grade(students[0]));
        
        double new_grade;
        printf("Введите новый средний балл: ");
        while (scanf("%lf", &new_grade) != 1 || new_grade < 0 || new_grade > 10) {
            printf("Ошибка! Введите корректный средний балл (0-10): ");
            clear_input_buffer();
        }
        clear_input_buffer();
        
        student_set_average_grade(students[0], new_grade);
        printf("Данные обновлены!\n");
        student_display_info(students[0]);
    }
    
    // Освобождение памяти
    for (int i = 0; i < student_count; i++) {
        if (students[i] != NULL) {
            student_destroy(students[i]);
        }
    }
    free(students);
}

int main() {
    demonstrate_student_operations();
    printf("\nПрограмма завершена. Нажмите Enter для выхода...");
    getchar();
    return 0;
}
