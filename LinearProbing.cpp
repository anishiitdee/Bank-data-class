#include "LinearProbing.h"

LinearProbing::LinearProbing()
{
    bankStorage1d.resize(100003);
    for (int i = 0; i < bankStorage1d.size(); ++i)
    {
        bankStorage1d[i].balance = -1;
    }
}

void LinearProbing::createAccount(std::string id, int count)
{
    int index = hash(id);
    Account account;
    account.id = id;
    account.balance = count;

    while (!bankStorage1d[index].id.empty())
    {
        index = (index + 1) % bankStorage1d.size();
    }

    bankStorage1d[index] = account;
    bank++;
}

std::vector<int> LinearProbing::getTopK(int k)
{
    std::vector<int> topBalances;

    if (k <= 0)
    {
        return topBalances;
    }

    int n = bankStorage1d.size();
    std::vector<std::pair<int, int> > balancesWithIndices;

    for (int i = 0; i < n; ++i)
    {
        if (!bankStorage1d[i].id.empty() && bankStorage1d[i].balance != -1)
        {
            balancesWithIndices.push_back({bankStorage1d[i].balance, i});
        }
    }

    for (int i = 0; i < k && i < balancesWithIndices.size(); ++i)
    {
        int maxIndex = i;

        for (int j = i + 1; j < balancesWithIndices.size(); ++j)
        {
            if (balancesWithIndices[j].first > balancesWithIndices[maxIndex].first)
            {
                maxIndex = j;
            }
        }
        std::swap(balancesWithIndices[i], balancesWithIndices[maxIndex]);
        topBalances.push_back(balancesWithIndices[i].first);
    }

    return topBalances;
}

int LinearProbing::getBalance(std::string id)
{
    int index = hash(id);
    int initialIndex = index;

    while (true)
    {
        if (bankStorage1d[index].id == id)
        {
            return bankStorage1d[index].balance;
        }

        index = (index + 1) % bankStorage1d.size();

        if (index == initialIndex)
        {
            return -1;
        }
    }
    return -1;
}
void LinearProbing::addTransaction(std::string id, int count)
{
    int index = hash(id);
    int initialIndex = index;

    while (true)
    {
        if (bankStorage1d[index].id == id)
        {
            bankStorage1d[index].balance += count;
            return;
        }

        index = (index + 1) % bankStorage1d.size();

        if (index == initialIndex)
        {
            createAccount(id, count);
            return;
        }
    }

    createAccount(id, count);
}

bool LinearProbing::doesExist(std::string id)
{
    int index = hash(id);
    int initialIndex = index;
    while (true)
    {
        if (bankStorage1d[index].balance != -1 && bankStorage1d[index].id == id)
        {
            return true;
        }
        index = (index + 1) % bankStorage1d.size();

        if (index == initialIndex)
        {
            return false;
        }
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id)
{
    int index = hash(id);
    int initialIndex = index;

    while (true)
    {
        if (bankStorage1d[index].id == id)
        {
            bankStorage1d[index].id = "";
            bankStorage1d[index].balance = -1;
            --bank;
            return true;
        }

        index = (index + 1) % bankStorage1d.size();

        if (index == initialIndex)
        {
            return false;
        }
    }

    return false;
}

int LinearProbing::databaseSize()
{
    return bank;
}

int LinearProbing::hash(std::string id)
{
    int sum = 0;
    for (size_t i = 0; i < id.length(); ++i)
    {
        sum += static_cast<int>(id[i]);
    }
    return sum % 100003;
}