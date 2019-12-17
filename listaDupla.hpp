typedef struct no{

    string nome;
    string desc;
    struct no *prox;
    struct no *ant;
    struct no *rot;
    no(){//construtor
        nome = "";
        desc = "";
        prox = NULL;
        ant = NULL;
        rot = NULL;
    }
} No;

typedef struct lista{

    No *inicio;
    No *fim;
    int tamanho;
    lista(){//construtor
        inicio = NULL;
        fim = NULL;
        tamanho = 0;
    }
    ~lista(){//destrutor
        No *n = inicio;
        while(n){
            No *aux = n;
            n = n->prox;
            delete aux; //libera memória;
        }
        inicio = NULL;
        fim = NULL;
        tamanho = 0;
    }
} Lista;

void inserirInicio(Lista *l, string nome, string desc){

    No *novo = new No();
    novo->nome = nome;
    novo->desc = desc;
    novo->prox = l->inicio;
    if(!l->inicio){//quer dizer que a lista estava vazia
        l->fim = novo;
    }else{
        l->inicio->ant = novo;
    }
    l->inicio = novo;
    l->tamanho++;
}

bool removeValor(Lista *l, string nome){

    No *anterior = NULL;
    No *atual = l->inicio;
    while(atual && atual->nome != nome){
        anterior = atual;
        atual = atual->prox;
    }
    if(!atual){//não achou
        return false;
    }
    if(!anterior){//valor a ser removido é o primeiro da lista
        l->inicio = atual->prox;
        if(!l->inicio){//lista vai ficar vazia
            l->fim = l->inicio;
        }else{
            l->inicio->ant = NULL;
        }
    }else{
        anterior->prox = atual->prox;
        if(!atual->prox){//o valor a ser excluido é o ultimo da lista
            l->fim = anterior;
        }else{
            atual->prox->ant = anterior;
        }
    }
    l->tamanho--;
    delete(atual);
    return true;
}

void imprimeTerminal(Lista *l){

    No *n = l->inicio;
    cout <<"Nome\tDescrição\tLigação"<<endl<<endl;
    while(n){
        cout << n->nome;
        cout << "\t";
        cout << n->desc;
        cout << "\t\t";
        cout << n->rot->nome;
        n = n->prox;
        if(n){
            cout << "\n";
        }
    }
    cout << "\n";
}

void imprime(Lista *l){

    No *n = l->inicio;
    cout <<"Nome\tDescrição\tLigação"<<endl<<endl;
    while(n){
        cout << n->nome;
        cout << "\t";
        cout << n->desc;
        cout << "\t\t";
        No *ligado = n->rot;
        while(ligado != NULL){
            cout << ligado->nome << " - ";
            ligado = ligado->prox;
        }
        n = n->prox;
        if(n){
            cout << "\n";
        }
    }
    cout << "\n";
}

No* buscaRecursiva(No *no, string nome){

    if (!no) { // se nao tiver mais elementos
        return NULL;
    }else if (no->nome == nome){
        return no;
    }else{
        return buscaRecursiva(no->prox, nome);
    }
}

int frequencia(No *lista, string operadora, int c){

    if (!lista) { // se nao tiver mais elementos
        return c;
    }else if (lista->desc == operadora){
        c++;
    }
    return frequencia(lista->prox, operadora, c);
}

No* conectaRoteadorTerminal(No *roteador, string nome,No *terminal){

    if (!roteador) { // se nao tiver mais elementos
        return NULL;
    }else if (roteador->nome == nome){
        terminal->rot = roteador;
        return roteador;
    }else{
        return conectaRoteadorTerminal(roteador->prox, nome, terminal);
    }
}

bool checkRemocaoRoteador(No *lista, string nome){

    if (!lista) { // se nao tiver mais elementos
        return false;
    }else if (lista->nome == nome){
        return true;
    }else{
        cout << lista->nome << "\n";
        return buscaRecursiva(lista->prox, nome);
    }
}

void insereRoteador(No *rot1, No* rot2){

    No *novo = new No();
    novo->prox = rot1->rot;
    novo->nome = rot2->nome;
    rot1->rot = novo;
}

bool removeRoteador(No *rot1, string nome){

    No *atual = rot1->rot;
    No *anterior = NULL;
    while (atual && atual->nome != nome){
        anterior = atual;
        atual = atual->prox;
    }
    if (!atual) //se n?o encontrou valor -> atual == NULL
        return false;
    if (!atual->ant){ //valor está no primeiro nó da rot1 -> anterior == NULL
        rot1->rot = atual->prox;
    }else{
        atual->ant->prox = atual->prox;
        atual->prox->ant = atual->ant;
    } // valor está no meio/final da rot1
    return true;
}

bool enviaPacotes(No *rot1, No *rot2){

    if (!rot1) { // se n�o tiver mais elementos
        return false;
    }else if (rot1->nome == rot2->nome){
        return true;
    }else{
        return enviaPacotes(rot1->prox, rot2);
    }
}

ostream& operator<<(ostream& os, const No *n){

    return os << n->nome;
}

ostream& operator << (ostream& os, const Lista *l){

    No *n = l->inicio;
    while(n){
        os << n;
        n = n->prox;

        if(n){
            os << ", ";
        }
    }
    return os;
}
