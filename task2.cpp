#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <string.h>

namespace numbers {
/*
    class complex {
        double re_member;
        double im_member;
    public:
        complex(double a = 0, double b = 0) : re_member(a), im_member(b) {}

        explicit complex (const std::string& s) {
            std::stringstream str(s);
            str.ignore(1);
            str >> re_member;
            str.ignore(1);
            str >> im_member;
        }

        std::string to_string() const{
            std::stringstream str;
            str << "(" << std::setprecision(10) << re_member;
            str << ","  << std::setprecision(10) << im_member << ")";
            return str.str();
        }
        double re () const{
            return re_member;
        }

        double im () const{
            return im_member;
        }

        double abs () const{
            return sqrt(re_member * re_member + im_member * im_member);
        }

        double abs2 () const{
            return re_member * re_member + im_member * im_member;
        }

        complex& operator+= (const complex& a) {
            this->re_member += a.re_member;
            this->im_member += a.im_member;
            return *this;
        }

        complex& operator-= (const complex& a) {
            this->re_member -= a.re_member;
            this->im_member -= a.im_member;
            return *this;
        }

        complex& operator*= (const complex& a) {
            double tmp_re = re_member, tmp_im = im_member;
            this->re_member = tmp_re * a.re_member - tmp_im * a.im_member;
            this->im_member = tmp_re * a.im_member + tmp_im * a.re_member;
            return *this;
        }

        complex& operator/= (const complex& a) {
            long double im_part = a.re_member * a.re_member + a.im_member * a.im_member;
            double tmp_re = re_member, tmp_im = im_member;
            this->re_member = (tmp_re * a.re_member + tmp_im * a.im_member) / im_part;
            this->im_member = (tmp_im * a.re_member - tmp_re * a.im_member) / im_part;
            return *this;
        }

        complex operator~ (void) const{
            return {re_member, -im_member};
        }
        complex operator-(void) const {
            return complex(-re_member, -im_member);
        }

        friend complex operator+(complex z1, complex z2);
        friend complex operator-(complex z1, complex z2);
        friend complex operator*(complex z1, complex z2);
        friend complex operator/(complex z1, complex z2);
    };
    complex operator+ (complex z1, complex z2) {
        return (z1 += z2);
    }
    complex operator- (complex z1, complex z2) {
        return (z1 -= z2);
    }
    complex operator* (complex z1, complex z2) {
        return (z1 *= z2);
    }
    complex operator/ (complex z1, complex z2) {
        return (z1 /= z2);
    }
*/
    class complex_stack {
    public:
        complex_stack() : capacity(2), size_(0), mas(NULL) {
            mas = static_cast<complex*> (::operator new (capacity * sizeof(complex)));
        }

        ~complex_stack() {
            ::operator delete(mas);
        }

        complex_stack (const complex_stack& a, const size_t & delta = 0) : capacity(a.capacity), 
        size_(a.size_ - delta) {
            mas = static_cast<complex*> (::operator new (capacity * sizeof(complex)));
            memcpy(mas, a.mas, (size_ - delta) * sizeof(complex));
        }

        size_t size() const {
            return size_;
        }

        complex operator[] (size_t index) const {
            return mas[index];
        }

        complex_stack operator~() const {
            return complex_stack(*this, 1);
        }

        complex operator+() const {
            return mas[size_ - 1];
        }


        void operator=(const complex_stack& a) {
            if (&a == this) {
                return;
            }
            ::operator delete(mas);
            mas = static_cast<complex*> (::operator new(a.capacity * sizeof(complex)));
            capacity = a.capacity;
            size_ = a.size_;
            for (size_t i = 0; i < size_; ++i) {
                new (mas + i) complex(a[i]);
            }
            }

            complex_stack operator<<(const complex& a) const {
            complex_stack res = *this;
            if (res.size_ == res.capacity) {
                res.capacity *= 2;
                complex * mas_ = static_cast<complex*> (::operator new (res.capacity * sizeof(complex)));
                memcpy(mas_, mas, size_ * sizeof(complex));
                ::operator delete(res.mas);
                res.mas = mas_;
            }
            new(res.mas + res.size_) complex(a);
            res.size_++;
            return res;
            }

    private:
        size_t capacity;
        size_t size_;
        complex* mas;
    };

}