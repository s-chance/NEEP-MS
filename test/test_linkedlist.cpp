#include <iostream>
#include <string>

#include "../src/user/manager.cpp"
#include "../src/user/visitor.cpp"
#include "../src/user/worker.cpp"
using namespace std;

LinkedList<Student>* list = new LinkedList<Student>();

// 测试数据
// 合格
Student s1("李明", "202103150110456", "计算机", true,
           *new Subject(100, 100, 100, 100));
Student s2("大鹿", "202103150338456", "计算机", true,
           *new Subject(100, 100, 100, 130));
Student s3("王匡", "202103150123456", "计算机", true,
           *new Subject(100, 100, 100, 110));
Student s4("光良", "202103150221456", "计算机", true,
           *new Subject(100, 100, 100, 140));

// 不合格
Student s5("小小", "202103150110456", "计算机", true,
           *new Subject(100, 100, 100, 39));
Student s6("平成", "202103150338456", "计算机", true,
           *new Subject(30, 100, 100, 129));

/**
 * @brief 菜单
 *
 */
void menu() {
  cout << "功能菜单" << endl;
  cout << "1.新增" << endl;
  cout << "2.删除" << endl;
  cout << "3.修改" << endl;
  cout << "4.统计" << endl;
  cout << "5.保存" << endl;
  cout << "6.读取" << endl;
}

/**
 * @brief 测试新增
 *
 */
void test_add() {
  list->insert_tail(s1);
  list->insert_tail(s6);
  list->print();
  menu();
}

/**
 * @brief 测试删除
 *
 */
void test_remove() {
  string id;
  cout << "请输入准考证号：";
  cin >> id;
  list->remove(id);
  list->print();
  menu();
}

/**
 * @brief 测试更新
 *
 */
void test_updata() {
  s1.set_name("小鹿");
  list->update(s1);
  list->print();
  menu();
}

/**
 * @brief 测试查询
 *
 */
void test_query() {
  LinkedList<Student>* res = list->query("202103150110");
  if (res == nullptr) {
    cout << "没有找到该考生" << endl;
    return;
  }
  res->print();

  menu();
}

/**
 * @brief 测试排序
 *
 */
void test_sort() {
  list->mergeSort();
  list->print();
  menu();
}

/**
 * @brief 测试统计
 *
 */
void test_statistic() {
  LinkedList<Student>* res = list->statistic();
  res->print();
  menu();
}

/**
 * @brief 测试文件写
 *
 */
string filename = "/home/entropy/Documents/NEEP-MS/student.txt";
void test_save() {
  cout << "确定要保存吗？(y/n)" << endl;
  char c;
  while (cin >> c) {
    if (c == 'y' || c == 'n') {
      break;
    }
    cout << "输入错误，请重新输入" << endl;
  }
  if (c == 'y') {
    list->save(filename);
    cout << "保存成功" << endl;
  } else if (c == 'n') {
    cout << "取消保存" << endl;
  }
  menu();
}

/**
 * @brief 测试文件读
 *
 */
void test_load() {
  LinkedList<Student>* res = new LinkedList<Student>();
  res->load(filename);
  res->print();
  menu();
}

int main() {
  list->load(filename);

  menu();
  int a;
  while (cin >> a) {
    switch (a) {
      case 1:
        test_add();
        break;
      case 2:
        test_remove();
        break;
      case 3:
        test_updata();
        break;
      case 4:
        // test_query();
        test_statistic();
        break;
      case 5:
        test_save();
        break;
      case 6:
        test_load();
        break;
      default:
        break;
    }
  }
}