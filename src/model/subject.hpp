#ifndef SUBJECT_HPP
#define SUBJECT_HPP

// 学科类，带有数据自检功能
class Subject {
 public:
  Subject() : politics(0), mathematics(0), foreign(0), basics(0), sum(0) {}
  Subject(const double& p, const double& m, const double& f, const double& b)
      : politics(p),
        mathematics(m),
        foreign(f),
        basics(b),
        sum(p + m + f + b) {}
  double get_politics() const;

  double get_mathematics() const;

  double get_foreign() const;

  double get_basics() const;

  double get_sum() const;  // 获取总分

  bool check(const double& score, const double& min,
             const double& max) const;  // 数据合法性检测

  bool pass(const double& value = 310, const double& v1 = 40,
            const double& v2 = 65, const double& v3 = 40,
            const double& v4 = 65) const;  // 检查是否合格

  bool set_politics(const double& score);

  bool set_mathematics(const double& score);

  bool set_foreign(const double& score);

  bool set_basics(const double& score);

 private:
  double politics;     // 政治成绩
  double mathematics;  // 数学成绩
  double foreign;      // 外语成绩
  double basics;       // 专业基础课成绩
  double sum;          // 总分
};

#endif