#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cmath>
#include <omp.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Movie
{
    int start, end, category;
};

vector<vector<Movie>> generatePossibilities(vector<Movie> &movies)
{
    vector<vector<Movie>> possibilities;
    int n = movies.size();
    long long num_possibilities = static_cast<long long>(std::pow(2, n));

#pragma omp parallel for shared(movies, possibilities)
    for (long long i = 1; i < num_possibilities; i++)
    {
        vector<Movie> currentPossibility;

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                currentPossibility.push_back(movies[j]);
            }
        }
#pragma omp critical
        {
            possibilities.push_back(currentPossibility);
        }
    }
    return possibilities;
}

int main()
{
    // Variables
    int n, m;
    int maxAns = 0;
    int maxScreenTime = 0;

    // Read the number of movies and categories
    cin >> n;
    cin >> m;

    // Create the movies vector
    vector<Movie> movies(n);
    vector<int> maxQnt_per_category(m);

    // Read the number of movies of each category
    for (int i = 0; i < m; i++)
        cin >> maxQnt_per_category[i];

    // Read the movies
    for (int i = 0; i < n; i++)
        cin >> movies[i].start >> movies[i].end >> movies[i].category;

    // Generate all possibilities
    vector<vector<Movie>> possibilities = generatePossibilities(movies);

    vector<int> threadMaxAns(omp_get_max_threads(), 0);

// Parallelizing the loop with OpenMP
#pragma omp parallel for
    for (int p = 0; p < possibilities.size(); p++)
    {
        vector<Movie> &movies_select = possibilities[p];
        vector<int> currentQnt_per_category(maxQnt_per_category.size(), 0);
        vector<bool> schedule(24, 0);
        int ans = 0;

        for (Movie &movie : movies_select)
        {
            // Check if the movie can be watched
            if (currentQnt_per_category[movie.category - 1] < maxQnt_per_category[movie.category - 1] && movie.start <= movie.end)
            {
                // Check if the movie can be watched at the current time
                bool canWatch = true;
                for (int i = movie.start; i < movie.end; i++)
                {
                    if (schedule[i] == 1)
                    {
                        canWatch = false;
                        break;
                    }
                }

                // If the movie can be watched, update the schedule
                if (canWatch)
                {
                    for (int i = movie.start; i < movie.end; i++)
                    {
                        schedule[i] = 1;
                    }
                    currentQnt_per_category[movie.category - 1]++;
                    ans++;
                }
            }
            if (ans > threadMaxAns[omp_get_thread_num()])
            {
                threadMaxAns[omp_get_thread_num()] = ans;
            }
        }
    }

    // After all threads have finished, update maxAns and maxScreenTime with the max values from each thread
    for (int i = 0; i < omp_get_max_threads(); i++)
    {
        if (threadMaxAns[i] > maxAns)
        {
            maxAns = threadMaxAns[i];
        }
    }

    // Print the answer
    cout << "Number of movies allocated: " << maxAns << endl;

    return 0;
}
