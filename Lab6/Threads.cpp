#include <iostream>
#include <ctime>
#include <pthread.h>
#include <climits>

using namespace std;


int* array = nullptr;
int* result_array = nullptr;

struct Range{
    int start_index;
    int end_index;
};


void show_array(int* array, int array_size){
    for(int i=0; i < array_size; i++){
        cout << array[i] << " ";
    }
    
    cout << endl;
    return;
}

int EndSorting(Range* r, int max_index) {
	int index = max_index + (r->end_index - r->start_index);
	
	for(int i=r->start_index; i < r->start_index + (r->end_index - r->start_index); i++){
	   int num = array[i];
	   
	   for(int j=0; j < max_index; j++){
	   	if(result_array[j] > num){
	   		int temp = result_array[j];
	   		result_array[j] = num;
	   		num=temp;
	   	}
	   }
	   
	   result_array[max_index]=num;
	   max_index++;
	}
	
	return index;
}


void* bubble_sort(void* param){
   int start = ((Range*) param) -> start_index;
   int end = ((Range*) param) -> end_index;
   
   for(int i = start; i < end; i++){
   	for(int j = start; j < end; j++){
   	    if(array[i] < array[j]){
   	    	int temp = array[i];
   	    	array[i] = array[j];
   	    	array[j] = temp;
   	    }
   	}
   }   
}

int sorting(int array_size){ 
    int threads_amount;
    cout << "Enter amount of threads: " << endl;
    cin >> threads_amount;

    pthread_t threads[threads_amount];
    

    int start_index=0;
    int end_index=(array_size/threads_amount);
    
    Range** arr_range = new Range*[threads_amount];
    
    for(int i=0; i < threads_amount; i++){
        arr_range[i] = new Range(); 
        
        arr_range[i]->start_index = start_index;
        
        if(threads_amount-1 == i){
            arr_range[i]->end_index = array_size;
        } else {
            arr_range[i]->end_index = end_index;
            start_index += (array_size/threads_amount);
            end_index += (array_size/threads_amount);
        }
        
        pthread_create(&threads[i], NULL, bubble_sort, arr_range[i]);
    }
    
    for(int i=0; i < threads_amount; i++){
       pthread_join(threads[i], NULL);
    }
    
    result_array = new int[array_size];
    
    int index = 0;  
    
    for(int i=arr_range[index]->start_index; i<arr_range[index]->end_index;i++){
    	result_array[i]=array[i];
    }

    
    int max_index = (arr_range[index]->end_index - arr_range[index]->start_index);
    
    for(int i=index+1; i<threads_amount;i++){
    	max_index = EndSorting(arr_range[i], max_index);
    }
    
    
    return 0;
}

void create_array(int array_size){
    array = new int[array_size];
    
    for(int i=0; i < array_size; i++){
        array[i] = rand() % 103 + 1;
    }
}


int main(){
    srand(time(NULL)); 
    int array_size;
    cout << "Enter array size: " << endl;
    cin >> array_size;
    
    create_array(array_size);
    show_array(array, array_size); 
    
    sorting(array_size);
    
    show_array(result_array, array_size);
        
    return 0;
}

