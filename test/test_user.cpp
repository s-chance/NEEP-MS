#include <iostream>

#include "../src/user/manager.hpp"
#include "../src/user/visitor.hpp"
#include "../src/user/worker.hpp"

using namespace std;

Visitor* visitor = new Visitor();
Worker* worker;
Manager* manager;

const Student* studentInfo() {
  string name, id, major;
  bool fresh;
  double politics, math, foreignn, basics;
  cout << "请输入考生姓名：";
  cin >> name;
  cout << "请输入准考证号：";
  cin >> id;
  cout << "请输入报考专业：";
  cin >> major;
  cout << "请输入是否为应届生：";
  cin >> fresh;
  cout << "请输入政治成绩：";
  cin >> politics;
  cout << "请输入数学成绩：";
  cin >> math;
  cout << "请输入外语成绩：";
  cin >> foreignn;
  cout << "请输入基础课成绩：";
  cin >> basics;
  return new Student(name, id, major, fresh,
                     *new Subject(politics, math, foreignn, basics));
}

const string delete_student() {
  string id;
  cout << "请输入准考证号：";
  cin >> id;
  return id;
}

const string query_all_student_by_id() {
  string id;
  cout << "请输入准考证号：";
  cin >> id;
  return id;
}

const Worker* workerInfo() {
  string name, id, password;
  cout << "请输入工作人员姓名：";
  cin >> name;
  cout << "请输入工作人员账号：";
  cin >> id;
  id = "W" + id;  // 工作人员id前加W
  cout << "请输入工作人员密码：";
  cin >> password;
  return new Worker(id, name, password);
}

const string delete_worker() {
  string id;
  cout << "请输入工作人员账号：";
  cin >> id;
  return id;
}

const string query_all_worker_by_id() {
  string id;
  cout << "请输入工作人员账号：";
  cin >> id;
  return id;
}

// 工作人员用于管理考生信息

void worker_menu() {
  cout << "工作人员功能菜单" << endl;
  cout << "1.新增" << endl;
  cout << "2.修改" << endl;
  cout << "3.删除" << endl;
  cout << "4.查询" << endl;
  cout << "5.统计" << endl;
  cout << "6.保存" << endl;
  cout << "7.读取" << endl;
  cout << "8.登录" << endl;
  cout << "9.退出" << endl;
  int choice;
  bool logout = false;
  while (cin >> choice) {
    if (choice == 1) {
      visitor->add_student(*studentInfo());
    } else if (choice == 2) {
      visitor->modify_student(*studentInfo());
    } else if (choice == 3) {
      visitor->delete_student(delete_student());
    } else if (choice == 4) {
      cout << "条件查询/全部查询" << endl;
      cout << "1.条件查询" << endl;
      cout << "2.全部查询" << endl;
      int choice;
      cin >> choice;
      if (choice == 1) {
        visitor->query_all_student_by_condition(query_all_student_by_id());
      } else if (choice == 2) {
        visitor->query_all_student();
      }
    } else if (choice == 5) {
      visitor->statistics();
    } else if (choice == 6) {
      visitor->save();
    } else if (choice == 7) {
      visitor->load();
    } else if (choice == 8) {
      visitor->login();
    } else if (choice == 9) {
      logout = visitor->logout();
    }
    if (logout) {
      cout << "退出登录成功！" << endl;
      return;
    }
    worker_menu();
  }
}

// 管理员用于管理工作人员
void manager_menu() {
  cout << "管理员功能菜单" << endl;
  cout << "1.新增工作人员" << endl;
  cout << "2.修改工作人员" << endl;
  cout << "3.删除工作人员" << endl;
  cout << "4.查询工作人员" << endl;
  cout << "5.统计学生" << endl;
  cout << "6.保存账号信息" << endl;
  cout << "7.读取账号信息" << endl;
  cout << "8.登录账号信息" << endl;
  cout << "9.退出" << endl;
  int choice;
  bool logout = false;
  while (cin >> choice) {
    if (choice == 1) {
      manager->add_worker(*workerInfo());
    } else if (choice == 2) {
      manager->modify_worker(*workerInfo());
    } else if (choice == 3) {
      manager->delete_worker(delete_worker());
    } else if (choice == 4) {
      cout << "条件查询/全部查询" << endl;
      cout << "1.条件查询" << endl;
      cout << "2.全部查询" << endl;
      int choice;
      cin >> choice;
      if (choice == 1) {
        manager->query_all_worker_by_condition(query_all_worker_by_id());
      } else if (choice == 2) {
        manager->query_all_worker();
      }
    } else if (choice == 5) {
      manager->statistics();
    } else if (choice == 6) {
      manager->save();
    } else if (choice == 7) {
      manager->load();
    } else if (choice == 8) {
      manager->login();
    } else if (choice == 9) {
      logout = manager->logout();
    }
    if (logout) {
      cout << "退出登录成功！" << endl;
      return;
    }
    manager_menu();
  }
}

void visitor_menu() {
  cout << "访客功能菜单" << endl;
  cout << "1.凭准考证号查询" << endl;
  cout << "2.登录" << endl;
  cout << "3.退出" << endl;
  int choice;
  int status = 0;
  while (cin >> choice) {
    if (choice == 1) {
      cout << "请输入准考证号：";
      string id;
      cin >> id;
      Visitor* visitor = new Visitor();
      visitor->query_all_student_by_condition(id);
    } else if (choice == 2) {
      status = visitor->login();
    } else if (choice == 3) {
      exit(0);
    }
    if (status == 1) {
      delete visitor;
      visitor = new Manager();
      // 向下转型，把visitor转换成manager
      manager = dynamic_cast<Manager*>(visitor);
      manager_menu();
      // 退出登录后重新初始化visitor
      manager = nullptr;
      delete visitor;
      visitor = new Visitor();
      visitor->init();
      status = 0;
    } else if (status == 2) {
      delete visitor;
      visitor = new Worker();
      // 向下转型，把visitor转换成worker
      worker = dynamic_cast<Worker*>(visitor);
      worker_menu();
      worker = nullptr;
      delete visitor;
      visitor = new Visitor();
      visitor->init();
      status = 0;
    }
    visitor_menu();
  }
}

int main() {
  cout << "欢迎使用NEEP-MS" << endl;
  visitor->init();
  visitor_menu();
  return 0;
}