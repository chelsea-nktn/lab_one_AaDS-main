#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#define MASS_SIZE 100000
#define MAX_PRIME 10000
#define FILE_NAME "data_board.txt"
#define EXIT_NAME "exit_file.txt"
using namespace std;

typedef unsigned long int unint;

unsigned long int get_max_or_min(int setting, unint a, unint b)
{
    if (setting == 0)
    {
        if (a >= b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }
    if (setting == 1)
    {
        if (a <= b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }
}
unsigned long int get_square(unint x)
{
    unsigned long int counter = x;
    unsigned long int square = 0;
    while(counter > 0)
    {
        square += x;
        counter -= 1;
    }
    return square;
}

unsigned long int* sieve_eratosphenes(int n, unsigned long int& primes_count)
{
    int i, j;
    unint index = 0;
    primes_count = 0;
    if (n < 2)
    {
        return new unsigned long int[0];
    }
    bool isPrime[MASS_SIZE];
    for (i = 0; i<=n; i++)
    {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;
    for (i = 2; get_square(i) <= n; i++)
    {
        if (isPrime[i])
        {
            for (j = get_square(i); j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    for (i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            primes_count++;
        }
    }
    unsigned long int* primes = new unsigned long int[primes_count];
    for (i = 2; i <= n; i++)
    {
        if (isPrime[i]) primes[index++] = i;
    }
    return primes;
}

unsigned long int* experiment(unsigned long int* dividers, unint dividers_length, unint max_value, unint max_glad)
{
    unsigned long int* result = new unsigned long int[2];
    unint i, j, max_divider, count = 0, operations = 0;
    bool was_found;
    for (i = 2; i <= max_value; i++)
    {
        j = dividers_length-1;
        max_divider = 1;
        was_found = false;
        while (j >= 0 && !was_found && !(i % dividers[j] == 0 && dividers[j] > max_glad))
        {
            operations++;
            if (i % dividers[j] == 0 && dividers[j] <= max_glad)
            {
                count++;
                was_found = true;
            }
            j--;
        }
    }
    result[0] = count;
    result[1] = operations;
    return result;
}


void test_mode(int n, unsigned long int* dividers, unint length)
{
    cout << experiment(dividers, length, MAX_PRIME, n)[0]<< '\n';
}

int smooth_numbers_experiment(unsigned long int* dividers, unint length)
{
    unint board, number_of_lines = 1;
    string line;
    unsigned long int* result = new unsigned long int[2];
    ifstream fin(FILE_NAME);
    ofstream fout(EXIT_NAME);
    if(fin.is_open())
    {
        while(getline(fin, line))
        {
            board = stoul(line);
            result = experiment(dividers, length, MAX_PRIME, board);
            fout << result[0] << " " << result[1] << '\n';
            cout << number_of_lines << " LINES WERE READ" << '\n';
            number_of_lines++;
        }
    }
    delete[] result;
    fin.close();
    fout.close();
    return 0;
}
 
void experiment_test(unsigned long int* dividers, unsigned long int length, unint seed)
{
    srand(seed);
    unint a, b, c, d, test_one, test_two, board_one, board_two;
    a = rand();
    b = rand();
    c = rand();
    d = rand();
    test_one = ((a << 32) | b) % MAX_PRIME;
    test_two = ((c << 32) | d) % MAX_PRIME;
    board_one = get_max_or_min(0, test_one, test_two); // Большее
    board_two = get_max_or_min(1, test_one, test_two); // Меньшее
    cout << "----TEST----" << '\n';
    cout << "Board one: " << board_one << '\n';
    cout << "Board two: " << board_two << '\n';
    cout << '\n' <<"----RESULT----" << '\n';
    cout << "Result 1: " << experiment(dividers, length, MAX_PRIME, board_one)[0] << '\n';
    cout << "Result 2: " << experiment(dividers, length, MAX_PRIME, board_two)[0] << '\n';
    cout << "Result 1 >= Result 2" << '\n';
}
int main()
{
    unsigned int mode, flag;
    unint primes_count;
    unsigned long int* prime_numbers;
    prime_numbers = sieve_eratosphenes(MAX_PRIME, primes_count);
    //cin >> mode;
    //test_mode(mode, prime_numbers, primesCount);
    //flag = smooth_numbers_experiment(prime_numbers, primes_count);
    //experiment_test(prime_numbers, primes_count, mode);
    delete[] prime_numbers;
    if (flag == 0) cout << "SUCCESS";
    return 0;
}
