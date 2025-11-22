#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LENGTH 50
#define MAX_COURSES 10
#define MAX_COURSE_NAME_LENGTH 30

typedef struct {
    char name[MAX_NAME_LENGTH];
    int age;
    double average_grade;
    char student_id[20];
    char courses[MAX_COURSES][MAX_COURSE_NAME_LENGTH];
    int course_count;
} Student;

// Конструктор
Student* student_create(const char* name, int age, double average_grade);

// Деструктор
void student_destroy(Student* student);

// Методы установки значений
void student_set_name(Student* student, const char* name);
void student_set_age(Student* student, int age);
void student_set_average_grade(Student* student, double average_grade);
void student_set_student_id(Student* student, const char* student_id);

// Методы получения значений
const char* student_get_name(const Student* student);
int student_get_age(const Student* student);
double student_get_average_grade(const Student* student);
const char* student_get_student_id(const Student* student);

// Дополнительные методы
void student_display_info(const Student* student);
const char* student_calculate_grade(const Student* student);
int student_add_course(Student* student, const char* course_name);
int student_remove_course(Student* student, const char* course_name);
int student_is_excellent_student(const Student* student);
const char* student_get_study_year(const Student* student);
void student_get_courses(const Student* student, char* buffer, size_t buffer_size);

#endif
