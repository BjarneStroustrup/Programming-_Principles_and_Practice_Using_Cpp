
/*
    warning: this small multidimensional matrix library uses a few features
    not taught in ENGR112 and not explained in elementary textbooks

    (c) Bjarne Stroustrup, Texas A&M University. 

    Use as you like as long as you acknowledge the source.
*/

#ifndef MATRIX_LIB
#define MATRIX_LIB

#include<string>
#include<algorithm>
//#include<iostream>

namespace Numeric_lib {

//-----------------------------------------------------------------------------

struct Matrix_error {
    std::string name;
    Matrix_error(const char* q) :name(q) { }
    Matrix_error(std::string n) :name(n) { }
};

//-----------------------------------------------------------------------------

inline void error(const char* p)
{
    throw Matrix_error(p);
}

//-----------------------------------------------------------------------------

typedef long Index;    // I still dislike unsigned

//-----------------------------------------------------------------------------

// The general Matrix template is simply a prop for its specializations:
template<class T = double, int D = 1> class Matrix {
    // multidimensional matrix class
    // ( ) does multidimensional subscripting
    // [ ] does C style "slicing": gives an N-1 dimensional matrix from an N dimensional one
    // row() is equivalent to [ ]
    // column() is not (yet) implemented because it requires strides.
    // = has copy semantics
    // ( ) and [ ] are range checked
    // slice() to give sub-ranges 
private:
    Matrix();    // this should never be compiled
//	template<class A> Matrix(A);
};

//-----------------------------------------------------------------------------

template<class T = double, int D = 1> class Row ;    // forward declaration

//-----------------------------------------------------------------------------

// function objects for various apply() operations:

template<class T> struct Assign {
    void operator()(T& a, const T& c) { a = c; }
};

template<class T> struct Add_assign {
    void operator()(T& a, const T& c) { a += c; }
};
template<class T> struct Mul_assign {
    void operator()(T& a, const T& c) { a *= c; }
};
template<class T> struct Minus_assign {
    void operator()(T& a, const T& c) { a -= c; }
};
template<class T> struct Div_assign {
    void operator()(T& a, const T& c) { a /= c; }
};
template<class T> struct Mod_assign {
    void operator()(T& a, const T& c) { a %= c; }
};
template<class T> struct Or_assign {
    void operator()(T& a, const T& c) { a |= c; }
};
template<class T> struct Xor_assign {
    void operator()(T& a, const T& c) { a ^= c; }
};
template<class T> struct And_assign {
    void operator()(T& a, const T& c) { a &= c; }
};

template<class T> struct Not_assign {
    void operator()(T& a) { a = !a; }
};

template<class T> struct Not {
    T operator()(T& a) { return !a; }
};

template<class T> struct Unary_minus {
    T operator()(T& a) { return -a; }
};

template<class T> struct Complement {
    T operator()(T& a) { return ~a; }
};

//-----------------------------------------------------------------------------

// Matrix_base represents the common part of the Matrix classes:
template<class T> class Matrix_base {
    // matrixs store their memory (elements) in Matrix_base and have copy semantics
    // Matrix_base does element-wise operations
protected:
    T* elem;    // vector? no: we couldn't easily provide a vector for a slice
    const Index sz;    
    mutable bool owns;
    mutable bool xfer;
public:
    Matrix_base(Index n) :elem(new T[n]()), sz(n), owns(true), xfer(false)
        // matrix of n elements (default initialized)
    {
        // std::cerr << "new[" << n << "]->" << elem << "\n";
    }

    Matrix_base(Index n, T* p) :elem(p), sz(n), owns(false), xfer(false)
        // descriptor for matrix of n elements owned by someone else
    {
    }

    ~Matrix_base()
    {
        if (owns) {
            // std::cerr << "delete[" << sz << "] " << elem << "\n";
            delete[]elem;
        }
    }

    // if necessay, we can get to the raw matrix:
          T* data()       { return elem; }
    const T* data() const { return elem; }
    Index    size() const { return sz; }

    void copy_elements(const Matrix_base& a)
    {
        if (sz!=a.sz) error("copy_elements()");
        for (Index i=0; i<sz; ++i) elem[i] = a.elem[i];
    }

    void base_assign(const Matrix_base& a) { copy_elements(a); }

    void base_copy(const Matrix_base& a)
    {
        if (a.xfer) {          // a is just about to be deleted
                               // so we can transfer ownership rather than copy
            // std::cerr << "xfer @" << a.elem << " [" << a.sz << "]\n";
            elem = a.elem;
            a.xfer = false;    // note: modifies source
            a.owns = false;
        }
        else {
            elem = new T[a.sz];
            // std::cerr << "base copy @" << a.elem << " [" << a.sz << "]\n";
            copy_elements(a);
        }
        owns = true;
        xfer = false;
    }

    // to get the elements of a local matrix out of a function without copying:
    void base_xfer(Matrix_base& x)
    {
        if (owns==false) error("cannot xfer() non-owner");
        owns = false;     // now the elements are safe from deletion by original owner
        x.xfer = true;    // target asserts temporary ownership
        x.owns = true;
    }

    template<class F> void base_apply(F f) { for (Index i = 0; i<size(); ++i) f(elem[i]); }
    template<class F> void base_apply(F f, const T& c) { for (Index i = 0; i<size(); ++i) f(elem[i],c); }
private:
    void operator=(const Matrix_base&);    // no ordinary copy of bases
    Matrix_base(const Matrix_base&);
};

//-----------------------------------------------------------------------------

template<class T> class Matrix<T,1> : public Matrix_base<T> {
    const Index d1;

protected:
    // for use by Row:
    Matrix(Index n1, T* p) : Matrix_base<T>(n1,p), d1(n1)
    {
        // std::cerr << "construct 1D Matrix from data\n";
    }

public:

    Matrix(Index n1) : Matrix_base<T>(n1), d1(n1) { }

    Matrix(Row<T,1>& a) : Matrix_base<T>(a.dim1(),a.p), d1(a.dim1()) 
    { 
        // std::cerr << "construct 1D Matrix from Row\n";
    }

    // copy constructor: let the base do the copy:
    Matrix(const Matrix& a) : Matrix_base<T>(a.size(),0), d1(a.d1)
    {
        // std::cerr << "copy ctor\n";
        this->base_copy(a);
    }

    template<int n> 
    Matrix(const T (&a)[n]) : Matrix_base<T>(n), d1(n)
        // deduce "n" (and "T"), Matrix_base allocates T[n]
    {
        // std::cerr << "matrix ctor\n";
        for (Index i = 0; i<n; ++i) this->elem[i]=a[i];
    }

    Matrix(const T* p, Index n) : Matrix_base<T>(n), d1(n)
        // Matrix_base allocates T[n]
    {
        // std::cerr << "matrix ctor\n";
        for (Index i = 0; i<n; ++i) this->elem[i]=p[i];
    }

    template<class F> Matrix(const Matrix& a, F f) : Matrix_base<T>(a.size()), d1(a.d1)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&) would be a typical type for f
    {
        for (Index i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i]); 
    }

    template<class F, class Arg> Matrix(const Matrix& a, F f, const Arg& t1) : Matrix_base<T>(a.size()), d1(a.d1)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&, const Arg&) would be a typical type for f
    {
        for (Index i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i],t1); 
    }

    Matrix& operator=(const Matrix& a)
        // copy assignment: let the base do the copy
    {
        // std::cerr << "copy assignment (" << this->size() << ',' << a.size()<< ")\n";
        if (d1!=a.d1) error("length error in 1D=");
        this->base_assign(a);
        return *this;
    }

    ~Matrix() { }

    Index dim1() const { return d1; }    // number of elements in a row

    Matrix xfer()    // make an Matrix to move elements out of a scope
    {
        Matrix x(dim1(),this->data()); // make a descriptor
        this->base_xfer(x);                  // transfer (temporary) ownership to x
        return x;
    }

    void range_check(Index n1) const
    {
        // std::cerr << "range check: (" << d1 << "): " << n1 << "\n"; 
        if (n1<0 || d1<=n1) error("1D range error: dimension 1");
    }

    // subscripting:
          T& operator()(Index n1)       { range_check(n1); return this->elem[n1]; }
    const T& operator()(Index n1) const { range_check(n1); return this->elem[n1]; }

    // slicing (the same as subscripting for 1D matrixs):
          T& operator[](Index n)       { return row(n); }
    const T& operator[](Index n) const { return row(n); }

          T& row(Index n)       { range_check(n); return this->elem[n]; }
    const T& row(Index n) const { range_check(n); return this->elem[n]; }

    Row<T,1> slice(Index n)
        // the last elements from a[n] onwards
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;// one beyond the end
        return Row<T,1>(d1-n,this->elem+n);
    }

    const Row<T,1> slice(Index n) const
        // the last elements from a[n] onwards
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;// one beyond the end
        return Row<T,1>(d1-n,this->elem+n);
    }

    Row<T,1> slice(Index n, Index m)
        // m elements starting with a[n]
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        if (m<0) m = 0;
        else if (d1<n+m) m=d1-n;
        return Row<T,1>(m,this->elem+n);
    }

    const Row<T,1> slice(Index n, Index m) const
        // m elements starting with a[n]
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        if (m<0) m = 0;
        else if (d1<n+m) m=d1-n;
        return Row<T,1>(m,this->elem+n);
    }

    // element-wise operations:
    template<class F> Matrix& apply(F f) { this->base_apply(f); return *this; }
    template<class F> Matrix& apply(F f,const T& c) { this->base_apply(f,c); return *this; }

    Matrix& operator=(const T& c)  { this->base_apply(Assign<T>(),c);       return *this; }

    Matrix& operator*=(const T& c) { this->base_apply(Mul_assign<T>(),c);   return *this; }
    Matrix& operator/=(const T& c) { this->base_apply(Div_assign<T>(),c);   return *this; }
    Matrix& operator%=(const T& c) { this->base_apply(Mod_assign<T>(),c);   return *this; }
    Matrix& operator+=(const T& c) { this->base_apply(Add_assign<T>(),c);   return *this; }
    Matrix& operator-=(const T& c) { this->base_apply(Minus_assign<T>(),c); return *this; }

    Matrix& operator&=(const T& c) { this->base_apply(And_assign<T>(),c);   return *this; }
    Matrix& operator|=(const T& c) { this->base_apply(Or_assign<T>(),c);    return *this; }
    Matrix& operator^=(const T& c) { this->base_apply(Xor_assign<T>(),c);   return *this; }

    Matrix operator!() { return xfer(Matrix(*this,Not<T>())); }
    Matrix operator-() { return xfer(Matrix(*this,Unary_minus<T>())); }
    Matrix operator~() { return xfer(Matrix(*this,Complement<T>()));  }

    template<class F> Matrix apply_new(F f) { return xfer(Matrix(*this,f)); }
    
    void swap_rows(Index i, Index j)
        // swap_rows() uses a row's worth of memory for better run-time performance
        // if you want pairwise swap, just write it yourself
    {
        if (i == j) return;
    /*
        Matrix<T,1> temp = (*this)[i];
        (*this)[i] = (*this)[j];
        (*this)[j] = temp;
    */
        Index max = (*this)[i].size();
        for (Index ii=0; ii<max; ++ii) std::swap((*this)(i,ii),(*this)(j,ii));
    }
};

