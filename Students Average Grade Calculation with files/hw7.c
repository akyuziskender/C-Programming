/*===================================================
  ||	           BIL105E - Homework7	           ||
  || Students Average Grade Calculation with files ||
  ||                  İskender Akyüz               ||
  ||                     150150150                 ||
  ===================================================*/
// make hw6
// marnop proudly presents.
/* Warning: Error 2 works like that if a student has more than one record in his/her lecture file, his/her first average is
written into sortedlist.bin file, and for the second average, error 2 is implemented.
Since there is nothing about updating the grades in homework7.pdf and nothing was said to us about error 2
I coded error 2 as I understood. */

#include <stdio.h>  // adding standart input&output library
#include <stdlib.h>
#include <string.h>
#include <time.h>

int student_counter;  // a global variable to hold # of students saved to the database
size_t average_counter;  // a global variable to hold # of averages calculated
int error_flag;  // a global flag to write the titles into Error.bin file

typedef struct {
    int ID;  // an integer to hold students' ID
    char name[30];  // a char array to hold students' name
    char lecture_code[7];  // a char array to hold name of the lecture that the student takes
    int average[10];  // an integer array to hold the average points of the student's exams
} Student_Info;
// function prototypes
void sort(Student_Info *, int [], int [], int []);
void error(Student_Info *, char [], size_t);

