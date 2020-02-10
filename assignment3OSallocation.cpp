#include <chrono>
#include<iostream>
#include <time.h>
#include <cstdlib>
#include <ctime>

#define MAX_SIZE 128
#define TEST_SIZE 10000

using namespace std;

//Object Oriented Approach
class memory
{
    public:
        memory();
        void allocate_mem(int mode);
        int firstfit(int process_id, int num_units);
        int bestfit(int process_id, int num_units);
        int worstfit(int process_id, int num_units);
        int nextfit(int process_id, int num_units);
        int deallocate_mem (int process_id);
        int fragment_count();
        void statistics();
		
    private:
        void init_processes();
        void init_allocation();
        int processsize[TEST_SIZE];
        int array[MAX_SIZE];
        int fragments;
        int position;

};
memory::memory(){
    init_processes();
    init_allocation();
    fragments=0;
    position=0;
	//constructer
}

void memory::init_processes(){
   srand((unsigned int)time(NULL));
    for(int i=0;i<=TEST_SIZE;i++)
    {
        processsize[i]=rand()%8+3;
		//getting random numbers to declare process sizes between 3-10 
		//any number can be 0-7 between after %8 operation adding 3 will make it 3-10
    }

}

void memory::init_allocation(){
    for(int i=0;i<MAX_SIZE;i++) //256 divided by 2 is 128 we need 128 node,or array slot.
{
    array[i]=0;			//making initial memory slots that is filled by 0s.
}

}

void memory::statistics() {
    for(int i=0;i<MAX_SIZE-6;++i){
        
        cout<< array[i] << " ";


    }
    int fgtc = fragment_count();
    cout << endl;
    cout<<"There are "<< fgtc <<" fragments in memory."<<endl;
}

int memory::fragment_count() {
    
    fragments=0;
   
    for(int i=0;i<MAX_SIZE;i++){
        if(array[i] == 0 ){
            fragments++;
        }
       
    }
    return fragments; //return fragment count
}


int memory::firstfit(int process_id, int num_units)
{
    int ct=num_units; 
    for(int iterator=0;iterator<=MAX_SIZE-num_units;iterator++) 
    {
        if (array[iterator] == 0) 
        {
            for (int j = (iterator + 1); j < MAX_SIZE; j++)
            {
              if (array[j] == 0 && ct != 0) 
              {
                 ct--;
            	} else if (array[j] != 0) 
            		{
                	iterator = j;
                	ct = num_units;

           		 	} else if (ct == 0 && array[j] == 0) 
           		 	{
                	for (int k = iterator; k < iterator + num_units; k++) 
                		{
                    	array[k] = process_id;
						}
                
                return 1;
            		} else 
            	{
					return -1;
            	}
            }
        }
    }
    return -1;
}



int memory::bestfit(int process_id, int num_units){
    int bestfit=MAX_SIZE+1;
    int bf=0;

    for(int iterator=0;iterator<=MAX_SIZE-num_units;iterator++){
        if (array[iterator] == 0){
            for (int j = (iterator + 1); j < MAX_SIZE; j++){
                if (array[j] == 0){
                    bf++;
                    if(bf==MAX_SIZE-1){
                        for (int k = iterator; k < iterator + num_units; k++) {
                            array[k] = process_id;
                            cout<<"Process 1 is stored in "<<array[k]<< k <<endl;
                    }
                        return 1;   }
                }

        else if (array[j] != 0) {
                   

                    if (bf<bestfit && bf>num_units){
                            bestfit=bf;
                            iterator = j;
                            bf=0;
                    }
                    else if(bf>bestfit && bf>num_units){
                            iterator=j;
                            bf=0;
                    }
                    else if(bf=num_units){
                        for (int k = iterator; k < iterator + num_units; k++) {
                            array[k] = process_id;
                            cout<<"Process 2 is stored in"<< array[k] << k <<endl;
                    }
                        return 1;   }

                    }
                    else  {
                        
                        return -1; }
                }

                for (int k = iterator; k < iterator + num_units; k++) {
                    array[k] = process_id;
                    cout<<"Process 3 is stored in " <<array[k]<< k <<endl;   }
                    return 1;
    }

}

return -1;

}


