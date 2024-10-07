#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

struct Review{
    double rating;
    string comments;
    Review* next;
};

class Movie{
private:
    string title;
    Review* head;
    Review* tail;

public:
    Movie(const string& movie_title);
    ~Movie(); 
    void add_review(const string& comments);
    void display_reviews() const;
    double generate_random_rating() const;
};

Movie::Movie(const string& movie_title) {
    title = movie_title;
    head = nullptr;
    tail = nullptr;
}

Movie::~Movie() {
    while (head) {
        Review* temp = head;
        head = head->next;
        delete temp;
    }
};

double Movie::generate_random_rating() const {
    return (rand() % 41 + 10) / 10.0;
}

void Movie::add_review(const string& comments) {
    Review* new_node = new Review;
    new_node->rating = generate_random_rating();
    new_node->comments = comments;
    new_node->next = head;
    head = new_node;
    if (!tail) {
        tail = head;
    }
}

//display_review() outputs reviews and gets average rating
// arguments: head: reference to first node
// returns: void
void Movie::display_reviews() const{
    Review* temp = head;
    int count = 1;
    double total_rating = 0.0;
    int number_reviews = 0;

    while (temp){
        cout << "> Review #" << count << ": " << temp->rating << ":"
            << temp-> comments << endl;
        total_rating += temp->rating;
        number_reviews++;
        temp = temp->next;
        count++;
    }

    if (number_reviews > 0){
        cout << "> Average: " << total_rating / number_reviews << endl;
    } else {
        cout << "None" << endl;
    }
}

int main() {
    string comments;
    srand(static_cast<unsigned int>(time(0)));

    vector<Movie> movies;
    movies.push_back(Movie("movie 1"));
    movies.push_back(Movie("movie 2"));
    ifstream file("review.txt");
    
    while (getline(file, comments)) {
        movies[0].add_review(comments);
        if (getline(file, comments)) {
            movies[1].add_review(comments);
        }
    }

    cout << "Movie 1 review: " << endl;
    movies[0].display_reviews();
    cout << "Movie 2 review: " << endl;
    movies[1].display_reviews();

    return 0;
}