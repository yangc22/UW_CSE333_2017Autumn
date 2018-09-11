/*
 * Copyright ©2017 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Autumn Quarter 2017 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include "./fileindexutil.h"  // for FileDup().
#include "./HashTableReader.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw3 {

HashTableReader::HashTableReader(FILE *f, IndexFileOffset_t offset)
  : file_(f), offset_(offset) {
  // fread() the bucket list header in this hashtable from its
  // "num_buckets" field, and convert to host byte order.

  // MISSING:
  HWSize_t res = fseek(file_, offset, SEEK_SET);
  Verify333(res == 0);

  res = fread(&header_, sizeof(header_), 1, file_);
  Verify333(res == 1);

  header_.toHostFormat();
}

HashTableReader::~HashTableReader() {
  // fclose our (FILE *).
  fclose(file_);
  file_ = nullptr;
}

HashTableReader::HashTableReader(const HashTableReader &rhs) {
  // This is the copy constructor.

  // Duplicate the offset_, header_ fields.
  offset_ = rhs.offset_;
  header_ = rhs.header_;

  // FileDup() rhs's file_ into our own.
  file_ = FileDup(rhs.file_);
}

HashTableReader &HashTableReader::operator=(const HashTableReader &rhs) {
  // This is the assignment operator.

  if (this != &rhs) {
    // Duplicate the offset_, header_ fields.
    offset_ = rhs.offset_;
    header_ = rhs.header_;

    // Close out our current file_ (if it is open), and then FileDup()
    // rhs's file_ into our own.
    Verify333(file_ != nullptr);
    Verify333(fclose(file_) == 0);
    file_ = FileDup(rhs.file_);
  }

  // Return a reference to self.
  return *this;
}

std::list<IndexFileOffset_t>
HashTableReader::LookupElementPositions(HTKey_t hashKey) {
  // Figure out which bucket the hash value is in.  We assume
  // hash values are mapped to buckets using the modulo (%) operator.
  HWSize_t bucket_num = hashKey % header_.num_buckets;

  // Figure out the offset of the "bucket_rec" field for this bucket.
  IndexFileOffset_t bucketrec_offset =   offset_ 
                                       + sizeof(BucketListHeader)
                                       + sizeof(bucket_rec) * bucket_num;

  // Read the "chain len" and "bucket position" fields from the
  // bucket_rec record, and convert from network to host order.
  bucket_rec b_rec;
  // MISSING:
  Verify333(fseek(file_, bucketrec_offset, SEEK_SET) == 0);
  Verify333(fread(&b_rec, sizeof(b_rec), 1, file_) == 1);
  b_rec.toHostFormat();

  // This will be our returned list of element positions.
  std::list<IndexFileOffset_t> retval;

  // If the bucket is empty, return the empty list.
  if (b_rec.chain_len == 0) {
    return retval;
  }

  // Read the "element positions" fields from the "bucket" header into
  // the returned list.  Be sure to insert into the list in the
  // correct order (i.e., append to the end of the list).
  // MISSING:
  IndexFileOffset_t bucket_offset = b_rec.bucket_position;
  HWSize_t num_ele_chain = b_rec.chain_len;
  element_position_rec ele_pos;

  HWSize_t res = fseek(file_, bucket_offset, SEEK_SET);
  Verify333(res == 0);

  while (num_ele_chain > 0) {
    res = fread(&ele_pos, sizeof(ele_pos), 1, file_);
    Verify333(res == 1);
    ele_pos.toHostFormat();

    // Append the ele-pos to the end of the list.
    retval.push_back(ele_pos.element_position);

    num_ele_chain--;
  }
  // Return the list.
  return retval;
}

}  // namespace hw3
