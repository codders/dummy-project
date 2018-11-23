#include <grpcpp/grpcpp.h>

#include "ingestion.grpc.pb.h"

#include "ingestion.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using ingestion::Catalog;
using ingestion::Empty;
using ingestion::Ingestion;
using ingestion::Measurement;

using ingestion::Ingestion;

IngestionClient::IngestionClient()
    : stub_(Ingestion::NewStub(grpc::CreateChannel(
                               "localhost:50052", grpc::InsecureChannelCredentials()))) {}

void IngestionClient::GetCatalogs(void) {
  ClientContext context;
  Empty empty;
  std::unique_ptr<ClientReader<Catalog> > reader(
      stub_->GetCatalogs(&context, empty));

  Catalog catalog;
  while (reader->Read(&catalog)) {
    std::cout << "Catalog: "
              << catalog.hrn() << std::endl;
  }

  Status status = reader->Finish();
  // Act upon its status.
  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    std::cout << "RPC failed - is ingestion service running?" << std::endl;
  }
}

void IngestionClient::RecordMeasurement(const std::string& catalogHrn,
                       const std::string& layerId,
                       int value) {
  ClientContext context;
  Empty empty;
  Measurement measurement;
  measurement.set_cataloghrn(catalogHrn);
  measurement.set_layerid(layerId);
  measurement.set_value(value);
  Status status = stub_->RecordMeasurement(&context, measurement, &empty);

  if (!status.ok()) {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    std::cout << "RPC failed - is ingestion service running?" << std::endl;
  }
}

