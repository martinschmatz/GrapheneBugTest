#include <iostream>
#include <thread>
#include <chrono>



void WorkerThread1 (int MyID, int *ARG)
{
    std::cout << "In WorkerThreadGroup_1,#" << MyID << ": Setting ARG1[" << MyID <<"] = " << (*ARG = MyID) << std::endl;
}

void WorkerThread2 (int MyID, int *ARG)
{
    std::cout << "In WorkerThreadGroup_2,#" << MyID << ": Setting ARG2[" << MyID <<"] = " << (*ARG = MyID) << std::endl;
}


int main() {

    // setup worker threads of typ #1
    const int NumberOfWorkers1 = 5;
    std::thread Worker1[NumberOfWorkers1];

    // setup worker threads of typ #2
    const int NumberOfWorkers2 = 10;
    std::thread Worker2[NumberOfWorkers2];

    // Setup some additional variables
    int ARG1[NumberOfWorkers1] = {0};
    int ARG2[NumberOfWorkers2] = {0};
    std::thread::native_handle_type myhandle;

    std::cout << "\nStarting application...." << std::endl;
    std::cout << "... with " << NumberOfWorkers1 << " threads in first thread group...." << std::endl;
    std::cout << "... with " << NumberOfWorkers2 << " threads in second thread group...." << std::endl;

    ///////////////////////////
    // .....some computing.....
    std::cout << "\nSupposedly doing some initial work here" << std::endl << std::endl;
    ///////////////////////////

    std::cout << "Starting first bunch of threads: " << std::endl;
    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();
    // start the first bunch of parallel threads
    for (int i = 0; i < NumberOfWorkers1; i++)
        Worker1[i] = std::thread (&WorkerThread1, i, &ARG1[i]);

    // wait for the first bunch of parallel threads to be complete
    for (int i = 0; i < NumberOfWorkers1; i++)
    {
        // store a handle to the thread (while thread still exists)
        myhandle = Worker1[i].native_handle();
        // wait for the thread to be complete and join
        Worker1[i].join();
        // "Kill" the related (p)thread by using the previously stored handle
        pthread_cancel(myhandle);
    }
    // Stop timer and report result
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "All threads from first group of threads completed their work in " << elapsed_seconds.count()*1.0e6 << "us" << std::endl;
    // report what the threads calculated
    std::cout << "...now reporting results from first group of threads in main thread: " << std::endl;
    for (int i = 0; i < NumberOfWorkers1; i++)
        std::cout << "ARG1[" << i <<"] = " << ARG1[i] << std::endl;


    ///////////////////////////
    // .....some computing.....
    std::cout << "\nSupposedly doing some more work here" << std::endl << std::endl;
    ///////////////////////////


    std::cout << "Starting second bunch of threads: " << std::endl;
    // start the second bunch of parallel threads
    // Start the timer
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NumberOfWorkers2; i++)
        Worker2[i] = std::thread (&WorkerThread2, i, &ARG2[i]);

    // wait for the first bunch of parallel threads to be complete
    for (int i = 0; i < NumberOfWorkers2; i++)
    {
        // store a handle to the thread (while thread still exists)
        myhandle = Worker2[i].native_handle();
        // wait for the thread to be complete and join
        Worker2[i].join();
        // "Kill" the related (p)thread by using the previously stored handle
        pthread_cancel(myhandle);
    }
    // Stop timer and report result
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    std::cout << "All threads from second group of threads completed their work in " << elapsed_seconds.count()*1.0e6 << "us" << std::endl;
    // report what the threads calculated
    std::cout << "...now reporting results from second group of threads in main thread: " << std::endl;
    for (int i = 0; i < NumberOfWorkers2; i++)
        std::cout << "ARG2[" << i <<"] = " << ARG2[i] << std::endl;


    ///////////////////////////
    // .....some computing.....
    std::cout << "\nSupposedly continuing to work until application ends" << std::endl << std::endl;
    ///////////////////////////



    return 0;
}