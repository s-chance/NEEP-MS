#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

#include "subject.hpp"
using namespace std;
// 学生类，带有数据合法性检测
class Student {
 public:
  Student() {}
  Student(const string& name, const string& id, const string& major,
          const bool& fresh, Subject subject)
      : name(name), id(id), major(major), fresh(fresh), subject(subject) {}

  string get_name() const;

  string get_id() const;

  string get_major() const;

  bool get_fresh() const;

  Subject get_subject() const;

  bool is_not_null(const string& value) const;  // 数据合法性检测

  bool pass(const double& value = 310, const double& v1 = 40,
            const double& v2 = 65, const double& v3 = 40,
            const double& v4 = 65) const;  // 检查是否合格

  bool set_name(const string& name);

  bool set_id(const string& id);

  bool set_major(const string& major);

  bool set_fresh(const bool& fresh);

  bool set_subject(const Subject& subject);

 private:
  string name;      // 考生姓名
  string id;        // 准考证号
  string major;     // 报考专业
  bool fresh;       // 是否为应届生
  Subject subject;  // 4门课程成绩
};
#endif