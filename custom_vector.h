#include <stdlib.h>
#include <mem.h>

template <typename T>
struct custom_vector{
	custom_vector(){
		data = malloc(0);
		size = 0;
	}

	void push(T &a){
		data = realloc(data, size * sizeof(T) + sizeof(T));
		data[size++] = a;
	}

	void remove(T &a){
		for(T* h = data; h < h + size; h++){
			if(*h == a){
				if(h - data != size - 1)
					memmove(h, h + 1, (size - (h - data) - 1) * sizeof(T));
				data = realloc(data, size * sizeof(T) - sizeof(T));
				--size;
				break;
			}
		}
	}

	T& operator[](int i){
		return data[i];
	}

private:
	T* data;
	size_t size;
};