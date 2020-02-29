#ifndef TVector_h
#define TVector_h

#include "Arduino.h"
#include "Tile.h"

template <class T>
class TVector {
  private:
    uint8_t iSize;
    T *vector;

  public:
    TVector();//constructor with 1 element
    TVector(const TVector &V);//constructor that copies another vector
    ~TVector();

    uint8_t getSize();

    void pushTop(T t);
    void pushFront(T t);
    void popTop();
    void popFront();
    void set(T t, uint8_t index);
    void erase(uint8_t index);

    T& operator[](uint8_t index) const;
    void operator=(const TVector &V);
};

template <class T>
TVector<T>::TVector() {
  iSize = 0;
  vector = NULL;
}

template <class T>
TVector<T>::TVector(const TVector &V) {
  vector = new T[V.iSize];
  
  for (int i = 0 ; i < V.iSize ; i++) {
    vector[i] = V[i];
  }

  iSize = V.iSize;
}

template <class T>
TVector<T>::~TVector() {
  delete[] vector;
}

template <class T>
uint8_t TVector<T>::getSize() {
  return iSize;
}

template <class T>
void TVector<T>::pushTop(T t) {
  T *newVector = new T[iSize + 1];

  for(int i = 0 ; i < iSize ; i++) {
    newVector[i] = vector[i];
  }
  newVector[iSize] = t;

  delete[] vector;
  vector = newVector;
  iSize++;
}

template <class T>
void TVector<T>::pushFront(T t) {
  T *newVector = new T[iSize + 1];

  for(int i = 0 ; i < iSize ; i++) {
    newVector[i+1] = vector[i];
  }
  newVector[0] = t;

  delete[] vector;
  vector = newVector;
  iSize++;
}

template <class T>
void TVector<T>::popTop() {
  T *newVector = new T[iSize - 1];

  for (int i = 0 ; i < iSize - 1 ; i++) {
    newVector[i] = vector[i];
  }

  delete[] vector;
  vector = newVector;
  iSize--;
}

template <class T>
void TVector<T>::popFront() {
  T *newVector = new T[iSize - 1];

  for (int i = 0 ; i < iSize - 1 ; i++) {
    newVector[i] = vector[i + 1];
  }

  delete[] vector;
  vector = newVector;
  iSize--;
}

template <class T>
void TVector<T>::set(T t, uint8_t index) {
  vector[index] = t;
}

template <class T>
void TVector<T>::erase(uint8_t index) {
  if ( index >= 0 && index < iSize ) {
    T *newVector = new T[iSize - 1];

    for(int i = 0 ; i < iSize - 1 ; i++) {
      if ( i != index ) {
        if ( i < index ) {
            newVector[i] = vector[i];
        }
        else {
            newVector[i - 1] = vector[i];
        }
      }
    }

  delete[] vector;
  vector = newVector;
  iSize--;

  }
}

template <class T>
T& TVector<T>::operator[](uint8_t index) const {
  return vector[index];
}

template <class T>
void TVector<T>::operator=(const TVector &V) {
  delete vector;
  vector = new T[V.iSize];

  for (int i = 0 ; i < V.iSize ; i++) {
    vector[i] = V[i];
  }

  iSize = V.iSize;
}

#endif