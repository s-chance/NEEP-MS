#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <fstream>
#include <string>

#include "data.hpp"
#include "user.hpp"
// 访客类，只能查询自己的相关信息
class Visitor : virtual public User, virtual public Data {
 public:
  Visitor(const string& id = "visitor", const string name = "visitor",
          string password = "visitor")
      : User(id, name, password) {}

  string get_id() const override;

  string get_name() const override;

  string get_password() const override;

  bool set_id() override;

  bool set_name(const string& name) override;

  bool set_password(const string& password) override;

  int login() override;

  bool logout() const override;

  bool register_user() override;

  bool init() override;  // 检测数据是否已经存在

  bool is_exists(const string& id) const override;

  bool add_student(const Student& student) override;

  bool delete_student(const string& number) override;

  bool modify_student(const Student& student) override;

  // 访客只能根据准考证号查询自己的信息
  bool query_all_student_by_condition(const string& number) override;

  bool query_all_student() override;

  LinkedList<Student>* statistics() override;

  void sort() override;

  bool load(const string& filename =
                "/home/entropy/Documents/NEEP-MS/student.txt") override;

  bool save(const string& filename =
                "/home/entropy/Documents/NEEP-MS/student.txt") override;

  ~Visitor() override {}
};

// 特化模板函数
template <>
inline void LinkedList<Visitor>::output(const Visitor& user) const {
  cout << "用户ID：" << user.get_id() << endl;
  cout << "用户姓名：" << user.get_name() << endl;
  cout << "用户密码：" << user.get_password() << endl;
}

// 加载文件
template <>
inline bool LinkedList<Visitor>::load(const string& filename) {
  ifstream input(filename);
  if (!input.is_open()) {
    cout << "文件打开失败" << endl;
    return false;
  }
  string id, name, password;
  while (input >> id >> name >> password) {
    Visitor visitor(id, name, password);
    insert_tail(visitor);
  }
  input.close();
  return true;
}

// 保存文件
template <>
inline bool LinkedList<Visitor>::save(const string& filename) {
  ofstream output(filename, ios::app);
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