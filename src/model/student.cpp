#include "student.hpp"

#include <string>

#include "subject.hpp"

/**
 * @brief 获取学生姓名
 *
 * @return string
 */
string Student::get_name() const { return name; }

/**
 * @brief 获取学生准考证号
 *
 * @return string
 */
string Student::get_id() const { return id; }

/**
 * @brief 获取学生报考专业
 *
 * @return string
 */
string Student::get_major() const { return major; }

/**
 * @brief 获取学生是否为应届生
 *
 * @return true
 * @return false
 */
bool Student::get_fresh() const { return fresh; }

/**
 * @brief 获取学生4门课程成绩
 *
 * @return Subject
 */
Subject Student::get_subject() const { return subject; }

/**
 * @brief 检测数据是否为空
 *
 * @param value
 * @return true
 * @return false
 */
bool Student::is_not_null(const string& value) const {
  if (value == "") {
    return false;
  }
  return true;
}

/**
 * @brief 检查是否合格
 *
 * @param value 总分
 * @param v1 政治
 * @param v2 数学
 * @param v3 外语
 * @param v4 专业基础课
 * @return true
 * @return false
 */
bool Student::pass(const double& value, const double& v1, const double& v2,
                   const double& v3, const double& v4) const {
  return subject.pass(value, v1, v2, v3, v4);
}

/**
 * @brief 设置学生姓名
 *
 * @param name
 * @return true
 * @return false
 */
bool Student::set_name(const string& name) {
  bool res = is_not_null(name);
  if (res) {
    this->name = name;
  }
  return res;
}

/**
 * @brief 设置学生准考证号
 *
 * @param id
 * @return true
 * @return false
 */
bool Student::set_id(const string& id) {
  bool res = is_not_null(id);
  if (res) {
    this->id = id;
  }
  return res;
}

/**
 * @brief 设置学生报考专业
 *
 * @param major
 * @return true
 * @return false
 */
bool Student::set_major(const string& major) {
  bool res = is_not_null(major);
  if (res) {
    this->major = major;
  }
  return res;
}

/**
 * @brief 设置学生是否为应届生
 *
 * @param fresh
 * @return true
 * @return false
 */
bool Student::set_fresh(const bool& fresh) {
  this->fresh = fresh;
  return true;
}

/**
 * @brief 设置学生4门课程成绩
 *
 * @param subject
 * @return true
 * @return false
 */
bool Student::set_subject(const Subject& subject) {
  this->subject = subject;
  return true;
}
