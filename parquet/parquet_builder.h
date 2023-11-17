#pragma once

#include <stdint.h>

#include <string>
#include <utility>
#include <vector>

#include "db/dbformat.h"
#include "db/seqno_to_time_mapping.h"
#include "db/table_properties_collector.h"
#include "file/writable_file_writer.h"
#include "options/cf_options.h"
#include "rocksdb/options.h"
#include "parquet/parquet_properties.h"

namespace ROCKSDB_NAMESPACE {

class Slice;
class Status;

struct ParquetReaderOptions {
  ParquetReaderOptions(){}
};

struct ParquetBuilderOptions {
  ParquetBuilderOptions(){}
};

// ParquetBuilder provides the interface used to build a Parquet file
class ParquetBuilder {
 public:
  virtual ~ParquetBuilder() {}

  // Add key,value to the parquet file being constructed.
  // REQUIRES: key is after any previously added key according to comparator.
  // REQUIRES: Finish(), Abandon() have not been called
  virtual void Add(const Slice& key, const Slice& value) = 0;

  // Return non-ok iff some error has been detected.
  virtual Status status() const = 0;

  // Return non-ok iff some error happens during IO.
  virtual IOStatus io_status() const = 0;

  // Finish building the parquet file.
  // REQUIRES: Finish(), Abandon() have not been called
  virtual Status Finish() = 0;

  // Indicate that the contents of this builder should be abandoned.
  // If the caller is not going to call Finish(), it must call Abandon()
  // before destroying this builder.
  // REQUIRES: Finish(), Abandon() have not been called
  virtual void Abandon() = 0;

  // Number of calls to Add() so far.
  virtual uint64_t NumEntries() const = 0;

  // Whether the output file is completely empty. 
  virtual bool IsEmpty() const {
    return NumEntries() == 0;
  }

  // Returns table properties
  virtual ParquetProperties GetParquetProperties() const = 0;

  // Return file checksum
  virtual std::string GetFileChecksum() const = 0;

  // Return file checksum function name
  virtual const char* GetFileChecksumFuncName() const = 0;

  // Set the sequence number to time mapping
  virtual void SetSeqnoTimeTableProperties(
      const std::string& /*encoded_seqno_to_time_mapping*/,
      uint64_t /*oldest_ancestor_time*/){};
};

}  // namespace ROCKSDB_NAMESPACE
