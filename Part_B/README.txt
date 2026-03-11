How to Compile

From the Part_B directory:
g++ src/*.cpp -o scheduler
./scheduler


Output Files

Running the program generates scheduling traces and Gantt charts for each algorithm:

output_fcfs.txt
output_priority.txt
output_srtf.txt
output_rr.txt

Each file contains:
Time-step execution trace
READY queue state
RUNNING process
inal Gantt chart