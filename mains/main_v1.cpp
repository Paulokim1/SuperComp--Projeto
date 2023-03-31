#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Movie {
    int start, end, category;
};

bool sortByEndTime(const Movie& a, const Movie& b) {
    return a.end < b.end; // Sort by end time in ascending order
}

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Variables
    int n, m;
    int screenTime = 0;
    int ans = 0;

    // Read the number of movies and categories
    cin >> n;
    cin >> m;

    // Create the movies vector and the schedule vector
    vector<Movie> movies(n);
    vector<int> maxQnt_per_category(m); // Maximum number of movies of category i that can be displayed

    vector<int> currentQnt_per_category(m, 0); //
    vector<int> schedule(23, 0); // 24 hours in a day (0-23)

    // Read the number of movies of each category
    for (int i=0; i < m; i++)
        cin >> maxQnt_per_category[i];
    
    // Read the movies
    for (int i = 0; i < n; i++) 
        cin >> movies[i].start >> movies[i].end >> movies[i].category;

    // Sort the movies by end time in ascending order
    sort(movies.begin(), movies.end(), sortByEndTime);

    // Print number of movies and categories
    cout << n << endl;
    cout << m << endl;

    // For each movie, check if it can be added to the schedule
    for (int i = 0; i < n; i++) {
        int start = movies[i].start;
        int end = movies[i].end;
        int category = movies[i].category - 1;

        if (start >= end) { // If the movie starts after it ends, it is not valid
            continue;
        }
        else if (schedule[start+1] == 1) { // If the movie starts at the same time as another movie, it is not valid
            continue;
        }
        if (currentQnt_per_category[category] < maxQnt_per_category[category]) { // If the movie is of a category that has not reached its limit
            if (schedule[start] == 0 && schedule[end] == 0) { // and if the movie does not overlap with another movie, add it to the schedule
                for (int j = start; j < end; j++) // add the movie to the schedule
                    schedule[j] = 1;
                currentQnt_per_category[category]++;
                ans++;
                screenTime += end - start;      
            } 
        }
    }
    cout << ans << endl;
    cout << screenTime << endl;

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time); //µs
    cout << duration.count() << endl;

    // Outputs order
    // 1. Number of movies
    // 2. Number of categories
    // 3. Number of movies allowed to be displayed
    // 4. Total screen time
    // 5. Execution time
    return 0;
}
