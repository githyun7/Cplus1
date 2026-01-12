#include <iostream>
#include <cassert>

double *geometric( double a, double ratio, std::size_t cap);
double *cross_correlation(double array0[], std::size_t cap0, double array1[], std::size_t cap1);
std::size_t shift_duplicates( int array[], std::size_t capacity);
void deallocate( double *&ptr, bool is_array, std::size_t capacity = 0);

double *geometric( double a, double ratio, std::size_t cap)
{
    double *array{new double[cap]};
    for(std::size_t i{0}; i < cap; ++i)
    {
        array[i] = a;
        for(std::size_t j{0}; j < i; ++j)
        {
            array[i] *= ratio;
        }
    }

    return array;
}

double *cross_correlation(double array0[], std::size_t cap0, double array1[], std::size_t cap1)
{
    assert(cap0 + cap1 >= 1);
  
    double *new_arr = new double[cap0 + cap1 - 1];
    for (std::size_t k = 0; k < cap0 + cap1 - 1; ++k)
    {
        new_arr[k] = 0.0;
    }

    for (std::size_t i = 0; i < cap0; ++i)
    {
        for (std::size_t j = 0; j < cap1; ++j)
        {
            new_arr[i + j] += array0[i]*array1[j];
        }
    }
    return new_arr;
}

std::size_t shift_duplicates(int array[], std::size_t capacity)
{
    if (capacity == 0) 
    {
        return 0;
    }

    std::size_t unique{0};

    for (std::size_t i = 0; i < capacity; ++i)
    {
        bool is_duplicate = false;
        for (std::size_t j = 0; j < unique; ++j)
        {
            if (array[i] == array[j])
            {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate)
        {
            std::swap(array[unique], array[i]);
            ++unique;
        }
    }
    return unique; 
}


void deallocate(double *&ptr, bool is_array, std::size_t capacity)
{
    if (ptr == nullptr) 
    {
        return; 
    }

    if(is_array)
    {
        if(capacity > 0)
        {
            for(std::size_t i{0}; i < capacity; ++i)
            {
                ptr[i] = 0.0;
            }
            delete[] ptr;
        }
    }
    else
    {
        *ptr = 0.0;
        delete ptr;
    }
    ptr = nullptr;
}
