#include <iostream>
#include<vector>
#include<algorithm>
#include <map>
using namespace std;
class Scheduling {
    public:
        struct Process {
            int id;
            int arrival_time;
            int burst_time;
            int Completion_time;
            int TAT;
            int WT;
        };
    // using Queue
    struct RR_Process {
    int id;
    int burstTime;
    int remainingTime;
    };

    void RR(queue<RR_Process>& processes, int quantum) {
        while (!processes.empty()) {
            RR_Process currentProcess = processes.front();
            processes.pop();
            int executionTime = min(quantum, currentProcess.remainingTime);
            currentProcess.remainingTime -= executionTime;
            cout << "Executing process " << currentProcess.id << " for " << executionTime << " units." << endl;
            if (currentProcess.remainingTime > 0) {
                processes.push(currentProcess);
            }
        }
    }
    // using Vector
    void RR(vector<Process>& process, int t_quantum) {
        int x = 0;
        int current_time = 0;
        map<int, int> ans;
        vector<Process> it;
        vector<Process> ready_q;
        for (int i = 0; i < process.size(); i++) {
            it.push_back(process[i]);
        }
        while (!process.empty() || !ready_q.empty()) {
            while(!process.empty() && process.front().arrival_time <= current_time) {
                ready_q.push_back(process.front());
                process.erase(process.begin());
            }
                if (ready_q.empty()) {
                    current_time++;
                    continue;
                }
                Process current_process = ready_q.front();
                ready_q.erase(ready_q.begin());
                int executionTime = min(t_quantum, current_process.burst_time);
                current_time += executionTime;
                current_process.burst_time -= executionTime;

                cout << "Executing process " << current_process.id << " for " << executionTime << " units." << endl;
                x += executionTime;
                if (current_process.burst_time > 0) {
                    ready_q.push_back(current_process);
                }
                else if (current_process.burst_time == 0) {
                    ans[current_process.id] += x;
                }
        }
        for (auto y : ans)
            cout << "Process " << y.first << " Completed with " << y.second << endl;
        cout << "P\tAT\tBT\tCT\tTAT\tWT" << endl;
        for (auto y : it) {
            if(ans.find(y.id) != ans.end())
                y.Completion_time = ans[y.id];
            y.TAT = y.Completion_time - y.arrival_time;
            y.WT = y.TAT - y.burst_time;
            cout << "P" << y.id << "\t" << y.arrival_time << "\t" << y.burst_time << "\t" <<  y.Completion_time << "\t" << y.TAT << "\t" << y.WT << endl;
        }
    }
};
int main() {
    int n;
    cout << "Give No. of Process";
    cin >> n;
    vector<Scheduling::Process> processes;
    Scheduling scheduling;
    Scheduling:: Process process;
    for (int i = 0; i < n; i++)
    {
        process.id = i+1;
        cout << "Enter Burst time" << process.id;
        cin >> process.burst_time;
        cout << "Enter Arival Time" << process.id;
        cin >> process.arrival_time;
        processes.push_back(process);
    }
    scheduling.RR(processes,2);
    Scheduling:: RR_Process process;
    queue<Scheduling::RR_Process> x;
    for (int i = 1; i <= n; i++) {
    Scheduling:: RR_Process p;
    p.id = i;
    cout << "Enter burst time for process " << i << ": ";
    cin >> p.burstTime;
    p.remainingTime = p.burstTime;
    x.push(p);
    }
    scheduling.RR(x,2);
    return 0;
}