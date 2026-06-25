#include <bits/stdc++.h>
using namespace std;

struct Task {
    string id;
    int burst;
    vector<string> memBlocks;
};

class CacheLevel {
public:
    int capacity;
    queue<string> fifo;
    unordered_set<string> present;

    CacheLevel(int cap) {
        capacity = cap;
    }

    bool contains(const string& block) {
        return present.count(block);
    }

    void insert(const string& block) {
        if (contains(block))
            return;

        if ((int)fifo.size() >= capacity) {
            string old = fifo.front();
            fifo.pop();
            present.erase(old);
        }

        fifo.push(block);
        present.insert(block);
    }

    vector<string> getState() {
        vector<string> state;
        queue<string> temp = fifo;

        while (!temp.empty()) {
            state.push_back(temp.front());
            temp.pop();
        }

        return state;
    }
};

void printCache(const string& name, CacheLevel& cache) {
    cout << name << ": [";

    vector<string> state = cache.getState();

    for (int i = 0; i < (int)state.size(); i++) {
        cout << state[i];
        if (i != (int)state.size() - 1)
            cout << ", ";
    }

    cout << "]";
}

int main() {
    vector<Task> tasks;

    cout << "Paste tasks and type END when finished:\n";

    string line;

    while (getline(cin, line)) {
        if (line == "END")
            break;

        if (line.empty())
            continue;

        stringstream ss(line);

        Task t;
        string temp;

        ss >> temp;
        ss >> t.id;

        ss >> temp;
        ss >> t.burst;

        ss >> temp;

        string block;

        while (ss >> block)
            t.memBlocks.push_back(block);

        tasks.push_back(t);
    }

    CacheLevel L1(32);
    CacheLevel L2(128);
    CacheLevel L3(512);

    int executionCycles = 0;
    int totalLatencyCycles = 0;
    int ramAccesses = 0;

    for (auto& task : tasks) {
        int memIndex = 0;

        for (int i = 0; i < task.burst; i++) {
            executionCycles++;

            string block =
                task.memBlocks[memIndex % task.memBlocks.size()];

            memIndex++;

            cout << "\nCycle " << executionCycles
                 << " - Running: " << task.id
                 << " Requesting: " << block << "\n";

            int latency = 0;

            if (L1.contains(block)) {
                latency = 4;
                cout << "L1 HIT (4 cycles)\n";
            }
            else if (L2.contains(block)) {
                latency = 12;

                cout << "L1 MISS\n";
                cout << "L2 HIT (12 cycles)\n";

                L1.insert(block);
            }
            else if (L3.contains(block)) {
                latency = 40;

                cout << "L1 MISS\n";
                cout << "L2 MISS\n";
                cout << "L3 HIT (40 cycles)\n";

                L2.insert(block);
                L1.insert(block);
            }
            else {
                latency = 200;

                cout << "L1 MISS\n";
                cout << "L2 MISS\n";
                cout << "L3 MISS\n";
                cout << "Fetching from RAM (200 cycles)\n";

                ramAccesses++;

                L3.insert(block);
                L2.insert(block);
                L1.insert(block);
            }

            totalLatencyCycles += latency;

            printCache("L1", L1);
            cout << "\n";

            printCache("L2", L2);
            cout << "\n";

            printCache("L3", L3);
            cout << "\n";
        }
    }

    cout << "\n=== Final Results ===\n";
    cout << "Execution Cycles: " << executionCycles << "\n";
    cout << "Total Latency Cycles: " << totalLatencyCycles << "\n";
    cout << "Tasks Completed: " << tasks.size() << "\n";
    cout << "Scheduler: FCFS\n";
    cout << "RAM Accesses: " << ramAccesses << "\n";

    return 0;
}
