/* Julian Edison
 * CS 415
 * Comparing Sorting Algorithms
 */

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int NUM_TRIALS = 1;

const int SMALL_LIST = 10;
const int MEDIUM_SMALL_LIST = 100;
const int MEDIUM_LIST = 1000;
const int MEDIUM_LARGE_LIST = 10000;
const int LARGE_LIST = 100000;

void GenerateList(int list[], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        list[i] = rand() % n + 1;
    }
}

void GetProgress(float cur, float total)
{
    string str;
    ostringstream convert;
    convert << ((cur + 1) / total) * 100;
    str = convert.str() + "%";
    cout << str;
    cout << string(str.length(),'\b');
}

void OddEvenSort(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 2; j < n; j+=2)
                if (list[j] < list[j-1])
                    swap(list[j-1], list[j]);
        } else {
            for (int j = 1; j < n; j+=2)
                if (list[j] < list[j-1])
                    swap(list[j-1], list[j]);
        }
        //GetProgress(i,n);
    }
}

int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}

void countSort(int arr[], int n, int exp)
{
    int output[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(int arr[], int n)
{
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

void shellsort(int v[], int n)
{
    int gap, i, j, temp;
    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j=i-gap; j>=0 && v[j]>v[j+gap]; j-=gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
}

void reverseList(int list[], int listSize)
{
    int temp;
    for (int i = 0; i < listSize/2; ++i) {
        temp = list[listSize-i-1];
        list[listSize-i-1] = list[i];
        list[i] = temp;
    }
}

double getTime(clock_t s, clock_t e) {
    return (e - s);
}

int main()
{
    int listSize = LARGE_LIST;
    int unsortedList[listSize];
    int sortedList[listSize];

    bool showDetails = false;

    int numTrials = NUM_TRIALS;
    float oddEvenUnsortedTimes[numTrials], oddEvenSortedTimes[numTrials], oddEvenReverseSortedTimes[numTrials];
    float radixUnsortedTimes[numTrials], radixSortedTimes[numTrials], radixReverseSortedTimes[numTrials];
    float shellUnsortedTimes[numTrials], shellSortedTimes[numTrials], shellReverseSortedTimes[numTrials];

    float oddEvenUnsortedTotal = 0, oddEvenSortedTotal = 0, oddEvenReverseSortedTotal = 0;
    float radixUnsortedTotal = 0, radixSortedTotal = 0, radixReverseSortedTotal = 0;
    float shellUnsortedTotal = 0, shellSortedTotal = 0, shellReverseSortedTotal = 0;

    clock_t start;
    clock_t end;

    for (int j = 0; j < numTrials; j++) {
        GenerateList(unsortedList, listSize);

        for (int i = 0; i < listSize; i++) {
            sortedList[i] = unsortedList[i];
        }

        if (showDetails) cout << "Sorting an unsorted list of " << listSize << " items:" << endl;

        start = clock();
        OddEvenSort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Odd-Even: " << getTime(start, end) << "ms" << endl;
        oddEvenUnsortedTimes[j] = getTime(start, end);

        for (int i = 0; i < listSize; i++) {
            sortedList[i] = unsortedList[i];
        }

        start = clock();
        radixsort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Radix: " << getTime(start, end) << "ms" << endl;
        radixUnsortedTimes[j] = getTime(start, end);

        for (int i = 0; i < listSize; i++) {
            sortedList[i] = unsortedList[i];
        }

        start = clock();
        shellsort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Shell: " << getTime(start, end) << "ms" << endl;
        shellUnsortedTimes[j] = getTime(start, end);

        if (showDetails) cout << "\nSorting a sorted list of " << listSize << " items:" << endl;

        start = clock();
        OddEvenSort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Odd-Even: " << getTime(start, end) << "ms" << endl;
        oddEvenSortedTimes[j] = getTime(start, end);

        start = clock();
        radixsort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Radix: " << getTime(start, end) << "ms" << endl;
        radixSortedTimes[j] = getTime(start, end);

        start = clock();
        shellsort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Shell: " << getTime(start, end) << "ms" << endl;
        shellSortedTimes[j] = getTime(start, end);

        if (showDetails) cout << "\nSorting a reverse sorted list of " << listSize << " items:" << endl;

        reverseList(sortedList, listSize);

        start = clock();
        OddEvenSort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Odd-Even: " << getTime(start, end) << "ms" << endl;
        oddEvenReverseSortedTimes[j] = getTime(start, end);

        reverseList(sortedList, listSize);

        start = clock();
        radixsort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Radix: " << getTime(start, end) << "ms" << endl;
        radixReverseSortedTimes[j] = getTime(start, end);

        reverseList(sortedList, listSize);

        start = clock();
        shellsort(sortedList, listSize);
        end = clock();
        if (showDetails) cout << "Shell: " << getTime(start, end) << "ms" << endl;
        shellReverseSortedTimes[j] = getTime(start, end);

        if (showDetails) cout << endl;
        cout << "Trial " << j + 1 << " complete" << endl;
        if (showDetails) cout << endl;
    }

    for (int i = 0; i < numTrials; i++) {
        oddEvenUnsortedTotal += oddEvenUnsortedTimes[i];
        oddEvenSortedTotal += oddEvenSortedTimes[i];
        oddEvenReverseSortedTotal += oddEvenReverseSortedTimes[i];

        radixUnsortedTotal += radixUnsortedTimes[i];
        radixSortedTotal += radixSortedTimes[i];
        radixReverseSortedTotal += radixReverseSortedTimes[i];

        shellUnsortedTotal += shellUnsortedTimes[i];
        shellSortedTotal += shellSortedTimes[i];
        shellReverseSortedTotal += shellReverseSortedTimes[i];
    }

    cout << "\nRESULTS\n";

    cout << "\nOdd-Even" << endl
        << "Unsorted: " << oddEvenUnsortedTotal / numTrials << " ms" << endl
        << "Sorted: " << oddEvenSortedTotal / numTrials << " ms" << endl
        << "Reverse Sorted: " << oddEvenReverseSortedTotal / numTrials << " ms" << endl;

    cout << "\nRadix" << endl
        << "Unsorted: " << radixUnsortedTotal / numTrials << " ms" << endl
        << "Sorted: " << radixSortedTotal / numTrials << " ms" << endl
        << "Reverse Sorted: " << radixReverseSortedTotal / numTrials << " ms" << endl;

    cout << "\nShell" << endl
        << "Unsorted: " << shellUnsortedTotal / numTrials << " ms" << endl
        << "Sorted: " << shellSortedTotal / numTrials << " ms" << endl
        << "Reverse Sorted: " << shellReverseSortedTotal / numTrials << " ms" << endl;

	return 0;
}

