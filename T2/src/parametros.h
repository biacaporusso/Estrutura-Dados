#ifndef parametros_h
#define parametros_h

// realiza os tratamentos necessários e concatena o diretório e o nome do arquivo 
void diretorios(char* diretorio, char* nomeArq, char* arqCompleto);

// concatena a extensão .svg no arquivo já tratado
void concatenarSvg(char* dirSvg, char* arqQry, int leuQry);

// concatena a exntesão .txt no arquivo já tratado
void concatenarTxt(char* dirTxt, char* dirSvg);

// retorna apenas o nome do qry, sem a pasta em que se encontra e sem a extensão
char* getNomeQry(char* arquivoQry);

#endif