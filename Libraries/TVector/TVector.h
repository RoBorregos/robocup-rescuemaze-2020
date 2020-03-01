// Code made by the RoBorregos team in 2020 for the RoboCup JR. Rescue Maze category.
// Grecia Flores, Diego Prado, Marlon Romo, and Emérico Pedraza.
//
// This class is intended to be able to work with a simulation of Vectors in Arduino.
// It's principal use is the creation of an expandable map that helps the robot to travel the maze.

#ifndef TVector_h
#define TVector_h

#include "Arduino.h"
#include "Tile.h"

template <class T>
class TVector {
  private:
    uint8_t size_;
    T *vector_;

  public:
    //Constructor with 1 element.
    TVector();
    //Constructor that copies another vector.
    TVector(const TVector &V);
    //Destructor.
    ~TVector();

    //Returns an uint8_t with the size of the vector.
    uint8_t getSize();

    //Stock the parameter data at the end of the vector.
    void pushAsLast(T t);
    //Stock the parameter data at the beggining of the vector.
    void pushAsFirst(T t);
    //Deletes the last element of the vector and reduces it's size.
    void popLast();
    //Deletes the first element of the vector and reduces it's size.
    void popFirst();
    //Stock the parameter data at the specified index of the vector.
    void set(T t, uint8_t index);
    //Erase the element on the specified index of the vector and reduces it's size.
    void erase(uint8_t index);

    //Returns the element on the specified index of the vector (inside the []).
    T& operator[](uint8_t index) const;
    //Allows to equal two vectors.
    void operator=(const TVector &V);
};

template <class T>
TVector<T>::TVector() {
  size_ = 0;
  vector_ = NULL;
}

template <class T>
TVector<T>::TVector(const TVector &V) {
  vector_ = new T[V.size_];
  
  for (int i = 0 ; i < V.size_ ; i++) {
    vector_[i] = V[i];
  }

  size_ = V.size_;
}

template <class T>
TVector<T>::~TVector() {
  delete[] vector_;
}

template <class T>
uint8_t TVector<T>::getSize() {
  return size_;
}

template <class T>
void TVector<T>::pushAsLast(T t) {
  T *newVector = new T[size_ + 1];

  for(int i = 0 ; i < size_ ; i++) {
    newVector[i] = vector_[i];
  }
  newVector[size_] = t;

  delete[] vector_;
  vector_ = newVector;
  size_++;
}

template <class T>
void TVector<T>::pushAsFirst(T t) {
  T *newVector = new T[size_ + 1];

  for(int i = 0 ; i < size_ ; i++) {
    newVector[i+1] = vector_[i];
  }
  newVector[0] = t;

  delete[] vector_;
  vector_ = newVector;
  size_++;
}

template <class T>
void TVector<T>::popLast() {
  T *newVector = new T[size_ - 1];

  for (int i = 0 ; i < size_ - 1 ; i++) {
    newVector[i] = vector_[i];
  }

  delete[] vector_;
  vector_ = newVector;
  size_--;
}

template <class T>
void TVector<T>::popFirst() {
  T *newVector = new T[size_ - 1];

  for (int i = 0 ; i < size_ - 1 ; i++) {
    newVector[i] = vector_[i + 1];
  }

  delete[] vector_;
  vector_ = newVector;
  size_--;
}

template <class T>
void TVector<T>::set(T t, uint8_t index) {
  vector_[index] = t;
}

template <class T>
void TVector<T>::erase(uint8_t index) {
  if ( index >= 0 && index < size_ ) {
    T *newVector = new T[size_ - 1];

    for(int i = 0 ; i < size_ - 1 ; i++) {
      if ( i != index ) {
        if ( i < index ) {
            newVector[i] = vector_[i];
        }
        else {
            newVector[i - 1] = vector_[i];
        }
      }
    }

  delete[] vector_;
  vector_ = newVector;
  size_--;

  }
}

template <class T>
T& TVector<T>::operator[](uint8_t index) const {
  return vector_[index];
}

template <class T>
void TVector<T>::operator=(const TVector &V) {
  delete vector_;
  vector_ = new T[V.size_];

  for (int i = 0 ; i < V.size_ ; i++) {
    vector_[i] = V[i];
  }

  size_ = V.size_;
}

#endif