//-----------------------------------------------------------------------------

template<class T> class Matrix<T,2> : public Matrix_base<T> {
    const Index d1;
    const Index d2;

protected:
    // for use by Row:
    Matrix(Index n1, Index n2, T* p) : Matrix_base<T>(n1*n2,p), d1(n1), d2(n2) 
    {
       //  std::cerr << "construct 3D Matrix from data\n";
    }

public:

    Matrix(Index n1, Index n2) : Matrix_base<T>(n1*n2), d1(n1), d2(n2) { }

    Matrix(Row<T,2>& a) : Matrix_base<T>(a.dim1()*a.dim2(),a.p), d1(a.dim1()), d2(a.dim2())
    { 
       // std::cerr << "construct 2D Matrix from Row\n";
    }

    // copy constructor: let the base do the copy:
    Matrix(const Matrix& a) : Matrix_base<T>(a.size(),0), d1(a.d1), d2(a.d2)
    {
        // std::cerr << "copy ctor\n";
        this->base_copy(a);
    }

    template<int n1, int n2> 
    Matrix(const T (&a)[n1][n2]) : Matrix_base<T>(n1*n2), d1(n1), d2(n2)
        // deduce "n1", "n2" (and "T"), Matrix_base allocates T[n1*n2]
    {
        // std::cerr << "matrix ctor (" << n1 << "," << n2 << ")\n";
        for (Index i = 0; i<n1; ++i)
            for (Index j = 0; j<n2; ++j) this->elem[i*n2+j]=a[i][j];
    }

    template<class F> Matrix(const Matrix& a, F f) : Matrix_base<T>(a.size()), d1(a.d1), d2(a.d2)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&) would be a typical type for f
    {
        for (Index i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i]); 
    }

    template<class F, class Arg> Matrix(const Matrix& a, F f, const Arg& t1) : Matrix_base<T>(a.size()), d1(a.d1), d2(a.d2)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&, const Arg&) would be a typical type for f
    {
        for (Index i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i],t1); 
    }

    Matrix& operator=(const Matrix& a)
        // copy assignment: let the base do the copy
    {
        // std::cerr << "copy assignment (" << this->size() << ',' << a.size()<< ")\n";
        if (d1!=a.d1 || d2!=a.d2) error("length error in 2D =");
        this->base_assign(a);
        return *this;
    }

    ~Matrix() { }
    
    Index dim1() const { return d1; }    // number of elements in a row
    Index dim2() const { return d2; }    // number of elements in a column

    Matrix xfer()    // make an Matrix to move elements out of a scope
    {
        Matrix x(dim1(),dim2(),this->data()); // make a descriptor
        this->base_xfer(x);            // transfer (temporary) ownership to x
        return x;
    }

    void range_check(Index n1, Index n2) const
    {
        // std::cerr << "range check: (" << d1 << "," << d2 << "): " << n1 << " " << n2 << "\n";
        if (n1<0 || d1<=n1) error("2D range error: dimension 1");
        if (n2<0 || d2<=n2) error("2D range error: dimension 2");
    }

    // subscripting:
          T& operator()(Index n1, Index n2)       { range_check(n1,n2); return this->elem[n1*d2+n2]; }
    const T& operator()(Index n1, Index n2) const { range_check(n1,n2); return this->elem[n1*d2+n2]; }

    // slicing (return a row):
          Row<T,1> operator[](Index n)       { return row(n); }
    const Row<T,1> operator[](Index n) const { return row(n); }

          Row<T,1> row(Index n)       { range_check(n,0); return Row<T,1>(d2,&this->elem[n*d2]); }
    const Row<T,1> row(Index n) const { range_check(n,0); return Row<T,1>(d2,&this->elem[n*d2]); }

    Row<T,2> slice(Index n)
        // rows [n:d1)
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        return Row<T,2>(d1-n,d2,this->elem+n*d2);
    }

    const Row<T,2> slice(Index n) const
        // rows [n:d1)
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        return Row<T,2>(d1-n,d2,this->elem+n*d2);
    }

    Row<T,2> slice(Index n, Index m)
        // the rows [n:m)
    {
        if (n<0) n=0;
        if(d1<m) m=d1;    // one beyond the end
        return Row<T,2>(m-n,d2,this->elem+n*d2);

    }

    const Row<T,2> slice(Index n, Index m) const
        // the rows [n:sz)
    {
        if (n<0) n=0;
        if(d1<m) m=d1;    // one beyond the end
        return Row<T,2>(m-n,d2,this->elem+n*d2);
    }

    // Column<T,1> column(Index n); // not (yet) implemented: requies strides and operations on columns

    // element-wise operations:
    template<class F> Matrix& apply(F f)            { this->base_apply(f);   return *this; }
    template<class F> Matrix& apply(F f,const T& c) { this->base_apply(f,c); return *this; }

    Matrix& operator=(const T& c)  { this->base_apply(Assign<T>(),c);       return *this; }

    Matrix& operator*=(const T& c) { this->base_apply(Mul_assign<T>(),c);   return *this; }
    Matrix& operator/=(const T& c) { this->base_apply(Div_assign<T>(),c);   return *this; }
    Matrix& operator%=(const T& c) { this->base_apply(Mod_assign<T>(),c);   return *this; }
    Matrix& operator+=(const T& c) { this->base_apply(Add_assign<T>(),c);   return *this; }
    Matrix& operator-=(const T& c) { this->base_apply(Minus_assign<T>(),c); return *this; }

    Matrix& operator&=(const T& c) { this->base_apply(And_assign<T>(),c);   return *this; }
    Matrix& operator|=(const T& c) { this->base_apply(Or_assign<T>(),c);    return *this; }
    Matrix& operator^=(const T& c) { this->base_apply(Xor_assign<T>(),c);   return *this; }

    Matrix operator!() { return xfer(Matrix(*this,Not<T>())); }
    Matrix operator-() { return xfer(Matrix(*this,Unary_minus<T>())); }
    Matrix operator~() { return xfer(Matrix(*this,Complement<T>()));  }

    template<class F> Matrix apply_new(F f) { return xfer(Matrix(*this,f)); }
    
    void swap_rows(Index i, Index j)
        // swap_rows() uses a row's worth of memory for better run-time performance
        // if you want pairwise swap, just write it yourself
    {
        if (i == j) return;
    /*
        Matrix<T,1> temp = (*this)[i];
        (*this)[i] = (*this)[j];
        (*this)[j] = temp;
    */
        Index max = (*this)[i].size();
        for (Index ii=0; ii<max; ++ii) std::swap((*this)(i,ii),(*this)(j,ii));
    }
};

