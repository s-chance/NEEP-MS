#ifndef WORKER_HPP
#define WORKER_HPP

#include "visitor.hpp"
class Worker : public Visitor {
 public:
  Worker() {}
  Worker(const string& id, const string& name, const string& password)
      : User(id, name, password), Visitor(id, name, password) {
    this->student_manager = Visitor::student_manager;
    this->worker_manager = Visitor::worker_manager;
  }

  string get_id() const override;

  string get_password() const override;

  bool set_id() override;

  bool set_password(const string& password) override;

  int login() override;

  bool logout() const override;

  bool add_student(const Student& student) override;

  bool delete_student(const string& id) override;

  bool modify_student(const Student& student) override;

  bool query_all_student_by_condition(const string& value) override;

  bool query_all_student() override;

  LinkedList<Student>* statistics() override;

  void sort() override;

  bool load(const string& filename =
                "/home/entropy/Documents/NEEP-MS/student.txt") override;

  bool save(const string& filename =
                "/home/entropy/Documents/NEEP-MS/student.txt") override;

  ~Worker() {}
};
// 特化模板函数
template <>
inline void LinkedList<Worker>::output(const Worker& user) const {
  cout << "用户ID：" << user.get_id() << endl;
  cout << "用户姓名：" << user.get_name() << endl;
  cout << "用户密码：" << user.get_password() << endl;
}

// 加载文件
template <>
inline bool LinkedList<Worker>::load(const string& filename) {
  ifstream input(filename);
  if (!input.is_open()) {
    cout << "文件打开失败" << endl;
    return false;
  }
  string id, name, password;
  while (input >> id >> name >> password) {
    Worker worker(id, name, password);
    insert_tail(worker);
  }
  input.close();
  return true;
}

// 保存文件
template <>
inline bool LinkedList<Worker>::save(const string& filename) {
  ofstream output(filename);
  if (!output.is_open()) {
    cout << "文件打开失败" << endl;
    return false;
  }
  Node* curr = head->next;
  while (curr != head) {
    output << curr->data.get_id() << " " << curr->data.get_name() << " "
           << curr->data.get_password() << endl;
    curr = curr->next;
  }
  output.close();
  return true;
}
#endif