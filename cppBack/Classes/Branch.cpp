#include "Branch.hpp"
#include <mutex>

std::mutex listMutex;

BranchList::BranchList() : head(nullptr) {}

BranchList::~BranchList() {
    Branch* current = head;
    while (current != nullptr) {
        Branch* next = current->next;
        delete current;
        current = next;
    }
}

void BranchList::insert(Branch* node) {
    std::lock_guard<std::mutex> lock(listMutex);
    node->next = head;
    head = node;
}

Branch* BranchList::findById(int id) {
    std::lock_guard<std::mutex> lock(listMutex);
    Branch* cur = head;
    while (cur != nullptr) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

bool BranchList::removeById(int id) {
    std::lock_guard<std::mutex> lock(listMutex);
    Branch* cur = head;
    Branch* prev = nullptr;

    while (cur != nullptr) {
        if (cur->id == id) {
            if (prev == nullptr) head = cur->next;
            else prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

Branch* BranchList::getAll() {
    return head;
}