//-----------------------------------------------------------------------------

template<class T> class Matrix<T,3> : public Matrix_base<T> {
    const Index d1;
    const Index d2;
    const Index d3;

protected:
    // for use by Row:
    Matrix(Index n1, Index n2, Index n3, T* p) : Matrix_base<T>(n1*n2*n3,p), d1(n1), d2(n2), d3(n3) 
    {
        // std::cerr << "construct 3D Matrix from data\n";
    }

public:

    Matrix(Index n1, Index n2, Index n3) : Matrix_base<T>(n1*n2*n3), d1(n1), d2(n2), d3(n3) { }

    Matrix(Row<T,3>& a) : Matrix_base<T>(a.dim1()*a.dim2()*a.dim3(),a.p), d1(a.dim1()), d2(a.dim2()), d3(a.dim3())
    { 
        // std::cerr << "construct 3D Matrix from Row\n";
    }

    // copy constructor: let the base do the copy:
    Matrix(const Matrix& a) : Matrix_base<T>(a.size(),0), d1(a.d1), d2(a.d2), d3(a.d3)
    {
        // std::cerr << "copy ctor\n";
        this->base_copy(a);
    }

    template<int n1, int n2, int n3> 
    Matrix(const T (&a)[n1][n2][n3]) : Matrix_base<T>(n1*n2), d1(n1), d2(n2), d3(n3)
        // deduce "n1", "n2", "n3" (and "T"), Matrix_base allocates T[n1*n2*n3]
    {
        // std::cerr << "matrix ctor\n";
        for (Index i = 0; i<n1; ++i)
            for (Index j = 0; j<n2; ++j)
                for (Index k = 0; k<n3; ++k)
                    this->elem[i*n2*n3+j*n3+k]=a[i][j][k];
    }

    template<class F> Matrix(const Matrix& a, F f) : Matrix_base<T>(a.size()), d1(a.d1), d2(a.d2), d3(a.d3)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&) would be a typical type for f
    {
        for (Index i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i]); 
    }

    template<class F, class Arg> Matrix(const Matrix& a, F f, const Arg& t1) : Matrix_base<T>(a.size()), d1(a.d1), d2(a.d2), d3(a.d3)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&, const Arg&) would be a typical type for f
    {
        for (Index i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i],t1); 
    }

    Matrix& operator=(const Matrix& a)
        // copy assignment: let the base do the copy
    {
        // std::cerr << "copy assignment (" << this->size() << ',' << a.size()<< ")\n";
        if (d1!=a.d1 || d2!=a.d2 || d3!=a.d3) error("length error in 2D =");
        this->base_assign(a);
        return *this;
    }

    ~Matrix() { }

    Index dim1() const { return d1; }    // number of elements in a row
    Index dim2() const { return d2; }    // number of elements in a column
    Index dim3() const { return d3; }    // number of elements in a depth

    Matrix xfer()    // make an Matrix to move elements out of a scope
    {
        Matrix x(dim1(),dim2(),dim3(),this->data()); // make a descriptor
        this->base_xfer(x);            // transfer (temporary) ownership to x
        return x;
    }

    void range_check(Index n1, Index n2, Index n3) const
    {
        // std::cerr << "range check: (" << d1 << "," << d2 << "): " << n1 << " " << n2 << "\n";
        if (n1<0 || d1<=n1) error("3D range error: dimension 1");
        if (n2<0 || d2<=n2) error("3D range error: dimension 2");
        if (n3<0 || d3<=n3) error("3D range error: dimension 3");
    }

    // subscripting:
          T& operator()(Index n1, Index n2, Index n3)       { range_check(n1,n2,n3); return this->elem[d2*d3*n1+d3*n2+n3]; }; 
    const T& operator()(Index n1, Index n2, Index n3) const { range_check(n1,n2,n3); return this->elem[d2*d3*n1+d3*n2+n3]; };

    // slicing (return a row):
          Row<T,2> operator[](Index n)       { return row(n); }
    const Row<T,2> operator[](Index n) const { return row(n); }

          Row<T,2> row(Index n)       { range_check(n,0,0); return Row<T,2>(d2,d3,&this->elem[n*d2*d3]); }
    const Row<T,2> row(Index n) const { range_check(n,0,0); return Row<T,2>(d2,d3,&this->elem[n*d2*d3]); }

    Row<T,3> slice(Index n)
        // rows [n:d1)
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        return Row<T,3>(d1-n,d2,d3,this->elem+n*d2*d3);
    }

    const Row<T,3> slice(Index n) const
        // rows [n:d1)
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        return Row<T,3>(d1-n,d2,d3,this->elem+n*d2*d3);
    }

    Row<T,3> slice(Index n, Index m)
        // the rows [n:m)
    {
        if (n<0) n=0;
        if(d1<m) m=d1;    // one beyond the end
        return Row<T,3>(m-n,d2,d3,this->elem+n*d2*d3);

    }

    const Row<T,3> slice(Index n, Index m) const
        // the rows [n:sz)
    {
        if (n<0) n=0;
        if(d1<m) m=d1;    // one beyond the end
        return Row<T,3>(m-n,d2,d3,this->elem+n*d2*d3);
    }

    // Column<T,2> column(Index n); // not (yet) implemented: requies strides and operations on columns

    // element-wise operations:
    template<class F> Matrix& apply(F f)            { this->base_apply(f);   return *this; }
    template<class F> Matrix& apply(F f,const T& c) { this->base_apply(f,c); return *this; }

    Matrix& operator=(const T& c)  { this->base_apply(Assign<T>(),c);       return *this; }
                                                                            
    Matrix& operator*=(const T& c) { this->base_apply(Mul_assign<T>(),c);   return *this; }
    Matrix& operator/=(const T& c) { this->base_apply(Div_assign<T>(),c);   return *this; }
    Matrix& operator%=(const T& c) { this->base_apply(Mod_assign<T>(),c);   return *this; }
    Matrix& operator+=(const T& c) { this->base_apply(Add_assign<T>(),c);   return *this; }
    Matrix& operator-=(const T& c) { this->base_apply(Minus_assign<T>(),c); return *this; }

    Matrix& operator&=(const T& c) { this->base_apply(And_assign<T>(),c);   return *this; }
    Matrix& operator|=(const T& c) { this->base_apply(Or_assign<T>(),c);    return *this; }
    Matrix& operator^=(const T& c) { this->base_apply(Xor_assign<T>(),c);   return *this; }

    Matrix operator!() { return xfer(Matrix(*this,Not<T>())); }
    Matrix operator-() { return xfer(Matrix(*this,Unary_minus<T>())); }
    Matrix operator~() { return xfer(Matrix(*this,Complement<T>()));  }

    template<class F> Matrix apply_new(F f) { return xfer(Matrix(*this,f)); }
    
    void swap_rows(Index i, Index j)
        // swap_rows() uses a row's worth of memory for better run-time performance
        // if you want pairwise swap, just write it yourself
    {
        if (i == j) return;
        
        Matrix<T,2> temp = (*this)[i];
        (*this)[i] = (*this)[j];
        (*this)[j] = temp;
    }
};

