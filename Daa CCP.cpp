#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <limits>
#include <ctime>
#include <iomanip>
#include <map>

using namespace std;

// Job structure representing a job in the assembly line
struct Job {
    int id;  // Job identifier
    int processingTime;  // Time required to process the job
    vector<int> dependencies;  // List of jobs that must be completed before this job
    int skillRequired;  // Skill level required for the job
    bool completed;  // Flag to indicate if the job is completed

    Job(int _id, int _time, vector<int> _deps, int _skill)
        : id(_id), processingTime(_time), dependencies(_deps), skillRequired(_skill), completed(false) {
    }
};

// Worker structure representing workers in the factory
struct Worker {
    int id;  // Worker identifier
    int skillLevel;  // Worker skill level (higher is better)
    int busyUntil;  // Time until which worker is busy

    Worker(int _id, int _skill) : id(_id), skillLevel(_skill), busyUntil(0) {}
};

// AssemblyLine structure representing an assembly line
struct AssemblyLine {
    int id;  // Assembly line identifier
    double speedFactor;  // Efficiency of the assembly line (speed factor)
    int currentTime;  // Time that the line is free to start new jobs
    vector<int> scheduledJobs;  // List of job IDs scheduled on this line
    vector<pair<int, int>> maintenanceWindows;  // Scheduled maintenance windows (start_time, duration)

    AssemblyLine(int _id, double _speed) : id(_id), speedFactor(_speed), currentTime(0) {}

    // Method to check if a worker is available at a given time
    bool isWorkerAvailable(const Worker& worker, int startTime) {
        return worker.busyUntil <= startTime;
    }

    // Get the next available time after the given time
    int getNextAvailableTime(int startTime, int processingTime) {
        return startTime + processingTime;
    }
};

// Assembly Line Scheduling Problem Solver
class ALSPSolver {
private:
    vector<Job> jobs;  // List of jobs
    vector<AssemblyLine> lines;  // List of assembly lines
    vector<Worker> workers;  // List of workers
    unordered_map<int, int> jobStartTimes;  // Maps job ID to start time
    unordered_map<int, int> jobEndTimes;  // Maps job ID to end time
    unordered_map<int, int> jobToLine;  // Maps job ID to line ID
    unordered_map<int, int> jobToWorker;  // Maps job ID to worker ID
    unordered_map<int, int> jobDuration;  // Maps job ID to duration
    int makespan;  // Total time to complete all jobs

public:
    ALSPSolver(vector<Job>& _jobs, vector<AssemblyLine>& _lines, vector<Worker>& _workers)
        : jobs(_jobs), lines(_lines), workers(_workers), makespan(0) {
    }

    // Check if all dependencies of a job are completed
    bool areDependenciesMet(const Job& job) {
        for (int depId : job.dependencies) {
            if (!jobs[depId].completed) {
                return false;
            }
        }
        return true;
    }

    // Find the earliest time the job can start based on its dependencies
    int getEarliestStartTime(const Job& job) {
        int earliestTime = 0;
        for (int depId : job.dependencies) {
            if (jobEndTimes.find(depId) != jobEndTimes.end()) {
                earliestTime = max(earliestTime, jobEndTimes[depId]);
            }
        }
        return earliestTime;
    }

    // Get actual processing time based on worker skill and line speed
    int getActualProcessingTime(const Job& job, const Worker& worker, const AssemblyLine& line) {
        double skillFactor = 1.0 - (worker.skillLevel - job.skillRequired) * 0.1;
        double adjustedTime = job.processingTime * skillFactor / line.speedFactor;
        return static_cast<int>(adjustedTime) + 1;
    }

    // Assign worker to job and return the worker ID
    int assignWorker(const Job& job, int startTime) {
        for (int i = 0; i < workers.size(); ++i) {
            if (workers[i].skillLevel >= job.skillRequired && workers[i].busyUntil <= startTime) {
                return i;
            }
        }
        return -1;  // No worker available
    }

