#include <iostream>
#include <stdexcept>
#include <limits>

template<typename Temp>
class GenericArray {
private:
  Temp* data_;
  int size_;

  void copyFrom(const GenericArray &other) {
    if (other.size_ == 0) {
      data_ = nullptr;
      size_ = 0;
      return;
    }
    data_ = new Temp[other.size_];
    for (int i = 0; i < other.size_; ++i) data_[i] = other.data_[i];
    size_ = other.size_;
  }

public:
  GenericArray(): data_(nullptr), size_(0) {}

  // Copy constructor
  GenericArray(const GenericArray &other) {
    copyFrom(other);
  }

  // Copy assignment
  GenericArray& operator=(const GenericArray &other) {
    if (this == &other) return *this;
    delete[] data_;
    copyFrom(other);
    return *this;
  }

  ~GenericArray(){
    delete[] data_;
  }

  void addElement(const Temp &value){
    // Allocate new array
    Temp *newData = new Temp[size_ + 1];
    for (int i = 0; i < size_; ++i) newData[i] = data_[i];
    newData[size_] = value;
    // delete old and swap
    delete[] data_;
    data_ = newData;
    ++size_;
  }

  Temp at(int index) const {
    if (index < 0 || index >= size_) throw std::out_of_range("Index out of range in at()");
    return data_[index];
  }

  int size() const { return size_; }

  Temp sum() const {
    Temp s = Temp{};
    for (int i = 0; i < size_; ++i) s += data_[i];
    return s;
  }

  Temp max() const {
    if (size_ == 0) throw std::runtime_error("max() called on empty array");
    Temp m = data_[0];
    for (int i = 1; i < size_; ++i) if (data_[i] > m) m = data_[i];
    return m;
  }

  Temp min() const {
    if (size_ == 0) throw std::runtime_error("min() called on empty array");
    Temp m = data_[0];
    for (int i = 1; i < size_; ++i) if (data_[i] < m) m = data_[i];
    return m;
  }

  // Returns a NEW array pointer
  Temp* slice(int begin, int end) const {
    if (begin < 0 || end < 0 || begin >= size_ || end >= size_ || begin > end)
      throw std::out_of_range("Invalid slice bounds");
    int newSize = end - begin + 1;
    Temp *out = new Temp[newSize];
    for (int i = 0; i < newSize; ++i) out[i] = data_[begin + i];
    return out;
  }
};

int main(){
  // Test with int
  GenericArray<int> int_array;
  for (int i = 0; i < 11; ++i) int_array.addElement(i * 2);

  std::cout<< "\n=== INT ARRAY ===" << std::endl;
  std::cout << "Integer array contents: ";
  for (int i = 0; i < int_array.size(); ++i) std::cout << int_array.at(i) << (i+1<int_array.size()?",":"\n");

  std::cout << "size of array is: " << int_array.size() << std::endl;
  std::cout << "sum of the array is: " << int_array.sum() << std::endl;
  std::cout << "maximum and minimum of array is: " << int_array.max() << "\t" << int_array.min() << std::endl;

  // Slice example:
  int begin = 2, end = 5;
  int *sliced_array = int_array.slice(begin,end);
  int sliced_size = end - begin + 1;
  std::cout << "Sliced array [" << begin << "," << end << "] contents: ";
  for (int i = 0; i < sliced_size; ++i) std::cout << sliced_array[i] << (i+1<sliced_size?",":"\n");
  delete[] sliced_array;

  // Test with float
  GenericArray<float> float_array;
  float_array.addElement(1.5f);
  float_array.addElement(2.25f);
  float_array.addElement(-0.75f);
  std::cout<< "\n=== FLOAT ARRAY ===" << std::endl;
  std::cout << "Float array: ";
  for (int i = 0; i < float_array.size(); ++i) std::cout << float_array.at(i) << (i+1<float_array.size()?",":"\n");
  std::cout << "Size: " << float_array.size() << ", sum: " << float_array.sum() << ", max: " << float_array.max() << ", min: " << float_array.min() << std::endl;

  return 0;
}
