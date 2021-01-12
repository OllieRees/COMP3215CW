#include "OutputParser.h"

FILE * createOutputFile(char * fileLoc) {
    FILE * file = fopen(fileLoc, "w");
    //what if file can't be opened?
    return file;
}

void parseExecution(Task * task, int time, FILE * outputFile) {
   fprintf(outputFile, "%d %s Executes\n", time, task -> name); 
}

void parseMiss(Task * task, int time, FILE * outputFile) {
    fprintf(outputFile, "%d %s Misses\n", time, task -> name); 
}

void parseCompletion(Task * task, int time, FILE * outputFile) {
   fprintf(outputFile, "%d %s Completes\n", time, task -> name); 
}

void closeOutputFile(FILE * file) {
    fprintf(file, "Scheduling Finishes");
    fclose(file);
}
