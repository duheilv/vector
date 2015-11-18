#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <cstring>

// Minimal class to replace std::vector
template<typename Data>
class vector {

public:
   // Default constructor
   vector() : d_size(0), d_capacity(0), d_data(0) {}

   // Copy constuctor
   vector(vector const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) {
      d_data = (Data*)malloc(d_capacity*sizeof(Data));
      memcpy(d_data, other.d_data, d_size*sizeof(Data));
   }

   // Destructor
   ~vector(){
      free(d_data);
   }

   // Needed for memory management
   vector &operator=(vector const &other) {
      free(d_data);
      d_size = other.d_size;
      d_capacity = other.d_capacity;
      d_data = (Data*)malloc(d_capacity*sizeof(Data));
      memcpy(d_data, other.d_data, d_size*sizeof(Data));
      return *this;
   }

   // Adds new value. If needed, allocates more space
   void push_back(Data const &x) {
      if(d_capacity == d_size) {
         resize();
      }
      d_data[d_size++] = x;
   }

   // Erases a value. Compacts the rest of the vector. Does not call the destructor of complex objects. Does not reallocate.
   void erase(size_t idx) {
      if(idx < d_size) {
         for(size_t i = idx; i < d_size-1; i++) {
            d_data[i] = d_data[i+1];
         }
         d_size--;
      }
   }

   // Clears the entire array. Does not call the destructor of complex objects.
   void clear(void) {
      d_size = 0;
      d_capacity = 0;
      free(d_data);
   }

   // Size getter
   size_t size() const {
      return d_size;
   }

   // Const getter
   Data const &operator[](size_t idx) const {
      return d_data[idx];
   }

   // Changeable getter
   Data &operator[](size_t idx) {
      return d_data[idx];
   }

private:
   size_t d_size;      // Stores no. of actually stored objects
   size_t d_capacity;  // Stores allocated capacity
   Data*  d_data;      // Stores data

   // Allocates double the old space
   void resize() {
      d_capacity = d_capacity ? d_capacity*2 : 1;
      Data *newdata = (Data*)malloc(d_capacity*sizeof(Data));
      memcpy(newdata, d_data, d_size * sizeof(Data));
      free(d_data);
      d_data = newdata;
   }
};

#endif