int main(void) {
    Student_Info *students = (Student_Info *)malloc(sizeof(Student_Info) * 1); // taking a place in the memory for one student
    FILE *fPtr, *fPtr2, *fPtr3;  // file pointers
    size_t i, j, n; // counters
    char file_name[20];  // a string to hold file name in which students are
    char lecture_name[20];  // a string to hold lecture names that students take
    char *file_extension = ".txt";  // in order to form proper file name, we need file extension
    char buff[255];
    int id, read_counter, k = 0;
    int first, second, third;  // integer variables to hold exam results of the student
    char temp[20];  // a char array to hold the name of the student taken from studentsXX.txt file
    char code[7];  // a char array to hold the lecture name taken from studentsXX.txt file
    int error_0_check[300] = {0};  // an integer array to prevent writing same student for error 0 into the Error.bin file again
    int error_1_check[300] = {0};  // an integer array to prevent writing same student for error 1 into the Error.bin file again
    int error_2_check[300] = {0};  // an integer array to prevent writing same student for error 2 into the Error.bin file again
    student_counter = 0;  // setting student_counter to 0
    average_counter = 0;  // setting average_counter to 0
    error_flag = 1;  // a flag for Error.bin file, it is for writing titles only one time
    char *temp2 = "students";

    for(i = 0; i <= 99; i++) {  // a for loop to read students files from students00.txt to students99.txt
        if(i < 10) {
            sprintf(file_name, "%s0%d%s", temp2, (int)i, file_extension);  // forming proper file name for studentsXX.txt
        }
        else {
            sprintf(file_name, "%s%d%s", temp2, (int)i, file_extension);  // forming proper file name for studentsXX.txt
        }
        fPtr = fopen(file_name, "r");  // opening the file in reading mode
        if(fPtr != NULL) {  // checking if there exist a file in that name
            while(fgets(buff, sizeof(buff), fPtr)) {
                read_counter = sscanf(buff, "%d %s %s", &id, temp, code);  // reading the text file line by line
                if(read_counter != 3) break;  // if read_counter is not 3, then we are at the end of the file, so finish reading by breaking while loop
                students[student_counter].ID = id;  // saving student's id into the student info database
                strcpy(students[student_counter].name, temp);  // copying student's name into the student info database
                strcpy(students[student_counter].lecture_code, code);  // copying student's lecture name into the student info database
                strcpy(lecture_name, code);  // copying lecture name to the another string
                strcat(lecture_name, file_extension);  // concatenating lecture name and lecture extension to form proper file name
                for(n = 0; n < 10; n++) students[student_counter].average[n] = -1;
                fPtr2 = fopen(lecture_name, "r");  // opening the file in reading mode
                if(fPtr2 != NULL) {  // checking if there exist a file in that name
                    while(fgets(buff, sizeof(buff), fPtr2)) {
                        read_counter = sscanf(buff, "%d %d %d %d", &id, &first, &second, &third);  // reading the text file line by line
                        if(read_counter != 4) break;  // if read_counter is not 4, then we are at the end of the file, so finish reading by breaking while loop
                        if(id == students[student_counter].ID) {  // searching student's id in the lecture file
                            students[student_counter].average[k] = (first + second + third) / 3;  // calculating student's average
                            average_counter++;  // incrementing average_counter
                            k++;
                        }
                    }
                    fclose(fPtr2);  // closing the file
                }
                else {  // if there is no file in that lecture name, record that student in Error.bin file
                    students[student_counter].average[0] = -2;
                }
                k = 0;
                student_counter++;  // incrementing student_counter
                students = (Student_Info *)realloc(students,sizeof(Student_Info) * (student_counter + 1));  // allocating extra place for the new student
            }
            fclose(fPtr);  // closing the students file
            sort(students, error_0_check, error_1_check, error_2_check);  // sorting the students by their average
        }
        strcpy(file_name, "students");  // to use it again, setting string its initial case
    }
    free(students);  // deleting memory
    students = NULL;
    return 0;
}
// a function that sorts the students' average and writes into the sortedlist.bin file
void sort(Student_Info *students, int error_0_check[], int error_1_check[], int error_2_check[]) {
    FILE *fPtr, *fPtr2;
    int i, j, k; // counters
    int max = 0;  // an int variable to hold maximum rating
    int hold;  // an temporary variable to hold the index of the student with max average
    char sorted_text[200];
    char temp2[3];  // a char array to hold the average
    char titles[] = "ID Name Course Error type Time Stamp";  // titles for Error.bin file
    int sorted[300] = {0};  // creating a temporary array to check if the student's average is already listed
    fPtr = fopen("sortedlist.bin", "wb");
    for(i = 0; i < average_counter; i++) {
        for(j = 0; j < student_counter; j++) {
            for(k = 0; k < 10; k++) {
                if((students[j].average[0] == -1) && error_0_check[j] == 0) {  // checking if the student has an average point and he/she is already recorded
                    if(error_flag) {
                        fPtr2 = fopen("Error.bin", "wb");  // opening Error.bin file in binary writing mode
                        fwrite(titles, 1, sizeof(titles), fPtr2);  // writing the titles into the Error.bin file
                        fclose(fPtr2);  // closing Error.bin file
                        error_flag = 0;  // in order not to write the titles again, setting the error_flag to 0
                    }
                    error(students, "0", j);  // recording the error by calling error function
                    error_0_check[j] = 1;  // setting students index in the array to 1 in order to prevent writing again
                    break;
                }
                else if((students[j].average[0] == -2) && error_1_check[j] == 0) {  // if the student's first average grade is -2, that indicates that the course file the student takes does not exist
                    if(error_flag) {
                        fPtr2 = fopen("Error.bin", "wb");  // opening Error.bin file in binary writing mode
                        fwrite(titles, 1, sizeof(titles), fPtr2);  // writing the titles into the Error.bin file
                        fclose(fPtr2);  // closing Error.bin file
                        error_flag = 0;  // in order not to write the titles again, setting the error_flag to 0
                    }
                    error(students, "1", j);  // recording the error by calling error function
                    error_1_check[j] = 1;  // setting students index in the array to 1 in order to prevent writing again
                    break;
                }
                else if(students[j].average[k] == -1  || students[j].average[k] == -2) break;
                else if((k > 0) && (error_2_check[j] == 0)) {  // if k is greater than zero, that means student has more than 1 average grade
                    if(error_flag) {
                        fPtr2 = fopen("Error.bin", "wb");  // opening Error.bin file in binary writing mode
                        fwrite(titles, 1, sizeof(titles), fPtr2);  // writing the titles into the Error.bin file
                        fclose(fPtr2);  // closing Error.bin file
                        error_flag = 0;  // in order not to write the titles again, setting the error_flag to 0
                    }
                    error(students, "2", j);  // recording the error by calling error function
                    error_2_check[j] = 1;  // setting students index in the array to 1 in order to prevent writing again
                }
                else if((students[j].average[k] > max) && sorted[j] == 0) {
                    max = students[j].average[k];  // changing maximum rating
                    hold = j;  // holding its index
                }
            }
        }
        if(i > 199) break; // the maximum record in sortedlist.bin is gonna be 200, so if it passes 200 or we are end of the students average records, break the loop.
        if(sorted[hold] == 0) {
        	sprintf(sorted_text, "%d %s %s %d\n", students[hold].ID, students[hold].name, students[hold].lecture_code, students[hold].average[0]);  // forming proper format to write it into the file
            fwrite(sorted_text, sizeof(char), strlen(sorted_text), fPtr);  // writing the text into the sortedlist.bin file
        	sorted_text[0] = '\0';  // making it null to use it again
        }
        sorted[hold] = 1;  // setting student's index to 1 for indicating he/she is sorted
        max = 0;  // setting max to 0 to use it again
    }
    fclose(fPtr);  // closing the file
}
// a function that saves the errors into the Error.bin file
void error(Student_Info *students, char type[], size_t index) {
    FILE *fPtr;
    time_t now = time(NULL);  // getting the time since the Epoch (00:00:00 UTC, January 1, 1970), measured in seconds
    struct tm *t = localtime(&now);  // getting the local time
    char curr_time[26];  // a char array to hold the current time
    char error_text[100];  // a char array to hold the error text which will be written into the Error.bin file
    strftime(curr_time, sizeof(curr_time), "%d.%m.%Y %H:%M", t );  // getting current time
    fPtr = fopen("Error.bin", "ab+");  // opening Error.bin file in binary appending format
    sprintf(error_text, "%d %s %s %s %s\n", students[index].ID, students[index].name, students[index].lecture_code, type, curr_time);  // forming the text that will be written into the Error.bin file
    fwrite(error_text, sizeof(char), strlen(error_text), fPtr);  // writing the text into the Error.bin file
    fclose(fPtr);  // closing the file
}
