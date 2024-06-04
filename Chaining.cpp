#include "Chaining.h"

void Chaining::createAccount(std::string id, int count) {
    int index = hash(id);
    Account account;
    account.id = id;
    account.balance = count;
    while (bankStorage2d.size() <= index) {
        bankStorage2d.push_back(std::vector<Account>());
    }
    bankStorage2d[index].push_back(account);
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> topBalances;

    for (int i = 0; i < bankStorage2d.size(); ++i) {
        for (int j = 0; j < bankStorage2d[i].size(); ++j) {
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

    for (int i = 0; i < k - 1; ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < k; ++j) {
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


int Chaining::getBalance(std::string id) {
    int index = hash(id);
    if (index >= 0 && index < bankStorage2d.size()) {
        for (int i = 0; i < bankStorage2d[index].size(); ++i) {
            if (bankStorage2d[index][i].id == id) {
                return bankStorage2d[index][i].balance;
            }
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    int index = hash(id);
    if (index >= 0 && index < bankStorage2d.size()) {
        for (int i = 0; i < bankStorage2d[index].size(); ++i) {
            if (bankStorage2d[index][i].id == id) {
                bankStorage2d[index][i].balance += count;
                return;
            }
        }
    }
    createAccount(id, count);
}

bool Chaining::doesExist(std::string id) {
    int index = hash(id);
    if (index >= 0 && index < bankStorage2d.size()) {
        for (int i = 0; i < bankStorage2d[index].size(); ++i) {
            if (bankStorage2d[index][i].id == id) {
                return true;
            }
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int index = hash(id);
    if (index >= 0 && index < bankStorage2d.size()) {
        for (int i = 0; i < bankStorage2d[index].size(); ++i) {
            if (bankStorage2d[index][i].id == id) {
                bankStorage2d[index].erase(bankStorage2d[index].begin() + i);
                return true;
            }
        }
    }
    return false;
}

int Chaining::databaseSize() {
    int size = 0;
    for (int i = 0; i < bankStorage2d.size(); ++i) {
        size += bankStorage2d[i].size();
    }
    return size;
}

int Chaining::hash(std::string id) {

        const int prime = 31;
        int hashValue = 0;
        for (size_t i = 0; i < id.length(); ++i) {
            hashValue = (hashValue * prime + int(id[i])) % 1000003;
        }
        return hashValue;
    }


