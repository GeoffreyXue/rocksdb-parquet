
#include "parquet/compaction_parquet_outputs.h"

#include "db/builder.h"

namespace ROCKSDB_NAMESPACE {

IOStatus CompactionParquetOutputs::WriterSyncClose(const Status& input_status, bool use_fsync) {
  IOStatus io_s;
  if (input_status.ok()) {
    io_s = file_writer_->Sync(use_fsync);
  }
  if (input_status.ok() && io_s.ok()) {
    io_s = file_writer_->Close();
  }

  if (input_status.ok() && io_s.ok()) {
    // Write metadata
  }

  file_writer_.reset();

  return io_s;
}

}  // namespace ROCKSDB_NAMESPACE
