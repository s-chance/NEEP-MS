#ifndef DATA_HPP
#define DATA_HPP

#include <string>

#include "../model/student.hpp"
#include "../structure/linkedlist.hpp"
// 共享数据类
class Data {
 public:
  Data() {}

  virtual bool init() = 0;  // 检测数据是否加载，未加载则从文件读取加载

  virtual bool is_exists(const string& id) const = 0;  // 检测指定的数据是否存在

  virtual bool add_student(const Student& student) = 0;

  virtual bool delete_student(const string& number) = 0;

  virtual bool modify_student(const Student& student) = 0;

  virtual bool query_all_student_by_condition(const string& value) = 0;

  virtual bool query_all_student() = 0;

  virtual LinkedList<Student>* statistics() = 0;

  virtual void sort() = 0;

  virtual bool load(const string& input) = 0;

  virtual bool save(const string& output) = 0;

  virtual ~Data() {}

 protected:
  LinkedList<Student>* student_manager;  // 管理学生信息
  LinkedList<Worker>* worker_manager;    // 管理工作人员信息
};

// 特化模板函数
/**
 * @brief 格式化输出
 *
 * @tparam
 * @param student
 */
template <>
inline void LinkedList<Student>::output(const Student& student) const {
  cout << "考生姓名：" << student.get_name() << endl;
  cout << "准考证号：" << student.get_id() << endl;
  cout << "报考类别：" << student.get_major() << endl;
  cout << "是否为统招生：" << (student.get_fresh() ? "是" : "否") << endl;
  cout << "政治成绩：" << student.get_subject().get_politics() << endl;
  cout << "数学成绩：" << student.get_subject().get_mathematics() << endl;
  cout << "外语成绩：" << student.get_subject().get_foreign() << endl;
  cout << "专业课成绩：" << student.get_subject().get_basics() << endl;
  cout << "总分：" << student.get_subject().get_sum() << endl;
  cout << "是否通过：" << (student.pass(310) ? "是" : "否") << endl;
}

/**
 * @brief 文件读取
 *
 * @return true
 * @return false
 */
template <>
inline bool LinkedList<Student>::load(const string& filename) {
  ifstream input(filename);
  if (!input.is_open()) {
    cout << "文件打开失败" << endl;
    return false;
  }
  string name, number, major;
  bool fresh;
  double politics, mathematics, foreign, basics;
  while (input >> name >> number >> major >> fresh >> politics >> mathematics >>
         foreign >> basics) {
    Student s(name, number, major, fresh,
              *new Subject(politics, mathematics, foreign, basics));
    insert_tail(s);
  }
  input.close();
  return true;
}

/**
 * @brief 文件保存
 *
 * @return true
 * @return false
 */
template <>
inline bool LinkedList<Student>::save(const string& filename) {
  ofstream output(filename);
  if (!output.is_open()) {
    cout << "文件打开失败" << endl;
    return false;
  }
  LinkedList<Student>::Node* curr = head->next;
  while (curr != head) {
    output << curr->data.get_name() << " " << curr->data.get_id() << " "
           << curr->data.get_major() << " " << curr->data.get_fresh() << " "
           << curr->data.get_subject().get_politics() << " "
           << curr->data.get_subject().get_mathematics() << " "
           << curr->data.get_subject().get_foreign() << " "
           << curr->data.get_subject().get_basics() << endl;
    curr = curr->next;
  }
  output.close();
  return true;
}
#endif