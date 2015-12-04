#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;



int main(int argc, char *argv[])
{
  int th_id, nthreads;
  vector<int *> glb;
  glb.resize(20); 
  #pragma omp parallel private(th_id) shared(nthreads, glb)
  {
    th_id = omp_get_thread_num();
    int nt = omp_get_num_threads();
    int* ltid = new int;
    *ltid = th_id;
    glb[th_id] = ltid;
    #pragma omp barrier

    #pragma omp critical
    {
      cout << "Hello World from thread " << th_id
      << "next thread is "<< *glb[(th_id+1)%nt]
      << '\n';
    }
    #pragma omp barrier
 
    #pragma omp master
    {
      nthreads = omp_get_num_threads();
      cout << "There are " << nthreads << " threads" << '\n';
    }
  }
  return 0; 
}