#include <iostream>
#include <string>
using namespace std;

struct Review{
    double rating;
    string comments;
    Review* next;
};

void display_reviews() const; 
void add_review(const string& comments);
void display_review();

int main() {
    Review* head = nullptr;
    Review* tail = nullptr;
    int choice;
    double rating;
    string comments;

    cout << "Which linked list method should we use?" << endl;
    cout << "[1] New nodes are added at the head of the linked list";
    cout << "[2] New nodes are added at the tail of the linked list";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter review rating";
    cin >> rating;
    cin.ignore();
    cout << "Enter comments: ";
    getline(cin, comments);

    if (choice == 1){
        add_at_head(head, tail, rating, comments);
    } else{
        add_at_tail(head, tail, rating, comments);
    }

    cout  << "Outputting all reviews:";
    display_review(head);
    while (head){
        Review* temp = head;
        head = head-> next;
        delete temp;
    }

    return 0;
}

//display_review() outputs reviews and gets average rating
// arguments: head: reference to first node
// returns: void
void display_review(){
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

class Movie{
    private:
    string title;
    Review* head;
    Review* tail;

    public:
    Movie(const string& movie_title);
    void add_review(const string& comments);
    void display_reviews() const;
    double generate_random_rating() const;
};

Movie::Movie() {
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
}