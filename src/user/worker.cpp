#include "worker.hpp"

string Worker::get_id() const { return id; }

string Worker::get_password() const { return password; }

bool Worker::set_id() {
  auto now = chrono::system_clock::now();
  time_t now_c = chrono::system_clock::to_time_t(now);

  char time_str[20];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d-%H-%M-%S", localtime(&now_c));

  this->id = "W" + string(time_str);
  return true;
}

bool Worker::set_password(const string& password) {
  this->password = password;
  return true;
}

int Worker::login() {
  cout << "您已经登录！" << endl;
  return 2;
}

bool Worker::logout() const {
  cout << "退出登录成功！" << endl;
  return true;
}

/**
 * @brief 新增模块，头插法
 *
 * @param student
 * @return true
 * @return false
 */
bool Worker::add_student(const Student& student) {
  if (student.get_id().length() != 15) {
    cout << "准考证号不合法" << endl;
    return false;
  }
  // 检测数据是否已经存在
  if (is_exists(student.get_id())) {
    cout << "数据已存在，不能重复！" << endl;
    return false;
  }
  return student_manager->insert_tail(student);
}

/**
 * @brief 删除模块
 *
 * @param id
 * @return true
 * @return false
 */

bool Worker::delete_student(const string& id) {
  if (id.length() != 15) {
    cout << "准考证号不合法" << endl;
    return false;
  }
  // 检测数据是否已经存在
  if (is_exists(id)) {
    return student_manager->remove(id);
  }
  cout << "没有找到该考生" << endl;
  return false;
}

bool Worker::modify_student(const Student& student) {
  if (student.get_id().length() != 15) {
    cout << "准考证号不合法" << endl;
    return false;
  }
  // 检测数据是否已经存在
  if (is_exists(student.get_id())) {
    return student_manager->update(student);
  }
  cout << "没有找到该考生" << endl;
  return false;
}

/**
 * @brief 查询模块
 *
 * @param value
 * @return true
 * @return false
 */

bool Worker::query_all_student_by_condition(const string& value) {
  LinkedList<Student>* res = student_manager->query(value);
  if (res == nullptr) {
    cout << "没有找到该考生" << endl;
    return false;
  }
  res->print();
  return true;
}

/**
 * @brief 查询所有考生信息
 *
 * @return true
 * @return false
 */
bool Worker::query_all_student() {
  if (student_manager->get_size() == 0) {
    cout << "没有考生信息" << endl;
    return false;
  }
  student_manager->print();
  return true;
}

/**
 * @brief 统计模块
 *
 * @return LinkedList<Student>*
 */
LinkedList<Student>* Worker::statistics() {
  if (student_manager->get_size() == 0) {
    cout << "没有考生信息" << endl;
    return nullptr;
  }

  double score = 310;
  double v1 = 40, v2 = 65, v3 = 40, v4 = 65;

  cout << "统计条件设置" << endl;
  cout << "1.默认设置(合格总分310/500，各科合格分40/100、65/150)" << endl;
  cout << "2.自定义设置" << endl;
  int choice;
  cin >> choice;
  if (choice == 2) {
    score = -1;
    v1 = v2 = v3 = v4 = -1;
    while (score < 0 || score > 500) {
      cout << "请输入总分合格要求(默认310)" << endl;
      cin >> score;
      if (score < 0 || score > 500) {
        cout << "输入错误，请重新输入" << endl;
      }
    }

    while (v1 < 0 || v1 > 100) {
      cout << "请输入政治成绩合格要求(默认40)" << endl;
      cin >> v1;
      if (v1 < 0 || v1 > 100) {
        cout << "输入错误，请重新输入" << endl;
      }
    }

    while (v2 < 0 || v2 > 150) {
      cout << "请输入数学成绩合格要求(默认65)" << endl;
      cin >> v2;
      if (v2 < 0 || v2 > 150) {
        cout << "输入错误，请重新输入" << endl;
      }
    }

    while (v3 < 0 || v3 > 100) {
      cout << "请输入外语成绩合格要求(默认40)" << endl;
      cin >> v3;
      if (v3 < 0 || v3 > 100) {
        cout << "输入错误，请重新输入" << endl;
      }
    }

    while (v4 < 0 || v4 > 150) {
      cout << "请输入专业课成绩合格要求(默认65)" << endl;
      cin >> v4;
      if (v4 < 0 || v4 > 150) {
        cout << "输入错误，请重新输入" << endl;
      }
    }
  }

  LinkedList<Student>* res = student_manager->statistic(score, v1, v2, v3, v4);

  res->mergeSort();  // 从高到低排序

  if (res != nullptr) {
    cout << "合格考生总人数：" << res->get_size() << endl;
    cout << "合格考生信息(从高到低)：" << endl;
    res->print();
  } else {
    cout << "没有找到合格考生" << endl;
  }
  return res;
}

/**
 * @brief 排序模块
 *
 * @return LinkedList<Student>*
 */
void Worker::sort() {
  if (student_manager->get_size() == 0) {
    cout << "没有考生信息" << endl;
  }
  student_manager->mergeSort();
}

/**
 * @brief 从文件中加载数据
 *
 * @param input
 * @return LinkedList<Student>*
 */
bool Worker::load(const string& filename) {
  student_manager->destroy();  // 清除缓存
  return student_manager->load(filename);
}

/**
 * @brief 保存数据到文件
 *
 * @param output
 * @return LinkedList<Student>*
 */
bool Worker::save(const string& filename) {
  return student_manager->save(filename);
}