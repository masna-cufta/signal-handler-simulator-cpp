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

void azuriraj_kon(int sig, bool clear = false) {
    if(clear) {
        KON[sig-1] = "-";
    } else {
        KON[sig-1] = to_string(T_P) + ",reg[" + to_string(T_P) + "]";
    }
}

void obradi_prekid(int sig) {
    if (sig >= 1 && sig <= 5) K_Z[sig-1] = 1;

    if(T_P == 0)
        stog = "reg[0]";
    else
        stog = "reg[" + to_string(T_P) + "]";

    if (sig > T_P) {

        int prethodni_T_P = T_P;
        string prethodni_stog = stog;

        azuriraj_kon(sig);
        T_P = sig;
        stog = "reg[" + to_string(T_P) + "]";

        cout << endl << "Početak obrade signala " << sig << endl;
        cout << "Br. it.|T_P|   stog   |  K_Z  |"<< "|  KON[1]  |  KON[2]  |  KON[3]  |  KON[4]  |  KON[5]  |"
        <<endl;
        cout << "         " << T_P << "    " << stog << "    "
                << K_Z[0] << K_Z[1] << K_Z[2] << K_Z[3] << K_Z[4]<<"       "
       << KON[0]<<"       "<<KON[1]<<"       "<<KON[2]<<"       "
       <<KON[3]<<"       "<<KON[4]<<"       "<< endl;

        stog = "-";
        for(int i = 1; i <= 10; i++) {
            K_Z[sig - 1] = 0;
            cout <<"   "<< i<<"     " << T_P << ",     " << stog << "       "
                    << K_Z[0] << K_Z[1] << K_Z[2] << K_Z[3] << K_Z[4]<<"         "
            << KON[0]<<"         "<<KON[1]<<"         "<<KON[2]<<"         "
            <<KON[3]<<"         "<<KON[4]<<"         "<< endl<<endl;
            stog ="-";
            sleep(1);
        }

        T_P = prethodni_T_P;
        stog = prethodni_stog;
        azuriraj_kon(sig, true);

        cout << "Kraj obrade signala " << sig << endl << endl;
    }
}

void obradi_dogadjaj1(int sig) { obradi_prekid(1); }
void obradi_dogadjaj2(int sig) { obradi_prekid(2); }
void obradi_dogadjaj3(int sig) { obradi_prekid(3); }
void obradi_dogadjaj4(int sig) { obradi_prekid(4); }
void obradi_dogadjaj5(int sig) { obradi_prekid(5); }

int main() {
    struct sigaction act;

    memset(&act, 0, sizeof(act));

    act.sa_handler = obradi_dogadjaj1;
    sigemptyset(&act.sa_mask);
    sigaction(1, &act, NULL);

    act.sa_handler = obradi_dogadjaj2;
    sigemptyset(&act.sa_mask);
    sigaction(2, &act, NULL);

    act.sa_handler = obradi_dogadjaj3;
    sigemptyset(&act.sa_mask);
    sigaction(3, &act, NULL);

    act.sa_handler = obradi_dogadjaj4;
    sigemptyset(&act.sa_mask);
    sigaction(4, &act, NULL);

    act.sa_handler = obradi_dogadjaj5;
    sigemptyset(&act.sa_mask);
    sigaction(5, &act, NULL);

    cout << "Program s PID=" << getpid() << " je krenuo sa radom" << endl;
    cout << "Br. it.|T_P|   stog   |  K_Z  |  KON[1]  |  KON[2]  |  KON[3]  |  KON[4]  |  KON[5]  |" << endl;
    int i = 1;
    while (1) {
        if (K_Z[3] == 1) obradi_dogadjaj4(4);
        else if (K_Z[2] == 1) obradi_dogadjaj3(3);
        else if (K_Z[1] == 1) obradi_dogadjaj2(2);
        else if (K_Z[0] == 1) obradi_dogadjaj1(1);
        i++;
        stog="-";
        cout<<"  " << i<<"      " << T_P << "      " << stog << "        " << K_Z[0] << K_Z[1] << K_Z[2] << K_Z[3] << K_Z[4]

        << "       "<< KON[0] << "          " << KON[1] << "          "
        << KON[2] << "         " << KON[3] << "          " << KON[4] << endl;
        sleep(1);
    }
}