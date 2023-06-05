#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <cmath>

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
        possibilities.push_back(currentPossibility);
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

    // Loop to iterate over all possibilities
    vector<Movie> bestMovies;
    for (vector<Movie> &movies_select : possibilities)
    {
        vector<int> currentQnt_per_category(maxQnt_per_category.size(), 0);
        vector<bool> schedule(24, 0);
        int ans = 0, screenTime = 0;

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
                    screenTime += movie.end - movie.start;
                }
            }
            if (ans > maxAns)
            {
                maxAns = ans;
                maxScreenTime = screenTime;
                bestMovies = movies_select;
            }
        }
    }

    // Print the answer
    cout << "Number of movies allocated: " << maxAns << endl;

    return 0;
}