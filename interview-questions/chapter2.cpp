#include <stdio.h>
#include <map>
#include <cmath>

template<typename T>
struct Node {
    Node *Next;
    T Data;
    Node(T data) : Next(nullptr), Data(data) {}
};

template<typename T>
class LinkedList {
    Node<T> *_head;
    Node<T> *_tail;

    void _remove_head() {
        delete _head;
        _head = _tail = nullptr;
    }
    void _remove_tail() {
        if (!_head) return;
        auto tmp = _head;
        while (tmp->Next != _tail) {
            tmp = tmp->Next;
        }
        tmp->Next = nullptr;
        delete _tail;
        _tail = tmp;
    }
public:
    LinkedList() : _head(nullptr), _tail(nullptr) {}
    ~LinkedList() {
        while (_head) {
            auto next = _head->Next;
            delete _head;
            _head = next;
        }
        _head = _tail = nullptr;
    }
    void append(T data) {
        auto node = new Node<T>(data);
        if (!_head) {
            _head = node;
            _tail = _head;
        }
        else {
            _tail->Next = node;
            _tail = node;
        }
    }
    void prepend(T data) {
        if (!_head) {
            append(data);
        }
        else {
            auto node = new Node<T>(data);
            node->Next = _head;
            _head = node;
        }
    }
    void remove(Node<T> *node) {
        if (!_head || !node) {
            return;
        }
        if (node == _head) {
            _remove_head();
            return;
        }
        if (node == _tail) {
            _remove_tail();
            return;
        }
        auto tmp = _head;
        while (tmp) {
            if (tmp->Next == node) {
                break;
            }
            tmp = tmp->Next;
        }
        if (!tmp) { // Node not in list
            return;
        }
        tmp->Next = node->Next;
        delete node;
    }
    Node<T> *head(void) const {
        return _head;
    }
    Node<T> *tail(void) const {
        return _tail;
    }
};

void print_int_list(LinkedList<int> *list) {
    auto tmp = list->head();
    printf("(");
    while (tmp) {
        printf("%d, ", tmp->Data);
        tmp = tmp->Next;
    }
    printf("\b\b)\n"); // \b\b gets rid of the ", "
}

// 2.1 Write code to remove duplicates from an unsorted linked list.
template <typename T>
void remove_duplicates(LinkedList<T> &list) {
    auto tmp = list.head();
    std::map<T, int> data;
    while (tmp) {
        auto next = tmp->Next;
        data[tmp->Data]++;
        if (data[tmp->Data] > 1) {
            list.remove(tmp);
        }
        tmp = next;
    }
}

// 2.1 FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?
template <typename T>
void remove_duplicates_no_buffer_rec(LinkedList<T> &owner, Node<T> *start, T d) {
    if (!start) return;
    auto tmp = start->Next;
    while (tmp) {
        if (tmp->Data == d)
            owner.remove(tmp);
        tmp = tmp->Next;
        if (tmp)
            remove_duplicates_no_buffer_rec(owner, tmp, tmp->Data);
    }
}
template <typename T>
void remove_duplicates_no_buffer(LinkedList<T> &list) {
    remove_duplicates_no_buffer_rec(list, list.head(), list.head()->Data);
}

// 2.2 Implement an algorithm to find the kth to last element of a singly linked
// list.
template <typename T>
Node<T> *find_kth_to_last(LinkedList<T> &list, int k) {
    auto tmp = list.head();
    int count = 0;
    if (k == 0) {
        return list.tail();
    }
    while (tmp) {
        ++count;
        tmp = tmp->Next;
    }
    if (k > count) {
        return nullptr;
    }
    if (k == count) {
        return list.head();
    }
    tmp = list.head();
    while (tmp) {
        if (count == k) {
            return tmp;
        }
        --count;
        tmp = tmp->Next;
    }
    return nullptr;
}

// 2.3 Implement an algorithm to delete a node in the middle of a singly linked
// list, given only access to that node.
// EXAMPLE
// Input: the node c from the linked list a->b->c->d->e
// Result: nothing is returned, but the new linked list looks like a- >b- >d->e
template<typename T>
void remove_with_only_node(Node<T> *node) {
    if (!node || !node->Next) return;
    // Note this is impossible when attempting to remove the tail
    // and this makes freeing the node impractical
    node->Data = node->Next->Data;
    node->Next = node->Next->Next;
}

// 2.4 Write code to partition a linked list around a value x, such that all
// nodes less than x come before all nodes greater than or equal to x
void partition(LinkedList<int> &list, int x) {
    /* TODO: implement 2.4 */
}