int memory::worstfit(int process_id, int num_units){

    int worstfit=num_units;
    int dummmy=0;

    for(int iterator=0;iterator<=MAX_SIZE-num_units;iterator++){
        if (array[iterator] == 0){
            for (int j = (iterator + 1); j < MAX_SIZE; j++){
                if (array[j] == 0){
                    dummmy++;
                    if(dummmy==MAX_SIZE-1){
                        for (int k = iterator; k < iterator + num_units; k++) {
                            array[k] = process_id;
                            cout<< "Process 1 is stored in" << array[k] << k <<endl;
                    }
                        return 1;   }
                }

        else if (array[j] != 0) {
                    

                    if (dummmy<worstfit && dummmy>num_units){

                            iterator = j;
                            dummmy=0;
                    }
                    else if(dummmy>worstfit && dummmy>num_units){
                            worstfit=dummmy;
                            iterator=j;
                            dummmy=0;
                    }
                    else  
                    	{
                        
                        return -1; 
                        
                        }
                }

                for (int k = iterator; k < iterator + num_units; k++) {
                    array[k] = process_id;
                    cout<<"Process 3 is stored in "<< array[k] << k <<endl;   }
                    return 1;
    }

}
    }

return -1;


}


int memory::nextfit(int process_id, int num_units){
    int ct=num_units; //counting free blocks in a row
    for(int iterator=position;iterator<=MAX_SIZE-num_units;iterator++) {
        if (array[iterator] == 0) {
            for (int j = (iterator + 1); j < MAX_SIZE; j++){
                if (array[j] == 0 && ct != 0) {
                    ct--;
                } else if (array[j] != 0) {
                    iterator = j;
                    position = iterator;
                    ct = num_units;
         
                } else if (ct == 0 && array[j] == 0) {
                    int k;
                    for ( k = iterator; k < iterator + num_units; k++) {
                        array[k] = process_id;
              
                    }
                    position=k+1;
                    if(position==MAX_SIZE){position=0;}
                    return 1;
                } else {
               
                    return -1;
                }
            }
        }
    }
    return -1;
} 
 
void memory::allocate_mem(int input){
	
    int dummy;
    int dummy2=1;
for (int i=0;i<TEST_SIZE;i++)
{
    dummy = processsize[i];
    
    if(input==1) {
        while (firstfit(i + 1, dummy) == -1) {
            if (deallocate_mem(dummy2) == 1) {
                dummy2++;
            }
        }
    } else if(input==2) {
        while (nextfit(i + 1, dummy) == -1) {
            if (deallocate_mem(dummy2) == 1) {
                dummy2++;
            }
        }
    } else if(input==3) {
        while (bestfit(i + 1, dummy) == -1) {
            while (deallocate_mem(dummy2) == -1) {
                dummy2++;
            }
        }
    } else if(input==4) {
        while (worstfit(i + 1, dummy) == -1) {
            while (deallocate_mem(dummy2) == -1) {
                dummy2++;
            }

        }
    }
}
	

}




int memory::deallocate_mem(int process_id){
    int i=0;
    bool boo=false;
  
    while(i<MAX_SIZE){
        if(boo ||array[i]==process_id){
            boo=true;
            array[i]=0;
            if(array[i+1]!=process_id){
                return 1;
            }

        }
        i++;
    }
    return -1;

}

int main(){
    memory qwerty;
   
    cout << "first fit simulation = 1" << endl;  
    cout << "next fit simulation = 2" << endl;
    cout << "best fit simulation = 3" << endl;
    cout << "worst fit simulation = 4" << endl;  
    int choice = 0;
    cout << "enter your choice" << endl;
    cin >> choice;
    
    // Record start time
auto start = std::chrono::high_resolution_clock::now();
    qwerty.allocate_mem(choice);
    // Record end time
auto finish = std::chrono::high_resolution_clock::now();
    qwerty.statistics();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Allocation time: " << elapsed.count() << " s\n";
	

}


