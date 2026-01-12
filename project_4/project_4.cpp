#include "p_4_header.hpp"
#include <algorithm>

// 1. length
std::size_t length(char const *a)
{
    if (a == nullptr)
    {
        return 0;
    }

    std::size_t len{0};

    while (a[len] != '\0')
    {
        ++len;
    }

    return len;
}

// 2. compare
int compare(char const *str1, char const *str2)
{
    if (str1 == nullptr)
    {
        str1 = "";
    }
    if (str2 == nullptr)
    {
        str2 = "";
    }

    int i{0};

    while (true)
    {
        char c1{ str1[i] };
        char c2{ str2[i] };

        if (c1 == '\0' && c2 == '\0')
        {
            return 0;
        }
        if (c1 == '\0' || c1 < c2)
        {
            return -1;
        }
        if (c2 == '\0' || c1 > c2)
        {
            return 1;
        }
        ++i;
    }
}

// 3. assign
void assign(char *str1, char const *str2)
{
    if (str1 == nullptr)
    {
        return;
    }
    if (str2 == nullptr)
    {
        str1[0] = '\0';
        return;
    }

    int i{0};

    while (true)
    {
        str1[i] = str2[i];

        if (str2[i] == '\0')
        {
            break;
        }
        ++i;
    }
}

// 4. distance 
unsigned int distance(char const *str1, char const *str2)
{
    if (str1[0] == '\0')
    {
        return static_cast<unsigned int>(length(str2));
    }

    if (str2[0] == '\0')
    {
        return static_cast<unsigned int>(length(str1));
    }

    if (str1[0] == str2[0])
    {
        return distance(str1 + 1, str2 + 1);
    }

    unsigned int s{ distance(str1 + 1, str2 + 1) };
    unsigned int i{ distance(str1, str2 + 1) };
    unsigned int d{ distance(str1 + 1, str2) };

    unsigned int m{s};

    if (i < m)
    {
        m = i;
    }
    if (d < m)
    {
        m = d;
    }

    return m + 1;
}

// 5. is_sorted
std::size_t is_sorted(char *array[], std::size_t capacity)
{
    for (std::size_t i{0}; i < capacity - 1; i++)
    {
        if (compare(array[i], array[i + 1]) > 0)
        {
            return i + 1;
        }
    }
    return capacity;
}

// 6. insert
void insert(char *array[], std::size_t capacity)
{
    std::size_t index{ capacity - 1 };

    char temp[21];
    assign(temp, array[index]);

    while (index > 0 && compare(array[index - 1], temp) > 0)
    {
        assign(array[index], array[index - 1]);
        --index;
    }

    assign(array[index], temp);
}

// 7. insertion_sort
void insertion_sort(char *array[], std::size_t capacity)
{
    if (capacity <= 1)
    {
        return;
    }

    for (std::size_t i{1}; i < capacity; ++i)
    {
        insert(array, i + 1);
    }
}

// 8. remove_duplicates
std::size_t remove_duplicates(char *array[], std::size_t capacity)
{
    if (capacity == 0)
    {
        return 0;
    }

    std::size_t size{ capacity };
    std::size_t i{0};

    while (i < size - 1)
    {
        if (compare(array[i], array[i + 1]) == 0)
        {
            for (std::size_t j{i + 1}; j < size - 1; ++j)
            {
                assign(array[j], array[j + 1]);
            }
            --size;
        }
        else
        {
            ++i;
        }
    }

    return size;
}

// 9. find
std::size_t find(char *array[], std::size_t capacity, char const *str)
{
    if (capacity == 0)
    {
        return 0;
    }

    for (std::size_t i{0}; i < capacity; ++i)
    {
        if (compare(array[i], str) == 0)
        {
            return i;
        }
    }

    unsigned int min{9999999};
    std::size_t index{0};

    for (std::size_t i{0}; i < capacity; ++i)
    {
        unsigned int d{ distance(array[i], str) };

        if (d < min)
        {
            min = d;
            index = i;
        }
    }

    return index;
}

// 10. free_word_array
void free_word_array(char **word_array)
{
    if (word_array == nullptr)
    {
        return;
    }

    delete[] word_array[0];
    delete[] word_array;
}