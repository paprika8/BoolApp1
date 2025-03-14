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

	~custom_vector(){
		free(data);
	}

	iterator begin(){
		return iterator(data);
	}
	iterator end(){
		return iterator(data + size);
	}

	struct iterator{
		iterator(T* ait){
			it = ait;
		}

		T& operator*(){
			return *it;
		}

		iterator operator+=(int a){
			it += a;
			return *this;
		}
		iterator operator+(int a){
			iterator buf(it);
			buf += a;
			return buf;
		}

		iterator operator-=(int a){
			it -= a;
			return *this;
		}
		iterator operator-(int a){
			iterator buf(it);
			buf -= a;
			return buf;
		}

		int operator-(iterator b){
			return it - b.it;
		}

		bool operator==(iterator b){
			return it == b.it;
		}
		bool operator!=iterator b){
			return it != b.it;
		}
		bool operator<(iterator b){
			return it < b.it;
		}
		bool operator>(iterator b){
			return it > b.it;
		}
		private:
		T* it;
	}

private:
	T* data;
	size_t size;
};