#pragma once
namespace custom {
    template <typename T>
    class Stack {
        public: 
        Stack (T* begin, T* end);
        Stack () {
            begin = new T[0];
            end = begin;
            }
        T* getAlloc() const;
        Stack (const Stack& other);
        ~Stack();
        Stack (const Stack&& other);
        int getLength ();
        bool operator == (const Stack& other) const;
        void operator =(const Stack& other);
        Stack& operator =(const Stack&& other);
        Stack& push (T element);
        Stack& pop (T& changed);
        Stack& operator << (T element);
        Stack& operator >> (T& changed);
        T operator [](int current);
        private: 
        T* getEnd() const;
        T* begin;
        T* end;
    };
}


namespace custom {
    template <typename T>
    int Stack<T>::getLength () {
       return (end - begin) / sizeof(T); 
    }
    template <typename T>
    Stack<T>& Stack<T>::push (T element) {
        end += sizeof(T);
        begin[(end - begin) / sizeof(T) - 1] = element;
        return *this;
    }
    template <typename T> 
    Stack<T>& Stack<T>::operator << (T element) {
       return push(element);
    }
    template <typename T> 
    Stack<T>& Stack<T>::operator >> (T& changed) {
        return pop(changed);
    }
    template <typename T>
    Stack<T>& Stack<T>::pop (T& changed) {
        changed = *end;
        end -= sizeof(T);
        return *this;
    }
    template <typename T>
    T Stack<T>::operator [](int current) {
        if (current < getLength()) {
            return begin[current];
        }
        else throw "out of range";
    }
    template <typename T> 
    Stack<T>::Stack (T* begin, T* end){
            T* tmp = new T[(end - begin) / sizeof(begin)];
            for (int i = 0; i < (end - begin) / sizeof(begin); i++) {
                tmp[i] = begin[i];
            }
            this -> begin = tmp;
            this -> end = tmp + (end - begin);
        }
template <typename T>       
Stack<T>:: ~Stack(){
        
        }
template <typename T>    
        T* Stack<T>::getAlloc() const{
            return begin;
        }
template <typename T>
        T* Stack<T>::getEnd() const{
            return end;
        }
        template <typename T>  
        Stack<T>::Stack (const Stack<T>& other) {
          Stack(other.getAlloc(), other.getEnd());
        }
        template <typename T>
        Stack<T>::Stack (const custom::Stack<T>&& other) {
            this -> begin = other.getAlloc();
            this -> end = other.getEnd();
            delete []other.getAlloc();
            delete []other.getEnd();
        }
        template <typename T>
        void custom::Stack<T>::operator = (const Stack<T>& other) {
                this ->begin = other.getAlloc();
                this->end = other.getEnd();
            
        }
        template <typename T>
        Stack<T>& custom::Stack<T>::operator = (const Stack<T>&& other) {
            if (!(this == other)) {
                delete this;
                Stack (other);
                return *this;
            }
        }
        template <typename T>
        bool Stack<T>::operator ==(const Stack<T>& other) const{
            return (begin == other.getAlloc() && end == other.getEnd());
        }
}