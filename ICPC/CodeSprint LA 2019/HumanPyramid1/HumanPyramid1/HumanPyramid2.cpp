#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int T; // Number of test cases
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		// For each test case:

		int n; // Number of levels in the pyramid
		cin >> n;

		int people = n*(n+1)/2; // Number of people in the pyramid
		int* weights; // Array of weights of people
		double* effective; // Array of effective weights carried by each person
		if (n != 0)
		{
			weights = (int *) malloc(sizeof(int) * people);
			effective = (double *) malloc(sizeof(double) * people);
		}
		double maxEffectiveWeight = 0;									// Variable to store current maximum effective weight found

		// Store weights of each person in the pyramid
		for (int p = 0; p < people; p++)
			cin >> weights[p];

		// In a zero-level pyramid, there are no people.
		if (n == 0)
		{
			cout << 0 << endl;
			continue;
		}

		// Effective weight carried by first person is 0, calculate effective weight for all remaining people by level
		effective[0] = 0;
        long double sum = 0;
		for (int l = 1; l < n; l++)
		{
			int prev = l*(l-1)/2; // Index of the first person in the previous level
			int curr = l*(l+1)/2; // Index of the first person in this level

			// Calculate effective weight of first person in level
			effective[curr] = (effective[prev] + weights[prev])/2;
			maxEffectiveWeight = (maxEffectiveWeight < effective[curr]) ? effective[curr] : maxEffectiveWeight;

			// Calculate effective weights of intermediate people in level
			for (int p = 2; p <= l+1; p++)
			{
				effective[curr+p] = (effective[prev+p] + effective[prev+p-1] + weights[prev+p] + weights[prev+p-1])/2;
				maxEffectiveWeight = (maxEffectiveWeight < effective[curr+p]) ? effective[curr+p] : maxEffectiveWeight;
                cout << effective[curr + p] << " ";
                sum += effective[curr + p];
			}

			// Calculate effective weights of last people in level
			effective[curr+l] = (effective[prev+l-1] + weights[prev+l-1])/2;
			maxEffectiveWeight = (maxEffectiveWeight < effective[curr+l]) ? effective[curr+l] : maxEffectiveWeight;
		}

		cout << (int) round(sum) << endl;

		// Free dynamically allocated arrays
		free(effective);
		free(weights);
	}
}
