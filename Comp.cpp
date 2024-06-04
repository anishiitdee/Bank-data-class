#include "Comp.h"

void Comp::createAccount(std::string id, int count) {
    int index = hash(id);
    Account account;
    account.id = id;
    account.balance = count;

    while (bankStorage2d.size() <= index) {
        bankStorage2d.push_back(std::vector<Account>());
    }

    bankStorage2d[index].push_back(account);
}

std::vector<int> Comp::getTopK(int k) {
    std::vector<int> topBalances;

    for (size_t i = 0; i < bankStorage2d.size(); ++i) {
        for (size_t j = 0; j < bankStorage2d[i].size(); ++j) {
            if (topBalances.size() < k) {
                topBalances.push_back(bankStorage2d[i][j].balance);
            } else {
                int minBalance = topBalances[0];
                int minIndex = 0;

                for (int l = 1; l < k; ++l) {
                    if (topBalances[l] < minBalance) {
                        minBalance = topBalances[l];
                        minIndex = l;
                    }
                }

                if (bankStorage2d[i][j].balance > minBalance) {
                    topBalances[minIndex] = bankStorage2d[i][j].balance;
                }
            }
        }
    }

    for (size_t i = 0; i < k - 1; ++i) {
        int maxIndex = i;
        for (size_t j = i + 1; j < k; ++j) {
            if (topBalances[j] > topBalances[maxIndex]) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            std::swap(topBalances[i], topBalances[maxIndex]);
        }
    }

    return topBalances;
}

int Comp::getBalance(std::string id) {
    int index = hash(id);
    if (index >= 0 && index < bankStorage2d.size()) {
        for (size_t i = 0; i < bankStorage2d[index].size(); ++i) {
            if (bankStorage2d[index][i].id == id) {
                return bankStorage2d[index][i].balance;
            }
        }
    }
    return -1;
}

void Comp::addTransaction(std::string id, int count) {
    int index = hash(id);
    if (index >= 0 && index < bankStorage2d.size()) {
        for (size_t i = 0; i < bankStorage2d[index].size(); ++i) {
            if (bankStorage2d[index][i].id == id) {
                bankStorage2d[index][i].balance += count;
                return;
            }
        }
    }
    createAccount(id, count);
}

bool Comp::doesExist(std::string id) {
    int index = hash(id);
    if (index >= 0 && index < bankStorage2d.size()) {
        for (size_t i = 0; i < bankStorage2d[index].size(); ++i) {
            if (bankStorage2d[index][i].id == id) {
                return true;
            }
        }
    }
    return false;
}

bool Comp::deleteAccount(std::string id) {
    int index = hash(id);
    if (index >= 0 && static_cast<size_t>(index) < bankStorage2d.size()) {
        for (size_t i = 0; i < bankStorage2d[static_cast<size_t>(index)].size(); i++) {
            if (bankStorage2d[static_cast<size_t>(index)][i].id == id) {
                bankStorage2d[static_cast<size_t>(index)].erase(bankStorage2d[static_cast<size_t>(index)].begin() + i);
                return true;
            }
        }
    }
    return false;
}

int Comp::databaseSize() {
    int size = 0;
    for (size_t i = 0; i < bankStorage2d.size(); ++i) {
        size += bankStorage2d[i].size();
    }
    return size;
}

int Comp::hash(std::string id) {
    unsigned long long hashValue = 0;
    const int prime = 31;
    for (size_t i = 0; i < id.length(); i++) {
        hashValue = (hashValue * prime + static_cast<int>(id[i])) % 100003;
    }
    return static_cast<int>(hashValue);
}
