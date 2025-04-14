#include "algs.h"

void useOPT(std::string filename, Algorithms* algs)
{   
    algs->optAlg(filename);
  
}

int main()
{
    Algorithms* algs = new Algorithms(); 

    delete algs; 
}