server: server.cc
	g++ server.cc helloworld.grpc.pb.cc helloworld.pb.cc -L/usr/local/lin `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -pthread -o server
client: client.cc
	g++ client.cc server.h client.h helloworld.grpc.pb.cc helloworld.pb.cc -L/usr/local/lin `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -pthread -o client 

protoc: helloworld.proto
	protoc --grpc_out=./ --plugin=protoc-gen-grpc=./grpc_cpp_plugin  helloworld.proto
	protoc --cpp_out=./ helloworld.proto