#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "student.h"

Student* student_create(const char* name, int age, double average_grade) {
    Student* student = (Student*)malloc(sizeof(Student));
    if (student == NULL) {
        return NULL;
    }
    
    student_set_name(student, name);
    student_set_age(student, age);
    student_set_average_grade(student, average_grade);
    student->student_id[0] = '\0';
    student->course_count = 0;
    
    return student;
}

void student_destroy(Student* student) {
    free(student);
}

void student_set_name(Student* student, const char* name) {
    strncpy(student->name, name, MAX_NAME_LENGTH - 1);
    student->name[MAX_NAME_LENGTH - 1] = '\0';
}

void student_set_age(Student* student, int age) {
    if (age >= 18 && age <= 115) {
        student->age = age;
    } else {
        printf("Ошибка: возраст студента должен быть от 18 до 115 лет\n");
    }
}

void student_set_average_grade(Student* student, double average_grade) {
    if (average_grade >= 0.0 && average_grade <= 10.0) {
        student->average_grade = average_grade;
    } else {
        printf("Ошибка: средний балл должен быть от 0 до 10\n");
    }
}

void student_set_student_id(Student* student, const char* student_id) {
    strncpy(student->student_id, student_id, 19);
    student->student_id[19] = '\0';
}

const char* student_get_name(const Student* student) {
    return student->name;
}

int student_get_age(const Student* student) {
    return student->age;
}

double student_get_average_grade(const Student* student) {
    return student->average_grade;
}

const char* student_get_student_id(const Student* student) {
    return student->student_id;
}

void student_display_info(const Student* student) {
    printf("Информация о студенте:\n");
    printf("ID: %s\n", student->student_id);
    printf("Имя: %s\n", student->name);
    printf("Возраст: %d\n", student->age);
    printf("Средний балл: %.2f\n", student->average_grade);
    printf("Оценка: %s\n", student_calculate_grade(student));
    
    if (student->course_count > 0) {
        char courses_buffer[300];
        student_get_courses(student, courses_buffer, sizeof(courses_buffer));
        printf("Курсы: %s\n", courses_buffer);
    }
    printf("--------------------------------------\n");
}

const char* student_calculate_grade(const Student* student) {
    if (student->average_grade >= 8.5) {
        return "Отлично";
    } else if (student->average_grade >= 6.5) {
        return "Хорошо";
    } else if (student->average_grade >= 4.5) {
        return "Удовлетворительно";
    } else {
        return "Неудовлетворительно";
    }
}

int student_add_course(Student* student, const char* course_name) {
    if (student->course_count >= MAX_COURSES) {
        printf("Ошибка: достигнуто максимальное количество курсов\n");
        return 0;
    }
    
    if (strlen(course_name) >= MAX_COURSE_NAME_LENGTH) {
        printf("Ошибка: название курса слишком длинное\n");
        return 0;
    }
    
    // Проверяем, есть ли уже такой курс
    for (int i = 0; i < student->course_count; i++) {
        if (strcmp(student->courses[i], course_name) == 0) {
            printf("Курс '%s' уже добавлен студенту %s\n", course_name, student->name);
            return 0;
        }
    }
    
    strcpy(student->courses[student->course_count], course_name);
    student->course_count++;
    printf("Курс '%s' добавлен студенту %s\n", course_name, student->name);
    return 1;
}

int student_remove_course(Student* student, const char* course_name) {
    for (int i = 0; i < student->course_count; i++) {
        if (strcmp(student->courses[i], course_name) == 0) {
            // Сдвигаем оставшиеся курсы
            for (int j = i; j < student->course_count - 1; j++) {
                strcpy(student->courses[j], student->courses[j + 1]);
            }
            student->course_count--;
            printf("Курс '%s' удален у студента %s\n", course_name, student->name);
            return 1;
        }
    }
    
    printf("Курс '%s' не найден у студента %s\n", course_name, student->name);
    return 0;
}

int student_is_excellent_student(const Student* student) {
    return student->average_grade >= 8.5;
}

const char* student_get_study_year(const Student* student) {
    if (student->age >= 18 && student->age <= 19) {
        return "1-2 курс бакалавриата";
    } else if (student->age >= 20 && student->age <= 21) {
        return "3-4 курс бакалавриата";
    } else if (student->age >= 22 && student->age <= 23) {
        return "Магистратура";
    } else if (student->age >= 24 && student->age <= 28) {
        return "Аспирантура";
    } else {
        return "Слушатель/Дополнительное образование";
    }
}

void student_get_courses(const Student* student, char* buffer, size_t buffer_size) {
    buffer[0] = '\0';
    
    for (int i = 0; i < student->course_count; i++) {
        if (i > 0) {
            strncat(buffer, ", ", buffer_size - strlen(buffer) - 1);
        }
        strncat(buffer, student->courses[i], buffer_size - strlen(buffer) - 1);
        
        if (strlen(buffer) >= buffer_size - 1) {
            break;
        }
    }
}
