#include <iostream>
#include <csignal>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iomanip>

using namespace std;

int T_P = 0;
int K_Z[5] = {0, 0, 0, 0, 0};
string KON[5] = {"-", "-", "-", "-", "-"};
string stog = "-";

void update_kon(int sig, bool clear = false) {
    if (clear) {
        KON[sig - 1] = "-";
    } else {
        KON[sig - 1] = to_string(T_P) + ",reg[" + to_string(T_P) + "]";
    }
}

void handle_interrupt(int sig) {
    if (sig >= 1 && sig <= 5) K_Z[sig - 1] = 1;

    if (T_P == 0)
        stog = "reg[0]";
    else
        stog = "reg[" + to_string(T_P) + "]";

    if (sig > T_P) {

        int previous_T_P = T_P;
        string previous_stog = stog;

        update_kon(sig);
        T_P = sig;
        stog = "reg[" + to_string(T_P) + "]";

        cout << endl << "Start handling signal " << sig << endl;
        cout << "Iter.|T_P|   stack   |  K_Z  |" << "|  KON[1]  |  KON[2]  |  KON[3]  |  KON[4]  |  KON[5]  |"
             << endl;
        cout << "         " << T_P << "    " << stog << "    "
             << K_Z[0] << K_Z[1] << K_Z[2] << K_Z[3] << K_Z[4] << "       "
             << KON[0] << "       " << KON[1] << "       " << KON[2] << "       "
             << KON[3] << "       " << KON[4] << "       " << endl;

        stog = "-";
        for (int i = 1; i <= 10; i++) {
            K_Z[sig - 1] = 0;
            cout << "   " << i << "     " << T_P << ",     " << stog << "       "
                 << K_Z[0] << K_Z[1] << K_Z[2] << K_Z[3] << K_Z[4] << "         "
                 << KON[0] << "         " << KON[1] << "         " << KON[2] << "         "
                 << KON[3] << "         " << KON[4] << "         " << endl << endl;
            stog = "-";
            sleep(1);
        }

        T_P = previous_T_P;
        stog = previous_stog;
        update_kon(sig, true);

        cout << "End of handling signal " << sig << endl << endl;
    }
}

void handle_event1(int sig) { handle_interrupt(1); }
void handle_event2(int sig) { handle_interrupt(2); }
void handle_event3(int sig) { handle_interrupt(3); }
void handle_event4(int sig) { handle_interrupt(4); }
void handle_event5(int sig) { handle_interrupt(5); }

int main() {
    struct sigaction act;

    memset(&act, 0, sizeof(act));

    act.sa_handler = handle_event1;
    sigemptyset(&act.sa_mask);
    sigaction(1, &act, NULL);

    act.sa_handler = handle_event2;
    sigemptyset(&act.sa_mask);
    sigaction(2, &act, NULL);

    act.sa_handler = handle_event3;
    sigemptyset(&act.sa_mask);
    sigaction(3, &act, NULL);

    act.sa_handler = handle_event4;
    sigemptyset(&act.sa_mask);
    sigaction(4, &act, NULL);

    act.sa_handler = handle_event5;
    sigemptyset(&act.sa_mask);
    sigaction(5, &act, NULL);

    cout << "Program with PID=" << getpid() << " has started running" << endl;
    cout << "Iter.|T_P|   stack   |  K_Z  |  KON[1]  |  KON[2]  |  KON[3]  |  KON[4]  |  KON[5]  |" << endl;
    int i = 1;
    while (1) {
        if (K_Z[3] == 1) handle_event4(4);
        else if (K_Z[2] == 1) handle_event3(3);
        else if (K_Z[1] == 1) handle_event2(2);
        else if (K_Z[0] == 1) handle_event1(1);
        i++;
        stog = "-";
        cout << "  " << i << "      " << T_P << "      " << stog << "        " << K_Z[0] << K_Z[1] << K_Z[2] << K_Z[3] << K_Z[4]
             << "       " << KON[0] << "          " << KON[1] << "          "
             << KON[2] << "         " << KON[3] << "          " << KON[4] << endl;
        sleep(1);
    }
}
