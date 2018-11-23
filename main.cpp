#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <unistd.h>

#include "hereos/echo.h"
#include "hereos/ingestion.h"

int main(int argc, char **argv)
{
  EchoClient *echo = new EchoClient();
  IngestionClient *ingestion = new IngestionClient();

  while (true) {
    int measurement = rand() % 100;

    std::string reply = echo->Shout(std::to_string(measurement));
    std::cout << "Echo Client received: " << reply << std::endl;

    std::cout << "Recording measurement: " << measurement << std::endl;
    ingestion->RecordMeasurement("hrn:here:data:::arthur-hereos-test-20181121",
                                 "test-data-20181121",
                                 measurement);
    usleep(1000000);
  }
  return 0;
}
