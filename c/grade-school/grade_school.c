#include "grade_school.h"


int init_roster(roster_t *roster)
{
    if (!roster)
        return 0;
    
    roster->count = 0;
    
    return 1;
}


int add_student(roster_t *roster, char name[], uint8_t grade)
{
    student_t new_student, aux_student;

    if (!name || !roster || roster->count == MAX_STUDENTS)
        return 0;

    for (size_t i = 0; i < roster->count; i++){
        if (strncmp(roster->students[i].name, name, MAX_NAME_LENGTH) == 0)
            return 0;
    }
    
    new_student.grade = grade;
    strncpy(new_student.name, name, MAX_NAME_LENGTH);

    for (size_t i = 0; i < roster->count; i++){
        if (roster->students[i].grade > grade || \
            (roster->students[i].grade == grade && \
             strncmp(roster->students[i].name, new_student.name, MAX_NAME_LENGTH) > 0)){
            for(; i < roster->count; i++){
                aux_student = roster->students[i];
                roster->students[i] = new_student;
                new_student = aux_student;
            }
        }
    }
    roster->students[roster->count] = new_student;
    roster->count++;

    return 1;
}


roster_t get_grade(roster_t *roster, uint8_t desired_grade)
{
    roster_t grade_roster;
    init_roster(&grade_roster);

    if (!roster)
        return grade_roster;
    
    for (size_t i = 0; i < roster->count; i++){
        if (roster->students[i].grade == desired_grade){
            add_student(&grade_roster, roster->students[i].name, desired_grade);
        }
    }

    return grade_roster;
}