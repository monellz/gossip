#ifndef _CLIENT_
#define _CLIENT_
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterClient {
    std::unique_ptr<Greeter::Stub> stub_;
public:
    GreeterClient(std::shared_ptr<Channel> channel): stub_(Greeter::NewStub(channel)) {}

    void SayHello(const std::string& user, const int& key) {
        HelloRequest request;
        request.set_name(user);
        request.set_key(key);
        std::cout << "[client] request key: " << key << std::endl;

        HelloReply reply;
        ClientContext context;
        Status status = stub_->SayHello(&context,request,&reply);

        if (status.ok()) {
            std::cout << "[client] receice: " << reply.message() << std::endl;
            std::cout << "[client] the value is " << reply.value() << std::endl;
        } else {
            std::cout << "[client] " << status.error_code() << ": " << status.error_message();
        }
    }
};


#endif