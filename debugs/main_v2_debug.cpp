#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cstdlib>

using namespace std;

struct Movie {
    int start, end, category;
};

bool sortByEndTime(const Movie& a, const Movie& b) {
    return a.end < b.end; // Sort by end time in ascending order
}

int main() {
    // Variables
    int n, m;
    int ans = 0;

    // Read the number of movies and categories
    cin >> n;
    cin >> m;

    // Create the movies vector and the schedule vector
    vector<Movie> movies(n);
    vector<int> maxQnt_per_category(m); // qnt_per_category[i] = qnt of movies of category 
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

    // Open file to write output
    freopen("output_v2.txt", "w", stdout);

    // For each movie, check if it can be added to the schedule
    for (int i = 0; i < n; i++) {
        int rand_i, start, end, category;
        int rand_num = rand() % 100; // Generate a random number between 0 and 3
        //cout << "Rand: " << rand_num << endl;

        if (rand_num < 25) { // If the random number is 0 (25% chance), choose a random movie
            rand_i = (rand() * (n+1)) / RAND_MAX; // Generate a normalized random number between 0 and n
            start = movies[rand_i].start;
            end = movies[rand_i].end;
            category = movies[rand_i].category - 1;
            i--; // Decrement i so that the next iteration will be the same movie

        } else {
            start = movies[i].start;
            end = movies[i].end;
            category = movies[i].category - 1;

        }
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

                cout << start << " " << end << " " << category+1 << endl;
 
            } 
        }
    } 
    cout << ans << endl;
    return 0;
}
