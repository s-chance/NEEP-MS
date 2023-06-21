#include "manager.hpp"

bool Manager::set_id() {
  auto now = chrono::system_clock::now();
  time_t now_c = chrono::system_clock::to_time_t(now);

  char time_str[20];
  strftime(time_str, sizeof(time_str), "%Y-%m-%d-%H-%M-%S", localtime(&now_c));

  this->id = "M" + string(time_str);
  return true;
}

int Manager::login() {
  cout << "您已经登录！" << endl;
  return 1;
}

bool Manager::register_user() {
  cout << "创建工作账号" << endl;
  string id, name, password;
  cout << "请输入工作账号：";
  cin >> id;
  id = "W" + id;  // 工作人员id前加W
  cout << "请输入姓名：";
  cin >> name;
  cout << "请输入密码：";
  cin >> password;
  Worker worker(id, name, password);
  if (worker_manager->insert_tail(worker)) {
    cout << "创建成功" << endl;
    save();
    return true;
  }
  cout << "创建失败" << endl;
  return false;
}

bool Manager::add_worker(const Worker& worker) {
  // 检测数据是否已经存在
  if (is_exists(worker.get_id())) {
    cout << "数据已存在，不能重复！" << endl;
    return false;
  }
  return worker_manager->insert_tail(worker);
}

bool Manager::delete_worker(const string& id) {
  string uid = "W" + id;  // 工作人员id前加W
  // 检测数据是否已经存在
  if (is_exists(uid)) {
    return worker_manager->remove(uid);
  }
  cout << "没有找到该用户" << endl;
  return false;
}

bool Manager::modify_worker(const Worker& worker) {
  // 检测数据是否已经存在
  if (is_exists(worker.get_id())) {
    return worker_manager->update(worker);
  }
  cout << "没有找到该用户" << endl;
  return false;
}

bool Manager::query_all_worker_by_condition(const string& id) {
  LinkedList<Worker>* res = worker_manager->query(id);
  if (res == nullptr) {
    cout << "没有找到该用户" << endl;
    return false;
  }
  res->print();
  return true;
}

bool Manager::query_all_worker() {
  if (worker_manager->get_size() == 0) {
    cout << "没有数据" << endl;
    return false;
  }
  worker_manager->print();
  return true;
}

bool Manager::load(const string& filename) {
  worker_manager->destroy();  // 清空原有数据
  return worker_manager->load(filename);
}

bool Manager::save(const string& filename) {
  return worker_manager->save(filename);
}