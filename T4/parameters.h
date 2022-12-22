#ifndef parameters_h
#define parameters_h

char* getNomeQry(char* arquivoQry);
/* 
Retorna apenas o nome do arquivo, sem a extensão .qry 
*/

void diretorios(char* diretorio, char* arquivoGeo, char* arqCompleto);
/* 
Faz todos os tratamentos necessários para gerar corretamente 
todos os diretórios de entrada e saída.
*/

#endif