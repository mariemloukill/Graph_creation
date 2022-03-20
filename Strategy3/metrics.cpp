#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
using namespace std::chrono;


void add_result_to_file (double result, string f)
{
    ofstream results_file;
    results_file.open(f, ios_base::app); // append instead of overwrite
    results_file << result<< "\n";
    results_file.close();
}


/*void calculate_total_time ( std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long,
        std::ratio<1, 1000000000>>> start, string results_file)
{
    auto stop = std::chrono::high_resolution_clock::now();
    using Fpseconds =std::chrono::duration<float, std::chrono::seconds::period>;

    static_assert(std::chrono::treat_as_floating_point<Fpseconds::rep>::value,
                  "Rep required to be floating point");
    auto f_ms = Fpseconds(stop - start);
    cout << "total creation time is "<<f_ms.count()<<endl;


}*/

void calculate_peak_RAM (string results_file)
{
    FILE *fp;
    unsigned long peaksize = 0;
    char buf[1024];
    fp = fopen("/proc/self/status", "r");

    while (fgets(buf, sizeof(buf)-1, fp) != NULL) {
        if (sscanf(buf, "VmPeak:%lu", &peaksize) > 0) {
            break;
        }
    }
    fclose(fp);
    cout<< "peak ram usage:" <<peaksize/1024 <<endl;
    add_result_to_file(peaksize/1024,results_file);

}
