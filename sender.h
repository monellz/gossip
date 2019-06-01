#ifndef _SENDER_
#define _SENDER_
#include <string>
#include "client.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;
class Sender {
public:
    int time;
    std::string peerAddr1;
    std::string peerAddr2;
    std::string name;

    Sender(std::string n,std::string p1,std::string p2):time(0) {
        name = n;
        peerAddr1 = p1;
        peerAddr2 = p2;
    }

    void send() {
        GreeterClient greeter1(grpc::CreateChannel(peerAddr1.c_str(),grpc::InsecureChannelCredentials()));
        
        greeter1.SayHello(name,time);

        GreeterClient greeter2(grpc::CreateChannel(peerAddr2.c_str(),grpc::InsecureChannelCredentials()));

        greeter2.SayHello(name,time);
    }

    bool isNewest(int newTime) {
        return newTime > time;
    }

    void update(int newTime) {
        time = newTime;
    }
};



#endif