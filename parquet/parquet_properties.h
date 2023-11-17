#pragma once

#include <stdint.h>

#include <map>
#include <memory>
#include <string>

#include "rocksdb/customizable.h"
#include "rocksdb/status.h"
#include "rocksdb/types.h"

namespace ROCKSDB_NAMESPACE {

// ParquetProperties contains a bunch of read-only properties
struct ParquetProperties {
 public:

  // convert this object to a human readable form
  //   @prop_delim: delimiter for each property.
  std::string ToString(const std::string& prop_delim = "; ",
                       const std::string& kv_delim = "=") const;

  // Aggregate the numerical member variables of the specified
  // TableProperties.
  void Add(const ParquetProperties& tp);

  // Subset of properties that make sense when added together
  // between tables. Keys match field names in this class instead
  // of using full property names.
  std::map<std::string, uint64_t> GetAggregatablePropertiesAsMap() const;

  // Return the approximated memory usage of this TableProperties object,
  // including memory used by the string properties and UserCollectedProperties
  std::size_t ApproximateMemoryUsage() const;
};

} // namespace ROCKSDB_NAMESPACE