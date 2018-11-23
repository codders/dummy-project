#ifndef echo__INCLUDED
#define echo__INCLUDED

class EchoClient {
  public:
    EchoClient();

    std::string Shout(const std::string& message);
};

#endif // echo__INCLUDED
