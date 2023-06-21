#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "worker.hpp"

class Manager : public Worker {
 public:
  Manager() {}
  
  Manager(const string& id, const string& name, const string& password)
      : User(id, name, password), Worker(id, name, password) {
    init();
  }

  bool set_id() override;

  int login() override;

  bool register_user() override;

  // manager专有功能

  bool add_worker(const Worker& worker);

  bool delete_worker(const string& name);

  bool modify_worker(const Worker& worker);

  bool query_all_worker_by_condition(const string& id);

  bool query_all_worker();

  bool load(const string& filename =
                "/home/entropy/Documents/NEEP-MS/worker.txt") override;

  bool save(const string& filename =
                "/home/entropy/Documents/NEEP-MS/worker.txt") override;

  ~Manager() {}
};
#endif