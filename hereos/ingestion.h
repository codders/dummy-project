#ifndef ingestion__INCLUDED
#define ingestion__INCLUDED

class IngestionClient {
  public:
    IngestionClient();

    void RecordMeasurement(const std::string& catalogHrn,
                           const std::string& layerId,
                           int value);
};

#endif // ingestion__INCLUDED
