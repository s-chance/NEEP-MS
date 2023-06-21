#include "visitor.hpp"

#include "./manager.hpp"
#include "./worker.hpp"

string Visitor::get_id() const {
  cout << "该功能不对访客开放！" << endl;
  return "";
}

string Visitor::get_name() const { return name; }

string Visitor::get_password() const {
  cout << "该功能不对访客开放！" << endl;
  return "";
}

bool Visitor::set_id() {
  cout << "该功能不对访客开放！" << endl;
  return false;
}

bool Visitor::set_name(const string& name) {
  this->name = name;
  return true;
}

bool Visitor::set_password(const string& password) {
  cout << "该功能不对访客开放！" << endl;
  return false;
}

int Visitor::login() {
  bool flag = true;  // 工作人员及管理员信息文件状态
  if (worker_manager == nullptr) {
    worker_manager = new LinkedList<Worker>;
    string filename = "/home/entropy/Documents/NEEP-MS/worker.txt";
    flag = worker_manager->load(filename);
  }

  if (student_manager == nullptr) {
    student_manager = new LinkedList<Student>;
    string filename = "/home/entropy/Documents/NEEP-MS/student.txt";
    student_manager->load(filename);
  }
  // 账号文件不存在或者为空时，创建管理员账号
  if (!flag || worker_manager->get_size() == 0) {
    cout << "第一个用户登录自动成为管理员" << endl;

    string id, name, password;
    cout << "请输入管理员账号：";
    cin >> id;
    id = "M" + id;  // 管理员id前加M
    cout << "请输入姓名：";
    cin >> name;
    cout << "请输入密码：";
    cin >> password;
    Manager manager(id, name, password);
    if (worker_manager->insert_tail(manager) &&
        worker_manager->save("/home/entropy/Documents/NEEP-MS/worker.txt")) {
      cout << "创建成功" << endl;
      return 1;
    }
    cout << "创建失败" << endl;
    return 0;

  } else {
    cout << "是否登录管理员账号" << endl;
    cout << "1.是" << endl;
    cout << "2.否" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
      string id, name, password;
      cout << "请输入管理员账号：";
      cin >> id;
      id = "M" + id;  // 管理员id前加M
      cout << "请输入姓名：";
      cin >> name;
      cout << "请输入密码：";
      cin >> password;

      LinkedList<Worker>::Node* res = worker_manager->search(id);
      if (res == nullptr) {
        cout << "没有找到该用户" << endl;
        return 0;
      }
      if (res->data.get_password() == password) {
        cout << "登录成功" << endl;
        return 1;
      } else {
        cout << "密码错误" << endl;
        return 0;
      }
    }
  }

  int choice;
  cout << "是否登录工作账号" << endl;
  cout << "1.是" << endl;
  cout << "2.否" << endl;
  cin >> choice;
  if (choice == 1) {
    string id, password;
    cout << "请输入工作账号：";
    cin >> id;
    id = "W" + id;  // 工作人员id前加W
    cout << "请输入密码：";
    cin >> password;
    LinkedList<Worker>::Node* res = worker_manager->search(id);
    if (res == nullptr) {
      cout << "没有找到该用户" << endl;
      return 0;
    }
    if (res->data.get_password() == password) {
      cout << "登录成功" << endl;
      return 2;
    } else {
      cout << "密码错误" << endl;
      return 0;
    }
  }
  cout << "未能登录！" << endl;
  return 0;
}

bool Visitor::logout() const {
  cout << "该功能不对访客开放！" << endl;
  return false;
}

bool Visitor::register_user() {
  cout << "该功能不对普通用户开放！" << endl;
  return false;
}

/**
 * @brief 初始化数据
 *
 * @return true
 * @return false
 */
bool Visitor::init() {
  if (student_manager == nullptr) {
    student_manager = new LinkedList<Student>;
    string filename = "/home/entropy/Documents/NEEP-MS/student.txt";
    student_manager->load(filename);
  }

  if (worker_manager == nullptr) {
    worker_manager = new LinkedList<Worker>;
    string filename = "/home/entropy/Documents/NEEP-MS/worker.txt";
    worker_manager->load(filename);
  }

  if (student_manager == nullptr || worker_manager == nullptr) {
    return false;
  }
  return true;
}

/**
 * @brief 检测数据是否存在
 *
 * @param value
 * @return true
 * @return false
 */
bool Visitor::is_exists(const string& id) const {
  if (student_manager->get_size() == 0) {
    return false;
  }
  LinkedList<Student>::Node* res = student_manager->search(id);
  if (res == nullptr) {
    return false;
  }
  return true;
}

bool Visitor::add_student(const Student& student) {
  cout << "访客无权限操作！" << endl;
  return false;
}

bool Visitor::delete_student(const string& number) {
  cout << "访客无权限操作！" << endl;
  return false;
}

bool Visitor::modify_student(const Student& student) {
  cout << "访客无权限操作！" << endl;
  return false;
}

bool Visitor::query_all_student_by_condition(const string& id) {
  if (id.length() != 15) {
    cout << "准考证号不合法" << endl;
    return false;
  }
  init();
  LinkedList<Student>* res = student_manager->query(id);
  if (res->get_size() == 0) {
    cout << "没有找到该考生" << endl;
    return false;
  }
  res->print();
  return true;
}

bool Visitor::query_all_student() {
  cout << "访客无权限操作！" << endl;
  return false;
}

LinkedList<Student>* Visitor::statistics() {
  cout << "访客无权限操作！" << endl;
  return nullptr;
}

void Visitor::sort() { cout << "访客无权限操作！" << endl; }

bool Visitor::load(const string& filename) {
  cout << "访客无权限操作！" << endl;
  return false;
}

bool Visitor::save(const string& filename) {
  cout << "访客无权限操作！" << endl;
  return false;
}