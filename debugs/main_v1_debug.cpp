#include <iostream>
#include <algorithm>
#include <vector>
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
    freopen("output_v1.txt", "w", stdout);

    // Print the movies vector (debug)
    // cout << "MOVIE VECTOR: " << endl;
    // for (int i = 0; i < n; i++)
    //     cout << movies[i].start << " " << movies[i].end << " " << movies[i].category << endl;
    // cout << endl;
    // cout << endl;

    // For each movie, check if it can be added to the schedule
    for (int i = 0; i < n; i++) {
        int start = movies[i].start;
        int end = movies[i].end;
        int category = movies[i].category - 1;

        if (start >= end) { // If the movie starts after it ends, it is not valid
            //debug
            // cout << "---ERROR: Movie " << i << " cannot be added to schedule" << endl;
            // cout << "Start time is after end time" << endl;
            // cout << "start index: " << start << " end index: " << end-1 << endl;
            // cout << "Current schedule: " << endl;
            // for (int t = 0; t < 24; t++)
            //     cout << schedule[t] << " ";
            // cout << endl;
            // cout << endl;

            continue;
        }

        else if (schedule[start+1] == 1) { // If the movie starts at the same time as another movie, it is not valid
            //debug
            // cout << "---ERROR: Movie " << i << " cannot be added to schedule" << endl;
            // cout << "Start time is the same as another movie" << endl;
            // cout << "start index: " << start << " end index: " << end-1 << endl;
            // cout << "Current schedule: " << endl;
            // for (int t = 0; t < 24; t++)
            //     cout << schedule[t] << " ";
            // cout << endl;
            // cout << endl;

            continue;
        }

        if (currentQnt_per_category[category] < maxQnt_per_category[category]) {
            if (schedule[start] == 0 && schedule[end] == 0) {
                for (int j = start; j < end; j++)
                    schedule[j] = 1;
                currentQnt_per_category[category]++;
                ans++;

                //print start, end and category of the movie added to the schedule
                cout << start << " " << end << " " << category+1 << endl;
                
                //debug
                // cout << "---SUCCESS: Movie " << i << " added to schedule >" << endl;
                // cout << "--Start time: " << start << " --End time: " << end << endl;
                // cout << "start index: " << start << " end index: " << end-1 << endl;
                // cout << "Current schedule: " << endl;
                // for (int t = 0; t < 24; t++)
                //     cout << schedule[t] << " ";
                // cout << endl;
                // cout << endl;
            } else {
                //debug
                // cout << "---ERROR: Movie " << i << " cannot be added to schedule" << endl;
                // cout << "There is a conflict with movie " << start << " or " << end << endl;
                // cout << "start index: " << start << " end index: " << end-1 << endl;
                // cout << "Current schedule: " << endl;
                // for (int t = 0; t < 24; t++)
                //     cout << schedule[t] << " ";
                // cout << endl;
                // cout << endl;
            }
        } else {
            //debug
            // cout << "---ERROR: Movie " << i << " cannot be added to schedule" << endl;
            // cout << "There are already " << maxQnt_per_category[category] << " movies of category " << category+1 << endl;
            // cout << "start index: " << start << " end index: " << end-1 << endl;
            // cout << "Current schedule: " << endl;
            // for (int t = 0; t < 24; t++)
            //     cout << schedule[t] << " ";
            // cout << endl;
            // cout << endl;
        }
    }

    cout << "O número máximo de filmes é: " << ans << endl;
    return 0;
}
