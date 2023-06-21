#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
// #include "../model/student.cpp"
// #include "../model/student.hpp"
// 向前声明
class User;
class Visitor;
class Worker;
template <typename T>
class LinkedList {
 public:
  struct Node {
    T data;
    Node* prev;
    Node* next;
    Node() {}
    Node(T data) : data(data), prev(nullptr), next(nullptr) {}
  };

  LinkedList<T>() {
    // 哑元头节点初始化
    head = new Node;
    head->prev = head;
    head->next = head;
    size = 0;
  }

  ~LinkedList<T>() {
    Node* curr = head->next;
    while (curr != head) {
      Node* tmp = curr->next;
      delete curr;
      curr = tmp;
    }
    delete head;
  }

  /**
   * @brief 头插法
   *
   * @param data
   * @return true
   * @return false
   */
  bool insert_head(const T& data) {
    Node* newNode = new Node(data);

    // 新节点的指向关系处理
    newNode->prev = head;        // 新节点的前驱为头节点
    newNode->next = head->next;  // 新节点的后继为头文件的后继
    // 头节点的后继节点指向关系处理
    head->next->prev = newNode;  // 头节点的后继的前驱为新节点
    // 头节点指向关系处理
    head->next = newNode;  // 头文件的新后继为新节点

    size++;  // 更新个数
    return true;
  }

  /**
   * @brief 尾插法
   *
   * @param data
   * @return true
   * @return false
   */
  bool insert_tail(const T& data) {
    Node* newNode = new Node(data);

    // 新节点的指向关系处理
    newNode->prev = head->prev;  // 新节点的前驱为头节点的前驱
    newNode->next = head;        // 新节点的后继为头文件
    // 头节点的前驱节点指向关系处理
    head->prev->next = newNode;  // 头节点的前驱的后继为新节点
    // 头节点指向关系处理
    head->prev = newNode;  // 头文件的新前驱为新节点

    size++;  // 更新个数
    return true;
  }

  /**
   * @brief 查询模块，通过准考证号查询，返回节点，用于类内部的查询
   *
   * @param data
   * @return Node*
   */
  Node* search(const string& id) const {
    // 没有数据直接返回nullptr
    if (size == 0) {
      return nullptr;
    }
    Node* current = head->next;
    while (current != head) {
      if (current->data.get_id() == id) {
        // 找到数据后返回
        return current;
      }
      current = current->next;
    }
    // 未找到数据返回nullptr
    return nullptr;
  }

  /**
   * @brief 查询模块，根据数据查询，返回链表，用于类外部的查询
   *
   * @param t
   * @return LinkedList<T>*
   */
  LinkedList<T>* query(const string& value) const {
    if (size == 0) {
      return nullptr;
    }
    LinkedList<T>* res = new LinkedList<T>;
    Node* curr = head->next;
    while (curr != head) {
      if (curr->data.get_id() == value) {
        res->insert_tail(curr->data);
      }
      curr = curr->next;
    }
    return res;
  }

  /**
   * @brief 更新模块，通过准考证号更新
   *
   * @param data
   * @return true
   * @return false
   */
  bool update(const T& data) {
    if (size == 0) {
      return false;
    }
    Node* target = search(data.get_id());
    if (target != nullptr) {
      target->data = data;
    }
    return true;
  }

  /**
   * @brief 删除模块，通过准考证号删除
   *
   * @param id
   * @return true
   * @return false
   */
  bool remove(const string& id) {
    if (size == 0) {
      return 0;
    }
    Node* target = search(id);
    if (target != nullptr) {
      // 修改目标的后继节点的指向状态
      target->next->prev = target->prev;  // 后继节点的新前驱为目标的前驱节点
      // 修改目标的前驱节点的指向状态
      target->prev->next = target->next;  // 前驱节点的新后继为目标的后继节点
      // 修改目标节点自身的指向状态
      target->prev = nullptr;
      target->next = nullptr;
      delete target;
      target = nullptr;
      size--;
      return 1;
    }
    return 0;
  }

  /**
   * @brief 打印模块，打印所有数据
   *
   * @param target
   */
  void print() const {
    if (size == 0) {
      return;
    }
    Node* curr = head->next;
    while (curr && curr != head) {
      output(curr->data);
      curr = curr->next;
    }
  }

  /**
   * @brief 统计模块，通过总分统计
   *
   * @param value
   * @param v1
   * @param v2
   * @param v3
   * @param v4
   * @return LinkedList<T>*
   */
  LinkedList<T>* statistic(const double& value = 310, const double& v1 = 40,
                           const double& v2 = 65, const double& v3 = 40,
                           const double& v4 = 65) const {
    if (size == 0) {
      return nullptr;
    }

    LinkedList<T>* res = new LinkedList<T>;
    Node* curr = head->next;

    while (curr != head) {
      if (curr->data.pass(value, v1, v2, v3, v4)) {
        bool flag = res->insert_tail(curr->data);
      }
      curr = curr->next;
    }
    return res;
  }

  /**
   * @brief 归并排序
   *
   * @param h1
   * @param h2
   */
  void merge(Node*& h1, Node*& h2) {
    Node* a = h1->next;
    Node* b = h2->next;
    LinkedList<T>* res = new LinkedList<T>;
    while (a != h1 && b != h2) {
      if (a->data.get_subject().get_sum() >= b->data.get_subject().get_sum()) {
        res->insert_tail(a->data);
        a = a->next;
      } else {
        res->insert_tail(b->data);
        b = b->next;
      }
    }

    while (a != h1) {
      res->insert_tail(a->data);
      a = a->next;
    }

    while (b != h2) {
      res->insert_tail(b->data);
      b = b->next;
    }

    Node* curr = head->next;
    Node* tmp = res->head->next;
    while (tmp != res->head) {
      curr->data = tmp->data;
      curr = curr->next;
      tmp = tmp->next;
    }
    delete res;
  }

  void spilt(LinkedList<T>*& h1, LinkedList<T>*& h2) {
    Node* fast = head->next;
    Node* slow = head;
    // fast指向最后一个数据或者哑元头
    while (fast != head && fast->next != head) {
      fast = fast->next->next;
      slow = slow->next;
    }

    // 重新构建两个子链
    h1 = new LinkedList<T>;
    h2 = new LinkedList<T>;

    Node* tmp = slow;
    // 前半部分
    while (slow != head) {
      h1->insert_tail(slow->data);
      slow = slow->prev;
    }

    // 后半部分
    // fast指向哑元头，回溯到最后一个数据
    if (fast == head) {
      fast = fast->prev;
    }
    while (fast != tmp) {
      h2->insert_tail(fast->data);
      fast = fast->prev;
    }
  }

  void mergeSort() {
    // 针对哑元头的处理，只有一个数据或着没有数据直接返回
    if (head->next == head || head->next->next == head) {
      return;
    }

    // 分割成两个子链
    LinkedList<T>*h1, *h2;
    spilt(h1, h2);

    h1->mergeSort();
    h2->mergeSort();

    merge(h1->head, h2->head);
  }

  /**
   * @brief 销毁模块
   *
   * @return true
   * @return false
   */
  bool destroy() {
    if (size == 0) {
      return false;
    }
    Node* curr = head->next;
    while (curr != head) {
      Node* tmp = curr->next;
      delete curr;
      curr = tmp;
    }
    head->next = head;
    head->prev = head;
    size = 0;
    return true;
  }

  void output(const T&) const;

  bool load(const string& filename);

  bool save(const string& filename);

  int get_size() const { return size; }

 private:
  Node* head;  // 哑元头节点
  int size;    // 节点个数
};

#endif