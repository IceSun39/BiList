#include <iostream>
#include <Windows.h>
#include "BiList.h"

// Допоміжні функції
template<typename T, typename Predicate>
void change1(BiList<T>& list, Predicate is_odd) {
    BiNode<T>* temp = list.get_front();
    while (temp) {
        if (is_odd(temp->data)) {
            list.insert(temp->data + 1, temp);
            temp = temp->next;
        }
        else {
            list.insert(temp, temp->data - 1);
            temp = temp->next->next;
        }
    }
}

template<typename T>
void change2(BiList<T>& list) {
    BiNode<T>* temp = list.get_front();
    while (temp) {
        if (temp->data < 0) {
            BiNode<T>* nxt = temp->next;
            list.remove(temp);
            temp = nxt;
        }
        else {
            temp = temp->next;
        }
    }
}

template<typename T>
void swapNodes(BiList<T>& list) {
    T node1, node2;
    std::cout << "Введіть які вузли хочете змінити місцями: ";
    std::cin >> node1 >> node2;
    list.swap(list.find(node1), list.find(node2));
}

// Головна функція програми
template<typename T>
void run_program() {
    BiList<T> list;
    BiList<T> otherList;
    int const SIZE = 10;
    std::cout << "Введіть " << SIZE << " чисел: ";
    for (int i = 0; i < SIZE; i++) {
        T num;
        std::cin >> num;
        list.push_back(num);
    }
    std::cout << "Отриманий список: "; list.forward_view(); std::cout << "\n";

    int state = 0;
    do {
        std::cout << "\nМеню:\n"
            << "1 - додати елемент після заданого вузла\n"
            << "2 - додати елемент перед заданим вузлом\n"
            << "3 - видалити заданий вузол\n"
            << "4 - додати новий вузол в кінець\n"
            << "5 - додати новий вузол в початок\n"
            << "6 - вивести список в звичайному порядку\n"
            << "7 - вивести список у зворотньому порядку\n"
            << "8 - вставити новий список після заданого індексу\n"
            << "9 - копіювати підсписок з індексів [index1, index2) в інший список\n"
            << "10 - змінити задані вузли місцями\n"
            << "11 - відсортувати список\n"
            << "12 - вставити після парних значення -1 та перед непарними +1\n"
            << "13 - видалити всі від'ємні числа\n"
            << "0 - кінець програми\n";
        std::cin >> state;
        switch (state) {
        case 1: {
            T data, node;
            std::cout << "Введіть значення яке потрібно вставити: "; std::cin >> data;
            std::cout << "\nВведіть після якого вузла вставити: "; std::cin >> node;
            list.insert(list.find(node), data);
            break;
        }
        case 2: {
            T data, node;
            std::cout << "Введіть значення яке потрібно вставити: "; std::cin >> data;
            std::cout << "\nВведіть перед яким вузлом вставити: "; std::cin >> node;
            list.insert(data, list.find(node));
            break;
        }
        case 3: {
            T node;
            std::cout << "Введіть вузол для видалення: "; std::cin >> node;
            list.remove(list.find(node));
            break;
        }
        case 4: {
            T data;
            std::cout << "Введіть значення для додавання в кінець: "; std::cin >> data;
            list.push_back(data);
            break;
        }
        case 5: {
            T data;
            std::cout << "Введіть значення для додавання в початок: "; std::cin >> data;
            list.push_front(data);
            break;
        }
        case 6: {
            list.forward_view(); std::cout << "\n";
            break;
        }
        case 7: {
            list.reverse_view(); std::cout << "\n";
            break;
        }
        case 8: {
            otherList.clear();
            int index;
            std::cout << "Вкажіть розмір нового списку: ";
            int m; std::cin >> m;
            std::cout << "Введіть " << m << " елементів нового списку: ";
            for (int i = 0; i < m; i++) { T v; std::cin >> v; otherList.push_back(v); }
            std::cout << "Введіть індекс після якого вставити список: "; std::cin >> index;
            list.slice_in(otherList.get_front(), index);
            break;
        }
        case 9: {
            int i1, i2;
            std::cout << "Введіть початковий та кінцевий індекси [index1 index2): "; std::cin >> i1 >> i2;
            if (i1 < 0 || i2 < 0 || i1 > SIZE || i2 > SIZE) {
                std::cout << "Введіть правильні індекси!\n";
                break;
            }
            otherList.clear();
            std::cout << "Вкажіть розмір нового списку: ";
            int m; std::cin >> m;
            std::cout << "Введіть " << m << " елементів нового списку: ";
            for (int i = 0; i < m; i++) { T v; std::cin >> v; otherList.push_back(v); }
            list.slice_out(otherList.get_front(), i1, i2);
            std::cout << "Підсписок скопійовано в інший список: "; otherList.forward_view(); std::cout << "\n";
            break;
        }
        case 10: {
            swapNodes(list);
            break;
        }
        case 11: {
            list.sort();
            std::cout << "Відсортований список: "; list.forward_view(); std::cout << "\n";
            break;
        }
        case 12: {
            change1<T>(list, [](T x) { return x % 2 != 0; });
            std::cout << "Після зміни: "; list.forward_view(); std::cout << "\n";
            break;
        }
        case 13: {
            change2(list);
            std::cout << "Після видалення від'ємних: "; list.forward_view(); std::cout << "\n";
            break;
        }
        case 0: break;
        default: std::cout << "Невірний пункт меню\n";
        }
    } while (state != 0);
}

int main() {
    SetConsoleOutputCP(1251);
    int type = 0;
    std::cout << "Який тип данних використовувати?\n"
        << "1 - int\n"
        << "2 - short\n"
        << "3 - long\n";
    std::cin >> type;
    switch (type) {
    case 1:
    {
        run_program<int>();
        break;
    }
    case 2:
    {
        run_program<short>();
        break;
    }
    case 3:
    {
        run_program<long>();
        break;
    }
    default:
    {
        std::cout << "Неправильне число!!!";
        break;
    }
    }
    
    return 0;
}
