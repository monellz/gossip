#include "node.h"

#include <string>
using namespace std;

int main(int argc, char *argv[]) {

    string user(argv[1]);
    string serverAddr(argv[2]);
    string peerAddr1(argv[3]);
    string peerAddr2(argv[4]);

    Node node(user,serverAddr,peerAddr1,peerAddr2);
    node.Start();

    return 0;
}