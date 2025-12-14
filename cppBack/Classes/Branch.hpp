#pragma once
#include <string>
using namespace std;

struct Branch {
    int id; // from DB
    string branch_name;
   string location_link;
   string phone;
    string address;

    Branch* next;

    Branch(int _id, string _name, string _loc, string _phone, string _addr)
        : id(_id), branch_name(_name), location_link(_loc),
          phone(_phone), address(_addr), next(nullptr) {}
};

class BranchList {
private:
    Branch* head;

public:
    BranchList();
    ~BranchList();
   
    void insert(Branch* node);
    Branch* findById(int id);
    bool removeById(int id);
    Branch* getAll(); // return head pointer
};
