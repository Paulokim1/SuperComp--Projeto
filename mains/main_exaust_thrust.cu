#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/copy.h>
#include <thrust/sequence.h>
#include <thrust/transform.h>
#include <thrust/extrema.h>

using std::cin;
using std::cout;
using std::endl;

struct Movie
{
    int start;
    int end;
    int category;
};

struct getMovieCount
{
    int numMovies;
    int numCategories;
    Movie *movies;
    int *maxQnt_per_category;

    __device__ __host__
    getMovieCount(int numMovies, int numCategories, Movie *movies, int *maxQnt_per_category)
        : numMovies(numMovies), numCategories(numCategories), movies(movies), maxQnt_per_category(maxQnt_per_category)
    {
    }

    __device__ __host__ int operator()(const int &x)
    {
        int schedule[24] = {0};
        int currentQnt_per_category[15] = {0};

        int count = 0;

        for (int i = 0; i < numMovies; i++)
        {
            if (x & (1 << i))
            {
                Movie &movie = movies[i];
                if (currentQnt_per_category[movie.category - 1] >= maxQnt_per_category[movie.category - 1] || movie.start > movie.end)
                    return 0;
                for (int j = movie.start; j < movie.end; j++)
                {
                    if (schedule[j] == 1)
                        return 0;
                    schedule[j] = 1;
                }
                currentQnt_per_category[movie.category - 1]++;
                count++;
            }
        }
        return count;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    thrust::host_vector<int> maxQnt_per_category_h(m);
    thrust::host_vector<Movie> movies_h(n);

    for (int i = 0; i < m; i++)
    {
        cin >> maxQnt_per_category_h[i];
    }

    for (int i = 0; i < n; i++)
    {
        Movie &movie = movies_h[i];
        cin >> movie.start >> movie.end >> movie.category;
    }

    thrust::device_vector<int> maxQnt_per_category_d(maxQnt_per_category_h);
    thrust::device_vector<Movie> movies_d(movies_h);

    thrust::device_vector<int> possibility_d(pow(2, n));
    thrust::sequence(possibility_d.begin(), possibility_d.end());

    thrust::transform(possibility_d.begin(), possibility_d.end(), possibility_d.begin(),
                      getMovieCount(n,
                                    m,
                                    thrust::raw_pointer_cast(movies_d.data()),
                                    thrust::raw_pointer_cast(maxQnt_per_category_d.data())));

    int maxMovies = *thrust::max_element(possibility_d.begin(), possibility_d.end());

    // Print the result
    cout << "Number of movies allocated: " << maxMovies << endl;

    return 0;
}