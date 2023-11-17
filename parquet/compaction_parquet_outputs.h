#pragma once

#include "db/blob/blob_garbage_meter.h"
#include "db/compaction/compaction.h"
#include "db/compaction/compaction_iterator.h"
#include "db/internal_stats.h"
#include "db/output_validator.h"

namespace ROCKSDB_NAMESPACE {

// Parquet files produced by subcompaction in parallel to SSTable files. 
// Used in parallel to compaction_outputs
// V1: Output writer syncs and closes the file
class CompactionParquetOutputs {
 public:
  CompactionParquetOutputs() = delete;

  explicit CompactionParquetOutputs();

  // Assign a new WritableFileWriter to the current output
  void AssignFileWriter(WritableFileWriter* writer) {
    file_writer_.reset(writer);
  }

  IOStatus WriterSyncClose(const Status& input_status, bool use_fsync);

 private:
  // writer
  std::unique_ptr<WritableFileWriter> file_writer_;
};

}  // namespace ROCKSDB_NAMESPACE