//-----------------------------------------------------------------------------

template<class T> Matrix<T> scale_and_add(const Matrix<T>& a, T c, const Matrix<T>& b)
    //  Fortran "saxpy()" ("fma" for "fused multiply-add").
    // will the copy constructor be called twice and defeat the xfer optimization?
{
    if (a.size() != b.size()) error("sizes wrong for scale_and_add()");
    Matrix<T> res(a.size());
    for (Index i = 0; i<a.size(); ++i) res[i] += a[i]*c+b[i];
    return res.xfer();
}

//-----------------------------------------------------------------------------

template<class T> T dot_product(const Matrix<T>&a , const Matrix<T>& b)
{
    if (a.size() != b.size()) error("sizes wrong for dot product");
    T sum = 0;
    for (Index i = 0; i<a.size(); ++i) sum += a[i]*b[i];
    return sum;
}

//-----------------------------------------------------------------------------

template<class T, int N> Matrix<T,N> xfer(Matrix<T,N>& a)
{
    return a.xfer();
}

//-----------------------------------------------------------------------------

template<class F, class A>            A apply(F f, A x)        { A res(x,f);   return xfer(res); }
template<class F, class Arg, class A> A apply(F f, A x, Arg a) { A res(x,f,a); return xfer(res); }

//-----------------------------------------------------------------------------

