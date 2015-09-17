#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

int verifyNumRegex(regex_t *regexT,char *tok);
int verifyOpRegex(regex_t *regexT,char *tok);
int compileRegex(regex_t *regexT, char *def);
void getTokens(int *retNum, int *retOp, regex_t *regexNum, regex_t *regexOp);
void doOperation(long pInt[2], char *op);

int main() {

    regex_t regexNum;
    regex_t regexOp;
    int retNum,retOp;

    retNum =compileRegex(&regexNum,"[[:digit:]]\\+");
    retOp = compileRegex(&regexOp,"[*'/'\\+\\-]");

    if (retNum) {
        fprintf(stderr, "Could not compile number regexNum\n");
        return 1;
    }
    if (retOp) {
        fprintf(stderr, "Could not compile operator regexOp\n");
        return 1;
    }

    getTokens(&retNum,&retOp,&regexNum,&regexOp);

    return 0;
}

int compileRegex(regex_t *regexT, char *def){
    return regcomp(regexT,def,0);
}

int verifyNumRegex(regex_t *regexT,char *tok){
    return regexec(regexT, tok, 0, NULL, 0);
}

int verifyOpRegex(regex_t *regexT,char *tok){
    return regexec(regexT, tok, 0, NULL, 0);
}

void getTokens(int *retNum, int *retOp, regex_t *regexNum, regex_t *regexOp){

    FILE *f;
    char linea[250];
    char *tok = NULL;
    char *end = NULL;
    long num[2];
    int numCont = 0;
    char *op = NULL;

    if((f=fopen("file.txt","r+"))!=NULL) {
        while (fgets(linea, 250, f)) {
            for (tok = strtok(linea, " "); tok != NULL; tok = strtok(NULL, " ")) {
                printf("%s\n", tok);
                *retNum = verifyNumRegex(regexNum,tok);
                *retOp = verifyOpRegex(regexOp,tok);
                if (!*retNum) {
                    num[numCont] = strtol(tok,&end,10);
                    numCont++;
                }
                if (!*retOp) {
                    op = tok;
                }
            }
        }
        doOperation(num,op);
    }
}

void doOperation(long pInt[2], char *op) {
    int res = NULL;
    if((strcmp(op,"+")) == 0){
        res = (int)pInt[0] + (int)pInt[1];
        printf("The result of the operation is %d\n",res);
    }
    else if((strcmp(op,"*")) == 0){
        res = (int)pInt[0] * (int)pInt[1];
        printf("The result of the operation is %d\n",res);
    }
    else if((strcmp(op,"-")) == 0){
        res = (int)pInt[0] - (int)pInt[1];
        printf("The result of the operation is %d\n",res);
    }
    else if((strcmp(op,"/")) == 0){
        float floatRes = (float)pInt[0] / (float)pInt[1];
        printf("The result of the operation is %.3f\n",floatRes);
    }
}