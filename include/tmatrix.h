// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw "Vector size should be greater than zero";
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
      this->pMem = v.pMem;
      v.pMem = nullptr;
      this->sz = v.sz;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v)
          return *this;
      delete[] pMem;
      this->sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
      return *this;
      

  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }
      return *this;

  }

  size_t size() const noexcept { 
      return sz; 
  }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if ((ind >= sz) || (ind < 0))
          throw "Index out of range";
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if ((ind >= sz) || (ind < 0))
          throw "Index out of range";
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this->sz != v.sz)
          return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = this->pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = this->pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = this->pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      TDynamicVector<T> res(sz);
      if (sz != v.sz)
          throw "Vectors must be of the same size";
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = this->pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      TDynamicVector<T> res(sz);
      if (sz != v.sz)
          throw "Vectors must be of the same size";
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = this->pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw "not equal";
      }
      T sum = 0;

      for (int i = 0; i < sz; i++)
          sum += this->pMem[i] * v.pMem[i];
      return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }

  //доп метод

  T* get_pMem() {
      return this->pMem;
   }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz == 0 || sz > MAX_MATRIX_SIZE)
          throw "Vector size should be greater than zero";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this->sz != m.sz)
          return false;
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i])
              return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicMatrix<T> res(sz);  
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              res[i][j] = this->pMem[i][j] * val;  
          }
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (this->size != v.sz)
          throw "not equal sizes";
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = 0;
          for (int j = 0; j < sz; j++) {
              res[i] += this->pMem[i][j] * v[j]; 
          }
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw "sizes aren't equal";
      }
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++)
              res.pMem[i][j] = this->pMem[i][j] + m.pMem[i][j];
      }
        
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw "sizes aren't equal";
      }
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++)
              res.pMem[i][j] = this->pMem[i][j] - m.pMem[i][j];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz) {
          throw "multiplication rule not satisfied";
      }
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              res.pMem[i][j] = 0;
              for (int k = 0; k < sz; k++)
                  res.pMem[i][j] += this->pMem[i][k] * m.pMem[k][j];

          }

      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++)
              istr >> v.pMem[i][j];
      }
           
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++)
              ostr << v.pMem[i] << ' ';
      }
         
      return ostr;
  }

  //index
  T& at(size_t ind1, size_t ind2)
  {
      if ((ind1 >= sz) || (ind1 < 0) || (ind2 >= sz) || (ind2 < 0))
          throw "Index out of range";
      return pMem[ind1][ind2];
  }
  const T& at(size_t ind1, size_t ind2) const
  {
      if ((ind1 >= sz) || (ind1 < 0) || (ind2 >= sz) || (ind2 < 0))
          throw "Index out of range";
      return pMem[ind1][ind2];
  }

  //size
  int get_size() {
      return this->sz;
   }
};

#endif
