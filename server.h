#ifndef _SERVER_
#define _SERVER_
#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>

#include "helloworld.grpc.pb.h"
#include "sender.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

class GreeterServiceImpl final: public Greeter::Service {
public:
    std::string name;

    Sender* sender = nullptr;

    Status SayHello(ServerContext* context, const HelloRequest* request, HelloReply* reply) override {
        std::string prefix("hello ");
        int key = request->key();
        reply->set_message(prefix + request->name() + " from " + name);
        reply->set_value(key);
        std::cout << "[server] get message from " << request->name() << std::endl;

        if (sender->isNewest(key)) {
            std::cout << "[server] update time to " << key << std::endl;
            sender->update(key);
            std::cout << "[server] send to others" << std::endl;
            sender->send();
        } else {
            std::cout << "[server] the time has been updated" << std::endl;
        }
        return Status::OK;
    }
};
#endif