    // Schedule jobs using a greedy algorithm
    void scheduleJobs() {
        set<int> unscheduledJobs;
        for (const auto& job : jobs) {
            unscheduledJobs.insert(job.id);
        }

        while (!unscheduledJobs.empty()) {
            vector<int> readyJobs;
            for (int jobId : unscheduledJobs) {
                if (areDependenciesMet(jobs[jobId])) {
                    readyJobs.push_back(jobId);
                }
            }

            if (readyJobs.empty()) {
                cerr << "Error: Possible cycle in job dependencies detected." << endl;
                return;
            }

            // Sort ready jobs by processing time (longest processing time first)
            sort(readyJobs.begin(), readyJobs.end(), [this](int a, int b) {
                return jobs[a].processingTime > jobs[b].processingTime;
                });

            for (int jobId : readyJobs) {
                Job& job = jobs[jobId];
                int earliestStartTime = getEarliestStartTime(job);
                int bestLineId = -1;
                int bestWorkerId = -1;
                int bestEndTime = INT_MAX;
                int bestStartTime = earliestStartTime;

                for (auto& line : lines) {
                    int processingTime = getActualProcessingTime(job, workers[0], line);  // Assume worker 0 for simplicity
                    int lineStartTime = max(earliestStartTime, line.currentTime);
                    int workerId = assignWorker(job, lineStartTime);
                    if (workerId == -1) continue;

                    int endTime = lineStartTime + processingTime;

                    if (endTime < bestEndTime) {
                        bestLineId = line.id;
                        bestStartTime = lineStartTime;
                        bestWorkerId = workerId;
                        bestEndTime = endTime;
                    }
                }

                if (bestLineId != -1) {
                    lines[bestLineId].scheduledJobs.push_back(job.id);
                    lines[bestLineId].currentTime = bestEndTime;
                    jobStartTimes[job.id] = bestStartTime;
                    jobEndTimes[job.id] = bestEndTime;
                    jobToLine[job.id] = bestLineId;
                    jobToWorker[job.id] = bestWorkerId;
                    jobDuration[job.id] = job.processingTime;
                    job.completed = true;
                    makespan = max(makespan, bestEndTime);

                    unscheduledJobs.erase(job.id);
                }
            }
        }
    }

    // Method to print the schedule with job durations, worker utilization, maintenance, etc.
    void printSchedule() {
        cout << "========== Assembly Line Schedule ==========" << endl;
        cout << "Total Makespan: " << makespan << " time units" << endl;
        for (const auto& line : lines) {
            cout << "Assembly Line " << line.id << " (Speed Factor: " << line.speedFactor << "):" << endl;
            for (int jobId : line.scheduledJobs) {
                cout << "  Job " << jobId << ": Start=" << jobStartTimes[jobId]
                    << ", End=" << jobEndTimes[jobId] << ", Duration=" << jobDuration[jobId] << endl;
            }
        }

        cout << "\n========== Worker Utilization ==========" << endl;
        for (const auto& worker : workers) {
            int totalWorkTime = 0;
            for (const auto& jobEntry : jobToWorker) {
                if (jobEntry.second == worker.id) {
                    totalWorkTime += jobDuration[jobEntry.first];
                }
            }
            double utilization = static_cast<double>(totalWorkTime) / makespan * 100;
            cout << "Worker " << worker.id << " (Skill Level: " << worker.skillLevel << "): "
                << "Work Time=" << totalWorkTime << ", Utilization=" << fixed << setprecision(2) << utilization << "%" << endl;
        }

        cout << "\n========== Maintenance Windows ==========" << endl;
        for (const auto& line : lines) {
            cout << "Assembly Line " << line.id << " Maintenance Windows: ";
            for (const auto& window : line.maintenanceWindows) {
                cout << "[" << window.first << ", " << window.first + window.second << "] ";
            }
            cout << endl;
        }

        cout << "\n========== Gantt Chart ==========" << endl;
        for (const auto& line : lines) {
            cout << "Line " << line.id << ": ";
            for (const auto& jobId : line.scheduledJobs) {
                int startTime = jobStartTimes[jobId];
                int endTime = jobEndTimes[jobId];
                for (int t = startTime; t < endTime; t++) {
                    cout << "J" << jobId << " ";
                }
            }
            cout << endl;
        }

        cout << "\n========== Job Dependencies ==========" << endl;
        for (const auto& job : jobs) {
            cout << "Job " << job.id << " depends on: ";
            if (job.dependencies.empty()) {
                cout << "None";
            }
            else {
                for (size_t i = 0; i < job.dependencies.size(); ++i) {
                    if (i > 0) cout << ", ";
                    cout << job.dependencies[i];
                }
            }
            cout << endl;
        }

        cout << "\n========== Schedule Evaluation ==========" << endl;
        // Calculate average job waiting time
        double totalWaitingTime = 0;
        for (const auto& job : jobs) {
            int earliestPossibleStartTime = getEarliestStartTime(job);
            int actualStartTime = jobStartTimes[job.id];
            totalWaitingTime += (actualStartTime - earliestPossibleStartTime);
        }
        double avgWaitingTime = jobs.size() > 0 ? totalWaitingTime / jobs.size() : 0.0;
        cout << "Average Job Waiting Time: " << fixed << setprecision(2) << avgWaitingTime << " time units" << endl;

        // Total setup time
        int totalSetupTime = 0;
        for (const auto& line : lines) {
            int lastJobId = -1;
            for (const auto& jobId : line.scheduledJobs) {
                if (lastJobId != -1) {
                    totalSetupTime += 2; // Dummy setup time; you can replace this with actual setup time logic
                }
                lastJobId = jobId;
            }
        }
        cout << "Total Setup Time: " << totalSetupTime << " time units" << endl;
        double setupPercentage = static_cast<double>(totalSetupTime) / makespan * 100.0;
        cout << "Setup Time Percentage: " << fixed << setprecision(2) << setupPercentage << "%" << endl;
    }

