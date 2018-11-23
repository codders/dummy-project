#ifndef ingestion__INCLUDED
#define ingestion__INCLUDED

#include "ingestion.grpc.pb.h"

using ingestion::Ingestion;

class IngestionClient {
  public:
    IngestionClient();

    void RecordMeasurement(const std::string& catalogHrn,
                           const std::string& layerId,
                           int value);
  private:
    void GetCatalogs();
    std::unique_ptr<Ingestion::Stub> stub_;
};

#endif // ingestion__INCLUDED
