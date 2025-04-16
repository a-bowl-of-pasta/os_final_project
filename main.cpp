#include "algs.h"

void useOPT(std::string filename, Algorithms* algs)
{   
    algs->optAlg(filename);
}
void useFifo(std::string filename, Algorithms* algs)
{
     algs->fifo(filename);
}
int main()
{
    Algorithms* algs = new Algorithms(); 
    
    useOPT("OPT.txt", algs);
    
    std::cout<<std::endl<<std::endl; 
    
    useFifo("FIFO.txt", algs); 

    delete algs; 
}