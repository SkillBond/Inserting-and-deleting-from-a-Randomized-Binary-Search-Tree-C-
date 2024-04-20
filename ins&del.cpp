#include <iostream>
#include <cstdlib>
#include <memory>
#include <ctime> // Для доступа к std::time

// Узел рандомизированного бинарного дерева
struct Node {
    int key;
    int priority;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    // Конструктор узла
    Node(int _key) : key(_key), priority(std::rand()), left(nullptr), right(nullptr) {}
};

// Объявление функции insert
std::unique_ptr<Node> insert(std::unique_ptr<Node> root, int key);

// Объявление функции deleteNode
std::unique_ptr<Node> deleteNode(std::unique_ptr<Node> root, int key);

// Объявление функции minValueNode
std::unique_ptr<Node> minValueNode(std::unique_ptr<Node> root);

// Функция печати дерева
void printTree(Node* root) {
    if (root) {
        printTree(root->left.get());
        std::cout << root->key << " ";
        printTree(root->right.get());
    }
}

// Функция вставки нового узла в рандомизированное бинарное дерево
std::unique_ptr<Node> insert(std::unique_ptr<Node> root, int key) {
    auto new_node = std::make_unique<Node>(key); // Создаем новый узел

    if (!root) {
        return new_node;
    }

    if (key < root->key) {
        root->left = insert(std::move(root->left), key); // Рекурсивно вставляем новый узел в левое поддерево
    } else {
        root->right = insert(std::move(root->right), key); // Рекурсивно вставляем новый узел в правое поддерево
    }

    return root;
}

// Функция удаления узла из рандомизированного бинарного дерева
std::unique_ptr<Node> deleteNode(std::unique_ptr<Node> root, int key) {
    if (!root) {
        return nullptr;
    }

    if (key < root->key) {
        root->left = deleteNode(std::move(root->left), key);
    } else if (key > root->key) {
        root->right = deleteNode(std::move(root->right), key);
    } else {
        if (!root->left || !root->right) {
            auto child = std::move(root->left ? std::move(root->left) : std::move(root->right));
            return child;
        }

        auto successor = minValueNode(std::move(root->right));
        root->key = successor->key;
        root->right = deleteNode(std::move(root->right), successor->key);
    }

    return root;
}

// Функция для поиска узла с минимальным ключом в поддереве
std::unique_ptr<Node> minValueNode(std::unique_ptr<Node> root) {
    while (root->left) {
        root = std::move(root->left);
    }

    return root;
}

// Основная функция программы
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Инициализируем генератор случайных чисел

    std::unique_ptr<Node> root = nullptr;

    // Вставляем элементы
    root = insert(std::move(root), 4);
    root = insert(std::move(root), 7);
    root = insert(std::move(root), -11);
    root = insert(std::move(root), 11);
    root = insert(std::move(root), 10);

    // Удаляем элемент
    root = deleteNode(std::move(root), 7);
    // Если не нужно удалять элемент поставьте 0


    // Печатаем дерево
    printTree(root.get());
    std::cout << std::endl;

    return 0;
}