// 2.5 You have two numbers represented by a linked list, where each node
// contains a single digit. The digits are stored in reverse order, such that
// the 1's digit is at the head of the list. Write a function that adds the
// two numbers and returns the sum as a linked list.
// EXAMPLE
// Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295
// Output: (2 -> 1 -> 9). That is, 912.
int linked_list_to_num_reverse(const LinkedList<int> &list) {
    int exp = 0, result = 0;
    auto tmp = list.head();
    while (tmp) {
        result += tmp->Data * pow(10, exp++);
        tmp = tmp->Next;
    }
    return result;
}
LinkedList<int> *add_linked_list_reverse(const LinkedList<int> &lhs, const LinkedList<int> &rhs) {
    int lhs_num = linked_list_to_num_reverse(lhs);
    int rhs_num = linked_list_to_num_reverse(rhs);
    int sum = lhs_num + rhs_num;
    auto result = new LinkedList<int>();
    while (sum) {
        result->append(sum % 10);
        sum /= 10;
    }
    return result;
}

// 2.5 FOLLOWUP
// Suppose the digits are stored in forward order. Repeat the above problem.
// EXAMPLE
// Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
// Output: (9 -> 1 -> 2). That is, 912.
int linked_list_to_num_forward(const LinkedList<int> &list) {
    int exp = 0, result = 0;
    auto tmp = list.head();
    while (tmp) {
        ++exp;
        tmp = tmp->Next;
    }
    tmp = list.head();
    while (tmp) {
        result += tmp->Data * pow(10, exp-1);
        --exp;
        tmp = tmp->Next;
    }
    return result;
}
LinkedList<int> *add_linked_list_forward(const LinkedList<int> &lhs, const LinkedList<int> &rhs) {
    int lhs_num = linked_list_to_num_forward(lhs);
    int rhs_num = linked_list_to_num_forward(rhs);
    int sum = lhs_num + rhs_num;
    auto result = new LinkedList<int>();
    while (sum) {
        result->prepend(sum % 10);
        sum /= 10;
    }
    return result;
}

// 2.6 Given a circular linked list, implement an algorithm which returns the node
// at the beginning of the loop.
// DEFINITION
// Circular linked list: A (corrupt) linked list in which a node's next pointer
// points to an earlier node, so as to make a loop in the linked list.
// EXAMPLE
// Input: A->B->C->D->E->C [the same C as earlier]
// Output: C
template<typename T>
Node<T> *find_cycle(const LinkedList<T> &list) {
    std::map<Node<T>*, int> visited;
    auto tmp = list.head();
    while (tmp) {
        if (visited[tmp] > 0) {
            return tmp;
        }
        visited[tmp]++;
        tmp = tmp->Next;
    }
    return nullptr;
}

// 2.7 Implement a function to check if a linked list is a palindrome.
template<typename T>
bool is_palindrome(const LinkedList<T> &list) {
    /* TODO: implement 2.7 */
}

int main() {
    LinkedList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.append(i+1);
    }
    list.prepend(5);
    list.append(5);
    list.append(5);
    print_int_list(&list);
    remove_duplicates(list);
    print_int_list(&list);

    LinkedList<int> list2;
    for (int i = 0; i < 5; ++i) {
        list2.append(i+1);
    }
    list2.prepend(5);
    list2.append(5);
    list2.append(5);
    print_int_list(&list2);
    remove_duplicates_no_buffer(list2);
    print_int_list(&list2);

    auto second_to_last = find_kth_to_last(list, 2);
    printf("%d\n", second_to_last->Data);

    remove_with_only_node(list2.head()->Next);
    print_int_list(&list2);

// Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295
// Output: (2 -> 1 -> 9). That is, 912.
    LinkedList<int> lhs;
    lhs.append(7);
    lhs.append(1);
    lhs.append(6);

    LinkedList<int> rhs;
    rhs.append(5);
    rhs.append(9);
    rhs.append(2);

    auto result = add_linked_list_reverse(lhs, rhs);
    puts("Add:");
    print_int_list(&lhs);
    puts("+");
    print_int_list(&rhs);
    puts("=");
    print_int_list(result);

// Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
// Output: (9 -> 1 -> 2). That is, 912.
    LinkedList<int> lhs2;
    lhs2.append(6);
    lhs2.append(1);
    lhs2.append(7);

    LinkedList<int> rhs2;
    rhs2.append(2);
    rhs2.append(9);
    rhs2.append(5);

    result = add_linked_list_forward(lhs2, rhs2);
    puts("Add:");
    print_int_list(&lhs2);
    puts("+");
    print_int_list(&rhs2);
    puts("=");
    print_int_list(result);

    return 0;
}
