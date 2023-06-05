#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Movie
{
    int start, end, category;
    bool operator<(const Movie &m) const
    {
        return start < m.start;
    }
};

vector<vector<Movie>> generatePossibilities(vector<Movie> &movies)
{
    vector<vector<Movie>> possibilities;
    int n = movies.size();
    int count = 1;
    // Loop to iterate over all possibilities (2^n)
    for (int i = 1; i < (1 << n); i++)
    {
        vector<Movie> currentPossibility;

        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                currentPossibility.push_back(movies[j]);
            }
        }
        // print current possibility (debug)
        //  cout << "Possibility " << count++ << ": " << endl;
        //  for (const auto &movie : currentPossibility)
        //  {
        //      cout << "Movie starts: " << movie.start << ", ends: " << movie.end << ", category: " << endl;
        //  }
        //  cout << endl;
        possibilities.push_back(currentPossibility);
    }

    return possibilities;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

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
    for (auto &movies : possibilities)
    {
        vector<int> currentQnt_per_category(maxQnt_per_category.size(), 0);
        vector<int> schedule(24, 0);
        int ans = 0, screenTime = 0;
        vector<Movie> currentMovies;

        for (Movie &movie : movies)
        {
            int start = movie.start;
            int end = movie.end;
            int category = movie.category - 1;

            if (start >= end)
            {
                // If the movie starts after it ends, it is not valid
                continue;
            }
            else if (schedule[start + 1] == 1)
            { // If the movie starts at the same time as another movie, it is not valid
                continue;
            }
            if (currentQnt_per_category[category] < maxQnt_per_category[category])
            { // If the movie is of a category that has not reached its limit
                if (schedule[start] == 0 && schedule[end] == 0)
                {                                     // and if the movie does not overlap with another movie, add it to the schedule
                    for (int j = start; j < end; j++) // add the movie to the schedule
                        schedule[j] = 1;
                    currentQnt_per_category[category]++;
                    ans++;
                    screenTime += end - start;
                }
            }
        }
        if (ans > maxAns)
        {
            maxAns = ans;
            maxScreenTime = screenTime;
            bestMovies = movies;
        }
    }

    // Print the answer
    cout << endl;
    cout << "Number of movies allocated: " << maxAns << endl;
    cout << "Screen time: " << maxScreenTime << endl
         << endl;
    // Print the movies that were selected to be watched
    for (const auto &movie : bestMovies)
    {
        cout << "Movie starts: " << movie.start << ", ends: " << movie.end << ", category: " << movie.category << endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Execution time: " << duration.count() / 1000000.0 << " seconds" << endl;

    return 0;
}