#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

class Question {
public:
    virtual void display() const = 0;
    virtual bool checkAnswer(char userAnswer) const = 0;
    virtual string getExplanation() const = 0;
    virtual void fiftyFifty() = 0; 
};

class MCQ : public Question {
private:
    string question;
    string options[4];
    char correctAnswer;
    string explanation;

public:
    MCQ(string question, string optionA, string optionB, string optionC, string optionD, char correctAnswer, string explanation)
        : question(question), correctAnswer(correctAnswer), explanation(explanation) {
        options[0] = optionA;
        options[1] = optionB;
        options[2] = optionC;
        options[3] = optionD;
    }

    void display() const override {
        cout << "Question: " << question << endl;
        cout << "Options:\n";
        for (int i = 0; i < 4; ++i) {
            char option = 'A' + i;
            cout << option << ") " << options[i] << endl;
        }
    }

    bool checkAnswer(char userAnswer) const override {
        return toupper(userAnswer) == correctAnswer;
    }

    string getExplanation() const override {
        return explanation;
    }

    void fiftyFifty() override {
        vector<char> optionsList = {'A', 'B', 'C', 'D'};
        optionsList.erase(remove(optionsList.begin(), optionsList.end(), correctAnswer), optionsList.end());
        shuffle(optionsList.begin(), optionsList.end(), default_random_engine{});

        char option1 = optionsList[0];
        char option2 = optionsList[1];

        for (int i = 0; i < 4; ++i) {
            if (options[i][0] == option1 || options[i][0] == option2) {
                options[i] = " ";
            }
        }
    }
};

int main() {
    vector<Question*> questions;
    questions.push_back(new MCQ("Who is known as the 'God of Cricket'?", "Sachin Tendulkar", "Virat Kohli", "Rahul Dravid", "MS Dhoni", 'A', "Sachin Tendulkar is known as the 'God of Cricket'."));
    questions.push_back(new MCQ("Which country won the ICC Cricket World Cup in 2019?", "India", "England", "Australia", "South Africa", 'B', "England won the ICC Cricket World Cup in 2019."));
    questions.push_back(new MCQ("Who has scored the fastest century in T20 international cricket?", "Yuvraj Singh", "Chris Gayle", "Rohit Sharma", "David Miller", 'B', "Chris Gayle has scored the fastest century in T20 international cricket."));
    questions.push_back(new MCQ("Which of these counties has never won the cricket world cup?","england","south africa","west indies","Australia", 'B',"SOUTH AFRICA has never won the world cup"));
    
    cout << "Welcome to Cricket Quiz Competition!\n\n";

    string player1, player2;
    cout << "Enter Player 1's Name: ";
    cin >> player1;
    cout << "Enter Player 2's Name: ";
    cin >> player2;

    int score1 = 0, score2 = 0;
    try {
        for (int i = 0; i < questions.size(); ++i) {
            if (i % 2 == 0) {
                cout << "\n" << player1 << ", ";
            } else {
                cout << "\n" << player2 << ", ";
            }

            questions[i]->display();

            char userAnswer;
            cout << "\nEnter your choice (A/B/C/D) or type 'L' for Lifeline: ";
            cin >> userAnswer;

            if (!isalpha(userAnswer)) {
                throw runtime_error("Invalid input! Please enter A, B, C, D, or L.");
            }

            if (toupper(userAnswer) == 'L') {
                questions[i]->fiftyFifty();
                cout << "\nYou've used the 50/50 lifeline! Here are the remaining options:\n";
                questions[i]->display();
                cout << "\nEnter your choice (A/B/C/D): ";
                cin >> userAnswer;
            }

            if (questions[i]->checkAnswer(userAnswer)) {
                cout << "\nCorrect Answer! You earn 100 points.\n";
                if (i % 2 == 0) {
                    score1 += 100;
                } else {
                    score2 += 100;
                }
            } else {
                cout << "\nWrong Answer! The correct answer is " << questions[i]->getExplanation() << ".\n";
            }
        }

        cout << "\nQuiz completed!\n";
        cout << player1 << " scored: " << score1 << " points\n";
        cout << player2 << " scored: " << score2 << " points\n";

        if (score1 > score2) {
            cout << "\nCongratulations, " << player1 << " wins!\n";
        } else if (score1 < score2) {
            cout << "\nCongratulations, " << player2 << " wins!\n";
        } else {
            cout << "\nIt's a tie!\n";
        }
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    for (auto& q : questions) {
        delete q;
    }
    questions.clear();

    return 0;
}