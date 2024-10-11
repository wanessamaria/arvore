#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

// Estrutura para um nó da árvore de Huffman
struct Node {
    char symbol;       
    int frequency;     
    Node *left, *right; 

    // Construtor para um nó de folha
    Node(char symbol, int frequency);

    // Construtor para nós internos
    Node(int frequency, Node *left, Node *right);
};

// Comparador para a fila de prioridade (min-heap)
struct Compare {
    bool operator()(Node* left, Node* right);
};

// Função para construir a árvore de Huffman
Node* buildHuffmanTree(std::unordered_map<char, int>& frequencies);

// Função para imprimir os códigos de Huffman
void printHuffmanCodes(Node* root, std::string str);

#endif // HUFFMAN_H