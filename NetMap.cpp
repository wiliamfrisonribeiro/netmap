#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;
#include "listaDupla.hpp"

bool nomeCompostoVerify(string nome);
bool roteadorNomeIgual(Lista *roteadores, string nome);
void cadastrarRoteador(string nome, string desc, Lista *roteadores);
void cadastrarTerminal(string nome, string desc, Lista *roteadores, Lista *terminais);
void removerTerminal(string nome, Lista *terminais);
void removerRoteador(string nome, Lista *roteadores, Lista *terminais);
void conectarRoteadores(string nome, Lista *roteadores);
void desconectarRoteadores(string nome, string desc, Lista *roteadores);
void frequenciaOperadora(string nome, Lista *roteadores);
void enviarDados(string nome, string desc, Lista *roteadores, Lista *terminais);

int main(){
    Lista *roteadores = new Lista();
    Lista *terminais = new Lista();
    int menu;
    string nome, desc;

    //INSERIR VALORES
    inserirInicio(roteadores, "r1", "oi");
    inserirInicio(roteadores, "r2", "telemar");
    inserirInicio(roteadores, "r3", "gvt");
    inserirInicio(roteadores, "r4", "net");
    inserirInicio(roteadores, "r5", "telemar");
    /////////////////
    do{
        system("cls");
        cout << "\n ___________ NETMAP ____________" << endl
             << "|                               |" << endl
             << "|  0 - Sair                     |" << endl
             << "|  1 - Cadastrar roteador       |" << endl
             << "|  2 - Cadastrar Terminal       |" << endl
             << "|  3 - Remover Roteador         |" << endl
             << "|  4 - Remover Terminal         |" << endl
             << "|  5 - Conectar Roteadores      |" << endl
             << "|  6 - Desconectar Roteadores   |" << endl
             << "|  7 - Frequencia Operadoras    |" << endl
             << "|  8 - Enviar Pacotes de Dados  |" << endl
             << "|  9 - Mostrar Terminais        |" << endl
             << "|  10 - Mostrar Roteadores      |" << endl
             << "|_______________________________|" << endl
             << "\n $ ";
        cin >> menu;
        fflush(stdin);

        switch(menu){

            case 0:
                return 0;

            case 1:
                system("cls");

                cadastrarRoteador(nome, desc, roteadores);

                break;

            case 2:
                system("cls");

                cadastrarTerminal(nome, desc, roteadores, terminais);

                getchar();
                break;

            case 3:
                system("cls");

                removerRoteador(nome, roteadores, terminais);

                getchar();
                break;

            case 4:
                system("cls");

                removerTerminal(nome, terminais);

                getchar();
                break;

            case 5:
                system("cls");

                conectarRoteadores(nome, roteadores);

                getchar();
                break;

            case 6:
                system("cls");

                desconectarRoteadores(nome, desc, roteadores);

                getchar();
                break;

            case 7:
                system("cls");

                frequenciaOperadora(nome, roteadores);

                getchar();
                break;

            case 8:
                system("cls");

                enviarDados(nome, desc, roteadores, terminais);

                getchar();
                break;

            case 9:
                system("cls");

                imprimeTerminal(terminais);

                getchar();
                break;

            case 10:
                system("cls");

                imprime(roteadores);

                getchar();
                break;
        }
    }while(menu != 0);
}

bool nomeCompostoVerify(string nome){

    for(int i = 0; i < nome.size(); i++){
        if(isspace(nome[i])){
            return false;
        }
    }
    return true;
}

bool roteadorNomeIgual(Lista *roteadores, string nome){

    No *roteador = roteadores->inicio;
    while(roteador){
        if(roteador->nome == nome){
            return false;
        }
        roteador = roteador->prox;
    }
    return true;
}

void cadastrarRoteador(string nome, string desc, Lista *roteadores){

    do{
        cout << "Nome do roteador: ";
        getline(cin, nome);
        fflush(stdin);
    }while(!nomeCompostoVerify(nome) && !roteadorNomeIgual(roteadores, nome));

    do{
        cout << "Operadora do roteador: ";
        getline(cin, desc);
        fflush(stdin);
    }while(!nomeCompostoVerify(desc) && !roteadorNomeIgual(roteadores, desc));

    inserirInicio(roteadores, nome, desc);
}

