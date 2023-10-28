#include <bits/stdc++.h>

#define IN "in.txt"
#define OUT "out.txt"

using namespace std;
ifstream in(IN);
ofstream out(OUT);

int numberOfTournaments;
int numberOfFighters;
int numberOfRounds;
char s[10003];
queue<char> fightersStyles;

char getWinningStyle(char s1, char s2) {
    char winningStyle;
    if (s1 == s2) {
        winningStyle = s1;
    }
    if ((s1 == 'R' and s2 == 'S') or (s2 == 'R' and s1 == 'S')) {
        winningStyle = 'R';
    }
    if ((s1 == 'R' and s2 == 'P') or (s2 == 'R' and s1 == 'P')) {
        winningStyle = 'P';
    }
    if ((s1 == 'S' and s2 == 'P') or (s2 == 'S' and s1 == 'P')) {
        winningStyle = 'S';
    }
    return winningStyle;
}

void problem1() {
    in >> numberOfTournaments;
    in.getline(s, 10);//read empty line
    for (int i = 1; i <= numberOfTournaments; i++) {
        in.getline(s, 10);
        char s1 = s[0];
        char s2 = s[1];
        if (s1 == s2) {
            out << s1;
        }
        if ((s1 == 'R' and s2 == 'S') or (s2 == 'R' and s1 == 'S')) {
            out << 'R';
        }
        if ((s1 == 'R' and s2 == 'P') or (s2 == 'R' and s1 == 'P')) {
            out << "P";
        }
        if ((s1 == 'S' and s2 == 'P') or (s2 == 'S' and s1 == 'P')) {
            out << 'S';
        }
        out << '\n';
    }
}

void problem2() {
    in >> numberOfTournaments >> numberOfFighters;
    in.getline(s, 100);
    for (int i = 1; i <= numberOfTournaments; i++) {
        in.getline(s, 10003);
        for (int j = 0; j < numberOfFighters; j = j + 2) {
            char winningStyle = getWinningStyle(s[j], s[j + 1]);
            fightersStyles.push(winningStyle);
        }
        while (!fightersStyles.empty()) {
            char style1 = fightersStyles.front();
            fightersStyles.pop();
            char style2 = fightersStyles.front();
            char winningStyle = getWinningStyle(style1, style2);
            fightersStyles.pop();
            out << winningStyle;
        }
        out << "\n";
    }
}

int numberOfRocks, numberOfScissors, numberOfPaper;

string getWinningStylePairForGivenStyleForScissors(int *sCount, char style, int *pCount) {
    if (style == 'S') {
        if (*pCount + 1 <= numberOfPaper) {
            (*pCount) = (*pCount) + 1;
            return "SP";
        }
        if (*sCount + 1 <= numberOfScissors) {
            (*sCount) = (*sCount) + 1;
            return "SS";
        }
    }
    return "";
}

string getWinningStylePairForGivenStyleForPaper(int *rCount, char style, int *pCount) {
    if (style == 'P') {
        if (*rCount + 1 <= numberOfRocks) {
            (*rCount) = (*rCount) + 1;
            return "PR";
        }
        if (*pCount + 1 <= numberOfPaper) {
            (*pCount) = (*pCount) + 1;
            return "PP";
        }
    }
    return "";
}

string getWinningStylePairForGivenStyleForRock(int *rCount, char style, int *sCount) {
    if (style == 'R') {
        if (*rCount + 1 <= numberOfRocks) {
            (*rCount) = (*rCount) + 1;
            return "RR";
        }
        if (*sCount + 1 <= numberOfScissors) {
            (*sCount) = (*sCount) + 1;
            return "SR";
        }
    }
    return "";
}

