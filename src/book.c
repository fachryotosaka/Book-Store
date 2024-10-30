#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "book.h"


int getNewId(FILE* file){
    int maxId = 0;
    char line [MAX_LENGTH];

    // Loop setiap line di file
    while(fgets(line, sizeof(line), file) !=NULL){
        
        // Remove spaces/newline
        line[strcspn(line, "\n")] = '\0';

        // Seperate string, ambil id
        char *idStr = strtok(line, "#");

        if(idStr != NULL){
            // Parse id ke int
            int id = atoi(idStr);

            //Check dan replace max id dengan id terbesar
            if(maxId < id){
                maxId = id;
            } 
        }

    }

    //Return id terbesar + 1
    return ++maxId;

}