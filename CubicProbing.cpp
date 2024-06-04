#include "CubicProbing.h"
int bank=0;
void CubicProbing::createAccount(std::string id, int count) {
   int index = hash(id);
    Account account;
    account.id = id;
    account.balance = count;
    int q = 1;

    for (; bankStorage1d.size() <= index; ) {
        bankStorage1d.push_back(Account());
    }

    for (; !bankStorage1d[index].id.empty()|| bankStorage1d[index].balance == -1 ;) {
        index = (index + q * q * q) % bankStorage1d.size();
        ++q;
    }

    bankStorage1d[index] = account;
    bank++;
}

std::vector<int>CubicProbing::getTopK(int k) {
    std::vector<int> topBalances;

    if (k <= 0) {
        return topBalances;
    }

    int n = bankStorage1d.size();
    std::vector<std::pair<int, int>> balancesWithIndices;
    
    for (int i = 0; i < n; ++i) {
        if (!bankStorage1d[i].id.empty() && bankStorage1d[i].balance != -1) {
            balancesWithIndices.push_back({ bankStorage1d[i].balance, i });
        }
    }

    for (int i = 0; i < k && i < balancesWithIndices.size(); ++i) {
        int maxIndex = i;

        for (int j = i + 1; j < balancesWithIndices.size(); ++j) {
            if (balancesWithIndices[j].first > balancesWithIndices[maxIndex].first) {
                maxIndex = j;
            }
        }

        std::swap(balancesWithIndices[i], balancesWithIndices[maxIndex]);
        topBalances.push_back(balancesWithIndices[i].first);
    }

    return topBalances;
}


int CubicProbing::getBalance(std::string id) {
    int index = hash(id);
    int initialIndex = index;
    int q = 1;

    for (; !bankStorage1d[index].id.empty(); ) {
    if (bankStorage1d[index].id == id) {
        return bankStorage1d[index].balance;
    }

    index = (index + q * q * q) % bankStorage1d.size();
    ++q;

    if (index == initialIndex) {
        return -1;
    }
}

return -1;
}

void CubicProbing::addTransaction(std::string id, int count) {
     int index = hash(id);
int initialIndex = index;
int q = 1;

for (; !bankStorage1d[index].id.empty(); ) {
    if (bankStorage1d[index].id == id) {
        bankStorage1d[index].balance += count;
        return;
    }

    index = (index + q * q * q) % bankStorage1d.size();
    ++q;

    if (index == initialIndex) {
        break;
    }
}

createAccount(id, count);
}

bool CubicProbing::doesExist(std::string id) {
    int index = hash(id);
    int q=1;
    for (int i = 0; i < bankStorage1d.size(); ++i) {
        if (bankStorage1d[index].balance != -1 && bankStorage1d[index].id == id) {
            return true; 
        }
        index = (index + q*q*q) % bankStorage1d.size();
        q++;
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id) {
    int index = hash(id);
    int initialIndex = index;
    int q = 1;

    for (; !bankStorage1d[index].id.empty(); ) {
        if (bankStorage1d[index].id == id) {
            bankStorage1d[index].id = "anish";
            bankStorage1d[index].balance = -1;
            bank--;
            return true;
        }

        index = (index + q * q * q) % bankStorage1d.size();
        ++q;

        if (index == initialIndex) {
            return false;
        }
    }

    return false;
}

int CubicProbing::databaseSize() {
    
    return bank;
}

int CubicProbing::hash(std::string id) {
    const int prime = 31;
    int hashValue = 0;
    for (int i = 0; i < id.length(); ++i) {
        hashValue = (hashValue * prime + id[i]) % 100003;
    }
    return hashValue;
}

