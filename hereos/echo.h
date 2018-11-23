#ifndef echo__INCLUDED
#define echo__INCLUDED

#include "echo.grpc.pb.h"

using echo::Echo;

class EchoClient {
  public:
    EchoClient();

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string Shout(const std::string& message);
  private:
    std::unique_ptr<Echo::Stub> stub_;
};

#endif // echo__INCLUDED
