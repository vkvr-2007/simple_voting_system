#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Voter node (linked list)
struct Voter {
    char name[50];
    char phone[20];
    char aadhar[20];
    struct Voter* next;
};

// Candidate node (array element)
struct Candidate {
    char name[50];
    int id;
    int voteCount;
    struct Voter* voterHead; // Linked list of voters
};

struct Candidate candidates[100]; // Array of candidates
int candidateCount = 0;

//registration for new candidates
void registerCandidate() {
    if (candidateCount >= 100) {
        printf("Candidate limit reached.\n"); //max limit
        return;
    }

    printf("Enter candidate name: ");
    scanf("%s", candidates[candidateCount].name);
    candidates[candidateCount].id = candidateCount + 1;
    candidates[candidateCount].voteCount = 0;
    candidates[candidateCount].voterHead = NULL;

    printf("Candidate '%s' registered with ID %d\n\n", candidates[candidateCount].name, candidates[candidateCount].id);
    candidateCount++;
}

//voting a candidate
void vote() {
    if (candidateCount == 0) {
        printf("No candidates registered yet.\n\n");
        return;
    }

    printf("Enter your name: "); //name
    char name[50];
    scanf("%s", name);

    printf("Enter your phone number: "); // number
    char phone[20];
    scanf("%s", phone);

    printf("Enter your Aadhar number: "); // aaadhar
    char aadhar[20];
    scanf("%s", aadhar);

    printf("\nCandidates:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s\n", candidates[i].id, candidates[i].name);
    }

    printf("Enter candidate ID to vote for: ");
    int voteID;
    scanf("%d", &voteID);

    if (voteID < 1 || voteID > candidateCount) {
        printf("Invalid candidate ID.\n\n");
        return;
    }

    // Create new voter node
    struct Voter* newVoter = (struct Voter*)malloc(sizeof(struct Voter));
    strcpy(newVoter->name, name);
    strcpy(newVoter->phone, phone);
    strcpy(newVoter->aadhar, aadhar);
    newVoter->next = NULL;

    // Add voter to the linked list of chosen candidate
    struct Candidate* chosen = &candidates[voteID - 1];
    newVoter->next = chosen->voterHead;
    chosen->voterHead = newVoter;
    chosen->voteCount++;

    printf("Thank you for voting!\n\n");
}

// Function to show vote results
void showResults() {
    if (candidateCount == 0) {
        printf("No candidates registered.\n\n");
        return;
    }

    printf("---- Vote Count ----\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%s - %d votes\n", candidates[i].name, candidates[i].voteCount);
    }
    printf("\n");
}

// Function to show voter details per candidate
void showVoters() {
    if (candidateCount == 0) {
        printf("No candidates registered.\n\n");
        return;
    }

    for (int i = 0; i < candidateCount; i++) {
        printf("\nVoters for %s:\n", candidates[i].name);
        struct Voter* current = candidates[i].voterHead;
        if (current == NULL) {
            printf("  No voters yet.\n");
        }
        while (current != NULL) {
            printf("  Name: %s | Phone: %s | Aadhar: %s\n", current->name, current->phone, current->aadhar);
            current = current->next;
        }
    }
    printf("\n");
}

// Function to show all registered candidate details
void showCandidates() {
    if (candidateCount == 0) {
        printf("No candidates registered.\n\n");
        return;
    }

    printf("---- Candidate List ----\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("ID: %d | Name: %s\n", candidates[i].id, candidates[i].name);
    }
    printf("\n");
}

// Main driver function
int main() {
    int choice;

    while (1) {
        printf("===== Simple Voting System =====\n");
        printf("1. Register Candidate\n");
        printf("2. Vote\n");
        printf("3. Show Vote Results\n");
        printf("4. Show Voter Details\n");
        printf("5. Show Candidate List\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerCandidate();
                break;
            case 2:
                vote();
                break;
            case 3:
                showResults();
                break;
            case 4:
                showVoters();
                break;
            case 5:
                showCandidates();
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}
