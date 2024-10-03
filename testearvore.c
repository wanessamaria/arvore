#include <iostream>        
#include <queue>           
#include <unordered_map>   
#include <vector>          
#include <string>          

using namespace std; 

// Estrutura para um nó da árvore de Huffman
struct Node {
    char symbol;       // O caractere (ou valor) que está sendo codificado
    int frequency;     // Frequência desse caractere
    Node *left, *right; // Nós filhos esquerdo e direito

    // Construtor para um nó de folha
    Node(char symbol, int frequency) {
        left = right = nullptr;
        this->symbol = symbol;
        this->frequency = frequency;
    }
    
    // Construtor para nós internos
    Node(int frequency, Node *left, Node *right) {
        this->symbol = '\0'; 
        this->frequency = frequency;
        this->left = left;
        this->right = right;
    }
};

// Comparador para a fila de prioridade (min-heap)
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// Função para construir a árvore de Huffman
Node* buildHuffmanTree(unordered_map<char, int>& frequencies) {
    // Fila de prioridade para manter os nós da árvore
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    // Inserir todos os nós na fila de prioridade
    for (auto& pair : frequencies) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Combinar nós até restar apenas um
    while (minHeap.size() != 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        // Criar um novo nó interno com a soma das frequências
        int combinedFrequency = left->frequency + right->frequency;
        Node* internalNode = new Node(combinedFrequency, left, right);

        // Inserir o novo nó na fila de prioridade
        minHeap.push(internalNode);
    }

    // O nó restante é a raiz da árvore
    return minHeap.top();
}

// Função para imprimir os códigos de Huffman (recursiva)
void printHuffmanCodes(Node* root, string str) {
    if (!root) return;

    // Se for uma folha, imprime o símbolo e o código correspondente
    if (!root->left && !root->right) {
        cout << root->symbol << ": " << str << endl;
    }

    // Chamada recursiva para os filhos esquerdo e direito
    printHuffmanCodes(root->left, str + "0");
    printHuffmanCodes(root->right, str + "1");
}

int main() {
    // Exemplo de contagem de frequências (você pode adaptar para ler entrada)
    unordered_map<char, int> frequencies = {
        {'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}
    };

    // Construir a árvore de Huffman
    Node* root = buildHuffmanTree(frequencies);

    // Imprimir os códigos de Huffman
    cout << "Códigos de Huffman para os símbolos são:\n";
    printHuffmanCodes(root, "");

    return 0;
}
