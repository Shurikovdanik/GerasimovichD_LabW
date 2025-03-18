#pragma once
namespace custom {
    template <typename T>
    class Stack {
        public: 
        Stack (T* begin, T* end);
        Stack();
        Stack(T* begin, int length);
        T* getAlloc() const;
        Stack (const Stack& other);
        ~Stack();
        Stack (const Stack&& other);
        int getLength () const;
        bool operator == (const Stack& other) const;
        void operator =(const Stack& other);
        Stack& operator =(const Stack&& other);
        Stack& push (T element);
        Stack& pop (T& changed);
        Stack reverse() const;
        void selfreverse();
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
    Stack<T> Stack<T>::reverse() const{
        int length = getLength();
        T* array = new T[length];
        for (int i = 0; i < length; i++) {
            array[i] = begin[length - i - 1];
        }
        Stack<T> res(array, length);
        return res;
    }
    template <typename T>
    void Stack<T>::selfreverse() {
        int length = getLength();
        
        for (int i = 0; i < length / 2; i++) {
            T temp;
            temp = begin[i];
           begin[i]=begin[length - i - 1];
           begin[length - i - 1] = temp;
        }
       
    }
    template <typename T>
    int Stack<T>::getLength () const{
        size_t length = end - begin;
        int res = 0;
        for (int i = 0; i < length; i += sizeof(begin[i])) {
            res++;
        }
       return  res; 
    }
    template <typename T>
    Stack<T>& Stack<T>::push (T element) { 
        int length = getLength();
        size_t byteLength = end - begin;
       
        if (length == 0) {
            this->begin = new T[1];
            begin[0] = element;
            this->end = begin + sizeof(element);
        }
        else {
            T* temp = new T[length];
            for (int i = 0; i < length; i++) {
                temp[i] = begin[i];
            }
            this->begin = new T[length + 1];
            for (int i = 0; i < length; i++) {
                begin[i] = temp[i];
            }
            begin[length] = element;
            this->end = this->begin + byteLength + sizeof(element);
        }
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
        if (begin == end) {
            throw std::runtime_error("Less than zero elements will be");
        }
            int length = this->getLength();
            changed = getAlloc()[length - 1];
            this->end = getEnd() - sizeof(getAlloc()[length - 1]);
        return *this;
    }
    template <typename T>
    T Stack<T>::operator [](int current){
        if (current < getLength()) {
            return begin[current];
        }
        else throw std::runtime_error("out of range");
        throw std::exception_ptr();
    }
    template <typename T> 
    Stack<T>::Stack (T* begin, T* end){
        int length = end - begin;
        
            this->begin = new T[length];
            for (int i = 0; i < length; i+=sizeof(begin[i])) {
                this->begin[i] = begin[i];
            }
            this -> end = (this -> begin) +length;
        }
    template <typename T>
    Stack<T>::Stack(T* begin, int length) {
        this->begin = new T[length];
        for (int i = 0; i < length; i++) {
            this->begin[i] = begin[i];
        }
        this->end = this -> begin + sizeof(T) * (length);
    }
    template <typename T>
    Stack<T>::Stack() {
        T* tmp = new T[1];
        this->begin = tmp;
        this->end = tmp;
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
            
        }
        template <typename T>
        void custom::Stack<T>::operator = (const Stack<T>& other) {
                this ->begin = other.getAlloc();
                this->end = other.getEnd();
            
        }
        template <typename T>
        Stack<T>& custom::Stack<T>::operator = (const Stack<T>&& other) {
                Stack res (other);
                this -> begin = res.getAlloc();
                this->end = res.getEnd();
                return res;
        }
        template <typename T>
        bool Stack<T>::operator ==(const Stack<T>& other) const{
            return (begin == other.getAlloc() && end == other.getEnd());
        }
}