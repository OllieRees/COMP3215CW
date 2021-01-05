#include "OutputParser.h"

FILE * createOuputFile(char * fileLoc) {
    FILE * file = fopen(fileLoc, "w");
    //what if file can't be opened?
    return file;
}

void parseExecution(Task * task, int time, FILE * outputFile) {
   fprintf(outputFile, "%d %s Executes", time, task -> name); 
}

void parseMiss(Task * task, int time, FILE * outputFile) {
    fprintf(outputFile, "%d %s Misses", time, task -> name); 
}

void parseCompletion(Task * task, int time, FILE * outputFile) {
   fprintf(outputFile, "%d %s Completes", time, task -> name); 
}

void closeOutputFile(FILE * file) {
    fprintf(file, "Scheduling Finishes");
    fclose(file);
}