    int getMakespan() const {
        return makespan;
    }
};


int main() {
    vector<Job> jobs;
    vector<AssemblyLine> lines;
    vector<Worker> workers;

    // Map dataset into jobs, workers, and assembly lines here based on the uploaded data

    // Example setup
    jobs.push_back(Job(0, 35 + 30, {}, 2));  // Adding processing time as sum of downtime
    jobs.push_back(Job(1, 150 + 10, { 0 }, 3));
    jobs.push_back(Job(2, 110 + 40, { 0 }, 2));
    jobs.push_back(Job(3, 80 + 40, { 1, 2 }, 4));

    lines.push_back(AssemblyLine(0, 1.0));
    lines.push_back(AssemblyLine(1, 0.9));

    workers.push_back(Worker(0, 3));
    workers.push_back(Worker(1, 4));

    ALSPSolver solver(jobs, lines, workers);
    solver.scheduleJobs();
    solver.printSchedule();

    return 0;
}

// Function to create a test scenario
//void createTestScenario(vector<Job>& jobs, vector<AssemblyLine>& lines, vector<Worker>& workers) {
//    jobs.push_back(Job(0, 5, {}, 2));
//    jobs.push_back(Job(1, 8, { 0 }, 3));
//    jobs.push_back(Job(2, 6, { 0 }, 2));
//    jobs.push_back(Job(3, 7, { 1, 2 }, 4));
//
//    lines.push_back(AssemblyLine(0, 1.0));
//    lines.push_back(AssemblyLine(1, 0.9));
//
//    lines[0].maintenanceWindows.push_back({ 20, 5 });  // Maintenance at time 20 for 5 units
//    lines[1].maintenanceWindows.push_back({ 15, 3 });  // Maintenance at time 15 for 3 units
//
//    workers.push_back(Worker(0, 3));
//    workers.push_back(Worker(1, 4));
//}

//int main() {
//    vector<Job> jobs;
//    vector<AssemblyLine> lines;
//    vector<Worker> workers;
//
//    createTestScenario(jobs, lines, workers);
//
//    ALSPSolver solver(jobs, lines, workers);
//    solver.scheduleJobs();
//    solver.printSchedule();
//
//    return 0;
//}
