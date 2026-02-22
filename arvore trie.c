#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO_ALFABETO 26

// Estrutura do nó da Trie
struct NoTrie {
    struct NoTrie* filhos[TAMANHO_ALFABETO];
    bool ehFimDePalavra;
};

// Cria um novo nó
struct NoTrie* criarNo() {
    struct NoTrie* novoNo = (struct NoTrie*) malloc(sizeof(struct NoTrie));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    novoNo->ehFimDePalavra = false;

    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        novoNo->filhos[i] = NULL;
    }

    return novoNo;
}

// Insere palavra na Trie
void inserir(struct NoTrie* raiz, const char* palavra) {
    struct NoTrie* atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        if (indice < 0 || indice >= TAMANHO_ALFABETO)
            continue;

        if (atual->filhos[indice] == NULL) {
            atual->filhos[indice] = criarNo();
        }

        atual = atual->filhos[indice];
    }

    atual->ehFimDePalavra = true;
}

// Busca palavra na Trie
bool buscar(struct NoTrie* raiz, const char* palavra) {
    struct NoTrie* atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++) {
        int indice = palavra[i] - 'a';

        if (indice < 0 || indice >= TAMANHO_ALFABETO)
            return false;

        if (atual->filhos[indice] == NULL)
            return false;

        atual = atual->filhos[indice];
    }

    return atual != NULL && atual->ehFimDePalavra;
}

// Lista todas as palavras armazenadas
void listarPalavras(struct NoTrie* no, char* buffer, int nivel) {
    if (no->ehFimDePalavra) {
        buffer[nivel] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (no->filhos[i] != NULL) {
            buffer[nivel] = 'a' + i;
            listarPalavras(no->filhos[i], buffer, nivel + 1);
        }
    }
}

// Normaliza string (remove espaços, acentos e deixa minúsculo)
void normalizar(const char* entrada, char* saida) {
    int j = 0;

    for (int i = 0; entrada[i] != '\0'; i++) {
        char c = entrada[i];

        if (c >= 'A' && c <= 'Z')
            c += 32; // converte para minúsculo

        if (c >= 'a' && c <= 'z')
            saida[j++] = c; // mantém apenas letras
    }

    saida[j] = '\0';
}

int main() {
    struct NoTrie* raiz = criarNo();
    char normalizada[100];

    normalizar("Pegadas de Lama", normalizada);
    inserir(raiz, normalizada);

    normalizar("Chave perdida", normalizada);
    inserir(raiz, normalizada);

    normalizar("Livro com página faltando", normalizada);
    inserir(raiz, normalizada);

    normalizar("Lençol manchado", normalizada);
    inserir(raiz, normalizada);

    normalizar("Gaveta perdida", normalizada);
    inserir(raiz, normalizada);

    printf("Palavras armazenadas na Trie:\n\n");

    char buffer[100];
    listarPalavras(raiz, buffer, 0);

    return 0;
}