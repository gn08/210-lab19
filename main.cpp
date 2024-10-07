#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

// struct with review for movie info
struct Review{
    double rating;
    string comments;
    Review* next;
};

//class with movie review info
class Movie{
private:
    string title;
    Review* head;
    Review* tail;

public:
//movie constructor
//sets with title and head and tail to nullptr
//arguments: movie_title- movie title
    Movie(const string& movie_title);
//movie deconstructor, memory of review
    ~Movie(); 
//add_review() adds review and a random rating
//arguments: comments- comments of review
//returns void
    void add_review(const string& comments);
//display_reviews() displays review and average rating
// returns void
    void display_reviews() const;
//generate_random_rating() generate random rating
//return: double number of random rating
    double generate_random_rating() const;
};

Movie::Movie(const string& movie_title) {
    title = movie_title;
//set head and tail to nullptr
    head = nullptr;
    tail = nullptr;
}
//delete review from list
Movie::~Movie() {
    while (head) {
        Review* temp = head;
        //head to next review
        head = head->next;
        //clean memory
        delete temp;
    }
};

double Movie::generate_random_rating() const {
    //random rating between 1.0 and 5.0
    return (rand() % 41 + 10) / 10.0;
}

void Movie::add_review(const string& comments) {
//create review, new node
    Review* new_node = new Review;
//random rating
    new_node->rating = generate_random_rating();
    new_node->comments = comments;
    new_node->next = head;
    head = new_node;
//if first review then make tail set to head
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
//display every review
    while (temp){
        cout << "> Review #" << count << ": " << temp->rating << ":"
            << temp-> comments << endl;
        total_rating += temp->rating;
        number_reviews++;
        temp = temp->next;
        count++;
    }
//add reviews
    if (number_reviews > 0){
        cout << "> Average: " << total_rating / number_reviews << endl;
    } else {
        cout << "None" << endl;
    }
}

int main() {
    int movie_index = 0;
    string comments;
    srand(static_cast<unsigned int>(time(0)));

    vector<Movie> movies;
    movies.push_back(Movie("movie 1"));
    movies.push_back(Movie("movie 2"));
    vector<string> review_comments;
//open file
    ifstream file("review.txt");
     while (getline(file, comments)) {
        review_comments.push_back(comments);
    }
    // assign reviews to movies
    for (size_t i = 0; i < review_comments.size(); ++i) {
        movies[i % 2].add_review(review_comments[i]);
    }

//output reviews in organized format
    cout << "Movie 1 review: " << endl;
    movies[0].display_reviews();
    cout << "Movie 2 review: " << endl;
    movies[1].display_reviews();

    return 0;
}