#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <iostream>
#include <string>
using namespace std;

class Performance
{
private:
    string personID;
    int rating;
    string review;
    string reviewDate;
    string givenBy;

public:

    Performance()
    {
        personID = "";
        rating = 0;
        review = "";
        reviewDate = "";
        givenBy = "";
    }

    void giveRating(
        string id,
        int newRating,
        string newReview,
        string date,
        string reviewerID
    )
    {
        personID = id;
        rating = newRating;
        review = newReview;
        reviewDate = date;
        givenBy = reviewerID;
    }

    string getPersonID()
    {
        return personID;
    }

    int getRating()
    {
        return rating;
    }

    string getReview()
    {
        return review;
    }

    string getReviewDate()
    {
        return reviewDate;
    }

    // THIS WAS MISSING
    string getGivenBy()
    {
        return givenBy;
    }

    void displayPerformance()
    {
        cout << "\n========== PERFORMANCE ==========\n";

        cout << "Person ID: " << personID << endl;
        cout << "Rating: " << rating << "/10" << endl;
        cout << "Review: " << review << endl;
        cout << "Review Date: " << reviewDate << endl;
        cout << "Given By: " << givenBy << endl;
    }
};

#endif