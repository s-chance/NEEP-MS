#ifndef USER_HPP
#define USER_HPP
#include <chrono>
#include <ctime>
#include <string>

using namespace std;
// 用户类，基本信息
class User {
 public:
  User(const string& id = "visitor", const string& name = "visitor",
       const string& password = "visitor")
      : id(id), name(name), password(password) {}

  virtual string get_id() const = 0;

  virtual string get_name() const = 0;

  virtual string get_password() const = 0;

  virtual bool set_id() = 0;  // 这里的id由系统自动生成

  virtual bool set_name(const string& name) = 0;

  virtual bool set_password(const string& password) = 0;

  // 登录
  // 返回1表示登录管理员账号
  // 返回2表示登录工作人员账号
  // 返回0表示登录失败
  virtual int login() = 0;
  virtual bool logout() const = 0;

  // 工作人员和访客不可注册
  // 工作人员的帐号由管理员预先设置好
  // 通过以下函数注册工作人员账号
  virtual bool register_user() = 0;

  virtual ~User() {}

 protected:
  string id;  // 用户id，全局唯一
  string name;
  string password;
};
#endif