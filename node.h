#ifndef _NODE_
#define _NODE_
#include "server.h"
#include "client.h"
#include "sender.h"
#include <thread>

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

class Node {
public:
    GreeterServiceImpl service;
    Sender sender;
    std::string serverAddr;

    int time;

    Node(std::string user_, std::string serverAddr_, std::string peerAddr1_, std::string peerAddr2_)
        :sender(user_,peerAddr1_,peerAddr2_) 
    {
        time = 0;
        serverAddr = serverAddr_;
        service.name = user_;
        service.sender = &sender;
    }

    void RunServer() {
        std::string server_address(serverAddr.c_str());
        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<Server> server(builder.BuildAndStart());

        std::cout << "Server listening on " << server_address << std::endl;
        std::cout << "thread id: "  << std::this_thread::get_id() << std::endl;

        server->Wait();
    }

    void Start() {
        //把server放到一个线程中
        //client 循环读取命令参数
        std::thread th(&Node::RunServer,this);
        th.detach();

        //client
        int cnt = 1;
        while (true) {
            std::string cmd;
            std::cin >> cmd;
            std::cout << "cmd cnt: " << cnt << std::endl;
            //向两个服务器发消息

            sender.update(cnt); 
            sender.send();

            cnt++;
        }

    }
};



#endif