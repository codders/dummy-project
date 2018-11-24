#include <grpcpp/grpcpp.h>

#include "echo.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using echo::EchoRequest;
using echo::EchoReply;

EchoClient::EchoClient()
    : stub_(Echo::NewStub(grpc::CreateChannel(
                         "localhost:50051", grpc::InsecureChannelCredentials()))) {}

std::string EchoClient::Shout(const std::string& message) {
  // Data we are sending to the server.
  EchoRequest request;
  request.set_message(message);

  // Container for the data we expect from the server.
  EchoReply reply;

  // Context for the client. It could be used to convey extra information to
  // the server and/or tweak certain RPC behaviors.
  ClientContext context;

  // The actual RPC.
  Status status = stub_->Shout(&context, request, &reply);

  // Act upon its status.
  if (status.ok()) {
    return reply.message();
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    return "RPC failed - is echo service running?";
  }
}

