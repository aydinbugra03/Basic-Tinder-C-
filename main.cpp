// Buğra Aydın 

#include <string>
#include <iostream>
#include <fstream>


using namespace std;


// struct definitions as written in the hw document (likeds)
struct LikingNod {
    string Liker; //subject
    string being_liked; //object
    LikingNod* next;
};
// second struct (matcheds)
struct MatchedNods {
    string name;
    MatchedNods* next;
};

// construction function of like node and returning the node
LikingNod* createLikingNod(string liker, string being_liked) {
    // setting demanding nodes
    LikingNod* newNode = new LikingNod;
    newNode->Liker = liker;
    newNode->being_liked = being_liked;
    newNode->next = nullptr;
    return newNode;
}

// construction function of match node and returning the node
MatchedNods* make_matched_nodes(string namestr) {
    // setting demanding nodes
    MatchedNods* newNode = new MatchedNods;
    newNode->name = namestr;
    newNode->next = nullptr;
    return newNode;
}

// definitions of functions which will be used in the programme.

// true if name is already matched
bool CheckerMatched(MatchedNods * FirstNodeOfTaken, const string name) {
    // Traversing matched list to find the name
    while (FirstNodeOfTaken != nullptr) {
        if (FirstNodeOfTaken->name == name) return true;
        FirstNodeOfTaken = FirstNodeOfTaken->next;
    }
    return false; // when name dne
}

// adding couples to matched list
MatchedNods* addingToMatcheds(MatchedNods * FirstNodeOfTaken, const string  name) {
    MatchedNods* newNode = make_matched_nodes(name); // making new node
    // Plugging at beginning or before the first larger name (alphabetical order)
    if (FirstNodeOfTaken == nullptr || FirstNodeOfTaken->name > name) {
        newNode->next = FirstNodeOfTaken;
        return newNode;
    } else { // Finding the correct pos to plug
        MatchedNods * current = FirstNodeOfTaken;
        while ( (current->next != nullptr) and (current->next->name < name)) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        return FirstNodeOfTaken; // Returning the head
    }
}

// true if liker is old liker
bool CheckerLikeAlready(LikingNod * FirstNodeOfLikes, string Liker, string being_liked) {
    // Traversing the likes list to find the relationship
    while (FirstNodeOfLikes != nullptr) {
        if (FirstNodeOfLikes->Liker == Liker && FirstNodeOfLikes->being_liked == being_liked) return true;
        FirstNodeOfLikes = FirstNodeOfLikes->next;
    }
    return 0; // when liker is new
}

