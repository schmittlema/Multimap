#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
//Jake Papineau
//Mike Gallo
//Matt Schmittle
//Drake Smith
template <typename type>
class DynArray{
    private:
        type *ar;
        int length;
        int nextIndex;
    public:
        DynArray(){
            ar = (type*) malloc(sizeof(type)*1);
            length = 1;
            nextIndex = 0;
        }
        
        ~DynArray(){
            free(ar);
        }

	void setVal(int loc, type val){
		ar[loc] = val;			
	}
	
	void clear(){
		free(ar);
		ar = (type*) malloc(sizeof(type)*1);
		length = 1;
		nextIndex = 0;	
	}
        
        int getLength(){
            return length;
        }
        
        int getNextIndex(){
            return nextIndex;
        }
        
        type get(int index){
            return ar[index];
        }
	

	bool isIn(type val){
		for(int i = 0; i <length; i++){
			if(val== ar[i]){
				return true;
			}
		}

		return false;
	}	
        
	int indexofVal(type val){
		for(int i = 0; i <length; i++){
			if(val == ar[i]){
				return i;
			}
		}
		return -1;
	}	

        void add(type val){
            type *newAr;
            if (nextIndex == length){
                length *=2;
                newAr = (type*)malloc(sizeof(type)*(length));
                for(int i = 0; i < nextIndex; i++){
                    newAr[i] = ar[i];
                }
                free(ar);
                ar = newAr;
            }
            ar[nextIndex++] = val;
        }
	
        
        void display(){
            cout << "Array: ";
            for (int i = 0; i< getNextIndex(); i++){
                cout << get(i) << ", ";
            }
        cout << endl;
        }
    
};



class MultiMap{
	private:
		DynArray< DynArray<int>* > *valarray;
		DynArray<const char *> *keys;		
	public:
		MultiMap(){
			valarray = new DynArray<  DynArray<int>* >();	
			keys = new DynArray<const char *>();
		}
		~MultiMap(){
			delete(valarray);
			delete(keys);
		}


	void set(const char * key, int val){
		if(keys->isIn(key)){
			valarray->get(keys->indexofVal(key))->add(val);
		}
		else{
			keys->add(key);
			DynArray<int> *vala = new DynArray<int>();
			vala->add(val);
			valarray->add(vala);
		}
			
	}
	
	void removeAll(const char* key){
		valarray->get(keys->indexofVal(key))->clear();	
		
	}
	
	int count(const char* key){
		DynArray<int> * a = valarray->get(keys->indexofVal(key));
		int count = 0;
		for(int i = 0; i<a->getLength();i++){
			if(a->get(i) >= 0){
				count++;
			}	
		}
		return count;
	}

	DynArray<int>* getAll(const char* key){
		return valarray->get(keys->indexofVal(key));
	}

	
	void printMap(){
		for(int i = 0; i<keys->getLength();i++){
			cout<< "Key: "<<keys->get(i)<<endl;	
			valarray->get(i)->display();
			cout<<endl;
		}
	}

};

int main(){
	MultiMap mmap = MultiMap();
	mmap.set("key1",5);
	mmap.set("key2", 4);
	mmap.set("key2",7);
	mmap.set("key1",9);
	mmap.printMap();
	cout<< "After removeAll"<<endl;
	mmap.removeAll("key1");
	mmap.printMap();

	cout<< "Count 'key2': "<< mmap.count("key2")<<endl;
	cout<< "getAll Function output: ";
	mmap.getAll("key2")->display();
}