void doesNotWorkForPr3ToBuildFightersFromPairs(int &sCount, int &rCount, int &pCount, const string &secondRound) {
    unsigned long long lengthSecondRound = secondRound.size();
    string firstRound;
    for (unsigned long long i = 0; i < lengthSecondRound; i++) {
        char style = secondRound[i];
        string auxString = getWinningStylePairForGivenStyleForScissors(&sCount, style, &pCount);
        firstRound.append(auxString);
        auxString = getWinningStylePairForGivenStyleForPaper(&rCount, style, &pCount);
        firstRound.append(auxString);
    }
    unsigned long long lengthFirstRound = firstRound.size();
    string initialFighters;
    int pRest = 0, rRest = 0, sRest = 0;
    for (int i = 0; i < lengthFirstRound; i++) {
        char style = firstRound[i];
        string auxString;
        auxString = getWinningStylePairForGivenStyleForPaper(&rCount, style, &pCount);
        if (auxString == "" and style == 'P') pRest++;
        initialFighters.append(auxString);
        auxString = getWinningStylePairForGivenStyleForScissors(&sCount, style, &pCount);
        if (auxString == "" and style == 'S') sRest++;
        initialFighters.append(auxString);
        auxString = getWinningStylePairForGivenStyleForRock(&rCount, style, &sCount);
        if (auxString == "" and style == 'R') rRest++;
        initialFighters.append(auxString);
    }
    while (sRest > 0) {
        initialFighters.append("S");
        sRest--;
    }
    while (pRest > 0) {
        initialFighters.append("P");
        pRest--;
    }
    if (initialFighters.length() != numberOfFighters) {
        while (sCount < numberOfScissors or pCount < numberOfPaper or rCount < numberOfRocks) {
            if (rCount < numberOfRocks) {
                initialFighters.append("R");
                rCount++;
            }
            if (pCount < numberOfPaper) {
                initialFighters.append("P");
                pCount++;
            }
            if (sCount < numberOfScissors) {
                initialFighters.append("S");
                sCount++;
            }
        }
    }
    out << initialFighters << "\n";
}

int main() {
    in >> numberOfTournaments >> numberOfFighters;
    int auxInt = numberOfFighters;
    while (auxInt > 1) {
        auxInt /= 2;
        numberOfRounds++;
    }
    for (int tournament = 1; tournament <= numberOfTournaments; tournament++) {
        char auxChar;
        in >> numberOfRocks >> auxChar;
        in >> numberOfPaper >> auxChar;
        in >> numberOfScissors >> auxChar;
        int numberOfFightersForSemifinals = numberOfFighters / 2;
        string sol = "P";
        numberOfPaper--;
        for (int i = 2; i <= numberOfFightersForSemifinals; i++) {
            if (numberOfRocks > 0) {
                sol.append("R");
                numberOfRocks--;
            } else {
                if (numberOfPaper > 0) {
                    sol.append("P");
                    numberOfPaper--;
                } else {
                    if (numberOfScissors > 1) {
                        sol.append("S");
                        numberOfScissors--;
                    }
                }
            }
        }
        int auxInt = 1;
        if (numberOfPaper > 0) {
            sol.append("P");
            numberOfPaper--;
            auxInt = 2;
        }
        for (int i = auxInt; i <= numberOfFightersForSemifinals; i++) {
            if (i == numberOfFightersForSemifinals / 2 + 1) {
                if (numberOfPaper > 0) {
                    numberOfPaper--;
                    sol.append("P");
                    continue;
                }
            }
            if (i == numberOfFightersForSemifinals / 4 * 3 + 1) {
                if (numberOfPaper > 0) {
                    numberOfPaper--;
                    sol.append("P");
                    continue;
                }
            }

            if (i == numberOfFightersForSemifinals / 8 * 7 + 1) {
                if (numberOfPaper > 0) {
                    numberOfPaper--;
                    sol.append("P");
                    continue;
                }
            }

            if (i == numberOfFightersForSemifinals / 16 * 15 + 1) {
                if (numberOfPaper > 0) {
                    numberOfPaper--;
                    sol.append("P");
                    continue;
                }
            }

            if (i == numberOfFightersForSemifinals / 32 * 31 + 1) {
                if (numberOfPaper > 0) {
                    numberOfPaper--;
                    sol.append("P");
                    continue;
                }
            }
            if (numberOfRocks > 0) {
                sol.append("R");
                numberOfRocks--;
                if (numberOfRocks < numberOfPaper) {
                    if (numberOfPaper > 0) {
                        sol.append("P");
                        numberOfPaper--;
                        i++;
                    }
                }
            } else {
                if (numberOfPaper > 0) {
                    sol.append("P");
                    numberOfPaper--;
                } else {
                    if (numberOfScissors > 0) {
                        sol.append("S");
                        numberOfScissors--;
                    }
                }
            }
        }
        out << sol << "\n";
    }
    return 0;
}
