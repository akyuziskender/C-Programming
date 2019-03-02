/************************************
****	 BIL105E - Homework6	 ****
****	    Movie Database	     ****
****        İskender Akyüz       ****
****          150150150          ****
************************************/
// make hw6

#include <stdio.h>  // adding standart input&output library
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int num_of_movies;  // a global variable to hold the number of movies

typedef struct {
	char book_name[40];  // a char array to hold name of the book
    char book_writer[25];  // a char array to hold name of the author
    int book_year;  // an integer to hold the year of book
}book_properties;

typedef struct {
    char name[40];  // a char array to hold the movie name
    int year;  // an integer to hold the year of the movie made
    char country[15];  // a char array to hold the country which the movie shot
    float rating;  // a float to hold the rating of the movie
    char from_book[4];  // a char array which will hold if the movie is from a book or not
    book_properties book;
}Movies;
// function prototypes
void insert(Movies *, char []);
void search(Movies *, char []);
void top_movies(Movies *, int);
void all_lower(char [], size_t);
int found(Movies *, char []);
int max_length(Movies *, int);

int main(void) {
    Movies *movies = (Movies *)malloc(sizeof(Movies) * 1);  // allocating memory
    // initializing required variables
    char option;
    char input[150];
    char word[10]; // a char array which we'll use in search function
    num_of_movies = 0;  // setting number 0f movies to 0
    int number;  // an integer that we'll use in top_movies function
    puts("Welcome to Movie Database!");
    do {
        // The user menu
        puts("Which option do you want:");
        puts("      1- Insert a movie");
        puts("      2- Search a movie");
        puts("      3- Recommend top movies");
        puts("      4- Exit");
        scanf(" %c", &option);  // getting a choice from user
        puts("");
        switch(option) {
            case '1':
                while(1) {
                    printf("Insert a movie with its details (for exit please enter -1): ");
                    scanf(" %[^\n]s", input);  // getting all information to insert a movie into the database
                    if(strcmp(input, "-1") == 0) {  // if user enters -1, finish inserting a movie
                        puts("");
                        break;
                    }
                    insert(movies, input);  // calling insert function
                    movies = (Movies *)realloc(movies,sizeof(Movies) * (num_of_movies + 1));  // reallocating memory to increase array size
                    if(movies == NULL) {  // checking memory failure
                        puts("Memory reallocation failed!");
                        return 1;
                    }
                }
                break;
            case '2':
                if(num_of_movies < 1) {  // checking whether or not there is at least one movie in the database
                    puts("The database is empty. There is nothing to search.\n");
                    break;
                }
                printf("Please Enter at least 3 characters for searching the database: ");
                scanf(" %[^\n]", word);  // getting at least 3 characters from user in order to search
                search(movies, word);  // calling search function
                break;
            case '3':
                if(num_of_movies < 1) {  // checking whether or not there is at least one movie in the database
                    puts("The database is empty.\n");
                    break;
                }
                while(1) {
                    printf("How many movies will be listed? ");
                    scanf("%d", &number);  // getting the number of movie which will listed from user
                    if(number <= num_of_movies) break;
                    else {  // if user enters a number more than the database has, warn him/her
                        printf("Give me a number less than or equal to %d.\n", num_of_movies);
                    }
                }
                top_movies(movies, number);  // calling top_movies function to list top movies
                break;
            case '4':
                break;
            default:
                puts("Enter a valid option\n");
        }
    }while(option != '4');  // in case of entering 4, exit the menu
    puts("Goodbye");
    free(movies);  // deleting memory
    movies = NULL;
    return 0;
}
// a function that adds new movies into the database
void insert(Movies *movies, char input[]) {
    size_t i = 0, temp; // counters
    int flag = 0;  // a control flag to check if the input is valid
    char name[40];  // a temporary char array to hold the movie name
    char year[5];  // a temporary char array to hold the year of the movie
    char country[15];  // a temporary char array to hold the country of the movie
    char rating[4];  // a temporary char array to hold the rating
    char from_book[4];
    char book_name[40];  // a temporary char to told the book name
    char book_writer[25];  // a temporary char array to hold name of the author
    char book_year[5];  // a temporary char array to hold the year of book
    while(1) {
        if(strlen(input) < 15) {  // the minimum input length must be 15; otherwise, it is invalid
            puts("Error: Invalid input. Try like this:\nMovie name,Year,Country,Rating,Is it from book,Book name,Book writer,Book year\n");
            break;
        }
        else {
            while(input[i] != ',') {  // take all characters until the comma
                name[i] = input[i];
                i++;
            }
            name[i] = '\0';  // to form a string, we need this end character
            if(found(movies, name)) {  // checking if the movie is already in the database
                puts("Error: This movie is already in the database. Try another one.\n");
                break;
            }
            i++;
            temp = i;
            while(input[i] != ',') {  // take all characters until the comma
                if(input[i] == ' ') {  // if the char is a space, pass it
                    i++;
                    temp++;
                    continue;
                }
                else if (!((input[i] >= 48) && (input[i] <= 57))) {  // it he char is not a number, finish the process
                    puts("Error: Invalid year. Try again.\n");
                    flag = 1;
                    break;
                }
                year[i-temp] = input[i];
                i++;
            }
            if(flag == 1) break;
            year[i-temp] = '\0';  // to form a string, we need this end character
            i++;
            temp = i;
            while(input[i] != ',') {  // take all characters until the comma
                country[i-temp] = input[i];
                i++;
            }
            country[i-temp] = '\0';  // to form a string, we need this end character
            i++;
            temp = i;
            while(input[i] != ',') {  // take all characters until the comma
                if(input[i] == ' ') {  // if the char is a space, pass it
                    i++;
                    temp++;
                    continue;
                }
                else if (!((input[i] >= 48) && (input[i] <= 57)) && (input[i] != '.')) {  // it he char is not a number or a point, finish the process
                    puts("Error: Invalid rating. Try again.\n");
                    flag = 1;
                    break;
                }
                rating[i-temp] = input[i];
                i++;
            }
            if(flag == 1) break;
            rating[i-temp] = '\0';  // to form a string, we need this end character
            i++;
            temp = i;
            while(input[i] != ',') {  // take all characters until the comma
                if(input[i] == ' ') {  // if the char is a space, pass it, since it must be exactly one word
                    i++;
                    temp++;
                    continue;
                }
                from_book[i-temp] = toupper(input[i]);
                if(strcmp(from_book, "NO") == 0) {
                    i++;
                    break;
                }
                i++;
            }
            from_book[i-temp] = '\0';  // to form a string, we need this end character
            i++;
            if(strcmp(from_book, "YES") == 0) {  // if the movie is from a book, continue to take characters
                temp = i;
                while(input[i] != ',') {  // take all characters until the comma
                    book_name[i-temp] = input[i];
                    i++;
                }
                book_name[i-temp] = '\0';  // to form a string, we need this end character
                i++;
                temp = i;
                while(input[i] != ',') {  // take all characters until the comma
                    book_writer[i-temp] = input[i];
                    i++;
                }
                book_writer[i-temp] = '\0';  // to form a string, we need this end character
                i++;
                temp = i;
                while(input[i] != '\0') {  // take all characters until the comma
                    if(input[i] == ' ') {  // if the char is a space, pass it
                        i++;
                        temp++;
                        continue;
                    }
                    else if (!((input[i] >= 48) && (input[i] <= 57))) {  // it he char is not a number, finish the process
                        puts("Error: Invalid year. Try again.\n");
                        flag = 1;
                        break;
                    }
                    book_year[i-temp] = input[i];
                    i++;
                }
                if(flag == 1) break;
                book_year[i-temp] = '\0';  // to form a string, we need this end character
                strcpy((*(movies+num_of_movies)).book.book_name, book_name);  // copying the book name into the database
                strcpy((*(movies+num_of_movies)).book.book_writer, book_writer);  // copying the author name into the database
                (*(movies+num_of_movies)).book.book_year = atoi(book_year);  // saving the book year to the database
            }
            strcpy((movies+num_of_movies)->name, name);  // copying the movie name into the database
            (movies+num_of_movies)->year = atoi(year);  // saving the movie year to the database
            strcpy((movies+num_of_movies)->country, country);  // copying the country name into the database
            (movies+num_of_movies)->rating = atof(rating);  // saving the movie rating to the database
            strcpy((movies+num_of_movies)->from_book, from_book);  // copying if the movie is from a book to the database
            printf("%s was inserted.\n\n", movies[num_of_movies].name);  // printing the movie that inserted
            num_of_movies++;  // incrementing number of movies
            break;
        }
    }
}
// a function searching all database to find movies matches with the word user entered
void search(Movies *movies, char word[]) {
    size_t i;  // counters
    int j = 1;
    char temp[40];  // a temporary char array to hold the movie name
    char temp2[10];  // a temporary char aray to hold the word
    printf("The movies including %s:\n", word);
    for(i = 0; i < num_of_movies; i++) {
        strcpy(temp, movies[i].name);  // copying movie name to the temporary array
        strcpy(temp2, word);  // copying the word to the temporary array
        all_lower(temp, strlen(temp));  // converting all letters to lower case
        all_lower(temp2, strlen(temp2));  // converting all letters to lower case
        if( strstr(temp, temp2) != NULL) {  // checking if there is a match
            printf("   %d. %*s %d %*s %.1f %-3s ", j, -max_length(movies, 1), movies[i].name,
            movies[i].year, -max_length(movies, 2), movies[i].country, movies[i].rating,
            movies[i].from_book);
            if(strcmp(movies[i].from_book, "YES") == 0) {
                printf("%*s %*s %d\n", -max_length(movies, 3), movies[i].book.book_name,
				-max_length(movies, 4), movies[i].book.book_writer, movies[i].book.book_year);
            }
            else {
                puts(""); // new line
            }
            j++;
        }
    }
    puts("");  // new line
}
// a function which lists top movies
void top_movies(Movies *movies, int n) {
    size_t i, j, hold = 0; // counters
    int counter = 1;
    float max = 0;  // a float variable to hold maximum rating
    int *temp = (int *)calloc(num_of_movies, sizeof(int));  // creating a temporary array to check if the movie already listed
    int max_len = max_length(movies, 1);  // getting the length of the longest movie name
    puts("\nWe recommend you top 5 movies:");
    for(i = 0; i < n; i++) {
        for(j = 0; j < num_of_movies; j++) {
            if((movies[j].rating > max) && temp[j] == 0) {
                max = movies[j].rating;  // changing maximum rating
                hold = j;  // holding its index
            }
        }
        temp[hold] = 1;  // changing to 1 to indicate that it's listed
        printf("   %d. %*s %.1f\n", counter, -max_len, movies[hold].name, movies[hold].rating);
        counter++;
        max = 0;  // setting max to 0 in order to use it again
    }
    puts("");
    free(temp);  // deleting memory
}
// a function that takes a word and converts all its letters to lower case
void all_lower(char word[], size_t n) {
    size_t i;  // counter
    for(i = 0; i < n; i++) {
        word[i] = tolower(word[i]);  // converting process
    }
}
// a function that checks if the movie which user want to insert is already in the database
int found(Movies *movies, char name[]) {
    size_t i; // counter
    char temp[40];  // a temporary char array to hold the movie name
    char temp2[40];  // a temporary char array to hold the new movie name
    for(i = 0; i < num_of_movies; i++) {
        strcpy(temp, movies[i].name);  // copying the movie name in the database to temporary array in order to use it
        strcpy(temp2, name);  // copying the new movie name to the database in order to use it
        all_lower(temp, strlen(temp));  // converting all letters to lower case
        all_lower(temp2, strlen(temp2));  // converting all letters to lower case
        if(strcmp(temp, temp2) == 0) {  // checking if there is a match
            return 1;
        }
    }
    return 0;  // if there is no match, return 0
}
// a function that finds the length of the longest movie name
int max_length(Movies *movies, int choice) {
    size_t i; // counter
    int n = 0;  // max length
    switch(choice) {
        case 1:
            for(i = 0; i < num_of_movies; i++) {
                if(strlen(movies[i].name) > n) n = strlen(movies[i].name);
            }
            return n;
        case 2:
            for(i = 0; i < num_of_movies; i++) {
                if(strlen(movies[i].country) > n) n = strlen(movies[i].country);
            }
            return n;
        case 3:
            for(i = 0; i < num_of_movies; i++) {
                if(strlen(movies[i].book.book_name) > n) n = strlen(movies[i].book.book_name);
            }
            return n;
        case 4:
            for(i = 0; i < num_of_movies; i++) {
                if(strlen(movies[i].book. book_writer) > n) n = strlen(movies[i].book.book_writer);
            }
            return n;
    }
}
