#include <stdio.h>
#include <stdlib.h>

char* getline() {
    size_t lenIncrease = 100;
    size_t maxlen = lenIncrease;
    size_t len = 0;
    char *line = malloc(maxlen);

    if (line == NULL) {
        return NULL;
    }

    for(;;) {
        //get the next charecter and check if it is at the end of file
        char c = fgetc(stdin);
        if (c == EOF) {
            break;
        }
        
        //allocate more mem if needed
        if (len >= maxlen) {
            maxlen += lenIncrease;
            char *lineNew = realloc(line, maxlen);
            if (lineNew == NULL) {
                free(line);
                return NULL;
            }
            //update the position 
            line = lineNew;
        }
        //append c
        if (c != '\n') {
            line[len] = c;
        } else {
            break;
        }
        len++;
    }

    //return
    line[len] = '\0';
    //clear the empty slots in the buffer
    char *lineNew = realloc(line, len + 1);
    if (lineNew == NULL) {
        return line;
    }
    return lineNew;
}


int main() {    
    return 0;
}