// The default values for T and D have been declared before.
template<class T, int D> class Row {
    // general version exists only to allow specializations
private:
        Row();
};

//-----------------------------------------------------------------------------

template<class T> class Row<T,1> : public Matrix<T,1> {
public:
    Row(Index n, T* p) : Matrix<T,1>(n,p)
    {
    }

    Matrix<T,1>& operator=(const T& c) { this->base_apply(Assign<T>(),c); return *this; }

    Matrix<T,1>& operator=(const Matrix<T,1>& a)
    {
        return *static_cast<Matrix<T,1>*>(this)=a;
    }
};

//-----------------------------------------------------------------------------

template<class T> class Row<T,2> : public Matrix<T,2> {
public:
    Row(Index n1, Index n2, T* p) : Matrix<T,2>(n1,n2,p)
    {
    }
        
    Matrix<T,2>& operator=(const T& c) { this->base_apply(Assign<T>(),c); return *this; }

    Matrix<T,2>& operator=(const Matrix<T,2>& a)
    {
        return *static_cast<Matrix<T,2>*>(this)=a;
    }
};

//-----------------------------------------------------------------------------

template<class T> class Row<T,3> : public Matrix<T,3> {
public:
    Row(Index n1, Index n2, Index n3, T* p) : Matrix<T,3>(n1,n2,n3,p)
    {
    }

    Matrix<T,3>& operator=(const T& c) { this->base_apply(Assign<T>(),c); return *this; }

    Matrix<T,3>& operator=(const Matrix<T,3>& a)
    {
        return *static_cast<Matrix<T,3>*>(this)=a;
    }
};

//-----------------------------------------------------------------------------

template<class T, int N> Matrix<T,N-1> scale_and_add(const Matrix<T,N>& a, const Matrix<T,N-1> c, const Matrix<T,N-1>& b)
{
    Matrix<T> res(a.size());
    if (a.size() != b.size()) error("sizes wrong for scale_and_add");
    for (Index i = 0; i<a.size(); ++i) res[i] += a[i]*c+b[i];
    return res.xfer();
}

//-----------------------------------------------------------------------------

template<class T, int D> Matrix<T,D> operator*(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r*=c; }
template<class T, int D> Matrix<T,D> operator/(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r/=c; }
template<class T, int D> Matrix<T,D> operator%(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r%=c; }
template<class T, int D> Matrix<T,D> operator+(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r+=c; }
template<class T, int D> Matrix<T,D> operator-(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r-=c; }

template<class T, int D> Matrix<T,D> operator&(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r&=c; }
template<class T, int D> Matrix<T,D> operator|(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r|=c; }
template<class T, int D> Matrix<T,D> operator^(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r^=c; }

//-----------------------------------------------------------------------------

}
#endif