// when couple added to matcheds, for removing the specific name from the likers
void RemovingLikes(LikingNod * &FirstNodeOfLikes, string name) {
    LikingNod* previousptr = nullptr; // a prev node to keep the track of the list
    LikingNod* currentptr = FirstNodeOfLikes; // current = first

    // Iterating the entire list until it finishes
    while (currentptr != nullptr) {
        // if current node is liker or being liked. (or both)
        if (currentptr->Liker == name || currentptr->being_liked == name) {
            // if the node is the first node of the list
            if (previousptr == nullptr) {
                // removing that node
                FirstNodeOfLikes = currentptr->next;
            } else {
                // moving current node to the head to remove it
                previousptr->next = currentptr->next;
            }
            // for safe deletion temperory node
            LikingNod * temp = currentptr;

            currentptr = currentptr->next;

            delete temp;
        } else {
            // if current node not in, moving both pointers to forward
            previousptr = currentptr;
            currentptr = currentptr->next;
        }
    }
}
// I made this function long and let it do many tasks since I got penalty -2 from having long main
// adding couples to likeds as asked format, also checks for matches if exist adding them to matcheds list
// also do the all formatting jobs and deleting matched couples from likeds list
void addingToLikesList(LikingNod* & FirstNodeOfLikes, string Liker, string being_liked, MatchedNods *& FirstNodeOfTaken) {
    // checking for old match
    if (CheckerMatched(FirstNodeOfTaken, Liker) || CheckerMatched(FirstNodeOfTaken, being_liked)) {
        cout << "Either " << Liker << " or " << being_liked << " or both is/are already taken, so the like relation is not added." << endl;
        return;
    }
    if (CheckerLikeAlready(FirstNodeOfLikes, Liker, being_liked)) {
        cout << Liker << " likes " << being_liked << " relation already exists in the likes list, so it is not added to it." << endl;
        return;
    }
    // handling mutual likes leading to match
    if (CheckerLikeAlready(FirstNodeOfLikes, being_liked, Liker)) {
        cout << "Match found: " << Liker << " likes " << being_liked << " and " << being_liked << " likes " << Liker << "." << endl;
        FirstNodeOfTaken = addingToMatcheds(FirstNodeOfTaken, Liker);
        cout << "Added to taken list: " << Liker << endl;
        FirstNodeOfTaken = addingToMatcheds(FirstNodeOfTaken, being_liked);
        cout << "Added to taken list: " << being_liked << endl;
        cout << "Any node that has " << Liker << " or " << being_liked << " or both in it is removed from the likes list." << endl;
        RemovingLikes(FirstNodeOfLikes, Liker);
        RemovingLikes(FirstNodeOfLikes, being_liked);
        return;
    }
    // add new liked
    LikingNod* newNode = createLikingNod(Liker, being_liked);
    if (FirstNodeOfLikes == nullptr) {
        FirstNodeOfLikes = newNode; // new node is the first node if list is empty
    } else {
        // finding the correct pos and plugging the new node
        LikingNod* current = FirstNodeOfLikes;
        LikingNod* lastNodeOfLiker = nullptr;

        while (current != nullptr) {
            if (current->Liker == Liker) {
                lastNodeOfLiker = current; // finding the last occurence of the liker
            }
            current = current->next;
        }

        // if the liker is not new, adding the new node just after the last node of the current liker
        if (lastNodeOfLiker != nullptr) {
            newNode->next = lastNodeOfLiker->next;
            lastNodeOfLiker->next = newNode;
        } else {
            // append the new node at the end of the list
            current = FirstNodeOfLikes;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    cout << Liker << " likes " << being_liked << " relation has been added to the likes list." << endl;
}


// showing current lists (matcheds and like list)
void printinglists(LikingNod* FirstNodeOfLikes, MatchedNods * FirstNodeOfTaken) {
    cout << "Likes list: ";
    while (FirstNodeOfLikes != nullptr) {
        cout << "(" << FirstNodeOfLikes->Liker << ", " << FirstNodeOfLikes->being_liked << ") ";
        FirstNodeOfLikes = FirstNodeOfLikes->next;
    }
    cout << endl;

    cout << "Taken list: ";
    while (FirstNodeOfTaken != nullptr) {
        cout << FirstNodeOfTaken->name << " ";
        FirstNodeOfTaken = FirstNodeOfTaken->next;
    }
    cout << endl << endl;
}

// to free the memory (as asked in the hw doc)
void deletinglists(LikingNod*& FirstNodeOfLikes, MatchedNods* & FirstNodeOfTaken) {
    // Deleting every node in the likes list
    while (FirstNodeOfLikes != nullptr) {
        LikingNod* temp_like = FirstNodeOfLikes;
        FirstNodeOfLikes = FirstNodeOfLikes->next;
        delete temp_like;
    }
    // Deleting every node in the matched list
    while (FirstNodeOfTaken != nullptr) {
        MatchedNods* temp_Taken = FirstNodeOfTaken;
        FirstNodeOfTaken = FirstNodeOfTaken->next;
        delete temp_Taken;
    }
}


int main() {
    // Initializing empty likes and matched lists
    LikingNod* FirstNodeOfLikes = nullptr;
    MatchedNods* FirstNodeOfTaken = nullptr;

    string file_name;
    cout << "Please enter the file name: " << endl;
    bool breaker = false; // checker for while loop
    // controlling the file opening
    while (!breaker) {
        cin >> file_name;
        ifstream fil(file_name);

        if (fil.is_open()) { // when file is opened
            string Liker, unnes, being_liked; // unnes = the verb(likes) that unnecessary
            int line_number; // for showing line numbers in the output
            line_number = 1;

            // processing each line in the file.
            while (fil >> Liker >> unnes >> being_liked) {
                cout << "Read line number (" << line_number << "): " << Liker << " likes " << being_liked << endl;

                // adding to likeds list and checking for matches ( if yes add to matcheds list )
                // as asked format ( deleting from liked list etc.)
                addingToLikesList(FirstNodeOfLikes, Liker, being_liked, FirstNodeOfTaken);

                // printing the current lists
                printinglists(FirstNodeOfLikes, FirstNodeOfTaken);
                line_number = line_number + 1;
            }

            breaker = 1; // to exit loop when job is done
            fil.close(); // closing the file

        } else {
            // if file did not open
            cout << "Could not open the file. Please enter a valid file name: " << endl;
        }
    }

    // to empty memory, deleting all nodes from the lists
    deletinglists(FirstNodeOfLikes, FirstNodeOfTaken);
    cout << "Lists are deleted and the program ends successfully." << endl;

    return 0;
}

// Buğra Aydın