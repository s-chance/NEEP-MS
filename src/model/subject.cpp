#include "subject.hpp"

/**
 * @brief 获取政治成绩
 *
 * @return double
 */
double Subject::get_politics() const { return politics; }

/**
 * @brief 获取数学成绩
 *
 * @return double
 */
double Subject::get_mathematics() const { return mathematics; }

/**
 * @brief 获取外语成绩
 *
 * @return double
 */
double Subject::get_foreign() const { return foreign; }

/**
 * @brief 获取专业基础课成绩
 *
 * @return double
 */
double Subject::get_basics() const { return basics; }

/**
 * @brief 获取总分
 *
 * @return double
 */
double Subject::get_sum() const {
  return (politics + mathematics + foreign + basics);
}

/**
 * @brief 数据合法性检测
 *
 * @param score 待检测的数据
 * @param min 最小值
 * @param max 最大值
 * @return true 数据合法
 * @return false 数据不合法
 */
bool Subject::check(const double& score, const double& min,
                    const double& max) const {
  if (score < min || score > max) {
    return false;
  }
  return true;
}

/**
 * @brief 检查是否合格
 *
 * @param value 总分
 * @param v1 政治成绩
 * @param v2 数学成绩
 * @param v3 外语成绩
 * @param v4 专业基础课成绩
 * @return true 合格
 * @return false 不合格
 */
bool Subject::pass(const double& value, const double& v1, const double& v2,
                   const double& v3, const double& v4) const {
  // 总分不满足要求
  if (get_sum() < value) {
    return false;
  }
  // 各科中至少一科不满足要求
  if (politics < v1 || mathematics < v2 || foreign < v3 || basics < v4) {
    return false;
  }

  return true;
}

/**
 * @brief 设置政治成绩
 *
 * @param score
 * @return true
 * @return false
 */
bool Subject::set_politics(const double& score) {
  // 数据合法性检测
  bool res = check(score, 0, 100);
  if (res) {
    politics = score;
    sum += politics;
  }
  return res;
}

/**
 * @brief 设置数学成绩
 *
 * @param score
 * @return true
 * @return false
 */
bool Subject::set_mathematics(const double& score) {
  // 数据合法性检测
  bool res = check(score, 0, 150);
  if (res) {
    mathematics = score;
    sum += mathematics;
  }
  return res;
}

/**
 * @brief 设置外语成绩
 *
 * @param score
 * @return true
 * @return false
 */
bool Subject::set_foreign(const double& score) {
  // 数据合法性检测
  bool res = check(score, 0, 100);
  if (res) {
    foreign = score;
    sum += foreign;
  }
  return res;
}

/**
 * @brief 设置专业基础课成绩
 *
 * @param score
 * @return true
 * @return false
 */
bool Subject::set_basics(const double& score) {
  // 数据合法性检测
  bool res = check(score, 0, 150);
  if (res) {
    basics = score;
    sum += basics;
  }
  return res;
}