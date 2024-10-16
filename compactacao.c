#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <bitset> 

using namespace std;


struct Node {
    char symbol;
    int frequency;
    Node *left, *right;

    Node(char symbol, int frequency) {
        left = right = nullptr;
        this->symbol = symbol;
        this->frequency = frequency;
    }

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
        minHeap.push(internalNode);
    }

    // O nó restante é a raiz da árvore
    return minHeap.top();
}

// Função para gerar os códigos de Huffman e armazená-los em uma tabela
void generateHuffmanCodes(Node* root, string str, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    // Se for uma folha, armazena o código
    if (!root->left && !root->right) {
        huffmanCodes[root->symbol] = str;
    }

    generateHuffmanCodes(root->left, str + "0", huffmanCodes);
    generateHuffmanCodes(root->right, str + "1", huffmanCodes);
}

// Função para codificar uma string usando os códigos de Huffman
string encode(string text, unordered_map<char, string>& huffmanCodes) {
    string encodedString = "";
    for (char ch : text) {
        encodedString += huffmanCodes[ch];
    }
    return encodedString;
}

// Função para decodificar uma string codificada usando a árvore de Huffman
string decode(string encodedString, Node* root) {
    string decodedString = "";
    Node* current = root;
    for (char bit : encodedString) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // Se chegar numa folha, adicionar o símbolo ao resultado
        if (!current->left && !current->right) {
            decodedString += current->symbol;
            current = root;
        }
    }
    return decodedString;
}

int main() {
    // Exemplo de contagem de frequências (você pode adaptar para ler entrada)
    string text = "aaabbc";
    unordered_map<char, int> frequencies;
    
    // Calcular a frequência dos caracteres
    for (char ch : text) {
        frequencies[ch]++;
    }

    // Construir a árvore de Huffman
    Node* root = buildHuffmanTree(frequencies);

    // Gerar os códigos de Huffman
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Imprimir os códigos de Huffman
    cout << "Códigos de Huffman:\n";
    for (auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Codificar o texto original
    string encodedString = encode(text, huffmanCodes);
    cout << "\nTexto original: " << text << endl;
    cout << "Texto codificado (compactado): " << encodedString << endl;

    // Decodificar o texto compactado
    string decodedString = decode(encodedString, root);
    cout << "Texto decodificado: " << decodedString << endl;

    return 0;
}
