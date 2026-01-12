#include <iostream>
#include <cassert>

// Function 1: Pattern
void pattern(unsigned int n)
{
    if (n == 0)
    {
        std::cout << "*" << std::endl;
        return;
    }

    int max = 2 * (int)n + 1;

    for (int i{(int)n}; i >= 1; i--)
    {
        int stars = 2 * i + 1;
        int lead = (max - stars) / 2;
        for (int s{0}; s < lead; s++)
        {
            std::cout << ' ';
        }
        for (int s{0}; s < stars; s++)
        {
            std::cout << '*';
        }
        std::cout << std::endl;
    }

    // middle
    for (int s{0}; s < (max - 1) / 2; s++)
    {
        std::cout << ' ';
    }    
    std::cout << '*' << std::endl;

    for (int i{1}; i <= (int)n; i++)
    {
        int stars = 2 * i + 1;
        int lead = (max - stars) / 2;
        for (int s{0}; s < lead; ++s)
        { 
            std::cout << ' ';
        }
        for (int s{0}; s < stars; s++)
        {   
            std::cout << '*';
        }
        std::cout << std::endl;
    }
}

// Function 2: log10
unsigned int log10(unsigned int n) 
{
    assert(n != 0);
    unsigned int m = 0;
    while (n >= 10) 
    {
        n /= 10;
        ++m;
    }
    return m;
}

// Function 3: count bit occurrences
unsigned int count(unsigned int n, unsigned int bit) 
{
    // Ensure bit is either 0 or 1
    assert(bit == 0 || bit == 1);

    unsigned int cnt = 0;

    for (unsigned int i = 0; i < 32; ++i) 
    {
        // Check if the i-th bit matches the target bit
        if (((n >> i) & 1) == bit) 
        {
            ++cnt;
        }
    }

    return cnt;
}

// Function 4: swap_bytes
unsigned int swap_bytes(unsigned int n, unsigned int b0, unsigned int b1) 
{
    assert((b0 >= 0 && b0 <= 3) && (b1 >= 0 && b1 <= 3));

    unsigned int temp = 8u * b0;
    unsigned int byte0 = (n >> temp) & 0xFFu;
    
    temp = 8u * b1;
    unsigned int byte1 = (n >> temp) & 0xFFu;

    unsigned int temp0 = 8u * b0;
    unsigned int temp1 = 8u * b1;
    
    unsigned int mask = (0xFFu << temp0) | (0xFFu << temp1);
    mask = ~mask;

    unsigned int ret = n & mask;
    ret = ret | (byte0 << (8u * b1)) | (byte1 << (8u * b0));

    return ret;

}

// Main driver
int main()
{
   std::cout << "n = 1:" << std::endl;
   pattern(1);
   for ( unsigned int n{ 2 }; n <= 5; ++n)
   {


       std::cout << std::endl;
       std::cout << "n = " << n << ":" << std::endl;
       pattern( n );
   }
   // log10 test
   std::cout << "log10(1) = " << log10(1) << std::endl;
   std::cout << "log10(1234) = " << log10(1234) << std::endl;


   // count test
   std::cout << "count(13, 1) = " << count(13, 1) << std::endl;
   std::cout << "count(13, 0) = " << count(13, 0) << std::endl;


   // swap_bytes test
   unsigned int val = 0x12345678;
   unsigned int swapped = swap_bytes(val, 0, 3);
   std::cout << std::hex;
   std::cout << "Original: 0x" << val << std::endl;
   std::cout << "Swapped : 0x" << swapped << std::endl;


   return 0;
}