void cadastrarTerminal(string nome, string desc, Lista *roteadores, Lista *terminais){

    string rot;

    if(roteadores->tamanho > 0){

        do{
            cout << "Nome do terminal: ";
            getline(cin, nome);
            fflush(stdin);
        }while(!nomeCompostoVerify(nome));

        do{
            cout << "Localização do terminal: ";
            getline(cin, desc);
            fflush(stdin);
        }while(!nomeCompostoVerify(desc));

        inserirInicio(terminais, nome, desc);

        do{
            cout << "Roteador a ser conectado: ";
            getline(cin, rot);
            fflush(stdin);
        }while(!nomeCompostoVerify(rot));

        No *busca = buscaRecursiva(roteadores->inicio, rot);

        if(busca){

            terminais->inicio->rot = busca;
        }else{

            cout << "Roteador não encontrado.";
        }
    }else{

        cout << "Não há roteadores cadastrados.";
    }
}

void removerRoteador(string nome, Lista *roteadores, Lista *terminais){

    do{
        cout << "Roteador a ser removido: ";
        getline(cin, nome);
        fflush(stdin);
    }while(!nomeCompostoVerify(nome));

    No *busca = buscaRecursiva(roteadores->inicio, nome);
    if(busca){
        if(checkRemocaoRoteador(terminais->inicio->rot, nome)){

            cout << "Há conexões no roteador.";
        }else{

            removeValor(roteadores, nome);
            cout << "Roteador removido.";
        }
    }else{
        cout << "Roteador não encontrado.";
    }
}

void removerTerminal(string nome, Lista *terminais){

    do{
        cout << "Terminal a ser removido: ";
        getline(cin, nome);
        fflush(stdin);
    }while(!nomeCompostoVerify(nome));

    No *busca = buscaRecursiva(terminais->inicio, nome);
    if(busca){

        removeValor(terminais, nome);
        cout << "Terminal removido.";
    }else{

        cout << "Terminal não encontrado.";
    }
}

void conectarRoteadores(string nome, Lista *roteadores){

    cout << "Roteador a ser conectado: ";
    getline(cin, nome);
    fflush(stdin);
    No *rot1 = buscaRecursiva(roteadores->inicio, nome);

    cout << "Conectar no roteador: ";
    getline(cin, nome);
    fflush(stdin);
    No *rot2 = buscaRecursiva(roteadores->inicio, nome);

    if(rot1 == NULL || rot2 == NULL){
        cout << "Roteadores não encontrados.";
    }else{
        insereRoteador(rot1, rot2);
        insereRoteador(rot2, rot1);
    }
}

void desconectarRoteadores(string nome, string desc, Lista *roteadores){

    cout << "Roteador a ser desconectado: ";
    getline(cin, nome);
    fflush(stdin);
    No *rot1 = buscaRecursiva(roteadores->inicio, nome);

    cout << "Desconectar do roteador: ";
    getline(cin, desc);
    fflush(stdin);
    No *rot2 = buscaRecursiva(roteadores->inicio, desc);

    if(rot1 == NULL || rot2 == NULL){

        cout << "Roteadores não encontrados.";
        getchar();
    }else{

        if(removeRoteador(rot1, desc)){

            cout << "Roteador " << rot1->nome << " desconectado.";
        }else{

            cout << "Não foi possível desconectar o roteador " << rot1->nome;
        }

        cout << "\n";

        if(removeRoteador(rot2, nome)){

            cout << "Roteador " << rot2->nome << " desconectado.";
        }else{

            cout << "Não foi possível desconectar o roteador " << rot2->nome;
        }
    }
}

void frequenciaOperadora(string nome, Lista *roteadores){

    do{
        cout << "Operadora: ";
        getline(cin, nome);
        fflush(stdin);
    }while(!nomeCompostoVerify(nome));

    cout << "Quantidade de roteadores: " << frequencia(roteadores->inicio, nome, 0);
}

void enviarDados(string nome, string desc, Lista *roteadores, Lista *terminais){

    cout << "Enviar pacote do terminal: ";
    getline(cin, nome);
    fflush(stdin);
    No *term1 = buscaRecursiva(terminais->inicio, nome);
    term1 = buscaRecursiva(roteadores->inicio, term1->rot->nome);

    cout << "Para o terminal: ";
    getline(cin, desc);
    fflush(stdin);
    No *term2 = buscaRecursiva(terminais->inicio, desc);
    term2 = buscaRecursiva(roteadores->inicio, term2->rot->nome);

    if(term1 == NULL || term2 == NULL){
        cout << "Terminais não encontrados.";
    }else{
        bool envio = false;
        if(enviaPacotes(term1->rot, term2)){
            cout << "Pacotes Enviados\n";
        }else{
            cout << term1->nome;
            No *x = term1->rot;
            while(x){
                cout << x->nome;
                envio = enviaPacotes(x, term2);
                if(envio){
                    break;
                }
                x = x->prox;
            }
            if(envio){
                cout << "Pacotes Enviados\n";
            }else{
                cout << "Não foi possivel enviar dados\n";
            }
        }
    }
}
